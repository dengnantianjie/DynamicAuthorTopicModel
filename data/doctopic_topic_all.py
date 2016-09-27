#!/usr/bin/python
import collections
import pandas as pd
from collections import Counter
import sys
from heapq import nlargest
import numpy as np
file_index = sys.argv[1]
wordnumber = 29448
number = 20

step_steps = int(float(file_index))
print step_steps

wordmap = {}
with open("wordmap_temp.txt") as f:
    for line in f:
       (val, key) = line.split()
       wordmap[int(key)] = val


fp = open("model-%s.twords" %file_index,"r")
topicword_dict = {}
for i, line in enumerate(fp):
    lines = line.split()
    if lines[0] == "Topic":
        inner_topicword_dict = {}
        index = lines[1].replace("th:","")
        index = int(index)
        for a in range(wordnumber):
            newline = fp.next()
            newlines = newline.split("   ")
            inner_topicword_dict[newlines[0].strip()] = (newlines[1].strip())
        topicword_dict[index] = inner_topicword_dict


fp = open("model-%s.atopics" %file_index,"r")
authortopic_dict = {}
for i, line in enumerate(fp):
    lines = line.split()
    if lines[0] == "Author":
        inner_topicword_dict = {}
        index = lines[1].replace("th:","")
        index = int(index)
        for a in range(20):
            newline = fp.next()
            newlines = newline.split("   ")
            inner_topicword_dict[int(newlines[0].strip())] = (newlines[1].strip())
        authortopic_dict[index] = inner_topicword_dict
        




title = open("title.txt","r")
author = open("author.txt","r")
tassign = open("model-%s.tassign" %file_index,"r")
aassign = open("model-%s.aassign" %file_index,"r").readlines()
maps_csv = "categories_mapped.csv"

doctopics = open("docTopic_%s.csv" %file_index,"w")
header = "section" + "," + "doc_id" +"," + "topic_id" + "," + "probability" + "\n"
doctopics.write(header)

df = pd.read_csv(maps_csv)
map_df = dict(zip(list(df.url_grouping), list(df.manual_grouping)))


replace_author_array = []
for line in author:
  line = line.strip()
  replace_author = map_df[line]
  replace_author_array.append(replace_author)

title_array = []
for line in title:
  line = line.strip()
  title_array.append(line)

for i, line in enumerate(tassign):
    words = line.split()
    authors_no = []
    percs = []
    c = Counter()

    a = aassign[i].split()
    for (j,word) in enumerate(words):
      author_no = word.split(":")[1]
      authors_no.append(author_no)
      word_index = word.split(":")[0]
      author_ = a[j].split(":")[1]
        #print topicword_dict[int(author_no)][str(wordmap[int(word_index)])] 
        #rint (authortopic_dict[int(author_)][int(author_no)])
      perc = float(topicword_dict[int(author_no)][str(wordmap[int(word_index)])]) * (float(authortopic_dict[int(author_)][int(author_no)]))
      #perc = float(topicword_dict[int(author_no)][str(wordmap[int(word_index)])]) 
   
      percs.append(perc)
      c[author_no] += float(perc)
    
    most = c.most_common(1)[0][0]
    most_number = c.most_common(1)[0][1]

    percentage = most_number/float(sum(c.values()))
    if (replace_author_array[i+step_steps] != "-"):
      newline = str(replace_author_array[i+step_steps]) + "," + str(title_array[i+step_steps]) + "," + str(most) + "," + str(percentage) + "\n"
      doctopics.write(newline)
doctopics.close()

# for i, line in enumerate(assign):
#    words = line.split()
#    authors_no = []
#    line_dict = dict()
#    for word in words:
#        author_no = word.split(":")[1]
#        authors_no.append(author_no)
#    line_dict = Counter(authors_no)
#    most = line_dict.most_common(1)[0][0]
#    most_number = line_dict.most_common(1)[0][1]
#    percentage = most_number/float(sum(line_dict.values()))
#    if (replace_author_array[i] != "-"):
#        newline = str(replace_author_array[i]) + "," + str(title_array[i]) + "," + str(most) + "," + str(percentage) + "\n"
#        doctopics.write(newline)
# doctopics.close()




