import os

filenames = ["00000", "01631", "03510", "05350", "07200" ,"08947", "10650", "12405", "13976", "15515", "17357", "19136", "20448", "21765", "23366", "25081", "26843", "28588", "30155", "31930", "33646", "35310"]

#filenames = ["00000", "01631", "03510", "05350", "07200" ,"08947"]
#filenames = ["10650", "12405","13976", "15515", "17357", "19136", "20448", "21765"]
filenames = ["26843"]

with open('model-final.aassign', 'w') as outfile:
    for fname in filenames:
    	fname = "model-" + fname + ".aassign"
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)


with open('model-final.tassign', 'w') as outfile:
    for fname in filenames:
    	fname = "model-" + fname + ".tassign"
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)

with open('docTopic.csv', 'w') as outfile:
    header = "section" + "," + "doc_id" +"," + "topic_id" + "," + "probability" + "\n"
    outfile.write(header)
    for fname in filenames:
        fname = "docTopic_" + fname + ".csv"
        with open(fname) as infile:
            for line in infile:
                if line.split(",")[0]!="section" :
                    outfile.write(line)