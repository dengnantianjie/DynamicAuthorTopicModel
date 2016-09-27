from gensim import corpora, models, similarities
from collections import *
import collections


newfile = open('final_final_process_news.txt','w')

with open("stemming_process_news.txt") as file:
    documents = file.readlines()
file.close()

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

file.close()

wordcount = collections.OrderedDict(sorted(wordcount.items(),key=lambda x: x[1]))
filecount = collections.OrderedDict(sorted(filecount.items(),key=lambda x: x[1]))
with open('stemming_process_news.wordcount', 'w') as outfile:
	for k,v in wordcount.items():
		newline =  str(k) + "    " + str(v) + "\n"
		outfile.write(newline)
outfile.close()
with open('stemming_process_news.filecount', 'w') as outfile:
	for k,v in filecount.items():
		newline =  str(k) + "    " + str(v) + "\n"
		outfile.write(newline)
outfile.close()

# remove common words and tokenize
stoplist = set('for a of the and to in'.split())
texts = [[word for word in document.lower().split() if word not in stoplist]
         for document in documents]
print "1 step \n"
# remove words that appear only once
# all_tokens = sum(texts, [])
texts_temp = texts
tokens_once = set(word for word in filecount.keys() if filecount.get(word) < 4 )
tokens_more = set(word for word in filecount.keys() if filecount.get(word) > 10000 )
texts = [[word for word in text if word not in tokens_once]
        for text in texts]

texts = [[word for word in text if word not in tokens_more]
        for text in texts]
print "2 step \n"
for index, element in enumerate(texts):
    if len(element) == 0: 
        element = texts_temp[index]
    newline = ' '.join(element)
    newline = newline + "\n"
    newfile.write(newline)
newfile.close()
