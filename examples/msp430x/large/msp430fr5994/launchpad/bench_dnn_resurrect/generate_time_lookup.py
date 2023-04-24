import numpy as np
import matplotlib.pyplot as plt

v1 = np.arange(1792,2817, 64) # Considering a precision of 50mV from 1800mv to 2800mV
print(len(v1))
v2 = np.arange(1792,2817, 64)
t = np.arange(0,300,1)
slope = np.zeros((len(v1), len(v2)))
intercept = np.zeros((len(v1), len(v2)))

x1 = np.zeros((len(v1), len(v2)))
x_approx = np.zeros((len(v1), len(v2)))

k = 0
for i in range(len(v1)):
    for j in range(len(v2)):
        if v1[i] < v2[j]:
            k+=1
            slope[i][j] = (v2[j] - v1[i]) / 10 # Considering that a measurement is taken with a time difference of 10s
            intercept[i][j] = v2[j] - slope[i][j] * 10
            # print(v1[i], ":", v2[j], "::", slope[i][j], "::", intercept[i][j])
            # plt.figure(1)
            # plt.plot(t, slope[i][j] * t + intercept[i][j])
            
            # plt.figure(2)
            # y = v1[i] + (3300 * (1 - np.exp(-t * slope[i][j] / 3500)))
            # plt.plot(t, y)

# calculate the time at which y=3.3
y = 3300
print("----------------------------")
print("  v1  |  v2  ||  t  ||t_appx")
print("----------------------------")
for i in range(len(v1)):
    for j in range(len(v2)):
        if v1[i] < v2[j]:
            
            factor = 1 - ((3300 - v1[i])/3300) # values from 0.5 to 0.83
            # print(factor)
            coeff = np.log(factor)  # values from -0.18 to -0.61
            x1[i][j] = (-3500 / slope[i][j]) * coeff
            
            factor2 = ((v1[i]-3300)/3300)
            x = factor2
            # coeff2 =-2.486193160 + (5.951925226 + (-6.570618861 + (4.252664361 - 1.149089989*factor2)*factor2)*factor2)*factor2 #(factor2) - (factor2)**2/2 #+ (factor2)**3/3 # - (factor2)**4/4
            coeff2 = factor2 - (factor2*factor2)/2
            coeff3 = -8.6731532+(129.946172+(-558.971892+(843.967330-409.109529*x)*x)*x)*x
            x_approx[i][j] = (-3500 / slope[i][j]) * coeff2
            
            print(" {} | {} || {} || {} ".format(v1[i],v2[j],f"{int(x1[i][j]):03d}", f"{int(x_approx[i][j]):03d}"))
          
# print("Total number of valid points: ",k)

for i in range(len(v1)):
    print('{', end='')
    for j in range(len(v1)):
        print(int(x1[i][j]), end='')
        if j != len(v1)-1:
            print(',', end='')
    print('},')

plt.show()
