#! /usr/bin/env python3
# -*- coding: UTF-8 -*-

import PVEmu
import time

pv=PVEmu.PVEmu()
pv.connectToSupply()
pv.identification()
pv.setLogInterval(.05)        #log each 50ms
pv.setVoltageOffset(.2)       #voltage offset due to the diode at output
pv.start(3.3,0.01)            # start thread: 3.3V, 0.01A
time.sleep(5)
pv.setOperatingPoint(3.3,0.5) # another Irradiance ..
time.sleep(5)
pv.stop()                     # close connection
pv.showLogs()                 # also available with in list: pv.log