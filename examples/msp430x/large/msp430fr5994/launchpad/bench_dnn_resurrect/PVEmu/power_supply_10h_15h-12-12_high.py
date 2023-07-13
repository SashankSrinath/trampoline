import PVEmu
import time

pv=PVEmu.PVEmu()
pv.connectToSupply()
pv.identification()
pv.setLogInterval(.05)        #log each 50ms
pv.setVoltageOffset(0.7)      #voltage offset due to the diode at output
pv.start(3.3 ,0.004)          # start thread: 3.3V, 0.001A
time.sleep(5)

pv.setOperatingPoint(3.9,0.003)
time.sleep(1)

pv.setOperatingPoint(3.9,0.001)
time.sleep(1)

pv.setOperatingPoint(3.9,0.001)
time.sleep(16)

pv.setOperatingPoint(3.9,0.002)
time.sleep(18)

pv.setOperatingPoint(3.9,0.001)
time.sleep(48)

pv.setOperatingPoint(3.9,0.002)
time.sleep(19)

pv.setOperatingPoint(3.9,0.001)
time.sleep(17)

pv.setOperatingPoint(3.9,0.002)
time.sleep(41)

pv.setOperatingPoint(3.9,0.003)
time.sleep(34)

pv.setOperatingPoint(3.9,0.002)
time.sleep(11)

pv.setOperatingPoint(3.9,0.001)
time.sleep(23)

pv.setOperatingPoint(3.9,0.002)
time.sleep(24)

pv.setOperatingPoint(3.9,0.001)
time.sleep(5)

pv.setOperatingPoint(3.9,0.002)
time.sleep(36)

pv.setOperatingPoint(3.9,0.001)
time.sleep(307)

pv.setOperatingPoint(3.9,0.003)
time.sleep(12)

pv.setOperatingPoint(3.9,0.004)
time.sleep(19)

pv.setOperatingPoint(3.9,0.005)
time.sleep(1)

pv.setOperatingPoint(3.9,0.004)
time.sleep(7)

pv.setOperatingPoint(3.9,0.003)
time.sleep(6)

pv.setOperatingPoint(3.9,0.004)
time.sleep(18)

pv.setOperatingPoint(3.9,0.003)
time.sleep(25)

pv.setOperatingPoint(3.9,0.002)
time.sleep(2)

pv.setOperatingPoint(3.9,0.003)
time.sleep(3)

pv.setOperatingPoint(3.9,0.002)
time.sleep(5)

pv.setOperatingPoint(3.9,0.003)
time.sleep(14)

pv.setOperatingPoint(3.9,0.004)
time.sleep(4)

pv.setOperatingPoint(3.9,0.005)
time.sleep(8)

pv.setOperatingPoint(3.9,0.004)
time.sleep(8)

pv.setOperatingPoint(3.9,0.005)
time.sleep(4)

pv.setOperatingPoint(3.9,0.006)
time.sleep(15)

pv.setOperatingPoint(3.9,0.007)
time.sleep(13)

pv.setOperatingPoint(3.9,0.006)
time.sleep(14)

pv.setOperatingPoint(3.9,0.005)
time.sleep(6)

pv.setOperatingPoint(3.9,0.004)
time.sleep(20)

pv.setOperatingPoint(3.9,0.003)
time.sleep(53)

pv.setOperatingPoint(3.9,0.004)
time.sleep(61)

pv.setOperatingPoint(3.9,0.005)
time.sleep(29)

pv.setOperatingPoint(3.9,0.006)
time.sleep(14)

pv.setOperatingPoint(3.9,0.007)
time.sleep(29)

pv.setOperatingPoint(3.9,0.008)
time.sleep(7)

pv.setOperatingPoint(3.9,0.007)
time.sleep(13)

pv.setOperatingPoint(3.9,0.008)
time.sleep(5)

pv.setOperatingPoint(3.9,0.009)
time.sleep(12)

pv.setOperatingPoint(3.9,0.010)
time.sleep(33)

pv.setOperatingPoint(3.9,0.009)
time.sleep(10)

pv.setOperatingPoint(3.9,0.010)
time.sleep(11)

pv.setOperatingPoint(3.9,0.011)
time.sleep(28)

pv.setOperatingPoint(3.9,0.012)
time.sleep(16)

pv.setOperatingPoint(3.9,0.011)
time.sleep(27)

pv.setOperatingPoint(3.9,0.012)
time.sleep(3)

pv.setOperatingPoint(3.9,0.011)
time.sleep(4)

pv.setOperatingPoint(3.9,0.010)
time.sleep(2)

pv.setOperatingPoint(3.9,0.009)
time.sleep(2)

pv.setOperatingPoint(3.9,0.008)
time.sleep(12)

pv.setOperatingPoint(3.9,0.007)
time.sleep(3)

pv.setOperatingPoint(3.9,0.006)
time.sleep(15)

pv.setOperatingPoint(3.9,0.007)
time.sleep(2)

pv.setOperatingPoint(3.9,0.008)
time.sleep(2)

pv.setOperatingPoint(3.9,0.009)
time.sleep(3)

pv.setOperatingPoint(3.9,0.006)
time.sleep(5)

pv.setOperatingPoint(3.9,0.007)
time.sleep(13)

pv.setOperatingPoint(3.9,0.006)
time.sleep(17)

pv.setOperatingPoint(3.9,0.007)
time.sleep(99)

pv.setOperatingPoint(3.9,0.006)
time.sleep(326)

pv.setOperatingPoint(3.9,0.007)
time.sleep(92)

pv.setOperatingPoint(3.9,0.006)
time.sleep(48)

pv.setOperatingPoint(3.9,0.003)
time.sleep(221)

pv.setOperatingPoint(3.9,0.004)
time.sleep(756)

pv.setOperatingPoint(3.9,0.003)
time.sleep(223)

pv.stop()                     # close connection
pv.showLogs()                 # also available with in list: pv.log
