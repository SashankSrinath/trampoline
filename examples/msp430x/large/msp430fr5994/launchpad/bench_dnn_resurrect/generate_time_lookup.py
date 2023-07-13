import numpy as np
import matplotlib.pyplot as plt

v1 = np.arange(1792,3009, 32) # Considering a precision of 64mV from below 1800mv to above 2800mV

v2 = np.arange(1792,3009, 32)

slope = np.zeros((len(v1), len(v2)))
intercept = np.zeros((len(v1), len(v2)))

x = np.zeros((len(v1), len(v2)))
x_approx = np.zeros((len(v1), len(v2)))
x_approx_2 = np.zeros((len(v1), len(v2)))
x_linear = np.zeros((len(v1), len(v2)))

time = []
time_2 = []
time_3 = []
time_4 = []

err = []
err_2 = []
err_3 = []

k = 0
interval = 20
for i in range(len(v1)):
    for j in range(len(v2)):
        if v1[i] < v2[j]:
            k+=1
            slope[i][j] = (v2[j] - v1[i]) / interval # Considering that a measurement is taken with a time difference of 20s
            intercept[i][j] = v2[j] - slope[i][j] * interval

# calculate the time at which y=3.3
y = 3200 # Threshold value  
print("-----------------------------------------")
print("  v1  |  v2  ||  t  || t_2 || t_3 || lin")
print("-----------------------------------------")
for i in range(len(v1)):
    for j in range(len(v2)):
        if v1[i] < v2[j]:    
            factor = 1 - ((y  - v1[i])/y) # values from 0.5 to 0.83
            coeff = np.log(factor)  # values from -0.18 to -0.61
            x[i][j] = (-3500 / slope[i][j]) * coeff
            time.append(int(x[i][j]))
            factor2 = ((v1[i]- y)/y)
            coeff2 = factor2 - (factor2*factor2)/2
            coeff3 = factor2 - (factor2*factor2)/2 + (factor2**3/3)
            
            # x = factor2
            # coeff2 =-2.486193160 + (5.951925226 + (-6.570618861 + (4.252664361 - 1.149089989*factor2)*factor2)*factor2)*factor2 #(factor2) - (factor2)**2/2 #+ (factor2)**3/3 # - (factor2)**4/4            
            # coeff3 = -8.6731532+(129.946172+(-558.971892+(843.967330-409.109529*x)*x)*x)*x
            
            x_approx[i][j] = (-3500 / slope[i][j]) * coeff2
            time_2.append(int(x_approx[i][j]))
            
            x_approx_2[i][j] = (-3500 / slope[i][j]) * coeff3
            time_3.append(int(x_approx_2[i][j]))
            
            x_linear[i][j] = (y - intercept[i][j])/slope[i][j]
            time_4.append(int(x_linear[i][j]))
            
            print(" {} | {} || {} || {} || {} || {} ".format(v1[i],v2[j],f"{int(x[i][j]):03d}", f"{int(x_approx[i][j]):03d}", f"{int(x_approx_2[i][j]):03d}", f"{int(x_linear[i][j]):03d}"))
          

lookup_time = []
for i in range(len(v1)):
    print('{', end='')
    for j in range(len(v1)):
        print(int(x[i][j]), end='')
        if j != len(v1)-1:
            print(',', end='')
            if(i<=j):
                lookup_time.append(int(x[i][j+1]))
    print('},')

print("Total number of valid points: ",k)
print("Bytes: ",len(v1)*len(v1)*16/8)
plt.figure(3)
plt.title("Prediction of time")
t = np.arange(0,len(time),1)
plt.plot(t, time,'r', label = "Online prediction")
plt.plot(t,time_2,'b', label = "Taylor series 2nd order approximation")
plt.plot(t,time_3,'tab:orange', label = "Taylor series 3nd order approximation" )
plt.plot(t,time_4,'g', label = "Linear extrapolation")
plt.xlabel('Number of prediction')
plt.ylabel('Time(s)')
plt.legend()

for i in range(len(time)):
    err.append((time[i]-time_2[i])/time_2[i])
    err_2.append((time[i]-time_3[i])/time_3[i])
    err_3.append((time[i]-time_4[i])/time_4[i])
    
plt.figure(4)
plt.title("Relative time error")
t = np.arange(0,len(time),1)
plt.plot(t, err,'r', label = "Online prediction vs Taylor series 2nd order") # -rx
plt.plot(t, err_2,'b', label = "Online prediction vs Taylor series 3nd order") # -bx
plt.plot(t, err_3,'g', label = "Online prediction vs linear extrapolation") # -bx
plt.xlabel('Number of prediction')
plt.ylabel('Relative error')
plt.legend()
    
plt.show()

n = len(v1)
print(lookup_time)
# print(len(lookup_time))
# for i in range (n):
#     for j in range (i+1, n):
#         index = 528 - int((33-i)*((33-i)-1)/2) + j - i - 1
#         print("row: ",i," col: ",j,"time: ",lookup_time[index])
            