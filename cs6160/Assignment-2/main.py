# Vishal Vijay Devadiga
# CS21BTECH11061
# CS6160: Assignment-2

import random
import os
import math

# Question:
# Consider an RC4 scheme with a word size of $n = 5$, where the internal state consists of a table 𝑆 containing $2^n = 32$ words. 
# We use a fixed-size key 𝐾 which is 5 bytes long. 
# In this assignment, you will be provided with $2^{24}$ distinct ciphertexts, all generated from the same plaintext using $2^{24}$ different random keys, each 5 bytes in size, based on the RC4 scheme described above. 
# The plaintext consists of a 6-digit passcode containing digits ranging from 0 to 9.
# In this assignment, your task is to examine the vulnerabilities of the RC4 scheme and exploit them, using the provided list of ciphertexts, to retrieve the encrypted passcode.

# Constants
n = 5
NumKeys = 2**24
NumFiles = 2**12
data_folder = "Ciphertexts/"

# Number of samples to generate the keystream distribution
# Any value above 2**20 is good enough 
output_keystream_distribution = 2**24

# All algorithms are based on the pseudocode in the PDF

def KeyScheduleAlgorithm(K):
    S = [0] * 2**(n)
    mod = 2**n
    for i in range(mod):
        S[i] = i
    j = 0
    l = len(K)
    for i in range(mod):
        j = (j + S[i] + K[i % l]) % mod
        S[i], S[j] = S[j], S[i]
    return S

def PseudoRandomGenerationAlgorithm(S, m):
    i = 0
    j = 0
    KeyStream = []
    mod = 2**n
    for k in range(m):
        i = (i + 1) % mod
        j = (j + S[i]) % mod
        S[i], S[j] = S[j], S[i]
        KeyStream.append(S[(S[i] + S[j]) % mod])
    return KeyStream

def CipherTextGeneration(passcode):
    m = len(passcode)
    ciphertexts = []
    for i in range(NumKeys):
        K = [random.randint(0, 255) for i in range(5)]
        S = KeyScheduleAlgorithm(K)
        KeyStream = PseudoRandomGenerationAlgorithm(S, m)
        ciphertexts.append([passcode[i] ^ KeyStream[i] for i in range(m)])

# Load data

# Folder structure
# CipherTexts/ciphertexts_x.txt where each line is a ciphertext with [c0, c1, c2, c3, c4, c5] in a line and has 4096 lines

if not os.path.exists(data_folder):
    exit("Data folder does not exist")

ciphertexts = []
for i in range(NumFiles):
    file_name = data_folder + "ciphertexts_" + str(i+1) + ".txt"
    with open(file_name, "r") as f:
        s = f.readlines()
        # Remove newline characters
        s = [x.strip() for x in s]
        # Remove brackets
        s = [x[1:-1] for x in s]
        # Split by comma and space
        s = [x.split(", ") for x in s]
        # Convert to integers
        s = [[int(x) for x in y] for y in s]
        ciphertexts.extend(s)
print("Data loaded")

# Check data
# print(len(ciphertexts))
# print(ciphertexts[0])
# print(ciphertexts[-2])

# Stats

# Find the number of times each number appear in each position
# Numbers are from 0 to 255

stats = [[0] * 256 for _ in range(6)]

for c in ciphertexts:
    for i in range(6):
        stats[i][c[i]] += 1

print("Stats calculated")

# Find the keystream distribution

def get_biases(sample_size):
    # Biases of each key byte for each position
    key_biases = [[0] * 32 for _ in range(6)]

    # Generate random keys and find the distribution of the keystream
    for i in range(sample_size):
        key = [random.randint(0, 255) for i in range(5)]
        S = KeyScheduleAlgorithm(key)
        keyStream = PseudoRandomGenerationAlgorithm(S, 6)

        for i in range(6):
            key_biases[i][keyStream[i]] += 1
        
    # Normalize the biases
    key_biases = [[x / sample_size for x in y] for y in key_biases]
    return key_biases

# Keystream Distribution: Single Byte Bias

prob_key_biases = get_biases(output_keystream_distribution)
print("Probabilities calculated")

# Check the biases
# for i in range(6):
#     print(prob_key_biases[i])
#     print(len(prob_key_biases[i]))

ans = [0]*6

# Find the most probable passcode
for i in range(6):
    l_u = [0] * 10
    for u in range(10):
        for k in range(32):
            l_u[u] += math.log(prob_key_biases[i][k]) * stats[i][k ^ (u+48)]  
    # print(l_u)
    # Print the index of the maximum value
    ans[i] = l_u.index(max(l_u))

# Print the passcode
print("The passcode is: ", ans)

# Testing the variablity in obtaining the passcode
# for g in range (8, 26, 2):
#     for re in range(5):
#         prob_key_biases = get_biases(2**g)
#         ans = [0]*6
#         for i in range(6):
#             l_u = [0] * 10
#             for u in range(10):
#                 for k in range(32):
#                     l_u[u] += math.log(prob_key_biases[i][k]) * stats[i][k ^ (u+48)]  
#             ans[i] = l_u.index(max(l_u))
#         print(g,ans)