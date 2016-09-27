#!/usr/bin/python
from collections import *
import collections
import pandas as pd
import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt

file=open("final_final_process_news.txt","r")
wordcount={}
filecount = {}

for word in file.read().split():
    if word not in wordcount:
        wordcount[word] = 1
    else:
        wordcount[word] += 1


with open("final_final_process_news.txt","r") as infile:
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
with open('stemming_process_news_wordcount.csv', 'w') as outfile:
	outfile.write("word" + "," + "count" + "\n")
	for k,v in wordcount.items():
		newline =  str(k) + "," + str(v) + "\n"
		outfile.write(newline)
with open('stemming_process_news_filecount.csv', 'w') as outfile:
	outfile.write("word" + "," + "count" + "\n")
	for k,v in filecount.items():
		newline =  str(k) + "," + str(v) + "\n"
		outfile.write(newline)

wordcount = (pd.read_csv('stemming_process_news_wordcount.csv'))
filecount = (pd.read_csv('stemming_process_news_filecount.csv'))
counter =  Counter(wordcount['count'].tolist())

keys = counter.keys()
y_pos = np.arange(len(keys))
# get the counts for each key, assuming the values are numerical
performance = [counter[k] for k in keys]
# not sure if you want this :S
error = np.random.rand(len(keys))

plt.barh(y_pos, performance, xerr=error, align='center', alpha=0.4)
plt.yticks(y_pos, keys)
plt.xlabel('Counts per key')
plt.title('Word count distribution')

plt.show()



