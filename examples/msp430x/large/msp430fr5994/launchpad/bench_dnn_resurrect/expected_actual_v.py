import numpy as np
import matplotlib.pyplot as plt

LUT_x_3300 = [3309, 3282, 3294, 3280, 3297, 3302, 3310, 3293, 3271, 3281]

LUT_x_3200 = [3232, 3191, 3159, 3161, 3167, 3182, 3176, 3157, 3150, 3242] 

LUT_x_3100 = [3129, 3144, 3142, 3135, 3095, 3128, 3149, 3116, 3144, 3084]

LUT_x_3000 = [3082, 3082, 2983, 3066, 3034, 3032, 3001, 3068, 3047, 3048]



linear_x_3300 = [3119, 3127, 3073, 3117, 3113, 3141, 3161, 3147, 3177, 3145]

linear_x_3200 = [3129, 3075, 3085, 3140, 3130, 3134, 3138, 3136, 3130, 3053]

linear_x_3100 = [2998, 3115, 3026, 3099, 3022, 3143, 3165, 3168, 3029, 3100]

linear_x_3000 = [3092, 3091, 3094, 3095, 3094, 3103, 3095, 3090, 3089, 3081]
 
 
y_3300 = []
y_3200 = []
y_3100 = []
y_3000 = []
 
for i in range (len(LUT_x_3300)):
    y_3300.append(3300)
    y_3200.append(3200)
    y_3100.append(3100)
    y_3000.append(3000)
    
plt.figure()   
plt.scatter(linear_x_3300, y_3300, s=10, color = 'darkred', label = "Linear extrapolation")     
plt.scatter(LUT_x_3300, y_3300, s=10, color = 'navy', label = "Exponential extrapolation") 

plt.scatter(linear_x_3200, y_3200, s=10, color = 'crimson') 
plt.scatter(LUT_x_3200, y_3200, s=10, color = 'mediumblue') 

plt.scatter(linear_x_3100, y_3100, s=10, color = 'coral') 
plt.scatter(LUT_x_3100, y_3100, s=10, color = 'royalblue') 

plt.scatter(linear_x_3000, y_3000, s=10, color = 'lightcoral') 
plt.scatter(LUT_x_3000, y_3000, s=10, color = 'dodgerblue') 
plt.grid(True)

# Add labels and title
plt.xlabel('Actual value (mV)')
plt.ylabel('Expected value(mV)')
# plt.title('Expected value of 3100mV')
plt.xlim(1800, 4000)
plt.ylim(1800, 4000)

plt.vlines(3300,0, 3300, colors='k', linewidths=0.5, linestyles='--')
plt.vlines(3200,0, 3200, colors='k', linewidths=0.5, linestyles='--')
plt.vlines(3100,0, 3100, colors='k', linewidths=0.5, linestyles='--')
plt.vlines(3000,0, 3000, colors='k', linewidths=0.5, linestyles='--')

# plt.vlines(max(LUT_x_3300),0, 3300, colors='k', linewidths=0.5, linestyles='--')

# plt.vlines(min(LUT_x_3200),0, 3200, colors='k', linewidths=0.5, linestyles='--')
# plt.vlines(max(LUT_x_3200),0, 3200, colors='k', linewidths=0.5, linestyles='--')

# plt.vlines(min(LUT_x_3100),0, 3100, colors='k', linewidths=0.5, linestyles='--')
# plt.vlines(max(LUT_x_3100),0, 3100, colors='k', linewidths=0.5, linestyles='--')

# plt.vlines(min(LUT_x_3000),0, 3000, colors='k', linewidths=0.5, linestyles='--')
# plt.vlines(max(LUT_x_3000),0, 3000, colors='k', linewidths=0.5, linestyles='--')

# plt.annotate(min(LUT_x_3100), xy=(3000, 0), xytext=(min(LUT_x_3100), 100),
#              ha='center', va='top')
# plt.annotate(max(LUT_x_3100), xy=(3300, 0), xytext=(max(LUT_x_3100), 100),
#              ha='center', va='top')

plt.hlines(3300,0, 3300, colors='k', linewidths=0.5, linestyles='--')
plt.annotate('3300', xy=(0, 3300), xytext=(-85, 3325),
             ha='center', va='top')

plt.hlines(3200,0, 3200, colors='k', linewidths=0.5, linestyles='--')
plt.annotate('3200', xy=(0, 3200), xytext=(-85, 3225),
             ha='center', va='top')

plt.hlines(3100,0, 3100, colors='k', linewidths=0.5, linestyles='--')
plt.annotate('3100', xy=(0, 3100), xytext=(-85, 3125),
             ha='center', va='top')

plt.hlines(3000,0, 3000, colors='k', linewidths=0.5, linestyles='--')
# plt.annotate('3000', xy=(0, 3000), xytext=(-85, 3025),
#              ha='center', va='top')

plt.legend()


error_3300 = []
error_3200 = []
error_3100 = []
error_3000 = []

error_3300_l = []
error_3200_l = []
error_3100_l = []
error_3000_l = []


for i in range(len(LUT_x_3300)):
    error_3300.append((LUT_x_3300[i] - 3300)/33)
    error_3200.append((LUT_x_3200[i] - 3200)/32)
    error_3100.append((LUT_x_3100[i] - 3100)/31)
    error_3000.append((LUT_x_3000[i] - 3000)/30)
    
    error_3300_l.append((linear_x_3300[i] - 3300)/33)
    error_3200_l.append((linear_x_3200[i] - 3200)/32)
    error_3100_l.append((linear_x_3100[i] - 3100)/31)
    error_3000_l.append((linear_x_3000[i] - 3000)/30)

x = [0,1,2,3,4,5,6,7,8,9]

plt.figure()   

plt.plot(x,error_3300,color = 'navy', label ="3300mV exponential")
plt.plot(x,error_3200, color = 'mediumblue', label ="3200mV exponential")
plt.plot(x,error_3100, color = 'royalblue', label ="3100mV exponential")
plt.plot(x,error_3000, color = 'dodgerblue', label ="3000mV exponential")

plt.plot(x,error_3300_l,color = 'darkred', label ="3300mV linear")
plt.plot(x,error_3200_l, color = 'crimson', label ="3200mV linear")
plt.plot(x,error_3100_l, color = 'coral', label ="3100mV linear")
plt.plot(x,error_3000_l, color = 'lightcoral', label ="3000mV linear")


plt.grid(True)
plt.ylim(-10, 10)
plt.legend()
plt.show()
    