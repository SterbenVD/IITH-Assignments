import os, re, pandas as pd

source = "IIT"
sourcefile = source+".txt"
output = "routes_"+sourcefile

# URLS
urls = ['www.iith.ac.in',
'www.youtube.com',
'www.ubuntu.com',
'www.codeforces.com',
'www.chess.com',
'www.wikipedia.org',
'www.github.com',
'www.zomato.com',
'www.olacabs.com',
'www.zerodha.com']

# Dataframe
df = pd.DataFrame(columns=['IP','Latency','AS','Dest','Source'])

# For all destinations
for dest in urls:
    # Data for a destination
    os.system('traceroute -TAe '+dest+' >> '+ output)
    fptr = open(output,"r")
    lines =  fptr.readlines()
    # Extract Data into Dataframe
    for line in lines:
        AS = re.findall(r'\[AS\d+\]', line)
        if(len(AS)!=0):
            IP = re.findall(r'(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})', line)[0]
            lats = re.findall(r'\d+.\d+ ms', line)
            lat = (sum(float(f[:-4]) for f in lats))/len(lats)
            row = {'IP':IP,'Latency':lat,'AS':AS[0],'Dest':dest,'Source':source}
            df = df._append(row, ignore_index=True)
    # Store destination data in diff file
    os.system('mv '+output+' '+dest+"_"+output)
df.to_csv(source+'.csv', index=False)