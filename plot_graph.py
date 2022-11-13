import numpy as np
import matplotlib.pyplot as plt
from skimage import io
from skimage import filters
from skimage.color import rgb2gray
from skimage import feature
import os
import math


x =[1,2,3,4,5]
y = np.zeros(5)
z = np.zeros(5)

new_list = range(math.floor(min(x)), math.ceil(max(x))+1)
plt.xticks(new_list)

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
plt.xlabel('Testcase Number')
plt.ylabel('Time Taken (Microseconds)')
plt.title('Time Graph')
plt.show()
