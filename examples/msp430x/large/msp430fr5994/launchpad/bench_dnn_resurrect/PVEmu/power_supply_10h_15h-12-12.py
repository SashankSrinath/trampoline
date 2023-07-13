import PVEmu
import time

pv=PVEmu.PVEmu()
pv.connectToSupply()
pv.identification()
pv.setLogInterval(.05)        #log each 50ms
pv.setVoltageOffset(0.7)      #voltage offset due to the diode at output
pv.start(3.3 ,0.004)          # start thread: 3.3V, 0.001A
time.sleep(5)

pv.setOperatingPoint(3.9,0.002)
time.sleep(1)

pv.setOperatingPoint(3.9,0.001)
time.sleep(1)

pv.setOperatingPoint(3.9,0.001)
time.sleep(156)

pv.setOperatingPoint(3.9,0.002)
time.sleep(39)

pv.setOperatingPoint(3.9,0.001)
time.sleep(75)

pv.setOperatingPoint(3.9,0.002)
time.sleep(8)

pv.setOperatingPoint(3.9,0.001)
time.sleep(321)

pv.setOperatingPoint(3.9,0.002)
time.sleep(16)

pv.setOperatingPoint(3.9,0.003)
time.sleep(21)

pv.setOperatingPoint(3.9,0.002)
time.sleep(11)

pv.setOperatingPoint(3.9,0.003)
time.sleep(12)

pv.setOperatingPoint(3.9,0.002)
time.sleep(53)

pv.setOperatingPoint(3.9,0.003)
time.sleep(22)

pv.setOperatingPoint(3.9,0.004)
time.sleep(19)

pv.setOperatingPoint(3.9,0.005)
time.sleep(4)

pv.setOperatingPoint(3.9,0.004)
time.sleep(22)

pv.setOperatingPoint(3.9,0.003)
time.sleep(21)

pv.setOperatingPoint(3.9,0.002)
time.sleep(63)

pv.setOperatingPoint(3.9,0.003)
time.sleep(68)

pv.setOperatingPoint(3.9,0.004)
time.sleep(38)

pv.setOperatingPoint(3.9,0.005)
time.sleep(9)

pv.setOperatingPoint(3.9,0.004)
time.sleep(6)

pv.setOperatingPoint(3.9,0.005)
time.sleep(29)

pv.setOperatingPoint(3.9,0.006)
time.sleep(15)

pv.setOperatingPoint(3.9,0.007)
time.sleep(12)

pv.setOperatingPoint(3.9,0.006)
time.sleep(3)

pv.setOperatingPoint(3.9,0.007)
time.sleep(14)

pv.setOperatingPoint(3.9,0.006)
time.sleep(14)

pv.setOperatingPoint(3.9,0.007)
time.sleep(31)

pv.setOperatingPoint(3.9,0.008)
time.sleep(24)

pv.setOperatingPoint(3.9,0.007)
time.sleep(22)

pv.setOperatingPoint(3.9,0.008)
time.sleep(8)

pv.setOperatingPoint(3.9,0.007)
time.sleep(3)

pv.setOperatingPoint(3.9,0.006)
time.sleep(3)

pv.setOperatingPoint(3.9,0.005)
time.sleep(14)

pv.setOperatingPoint(3.9,0.004)
time.sleep(16)

pv.setOperatingPoint(3.9,0.005)
time.sleep(4)

pv.setOperatingPoint(3.9,0.006)
time.sleep(3)

pv.setOperatingPoint(3.9,0.004)
time.sleep(56)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(3)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(1)

pv.setOperatingPoint(3.9,0.005)
time.sleep(18)

pv.setOperatingPoint(3.9,0.004)
time.sleep(518)

pv.setOperatingPoint(3.9,0.002)
time.sleep(304)

pv.setOperatingPoint(3.9,0.003)
time.sleep(85)

pv.setOperatingPoint(3.9,0.002)
time.sleep(23)

pv.setOperatingPoint(3.9,0.003)
time.sleep(533)

pv.setOperatingPoint(3.9,0.002)
time.sleep(255)

pv.stop()                     # close connection
pv.showLogs()                 # also available with in list: pv.log
