import numpy as np
import matplotlib.pyplot as plt
from skimage import io
from skimage import filters
from skimage.color import rgb2gray
from skimage import feature
import os


x = np.zeros(5)
y = np.zeros(5)
z = np.zeros(5)

for i in range(5):
    x[i] = i+1

y[0] = 32085
z[0] = 8028

y[1] = 40119
z[1] = 8006

y[2] = 31259
z[2] = 6806

y[3] = 32245
z[3] = 13623

y[4] = 32146
z[4] = 15685

plt.scatter(x, y, color='red')
plt.scatter(x, z, color='blue')
plt.legend(["Ford Fulkerson", "Push Relabel"], loc="upper right")
# plt.yticks(np.arange(0, 0.1, 0.01))
plt.xlabel('Testcase Number')
plt.ylabel('Time Taken (Microseconds)')
plt.title('Time Graph')
plt.show()
