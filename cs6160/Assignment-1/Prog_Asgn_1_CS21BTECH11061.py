# Vishal Vijay Devadiga
# CS21BTECH11061
# Programming assignment-1

import os

# Set 1 Stream Ciphertexts
input_name = "Set1_streamciphertexts.txt"

# Output file
output_name = "Prog_Asgn_1_CS21BTECH11061.txt"

# Dictionary
diction = "dictionary.txt"

# Read cipherfile
with open(input_name, 'r') as f:
    messages = [line.strip() for line in f.readlines()]

# for i in range(len(messages)):
#     print(f"Message {i+1} Size:", len(messages[i]))
#     print(messages[i])

# Convert to appropriate format: bytes.
# Char are 0 to 255.
for i in range(len(messages)):
    # Convert to bytes
    # print(messages[i])
    decode = []
    for j in range(0, len(messages[i]), 2):
        byte = messages[i][j:j+2]
        # print(byte, end=": ")
        ch = int(byte, 16)
        # print(ch, end=": ")
        # print(chr(ch))
        decode.append(ch)
        # decode += chr(ch)
    # print()
    # print(f"Decoded {i+1}:")
    # print(decode)
    messages[i] = decode
    
# Key length is the maximum length of the messages
key_length = max([len(x) for x in messages])
key = [-1] * key_length

# Read dictionary
# There are 128 words in the dictionary, 16384 combinations
# So storing just words in a list  
dictonary = []
words = []
with open(diction, 'r') as f:
    words = [line.strip() for line in f.readlines()]

# print(len(words))

for word in words:
    x = word.split(' ')
    # print(x)
    for i in x:
        # print(i)
        if i not in dictonary:
            dictonary.append(i)

# print("Dictionary Size:", len(dictonary))
# print(dictonary)

# For Key-1

# Logic is to guess one word from a message
# Then check whether other plain text words are in the dictionary
# If not, then the guess is wrong
# Fortunately, only 1 guess is the correct one

# First 7 chars

for i in dictonary:
    plain = i
    key_7 = [0]*7
    t = 1
    for j in range(7):
        key_7[j] = ord(plain[j]) ^ messages[0][j]
    for j in messages:
        plain = [j[r] ^ key_7[r] for r in range(7)]
        plain = ''.join([chr(x) for x in plain])
        if plain not in dictonary:
            t = 0
            break
    if t:
        key[:7] = key_7
        break

# Next 7 chars

for i in dictonary:
    plain = i
    key_7 = [0]*7
    t = 1
    for j in range(7):
        key_7[j] = ord(plain[j]) ^ messages[0][j+8]
    for j in messages:
        plain = [j[r+8] ^ key_7[r] for r in range(7)]
        plain = ''.join([chr(x) for x in plain])
        if plain not in dictonary:
            t = 0
            break
    if t:
        key[8:15] = key_7
        break
    
# Space

key[7] = ord(' ') ^ messages[0][7]
key[15] = ord(' ') ^ messages[0][15]

# For key-2, since the messages are in english, the last char is '.' in all messages

for i in messages:
    length = len(i)
    key[length-1] = ord('.') ^ i[length-1]

# Idea is go column by column. Guess Spaces in the column then set key for that column
# Spaces will be the most common of all punctuations
# So punctuations lie in 0 - 63 range while letters lie in 64-127 range
# If the key is XOR with plaintext, the second last bit(2^6) will differ in letters and punctuation

for i in range(16,len(key)):
    ch_arr = []
    t = 1
    for j in range(len(messages)):
        # If '.' is reached, then should not guess as we already know
        if i == (len(messages[j])-1):
            t = 0
            break
        if i >= len(messages[j]):
            continue
        ch_arr.append(messages[j][i])
    
    if t == 0:
        continue    
    
    last_bit = ch_arr[0]//128
    # print(last_bit)
    ch_arr = [ch_arr[j]%128 for j in range(len(ch_arr))]
    # print(ch_arr)
    
    # Divide into 2 groups, based on second-last bit
    g1 = []
    g0 = []
    for j in ch_arr:
        if j//64 == 1:
            g1.append(j)
        else:
            g0.append(j)
    
    # print(g1)
    # print(g0)
    # if len(g1) == 6:
    #     print(i)
    #     print(g1, g0)
    
    # if len(g1) > len(g0):
    #     print(g1)
    # elif len(g0) > len(g1):
    #     print(g0)
    # else:
    #     print(g0, g1)
    
    # If one of the groups is empty, then we can't guess
    if len(g1) == 0 or len(g0) == 0:
        continue
    
    # For all columns, the lowest has the spaces in the same group(expect for columns where it is in groups with equal elements)
    if len(g1) > len(g0):
        key[i] = ord(' ') ^ g0[0]
    elif len(g0) > len(g1):
        key[i] = ord(' ') ^ g1[0]
    else:
        # Find the number of distinct elements in the group.
        # Normally lot less distinct punctuations than letters
        distinct_g0 = len(set(g0))
        distinct_g1 = len(set(g1))
        if distinct_g0 > distinct_g1:
            key[i] = ord(' ') ^ g1[0]
        elif distinct_g1 > distinct_g0:
            key[i] = ord(' ') ^ g0[0]
        else:
            # Not enough information to guess
            continue  
    if last_bit:
        key[i] += 128

# Decode the message using the built key.
# small_decoded = []
# for i in messages:
#     plain = i
#     for j in range(len(i)):
#         if key[j] != -1:
#             plain[j] = i[j] ^ key[j]
#         else:
#             plain[j] = '_'.encode()[0]
#     plain = ''.join([chr(x) for x in plain])
#     small_decoded.append(plain)

# with open(output_name, 'w') as f:
#     for i in range(len(small_decoded)):
#         f.write(small_decoded[i])
#         f.write('\n')
    
# Now we have all plaintexts with some correct answers, blanks or some incorrect answers

# scuttle welcome __s tde odd greet_ng he rec_ived rpon _nxeriig the clh _oute  a_ a hozen c_ab skitte_ed _cross the floor  th_ir c`aws _aised.
# frazzle quicken __re xhe effects _f the une_pectec new_ cn hbr nervis  _autibg _er dands t_ t~emble a_d h_r thoughts to rmce _s shi str_ggled to prociss the i_formation.
# triumph placebo __fecx often occu_s when pe_ple bbliev_ xhey ve acheeze_ shmith_ng ignifi_anx, leadi_g t_ a surge of conjide_ce abd im_roved performmnce.
# kinetic whimper __capid the dog a_ it chase_ its sail _nirgesically  et_ pbnx-u_ enirgy fi_dibg relea_e i_ the futile yet,amu_ing oircu_ar pursuit thmt left i_ dizzy and slig_tly c_nf_s__.
# swindle dwindle __s tde pattern o_ the con _rtist s sc_eaes fs peop`e,b_caje,mo_e a{are, f_rceng him _o c_nstantly adapt dis _actios an_ seek out new  more gu_lible victims.
# igneous humbled __e giologist as _e stood b_fore she m_gbifident vo`cmn_c ao~ma_ion  its t_we~ing spi_es _nd complex laye~s t_llink a s_ory of violenx eruptio_s.
# cockpit nowhere __ sikht, the pil_t realize_ he hfd st_mnled'into tde,w_on` |ar_ of,the ai_po~t, find_ng _imself surroundid b_ lugkage _onveyor belts,and conf_sed baggage han_lers.
# quixote rampage __s hcw critics d_scribed t_e eccbntri_ nillnonaire+s,l_tett,bu_ines vent_re  which _nvo_ved buying up difun_t wibdmil_s across the oountry a_d converting th_m int_ q_a__t.
# hangman varnish __eamid on the ne_ly refurb_shed `allo_s  a `rim sikhx _ndbeh t_at poke v_luaes abou_ th_ town's prioritees _nd ixs ca_lous approach,to justi_e in an age tha_ shou_d _a__ m____.
# hassock lamprey __s ab unusual co_bination _or a uesta_rmnt iame, byt,i_ shmiho_ wo~ked, a_trmcting c_rio_s diners who we~e i_trigyed b_ the juxtaposetion of _omfortable seat_ng.
# abusing inkblot __sts  the unethi_al psycho_ogist'mani_u`atec his pmtee_ts  hia_nosis, int_rp~eting t_e a_biguous images en w_ys tdat w_uld justify etpensive _nd unnecessary _reatm_nt_.
# dappled abusing __ado{s played ac_oss the w_lls, dreat_nk an'eerie mtao_phbri t_at eemed _o xwist an_ di_tort the room's,con_ents  mak_ng even familear objec_s appear sinist_r.

# Considering these are english sentences, easy to guess what should be the word, given the previous context
# If guessed correctly, other messages will also look correct. 

# Manually edit/complete words to make sense:-
# Thus guess key completely

# Shadows in message 12
key[16] = ord('s') ^ messages[11][16]
key[17] = ord('h') ^ messages[11][17]

# The in many messages
key[21] = ord('h') ^ messages[0][21]

# Received in message 1
key[33] = ord('i') ^ messages[0][33]
key[43] = ord('e') ^ messages[0][43]

# Upon in message 1
key[49] = ord('u') ^ messages[0][49]

# Entering in message 1
key[54] = ord('e') ^ messages[0][54]
key[56] = ord('t') ^ messages[0][56]
key[60] = ord('n') ^ messages[0][60]

# Patients in message 11
key[67] = ord('a') ^ messages[10][67]
key[69] = ord('i') ^ messages[10][69]
key[71] = ord('n') ^ messages[10][71]

# House in message 1
key[74] = ord('s') ^ messages[0][74]

# Causing in message 2
key[76] = ord('n') ^ messages[1][76]

# Her in message 2
key[79] = ord('h') ^ messages[1][79]

# Hands in message 2
key[83] = ord('h') ^ messages[1][83]

# To in message 12
key[90] = ord('t') ^ messages[11][90]

# Tremble in message 2
key[93] = ord('r') ^ messages[1][93]

# And in message 2
key[101] = ord('n') ^ messages[1][101]

# Ambigous in message 11
key[105] = ord('m') ^ messages[10][105]

# Race in message 2
key[121] = ord('a') ^ messages[1][121]

# Contents in message 12
key[125] = ord('t') ^ messages[11][125]

# She in message 2
key[130] = ord('e') ^ messages[1][130]

# Making in message 12
key[135] = ord('i') ^ messages[11][135]

# Violent in message 6
key[149] = ord('t') ^ messages[5][149]

# information in message 2
key[158] = ord('n') ^ messages[1][158]

# Sinister in message 12
key[174] = ord('e') ^ messages[11][174]

# Treatments in message 11
key[180] = ord('e') ^ messages[10][180]
key[183] = ord('s') ^ messages[10][183]

# Confused in message 4
key[185] = ord('e') ^ messages[3][185]
key[186] = ord('d') ^ messages[3][186]

# Moral in message 9. 
# This is a guess because it is the only word that makes sense.
# No way to confirm because only 1 ciphertext is available.
key[189] = ord('o') ^ messages[8][189]
key[190] = ord('r') ^ messages[8][190]
key[191] = ord('a') ^ messages[8][191]
key[192] = ord('l') ^ messages[8][192]

decoded = []

# Decode the message using the built key.
for i in messages:
    plain = i
    for j in range(len(i)):
        if key[j] != -1:
            plain[j] = i[j] ^ key[j]
        else:
            plain[j] = '_'.encode()[0]
    plain = ''.join([chr(x) for x in plain])
    decoded.append(plain)

# for i in range(len(decoded)):
#     print(f"Message {i+1} Size:", len(decoded[i]))
#     print(decoded[i])

# Write to file
        
# Convert key to Hex
hex_key = []
for x in key:
    ch = hex(x)[2:]
    if len(ch) == 1:
        ch = '0' + ch
    hex_key.append(ch)
key = hex_key
key = ''.join(key)
# print("Key:", key)
with open(output_name, 'w') as f:
    f.write(key)
    f.write('\n')

with open(output_name, 'a') as f:
    for i in range(len(decoded)):
        f.write(decoded[i])
        f.write('\n')