import numpy as np
import matplotlib.pyplot as plt

LUT_x_3200_10h_15h =       [3278,3192,3185,3196,3188,3225,3231,3189,3205,3182,3207,3179,3182,3183]

etat_art_x_3200_10h_15h  = [3352,3221,3288,3287,3316,3320,3334,3330,3332,3332,3296,3310,3320,3327,3327]

etat_20s_10h_15h =         [3248,3232,3238,3256,3256,3263,3240,3259,3266,3266,3269,3262,3207,3236,3245]

LUT_high_current =         [3309,3141,3197,3250,3244,3214,3285,3091,3303,3176,3221,3226,3306,3271,3267]

LUT_x_3200_14h_15h = [3258,3202,3242,3242,3190,3198,3184,3167,3199,3167,3161,3154,3182,3179]

etat_art_x_3200_14h_15h  = [3334,3331,3249,3315,3323,3323,3326,3287,3309,3305,3303,3328,3332,3329,3341]

LUT_y_3200_10h_15h = []
LUT_y_3200_14h_15h = []
etat_art_y_3200_10h_15h = []
etat_art_y_3200_14h_15h = []
etat_art_20s_y_3200_10h_15h = []
LUT_y_high_current = []

for i in range (len(LUT_x_3200_10h_15h)):
    LUT_y_3200_10h_15h.append(3200)
    
for i in range (len(LUT_x_3200_14h_15h)):
    LUT_y_3200_14h_15h.append(3200)
    
for i in range (len(etat_art_x_3200_10h_15h)):
    etat_art_y_3200_10h_15h.append(3200)
    
for i in range (len(etat_art_x_3200_14h_15h)):
    etat_art_y_3200_14h_15h.append(3200)

for i in range (len(etat_20s_10h_15h)):
    etat_art_20s_y_3200_10h_15h.append(3200)

for i in range (len(LUT_high_current)):
    LUT_y_high_current.append(3200)


plt.figure()   
plt.scatter(etat_art_x_3200_10h_15h, etat_art_y_3200_10h_15h, s=10, color = 'darkred', label = "60s interval - 10h - 15h")     
plt.scatter(LUT_x_3200_10h_15h, LUT_y_3200_10h_15h, s=10, color = 'navy', label = "LUT prediction - 10h - 15h") 

plt.scatter(etat_art_x_3200_14h_15h, etat_art_y_3200_14h_15h, s=10, color = 'salmon', label = "60s interval - 14h - 15h") 
plt.scatter(LUT_x_3200_14h_15h, LUT_y_3200_14h_15h, s=10, color = 'dodgerblue', label = "LUT prediction - 14h - 15h") 

plt.scatter(etat_20s_10h_15h, etat_art_20s_y_3200_10h_15h, s=10, color = 'green', label = "20s interval - 10h - 15h") 

plt.grid(True)

# Add labels and title
plt.xlabel('Actual value (mV)')
plt.ylabel('Expected value(mV)')
# plt.title('Expected value of 3100mV')
plt.xlim(3000, 3500)
plt.ylim(3000, 3500)

plt.vlines(3200,0, 3200, colors='k', linewidths=0.5, linestyles='--')

plt.hlines(3200,0, 3200, colors='k', linewidths=0.5, linestyles='--')
plt.annotate('3200', xy=(0, 3200), xytext=(-85, 3225),
             ha='center', va='top')

plt.legend()



plt.figure()   
plt.scatter(LUT_high_current,LUT_y_high_current, s=10, color = 'dodgerblue', label = "1.5x current")     
plt.scatter(LUT_x_3200_10h_15h, LUT_y_3200_10h_15h, s=10, color = 'salmon', label = "Regular current") 

plt.grid(True)

# Add labels and title
plt.xlabel('Actual value (mV)')
plt.ylabel('Expected value(mV)')
plt.xlim(3000, 3500)
plt.ylim(3000, 3500)

plt.vlines(3200,0, 3200, colors='k', linewidths=0.5, linestyles='--')

plt.hlines(3200,0, 3200, colors='k', linewidths=0.5, linestyles='--')
plt.annotate('3200', xy=(0, 3200), xytext=(-85, 3225),
             ha='center', va='top')

plt.legend()


error_3200_LUT = []
error_3200_LUT_2 = []
error_3200_60s = []
error_3200_60s_2 = []
error_3200_20s = []
error_hc = []

x = []

for i in range (len(LUT_x_3200_14h_15h)):
    error_3200_LUT.append((LUT_x_3200_10h_15h[i] - 3200)/32)
    
for i in range (len(LUT_x_3200_14h_15h)):
    error_3200_LUT_2.append((LUT_x_3200_14h_15h[i] - 3200)/32)
    x.append(i+1)   
     
for i in range (len(LUT_x_3200_14h_15h)):
    error_3200_60s.append((etat_art_x_3200_10h_15h[i] - 3200)/32)
       
for i in range (len(LUT_x_3200_14h_15h)):
    error_3200_60s_2.append((etat_art_x_3200_14h_15h[i] - 3200)/32)
 
for i in range (len(LUT_x_3200_14h_15h)):
    error_3200_20s.append((etat_20s_10h_15h[i] - 3200)/32)

for i in range (len(LUT_x_3200_14h_15h)):
    error_hc.append((LUT_high_current[i] - 3200)/32)


plt.figure()   

# plt.plot(x,error_3200_LUT_2, color = 'dodgerblue', label ="LUT prediction - 14h - 15h")
plt.plot(x,error_3200_60s, color = 'red', label ="60s interval")
# plt.plot(x,error_3200_60s_2, color = 'salmon', label ="20s interval - 14h - 15h")
plt.plot(x,error_3200_20s, color = 'orange', label ="20s interval")
plt.plot(x,error_3200_LUT, color = 'gold', label ="LUT prediction")
plt.plot(x,error_hc, color = 'dodgerblue', label ="LUT prediction - high current")


plt.grid(True)
plt.ylim(-10, 10)
plt.legend()


plt.figure()   

# Data for the bars

LUT_t_3200_10h_15h =      [188,110,110, 89, 84, 95, 65, 84, 84, 84, 84,102,102, 95]

etat_art_t_3200_10h_15h = [240,120,120,120,120,120,120,120,120,120,120,120,120,120]

etat_20s_t_3200_10h_15h = [200,120,120,120,120,100, 80,100,100,100,100,120,100,100]

actual_time_10h_15h =     [154,117,104,102, 79, 79, 70, 77, 92, 95, 87, 90, 91,102]

LUT_t_3200_14h_15h =      [121, 84, 80, 80, 71, 82, 71, 78, 66, 66 , 72, 68, 74,65]
    
etat_art_t_3200_14h_15h = [180,120,120,120,120,120,120,120,120,120,120,120,120,120]



categories = ['1', '2', '3','4', '5', '6','7', '8', '9','10', '11', '12','13', '14']

# Set the positions of the bars on the x-axis
x = np.arange(len(etat_art_t_3200_14h_15h))
width = 0.2  # Width of the bars

# Plot the bars

plt.bar(x - width*1.5, etat_art_t_3200_10h_15h, width, color = 'red', label = "60s interval")
plt.bar(x - width/2, etat_20s_t_3200_10h_15h, width,  color = 'orange', label = "20s interval") 
plt.bar(x + width/2, LUT_t_3200_10h_15h, width,  color = 'gold', label = "LUT prediction") 
plt.bar(x + width*1.5, actual_time_10h_15h, width,  color = 'dodgerblue', label = "Actual time") 

plt.title("Comparison of time taken to reach threshold")
plt.xlabel('Number of prediction')
plt.ylabel('Predicted time(s)')
plt.xticks(x, categories)
plt.legend()


# plt.figure()
# plt.bar(x - width/2, etat_art_t_3200_14h_15h, width, color = 'salmon', label = "60s interval") 
# plt.bar(x + width/2, LUT_t_3200_14h_15h, width, color = 'dodgerblue', label = "LUT prediction")  

# plt.title("14h - 15h")
# plt.xlabel('Number of prediction')
# plt.ylabel('Predicted time(s)')

# Set the x-axis ticks and labels
# plt.xticks(x, categories)
# plt.legend()

plt.show()

power_min = 2.24 #96 - practical consumption
power_max = 2.31 #99 - practical consumption

time_1 = []
time_2 = []

energy_1_min = []
energy_2_min = []

energy_1_max = []
energy_2_max = []


for i in range(len(LUT_t_3200_10h_15h)):
    time_1.append(etat_art_t_3200_10h_15h[i] - LUT_t_3200_10h_15h[i])
    time_2.append(etat_art_t_3200_14h_15h[i] - LUT_t_3200_14h_15h[i])

for i in range(len(LUT_t_3200_10h_15h)):
    energy_1_max.append(power_max*time_1[i])
    energy_1_min.append(power_min*time_1[i])
    energy_2_max.append(power_max*time_2[i])
    energy_2_min.append(power_min*time_2[i])


print(max(energy_1_max))
print(max(energy_2_max))

print(min(energy_1_min))
print(min(energy_2_min))

average1 = np.mean(energy_1_max)
average2 = np.mean(energy_2_max)
average3 = np.mean(energy_1_min)
average4 = np.mean(energy_2_min)

avg = (average1+average2+average3+average4)/4
print(avg)
    
print("10h - 15h at pmax: ",average1)
print("14h - 15h at pmax: ",average2)
print("10h - 15h at pmin: ",average3)
print("14h - 15h at pmin: ",average4)



# LUT_x_3200_10h_15h = [3278,3192,3185,3196,3188,3225,3231,3189,3205,3182,3207,3179,3182,3183,3151,3222,3215,3195,3234]

# LUT_x_3200_14h_15h = [3258,3202,3242,3242,3190,3198,3184,3167,3199,3167,3161,3154,3182,3179]


# etat_art_x_3200_10h_15h  = [3352,3221,3288,3287,3316,3320,3334,3330,3332,3332,3296,3310,3320,3327,3327,3317,3213]

# etat_art_x_3200_14h_15h  = [3334,3331,3249,3315,3323,3323,3326,3287,3309,3305,3303,3328,3332,3329,3341]
