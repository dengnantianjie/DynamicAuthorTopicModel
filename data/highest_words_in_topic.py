import sys
from heapq import nlargest
import numpy as np
fileindex = ["00000" ,"01631" ,"03510" ,"05350" ,"07200" ,"08947" ,"10650" ,"12405" ,"13976" ,"15515" ,"17357" ,"19136" ,"20448", "21765" ,"23366" ,"25081" ,"26843" ,"28588" ,"30155" ,"31930" ,"33646", "35310"]

#"00000" "01631" "03510" "05350" "07200" "08947" "10650" "12405" "13976" "15515" "17357" "19136" "20448" "21765" "23366" "25081" "26843" "28588" "30155" "31930" "33646" "35310"

wordnumber = 29448
number = 20
for index in fileindex:
    index = str(index)
    newfile = open('model-new-%s.twords'%index,'w')

    fp = open("model-%s.twords"%index)
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