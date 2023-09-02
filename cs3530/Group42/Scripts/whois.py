import os, re, pandas as pd

trace = "Trace_"
source = trace+"Airtel"
sourcefile = source+".csv"
sourcetxt = source+".txt"
output = "whois_"+sourcetxt

# Dataframe
df = pd.read_csv(sourcefile)
# new_df = pd.DataFrame(columns=['IP','Name','AS','Range'])


for ind in df.index:
    ip = df['IP'][ind]
    asn = df['AS'][ind]
    os.system('whois '+ip+' >> '+ output)
    # os.system('cat '+output+' | grep \'NetRange|inetnum\' > temp.txt')
    # Org = ""
    # Range = ""
    # temp = open("temp.txt","r")
    # txt =  temp.readlines()
    # if(len(txt) != 0):
    #     Range = txt[0].split(' ')[1]
    # os.system('echo '+output+' | grep \'NetName\|netname\' > temp.txt')
    # temp = open("temp.txt","r")
    # txt =  temp.readlines()
    # if(len(txt) != 0):
    #     Org = txt[0].split(' ')[1]
    # row = {'IP':ip,'Name': Org,'AS': asn, 'Range': Range}
    # new_df = new_df._append(row, ignore_index=True)
    os.system('mv '+output+' '+ip+"_"+output)

# new_df.to_csv('whois'+source+'.csv', index=False)
