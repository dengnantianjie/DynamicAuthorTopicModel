import collections
import pandas as pd
from collections import Counter

atopics = open("model-final.atopics","r")
newfile = open("wordTopic.string","w")

for i, line in enumerate(atopics):
    lines = line.split()
    if lines[0] == "Author":
    	author = lines[1].replace("th:","")
    	topic = []
    	prob = []
    	for a in range(10):
    		newline = atopics.next()
    		newlines = newline.split("   ")
    		topic.append(newlines[0].strip())
    		prob.append(newlines[1])

    	newl = author + "\t" + ','.join(topic) +","+ "\n"
    	newfile.write(newl)