
'''
In the second part, we do a meet-in-the-middle attack. Here the encryption is done using two 16-bit keys. 
Firstly, each key is expanded via a key expansion routine (given to you) to obtain two long (128-bit) keys. 
Then the message is encrypted with the first long key, and then again with the second long key, to obtain the ciphertext. 
Each AES operation is treated as a black box, but the two-key AES structure as a whole is not a black box, which means you can get the intermediate encryption and hence it allows for the meet-in-the-middle approach. 
A set of four plaintexts and five ciphertexts is given as input and the goal is the same as in part 1.
'''

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

# IV(Initialization vector) for 2-key AES is a zero vector
iv=b'\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0'

# Files
aesPlain = "2aesPlaintexts.txt"
aesCipher = "2aesCiphertexts.txt"
aesSecret = "2aesSecretMessage.txt"

def import_data():
    plaintexts=[]
    ciphertexts=[]
    with open(aesPlain,"r") as file:
        for line in file:
            if line[-1]=="\n":
                plaintexts.append(line[:-1])
            else:
                plaintexts.append(line)
    with open(aesCipher,"r") as file:
        for line in file:
            if line[-1]=="\n":
                ciphertexts.append(line[:-1])
            else:
                ciphertexts.append(line)
    return plaintexts,ciphertexts

def AES2KeyexpandKey(shortKey):    
    shortKeyval1=shortKey[0]
    shortKeyval2=shortKey[1]    
    
    ByteA=shortKeyval1.to_bytes(1,"big")
    ByteB=shortKeyval2.to_bytes(1,"big")
    ByteC=(shortKeyval1^shortKeyval2).to_bytes(1,"big")
    hexByte1=0x94
    Byte1=hexByte1.to_bytes(1,"big")
    hexByte2=0x5a
    Byte2=hexByte2.to_bytes(1,"big")
    hexByte3=0xe7
    Byte3=hexByte3.to_bytes(1,"big")
    
    longKey=bytearray(ByteA)    
    longKey.extend(Byte1)
    longKey.extend(ByteB)    
    longKey.extend(Byte2)
    
    for i in range(4,9):        
        hexByte=(longKey[i-1]+longKey[i-4])%257
        if (hexByte==256):
            hexByte=0
        Byte=hexByte.to_bytes(1,"big")              
        longKey.extend(Byte)
    longKey.extend(ByteC)
    longKey.extend(Byte3)
    for i in range(11,16):
        hexByte=(longKey[i-1]+longKey[i-4])%257
        if (hexByte==256):
            hexByte=0
        Byte=hexByte.to_bytes(1,"big")              
        longKey.extend(Byte)    
    
    return longKey

def aesEncrypt(plaintext_bytes, key):
    key = key.to_bytes(2, "big")
    longKey = AES2KeyexpandKey(key)
    cipher = Cipher(algorithms.AES(longKey), modes.CBC(iv))
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(plaintext_bytes) + encryptor.finalize()
    return ciphertext

def aesDecrypt(ciphertext_bytes, key):
    key = key.to_bytes(2, "big")
    longKey = AES2KeyexpandKey(key)
    cipher = Cipher(algorithms.AES(longKey), modes.CBC(iv))
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(ciphertext_bytes) + decryptor.finalize()
    return plaintext

# Use 2 keys, 1st to encrypt plaintext and 2nd to decrypt the final ciphertext 

def intermediate_encrypt_decrypt(plaintext, ciphertext):
    # Hash table to store intermediate ciphertexts
    inter_ciphertext = {}
    plaintext_bytes = plaintext.encode('UTF-8')
    for i in range(0, 2**16):
        inter_ciphertext[aesEncrypt(plaintext_bytes, i).hex()] = i
    ciphertext_bytes = bytes.fromhex(ciphertext)
    for i in range(0, 2**16):
        plain = aesDecrypt(ciphertext_bytes, i).hex()
        if plain in inter_ciphertext:
            return inter_ciphertext[plain], i
    return -1    

def main():
    plain, cipher = import_data()
    print(plain[0], cipher[0])
    key1, key2 = intermediate_encrypt_decrypt(plain[0], cipher[0])
    print("Keys are: ", key1, key2)
    for i in range(1, 4):
        print(plain[i], cipher[i])
        aesEn = aesEncrypt(plain[i].encode('UTF-8'), key1)
        aesEn2 = aesEncrypt(aesEn, key2)
        # print(aesEn2.hex())
        # print(cipher[i])
        if aesEn2.hex() != cipher[i]:
            print("Keys are inconsistent")
            return
    print("Keys are consistent")
    # Decrypt the secret message
    secret = aesDecrypt(bytes.fromhex(cipher[4]), key2).hex()
    secret = aesDecrypt(bytes.fromhex(secret), key1).decode('UTF-8')
    print("Secret message is: ", secret)
    # Output to file secret message
    with open(aesSecret, "w") as file:
        file.write(secret)
    
if __name__=="__main__":
    main()