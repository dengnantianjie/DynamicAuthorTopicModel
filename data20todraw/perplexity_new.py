import numpy as np

theta = np.loadtxt("model-final.theta", dtype='str',delimiter=" ")
phi = np.loadtxt("model-final.phi", dtype='str',delimiter=" ")

print theta.shape
print phi.shape

theta = theta[:,0:-1]
phi = phi[:,0:-1]
log_per = 0
N = 0



print "author number is " + str(theta.shape[0])
print "words number is " + str(N)

theta = np.ma.array(theta,dtype=float)
phi = np.ma.array(phi,dtype=float)


aassign = open("model-final.aassign")
tassign = open("model-final.tassign")
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

print perplexity






