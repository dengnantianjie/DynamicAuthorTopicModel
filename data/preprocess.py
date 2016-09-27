import sys
import re
import nltk
from nltk.corpus import stopwords


newss = open('processed_title.txt','w')

#with open('rightorder_news.txt','r') as file:
with open('title.txt','r') as file:
	for line in file:
	
		line = line.lower()
		line = line.strip("[")
		line = line.strip("]")

		#print line
		punctuation = re.compile(r'[#%-.?!,":;()|0-9]')
		word_list = line.split()
		word_list = [punctuation.sub("", word) for word in word_list] 
		filtered_words = [word for word in word_list if word not in stopwords.words('english')]

		#print filtered_words
		for item in filtered_words:
			newss.write(item + " ")
		newss.write("\n")






