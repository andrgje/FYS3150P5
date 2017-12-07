import numpy as np
import sys
import matplot.pyplot as plt

filename = sys.argv[1]

info = np.loadtxt(filename);

print info.shape
