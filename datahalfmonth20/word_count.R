library(gdata) 
library(ggplot2)
filecount = read.csv("stemming_process_news_filecount.csv")
wordcount = read.csv("stemming_process_news_wordcount.csv")
ggplot(filecount, aes(count)) +
  geom_histogram(binwidth = 0.01)


