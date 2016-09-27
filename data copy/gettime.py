import sys
from dateutil.relativedelta import relativedelta
import datetime

all_date = []
weeks = []

with open('times.txt','r') as f:
    for line in f:
        x = line.split('T')[0]
        date = datetime.datetime.strptime(x, "%Y-%m-%d").strftime("%d-%m-%Y")
        
        all_date.append(date)

        
#for idx, val in enumerate(all_date):
start_date = all_date[0]

print start_date
weeks.append(all_date.index(start_date))

while (any(start_date in item for item in all_date)):
	end_date = datetime.datetime.strptime(start_date, "%d-%m-%Y") + datetime.timedelta(days=7)
	
	end_date =  end_date.date().strftime("%d-%m-%Y")
	
	#end_date = str(end_date).split()[0]
	if (any(end_date in item for item in all_date)):
		weeks.append(all_date.index(end_date))
		start_date = end_date
	else:
		break
		
weeks.append(len(all_date)-1)
print weeks





#time1 = all_date.index(datetime.datetime.strptime("2016-01-07", "%Y-%m-%d").strftime("%d-%m-%Y"))
#time2 = all_date.index(datetime.datetime.strptime("2016-01-14", "%Y-%m-%d").strftime("%d-%m-%Y"))
#time1 = time1 + 1
#time2 = time2 + 1






