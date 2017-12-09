import numpy as np
import sys
import matplotlib.pyplot as plt



info1 = np.loadtxt(sys.argv[1])/500.;
info2 = np.loadtxt(sys.argv[2])/500.;
info3 = np.loadtxt(sys.argv[3])/500.;
info4 = np.loadtxt(sys.argv[4])/500.;

m=np.linspace(0,2.95,60)

print sum(info1), sum(info2), sum(info3), sum(info4)

plt.plot(m,info1, u'-*', markersize=8)
plt.plot(m, info2, u'-v', markersize=4)
plt.plot(m, info3, u'-s', markersize=4)
plt.plot(m ,info4, u'-d', markersize=4)
plt.legend(["lambda=0", "lambda=0.2", "lambda=0.5", "lambda=0.9"])
plt.show()
