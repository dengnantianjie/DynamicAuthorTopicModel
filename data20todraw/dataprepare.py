import sys

authors = open('author.txt','w')
titles = open('title.txt','w')
newss = open('news.txt','w')
times = open('time.txt','w')

with open('bbc-dataset-201601-201607-time.tab','r') as f:
    for line in f:
        author = line.split("\t")[0].strip()
        title = line.split("\t")[1].strip()
        news = line.split("\t")[3].strip()
        time = line.split("\t")[4].strip()
        authors.write(author + '\n')
        titles.write(title + '\n' )
        #newss.write(news + '\n')
        #times.write(time + '\n')
authors.close()
titles.close()
newss.close()
times.close()