import PVEmu
import time

pv=PVEmu.PVEmu()
pv.connectToSupply()
pv.identification()
pv.setLogInterval(.05)        #log each 50ms
pv.setVoltageOffset(0.7)      #voltage offset due to the diode at output
pv.start(3.3 ,0.001)          # start thread: 3.3V, 0.001A
time.sleep(5)

pv.setOperatingPoint(4,0.004)
time.sleep(1)

pv.setOperatingPoint(4,0.004)
time.sleep(1)

pv.setOperatingPoint(4,0.004)
time.sleep(3599)

pv.stop()                     # close connection
pv.showLogs()                 # also available with in list: pv.log
