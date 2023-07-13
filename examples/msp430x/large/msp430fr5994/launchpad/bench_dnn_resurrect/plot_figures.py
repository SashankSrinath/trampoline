import numpy as np
import matplotlib.pyplot as plt
# Set LaTeX font
plt.rcParams['text.usetex'] = True
plt.rcParams['text.latex.preamble'] = r'\usepackage{amsmath}'

# Constants
V0 = 1.8  # Initial voltage across the capacitor
VF = 3.6  # Final voltage across the capacitor
R = 100  # Resistance in the charging circuit
C = 0.5  # Capacitance of the capacitor

# Time values
start_time = 0
end_time = 150
num_points = 150
time = np.linspace(start_time, end_time, num_points)

# Calculate the time constant
tau = R * C

# Voltage across the capacitor over time
voltage = V0 + (VF - V0) * (1 - np.exp(-time / tau))

vv = []
xx = []
for i in range(-8,101):
    vv.append(1.941 + 3.300 * ( 1 - np.exp( -(i * ((2.31-1.941)/20) / 3.5 ))))
    xx.append(i+8)
 
# Split time and voltage arrays into two segments
time_segment0 = xx[:8]
time_segment1 = xx[8:28]
time_segment2 = xx[28:]

voltage_segment0 = vv[:8]
voltage_segment1 = vv[8:28]
voltage_segment2 = vv[28:]


# Plotting
# plt.plot(time_segment1, voltage_segment1, 'b-', label='Actual value')
# plt.plot(time_segment2, voltage_segment2, 'k--', label='Prediction')
# plt.xlabel('Time (s)')
# plt.ylabel('Voltage (V)')
# plt.grid(True)
# plt.show()

plt.plot(time_segment0, voltage_segment0, 'k--', label='Actual value')
plt.plot(time_segment1, voltage_segment1, 'b-', label='Actual value')
plt.plot(time_segment2, voltage_segment2, 'k--', label='Prediction')
plt.xlabel('Time (s)')
plt.ylabel('Voltage (V)')
plt.grid(True)


specific_t_values = [8, 28, 109]
specific_y_values = [1.941 + 3.300 * ( 1 - np.exp( -(t-8)* ((2.309-1.941)/20) / 3.5 ) ) for t in specific_t_values]

# # Draw markers
plt.plot(specific_t_values, specific_y_values, 'r.')
plt.vlines(8, 1.8, (1.941 + 3.300 * ( 1 - np.exp( -(0* ((2.309-1.941)/20) / 3.5 )))) , colors='k', linewidths=0.5, linestyles='--')
plt.vlines(28, 1.8,(1.941 + 3.300 * ( 1 - np.exp( -(20 * ((2.309-1.941)/20) / 3.5 )))), colors='k', linewidths=0.5, linestyles='--')
plt.vlines(109,1.8,3.3 , colors='k', linewidths=0.5, linestyles='--')

plt.hlines(3.3, 0, 109,colors='k', linewidths=0.5, linestyles='--')
plt.hlines(1.941, 0, 8,colors='k', linewidths=0.5, linestyles='--')
plt.hlines(2.27, 0, 28,colors='k', linewidths=0.5, linestyles='--')

plt.text(8, 1.77, '8', ha='center')
plt.text(28, 1.77, '28', ha='center')
plt.text(109, 1.77, '109', ha='center')

plt.text(-1.5, 3.29, '3.3V', ha='center')
plt.text(-1.5, 1.941, '1.9V', ha='center')
plt.text(-1.5, 2.27, '2.3V', ha='center')

# # Split time and voltage arrays into two segments
# time_segment1 = time[time <= 15]
# time_segment2 = time[time > 15]
# voltage_segment1 = voltage[time <= 15]
# voltage_segment2 = voltage[time > 15]

# specific_x_values = [5, 15]
# specific_y_values = [V0 + (VF - V0) * (1 - np.exp(-x / tau)) for x in specific_x_values]

# # Draw markers
# plt.plot(specific_x_values, specific_y_values, 'r.')

# plt.vlines(5, 1.8, V0 + (VF - V0) * (1 - np.exp(-5 / tau)), colors='k', linewidths=0.5, linestyles='--')
# plt.vlines(15, 1.8, V0 + (VF - V0) * (1 - np.exp(-15 / tau)), colors='k', linewidths=0.5, linestyles='--')
# plt.vlines(90, 1.8, V0 + (VF - V0) * (1 - np.exp(-90 / tau)), colors='k', linewidths=0.5, linestyles='--')


# plt.hlines(3.3, 0, 89.6,colors='k', linewidths=0.5, linestyles='--')
# plt.hlines(1.971, 0, 5,colors='k', linewidths=0.5, linestyles='--')
# plt.hlines(2.266, 0, 15,colors='k', linewidths=0.5, linestyles='--')

# plt.text(5, 1.77, '5 s', ha='center')
# plt.text(15, 1.77, '15 s', ha='center')
# plt.text(90, 1.77, '90 s', ha='center')

# # plt.text(50, 1.9, 't_pred', ha='center')

# plt.text(-1.5, 3.29, '3.3V', ha='center')
# plt.text(-1.5, 1.96, 'v[0]', ha='center')
# plt.text(-1.5, 2.255, 'v[1]', ha='center')


# plt.legend(loc='center right')
# plt.show()

# plt.plot(xx,vv)
# plt.xlabel('Time (s)')
# plt.ylabel('Voltage (V)')
# plt.grid(True)
# plt.show()

plt.show()