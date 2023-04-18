import numpy as np
import matplotlib.pyplot as plt

v1 = np.arange(1.8,2.85, 0.05) # Considering a precision of 50mV from 1800mv to 2800mV
print(len(v1))
v2 = np.arange(1.8,2.85, 0.05)
t = np.arange(0,300,1)
slope = np.zeros((len(v1), len(v2)))
intercept = np.zeros((len(v1), len(v2)))

x = np.zeros((len(v1), len(v2)))

k = 0
for i in range(len(v1)):
    for j in range(len(v2)):
        if v1[i] < v2[j]:
            k+=1
            slope[i][j] = (v2[j] - v1[i]) / 10 # Considering that a measurement is taken with a time difference of 10s
            intercept[i][j] = v2[j] - slope[i][j] * 10
            # print(v1[i], ":", v2[j], "::", slope[i][j], "::", intercept[i][j])
            plt.figure(1)
            plt.plot(t, slope[i][j] * t + intercept[i][j])
            
            plt.figure(2)
            y = v1[i] + (3.3 * (1 - np.exp(-t * slope[i][j] / 3.5)))
            plt.plot(t, y)

# calculate the time at which y=3.3
y = 3.3
print("--------------------")
print("  v1  |  v2  ||   t ")
print("--------------------")
for i in range(len(v1)):
    for j in range(len(v2)):
        if v1[i] < v2[j]:
            x[i][j] = (-3.5 / slope[i][j]) * np.log(1 - (y - v1[i]) / 3.3)
            print(" {} | {} || {} ".format("{:.2f}".format(v1[i]), "{:.2f}".format(v2[j]),int(x[i][j])))
          
print("Total number of valid points: ",k)

for i in range(0,21):
    print('{', end='')
    for j in range(0,21):
        print(int(x[i][j]), end='')
        if j != 20:
            print(',', end='')
    print('},')
plt.show()
