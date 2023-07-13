#! /usr/bin/env python3
# -*- coding: UTF-8 -*-

import PVEmu
import time

pv=PVEmu.PVEmu()
pv.connectToSupply()
pv.identification()
pv.setLogInterval(.05)        #log each 50ms
pv.setVoltageOffset(0.65)       #voltage offset due to the diode at output
pv.start(3.3 ,0.006)            # start thread: 3.2V, 0.01A
time.sleep(180)

pv.setOperatingPoint(2.45,0.01) # another Irradiance ..
time.sleep(10)

# pv.setOperatingPoint(3.2, 0.001) #No charging to reduce the voltage
# time.sleep(175)

# pv.setOperatingPoint(0, 0.00) #No charging to reduce the voltage
# time.sleep(20)

# #for i in range(30):
# pv.setOperatingPoint(4, 0.004)
# time.sleep(150)
    

pv.stop()                     # close connection
pv.showLogs()                 # also available with in list: pv.log