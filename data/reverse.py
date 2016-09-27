import sys
from dateutil.relativedelta import relativedelta
import datetime

#f1 =  open('rightorder_news.txt','w') 
f2 =  open('authors.txt','w') 

for line in reversed(open("author.txt").readlines()):
	f2.write(line)

#for line in reversed(open("news.txt").readlines()):
#	f1.write(line)
    