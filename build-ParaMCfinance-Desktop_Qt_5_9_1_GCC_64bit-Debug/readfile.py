import numpy as np
import sys
import matplotlib.pyplot as plt



info1 = np.loadtxt(sys.argv[1]);
info2 = np.loadtxt(sys.argv[2]);
info3 = np.loadtxt(sys.argv[3]);
info4 = np.loadtxt(sys.argv[4]);

m=np.linspace(0,2.95,60)

plt.plot(m,info1, u'-*', markersize=8)
plt.plot(m, info2, u'-v', markersize=4)
plt.plot(m, info3, u'-s', markersize=4)
plt.plot(m ,info4, u'-d', markersize=4)
plt.legend(["lambda=0", "lambda=0.2s", "lambda=0.5", "lambda=0.9"])
plt.show()
