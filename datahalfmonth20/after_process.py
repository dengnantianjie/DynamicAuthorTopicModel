import sys
from heapq import nlargest
import numpy as np


f = open("final_process_news","w")

title_file = open("stemming_process_title.txt","r")
title_lines = title_file.readlines()

with open("stemming_process_news.txt","r") as ff:
	for i, line in enumerate(ff):
		newline = title_lines[i].strip() + line
		f.write(newline) 