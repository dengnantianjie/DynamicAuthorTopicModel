import sys
from heapq import nlargest
import numpy as np

wordnumber = 29448
number = 20

newfile = open('new_model-final.twords','w')

fp = open("model-final.twords")
for i, line in enumerate(fp):
    lines = line.split()
    if lines[0] == "Topic":
    	newfile.write(line)
    	word = []
    	prob = []
    	for a in range(wordnumber):
    		newline = fp.next()
    		newlines = newline.split("   ")
    		word.append(newlines[0])
    		prob.append(newlines[1])
    	positions = nlargest(number, range(len(prob)), np.asarray(prob).take)
    	for k in range(number):
    		newfile.write(str(word[positions[k]] + "   " + str(prob[positions[k]])))