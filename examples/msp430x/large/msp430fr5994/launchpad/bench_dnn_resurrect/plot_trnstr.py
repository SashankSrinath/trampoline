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

for i in range(0,105):
    vv.append(1.8 + 3.300 * ( 1 - np.exp( -(i * ((2.3-1.9)/20) / 3.5 ))))
    xx.append(i)
 
x = np.arange(105, 135, 1)

# Generate y values for the straight line
y = np.linspace(vv[-1], 1.9, len(x))

vv2 = []
xx2 = []

for i in range(len(x)):
    
    vv2.append(y[i])   
    xx2.append(x[i])
 
vv3 = []
xx3 = []

for i in range(0,125):
    vv3.append(1.9 + 3.300 * ( 1 - np.exp( -(i * ((2.2-1.9)/20) / 3.5 ))))
    xx3.append(i+135)

x = np.arange(260, 290, 1)

# Generate y values for the straight line
y = np.linspace(vv3[-1], 1.9, len(x))

vv4 = []
xx4 = []

for i in range(len(x)):
    
    vv4.append(y[i])   
    xx4.append(x[i])
        
plt.plot(xx, vv, 'b', label='Capacitor charging')
plt.plot(xx2, vv2, 'b--', label='Capacitor discharging')
plt.plot(xx3, vv3, 'b')
plt.plot(xx4, vv4, 'b--')
plt.legend()
plt.xlabel('Time (s)')
plt.ylabel('Voltage (V)')
plt.grid(True)

plt.show()