#!/usr/bin/python
import collections
import pandas as pd
from collections import Counter

title = open("title.txt","r")
author = open("author.txt","r")
assign = open("model-final.aassign","r")
maps_csv = "categories_mapped.csv"

doctopics = open("docTopic.csv","w")
header = "section" + "," + "doc_id" +"," + "topic_id" + "," + "probability" + "\n"
doctopics.write(header)

df = pd.read_csv(maps_csv)
map_df = dict(zip(list(df.url_grouping), list(df.manual_grouping)))
print map_df

replace_author_array = []
for line in author:
	line = line.strip()
	replace_author = map_df[line]
	replace_author_array.append(replace_author)

title_array = []
for line in title:
	line = line.strip()
	title_array.append(line)

for i, line in enumerate(assign):
    words = line.split()
    authors_no = []
    line_dict = dict()
    for word in words:
    	author_no = word.split(":")[1]
    	authors_no.append(author_no)
    line_dict = Counter(authors_no)
    most = line_dict.most_common(1)[0][0]
    most_number = line_dict.most_common(1)[0][1]
    percentage = most_number/float(sum(line_dict.values()))
    if (replace_author_array[i] != "-"):
    	newline = str(replace_author_array[i]) + "," + str(title_array[i]) + "," + str(most) + "," + str(percentage) + "\n"
    	doctopics.write(newline)
doctopics.close()




