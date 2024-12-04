---
title: CS6160 Assignment-3
author:
  - Vishal Vijay Devadiga (CS21BTECH11061)
geometry: margin=1cm
documentclass: extarticle
fontsize: 10pt
header-includes:
  - \usepackage{setspace}
  - \onehalfspacing
---

# Running the code

The code for the assignment is written in Python.
Directory structure should be as follows:

```
AES-128/
|___ Prog_Asgn_3_1_cs21btech11061.py
|___ aesCiphertexts.txt
|___ aesPlaintexts.txt
2-Key AES-128/
|___ Prog_Asgn_3_2_cs21btech11061.py
|___ 2aesCiphertexts.txt
|___ 2aesPlaintexts.txt
```

**As in the cipher text and plain text files must reside in the same directory as the code.**

To run the code, just install the cryptography library using pip and run the code using Python.

# Answers

## Question 1

Simply brute-forced the key by trying all possible keys from 0 to $2^{24} - 1$ and checking if the encrypted message matches the given cipher text.

- Key: `9331504` in decimal, `0x8E6330` in hex
- Secret Message: `mediumaquamarine`


## Question 2:

Took the encryption of the given plain text using all possible keys from 0 to $2^{16} - 1$ and stored it in a dictionary. Then, took the decryption of the given cipher text using all possible keys from 0 to $2^{16} - 1$ and checked if the decrypted message is present in the dictionary. If it is present, then the key is found.

- Key-1: `45791` in decimal, `0xB2DF` in hex
- Key-2: `5827` in decimal, `0x16C3` in hex
- Secret Message: paddlingcanoeist
