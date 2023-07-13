import numpy as np

import argparse
import sys,csv

power_data = []
time = []
current_data = []

from_h = 10
to_h = 15
for i in range(from_h, to_h): # Hours
    for j in range(0,10):     # Minutes
        for k in range(0,60): # Seconds
            time.append("{:02}:{:02}:{:02}".format(i,j,k)) 
            
# print(time)   
date = 12
month = 12         
with open('Capture_{}-{}.csv'.format(date,month),'r') as csvfile:
        reader = csv.DictReader(csvfile)
        first_instance = None
        previous_value = None

        for row in reader:
            time_value = row['Time']
            try:
                if(row['Time'] in time):
                    if time_value != previous_value:
                        power_data.append(float(row["Power"]))   
                        # if(float(row["Power"])<3.3):
                        #     print(row)
                    previous_value = time_value
            except:
                pass
csvfile.close()

current_data = (np.divide(power_data, (1000 * 3.3))) # mW to W, then div by 3.3V

# current_data = 1.5 * np.array(current_data)

# print(len(current_data))
print("Max current : ",max(current_data))
print("Min current : ",min(current_data))

time_sleep = []
unique_current = []

count = 1 

for i in range(1, len(current_data)):
    current_data[i] = round(current_data[i],3)

for i in range(len(current_data)):    
    if current_data[i] == current_data[i-1]:
        count += 1
    else:
        time_sleep.append(count)
        unique_current.append(current_data[i-1])
        count = 1  # Reset count for the new element

time_sleep.append(count)  # Append the count for the last element
unique_current.append(current_data[-1])

# print(len(time_sleep))
print("Unique current values: ",len(unique_current))
with open('power_supply_{}h_{}h-{}-{}.py'.format(from_h,to_h, date, month),'w') as file:
    
    file.write("import PVEmu\nimport time\n\n")

    file.write("pv=PVEmu.PVEmu()\n")
    file.write("pv.connectToSupply()\n")
    file.write("pv.identification()\n")
    file.write("pv.setLogInterval(.05)        #log each 50ms\n")
    file.write("pv.setVoltageOffset(0.7)      #voltage offset due to the diode at output\n")
    file.write("pv.start(3.3 ,0.004)          # start thread: 3.3V, 0.001A\n")
    file.write("time.sleep(5)\n\n")

    for i in range(len(unique_current)):
        file.write('pv.setOperatingPoint(3.9,{:.3f})\n'.format(unique_current[i]))
        file.write('time.sleep({})\n\n'.format(time_sleep[i]))
        
    file.write("pv.stop()                     # close connection\n")
    file.write("pv.showLogs()                 # also available with in list: pv.log\n")

