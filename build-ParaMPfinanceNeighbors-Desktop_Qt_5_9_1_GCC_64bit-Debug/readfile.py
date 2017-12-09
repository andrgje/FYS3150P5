import numpy as np
import sys
import matplotlib.pyplot as plt



info1 = np.loadtxt(sys.argv[1])/500.0;
info2 = np.loadtxt(sys.argv[2])/500.0;
info3 = np.loadtxt(sys.argv[3])/500.;
info4 = np.loadtxt(sys.argv[4])/500.;

m=np.linspace(0,99.95,2000)

plt.loglog(m,info1, u'-', markersize=8)
plt.loglog(m, info2, u'-', markersize=4)
plt.loglog(m, info3, u'-', markersize=4)
plt.loglog(m ,info4, u'-', markersize=4)
plt.legend(["alpha=0.5", "alpha=1", "alpha=1.5", "alpha=2"])
plt.xlabel("log(m)")
plt.ylabel("log(p(m))")
plt.show()

plt.plot(m,info1, u'-*', markersize=8)
plt.plot(m, info2, u'-v', markersize=4)
#plt.plot(m, info3, u'-s', markersize=4)
#plt.plot(m, info4, u'-s', markersize=4)
plt.show()
