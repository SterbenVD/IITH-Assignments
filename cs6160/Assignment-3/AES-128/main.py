'''
In the first part, the goal is to find a 20-bit key by a brute-force attack. 
Since AES uses a 128-bit key, a 24-bit key is fed into an expansion subroutine that produces a 128-bit long key. 
The subroutine ignores the last 4-bits of the short key so that the effective key length is 20.
The key expansion subroutine is given to you as C and Python files.

A set of four plaintexts and five ciphertexts are given to you as two text files, with the ciphertexts corresponding to the four given plaintexts and one secret plaintext. 
Use one of the plaintext-ciphertext pairs to find the key and hence find the secret plaintext as well.
'''

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

# IV(Initialization vector) for AES is a zero vector
iv=b'\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0'

# Files
aesPlain = "aesPlaintexts.txt"
aesCipher = "aesCiphertexts.txt"
aesSecret = "aesSecretMessage.txt"


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
    
def AESexpandKey(shortKey):    
    shortKeyval1=shortKey[0]
    shortKeyval2=shortKey[1]
    #Last four bits are ignored
    shortKeyval3=shortKey[2]&0xF0
    
    ByteA=shortKeyval1.to_bytes(1,"big")
    ByteB=shortKeyval2.to_bytes(1,"big")
    ByteC=shortKeyval3.to_bytes(1,"big")
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

# Break the AES encryption using brute force attack

def checkKey(plaintext,ciphertext,key):
    key = key.to_bytes(3,"big")
    cipher = Cipher(algorithms.AES(AESexpandKey(key)), modes.CBC(iv))
    message_bytes=plaintext.encode('UTF-8')
    encryptor = cipher.encryptor()
    cipher = encryptor.update(message_bytes) + encryptor.finalize()
    if cipher.hex()==ciphertext:
        return True
    return False

def breakAES(plaintext,ciphertext):
    for i in range(2**24-1, -1, -1):
        if checkKey(plaintext,ciphertext,i):
            return i
    return -1

def decryptMessage(secretcipher,key):
    key = key.to_bytes(3,"big")
    cipher = Cipher(algorithms.AES(AESexpandKey(key)), modes.CBC(iv))
    secretcipher=bytes.fromhex(secretcipher)
    decryptor = cipher.decryptor()
    plain=decryptor.update(secretcipher) + decryptor.finalize()
    return plain

def main():
    plain, cipher=import_data()
    print(plain[0],cipher[0])
    key=breakAES(plain[0],cipher[0])
    print("Key is: ",key)
    for i in range(1,4):
        print (plain[i],cipher[i])
        if not checkKey(plain[i],cipher[i],key):
            print("Key is incorrect")
            return
    print("Key is consistent")
    # Decrypt the secret message
    secret=decryptMessage(cipher[4],key)
    secret=secret.decode("utf-8")
    print("Secret message is: ",secret)
    # Output to file secret message
    with open(aesSecret,"w") as file:
        file.write(secret)    

if __name__=="__main__":
    main()