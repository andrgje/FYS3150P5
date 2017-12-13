import numpy as np
import sys
import matplotlib.pyplot as plt
import math



info1 = np.loadtxt(sys.argv[1])/500.;
info2 = np.loadtxt(sys.argv[2])/500.;
info3 = np.loadtxt(sys.argv[3])/500.;
info4 = np.loadtxt(sys.argv[4])/500.;

m=np.linspace(0,2.95,60)

#print sum(info1), sum(info2), sum(info3), sum(info4)


plt.plot(m[24:], info2[24:]/0.05)
n=2
plt.plot(m[24:], (n**n/math.factorial(n-1)*m**(n-1)*np.exp(-n*m))[24:],'-v', markersize=4)
n2=1+3

plt.plot(m[24:], info3[24:]/0.05)
plt.plot(m[24:], (n2**n2/math.factorial(n2-1)*m**(n2-1)*np.exp(-n2*m))[24:],'-v', markersize=4)
plt.plot(m[24:], info4[24:]/0.05)
n3=28
plt.plot(m[24:], (n3**n3/math.factorial(n3-1)*m**(n3-1)*np.exp(-n3*m))[24:],'-o', markersize=4)
plt.legend(["Numerical result lambda=0.25", "Power law func lambda=.025", "Numerical result lambda=0.5","Powerlaw func lambda=0.5", "Numerical result lambda=0.9", "Powerlaw fun lambda=09."])
plt.xlabel("m0")
plt.ylabel("w_m")
plt.show()

plt.plot(m,info1, u'-*', markersize=8)
#plt.plot(m, info2, u'-v', markersize=4)
#plt.plot(m, info3, u'-s', markersize=4)
#plt.plot(m, info4, u'-s', markersize=4)
#plt.plot(m, 0.05*np.exp(-1*m), linewidth=2)
plt.legend(["lambda=0", "lambda=0.25", "lambda=0.5", "lambda=0.9", "analytical"])
plt.ylabel("0.05p(m)")
plt.xlabel("m0")
plt.show()
