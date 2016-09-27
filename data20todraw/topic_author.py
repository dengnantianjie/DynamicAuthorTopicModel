import sys
from heapq import nlargest
import numpy as np

topics = 20

newfile = open('model-final.tauthors','w')
prob = []
for i in range(9):
    prob.append([])
    for j in range(topics):
        prob[i].append(0)

fp = open("model-final.atopics")
for i, line in enumerate(fp):
    lines = line.split()
    if lines[0] == "Author":
        author = int(lines[1][0])
    	for a in range(topics):
            newline = fp.next()
            newlines = newline.split("   ")
            topic = int(newlines[0])
            prob[author][topic] = float(newlines[1])
sums = [sum([row[i] for row in prob]) for i in range(0,len(prob[0]))]
print sums

    		
for k in range(topics):
    newfile.write("Topic " + str(k) + ":" + "\n")
    prob_column = []
    for j in range(9):
        prob[j][k] = prob[j][k]/sums[k]
        prob_column.append(prob[j][k]/sums[k]) 
    prob_column = sorted(range(len(prob_column)), key=lambda k:prob_column[k],reverse=True)
    for jj in prob_column:
        newfile.write(str(jj) + "   " + str(prob[jj][k]) + "\n")
    