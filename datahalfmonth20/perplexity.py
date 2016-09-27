import numpy as np

#filenames = ["35310"]

filenames = ["00000", "01631", "03510", "05350", "07200" ,"08947", "10650", "12405", "13976", "15515", "17357", "19136", "20448", "21765", "23366", "25081", "26843", "28588", "30155", "31930", "33646", "35310"]
log_per = 0
N = 0
for file in filenames:
	theta_file = "model-" + str(file) + ".theta"
	phi_file = "model-" + str(file) + ".phi"

	theta = np.loadtxt(theta_file, dtype='str',delimiter=" ")
	phi = np.loadtxt(phi_file, dtype='str',delimiter=" ")

	print theta.shape
	print phi.shape

	theta = theta[:,0:-1]
	phi = phi[:,0:-1]




	print "author number is " + str(theta.shape[0])
	print "words number is " + str(N)

	theta = np.ma.array(theta,dtype=float)
	phi = np.ma.array(phi,dtype=float)

	ass_file = "model-" + str(file) + ".aassign"
	tas_file = "model-" + str(file) + ".tassign"
	aassign = open(ass_file)
	tassign = open(tas_file)
	aassign = aassign.readlines()
	tassign = tassign.readlines()
	print len(aassign)

	for m in range(0,len(aassign)):
		a_line = aassign[m]
		t_line = tassign[m]
		
		
		authors = a_line.split()
		topics = t_line.split()

		for element in range(0,len(authors)-1):
			w = authors[element].split(":")[0]
			a = authors[element].split(":")[1]
			#t = topics[element].split(":")[1]

			phi_line = phi[:,w].T
			theta_line = theta[a,:]
			with np.errstate(invalid='ignore'):
				log_per -= np.log(np.inner(phi_line, theta_line))
				#print np.inner(phi_line, theta_line)
		N += len(authors)-1
	
	
perplexity = np.exp(log_per / N)

print N

print perplexity






