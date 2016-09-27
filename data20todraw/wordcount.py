#!/usr/bin/python
from collections import *
import collections
file=open("stemming_process_news.txt","r")
wordcount={}
filecount = {}

for word in file.read().split():
    if word not in wordcount:
        wordcount[word] = 1
    else:
        wordcount[word] += 1


with open("stemming_process_news.txt","r") as infile:
	for line in infile:
		cnt = Counter()
		for item in line.split():
			cnt[item] += 1
		for word in cnt.keys():
			if word not in filecount:
				filecount[word] = 1
			else:
				filecount[word] += 1



wordcount = collections.OrderedDict(sorted(wordcount.items(),key=lambda x: x[1]))
filecount = collections.OrderedDict(sorted(filecount.items(),key=lambda x: x[1]))
with open('stemming_process_news.wordcount', 'w') as outfile:
	for k,v in wordcount.items():
		newline =  str(k) + "    " + str(v) + "\n"
		outfile.write(newline)
with open('stemming_process_news.filecount', 'w') as outfile:
	for k,v in filecount.items():
		newline =  str(k) + "    " + str(v) + "\n"
		outfile.write(newline)
