import PVEmu
import time

pv=PVEmu.PVEmu()
pv.connectToSupply()
pv.identification()
pv.setLogInterval(.05)        #log each 50ms
pv.setVoltageOffset(0.7)      #voltage offset due to the diode at output
pv.start(3.3 ,0.004)          # start thread: 3.3V, 0.001A
time.sleep(5)

pv.setOperatingPoint(3.9,0.008)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(671)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(9)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(2)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(2)

pv.setOperatingPoint(3.9,0.005)
time.sleep(3)

pv.setOperatingPoint(3.9,0.004)
time.sleep(3)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(2)

pv.setOperatingPoint(3.9,0.005)
time.sleep(3)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(15)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(2)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(9)

pv.setOperatingPoint(3.9,0.004)
time.sleep(12)

pv.setOperatingPoint(3.9,0.005)
time.sleep(89)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(6)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(3)

pv.setOperatingPoint(3.9,0.004)
time.sleep(36)

pv.setOperatingPoint(3.9,0.005)
time.sleep(251)

pv.setOperatingPoint(3.9,0.006)
time.sleep(1248)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(10)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(9)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(9)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(2)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(1)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(2)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(1)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(5)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.006)
time.sleep(2)

pv.setOperatingPoint(3.9,0.007)
time.sleep(14)

pv.setOperatingPoint(3.9,0.006)
time.sleep(4)

pv.setOperatingPoint(3.9,0.007)
time.sleep(535)

pv.setOperatingPoint(3.9,0.008)
time.sleep(1)

pv.setOperatingPoint(3.9,0.007)
time.sleep(3)

pv.setOperatingPoint(3.9,0.008)
time.sleep(1)

pv.setOperatingPoint(3.9,0.007)
time.sleep(2)

pv.setOperatingPoint(3.9,0.008)
time.sleep(1)

pv.setOperatingPoint(3.9,0.007)
time.sleep(216)

pv.setOperatingPoint(3.9,0.008)
time.sleep(2)

pv.setOperatingPoint(3.9,0.007)
time.sleep(1)

pv.setOperatingPoint(3.9,0.008)
time.sleep(390)

pv.stop()                     # close connection
pv.showLogs()                 # also available with in list: pv.log
