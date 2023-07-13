#! /usr/bin/env python3
# -*- coding: UTF-8 -*-
import time
import sys
import threading

# some code from http://www.pinon-hebert.fr/Knowledge/index.php/TENMA_72_2705

class PVEmu:
    """ class to emulate a PV+MPPT, 
    based on the TENMA programmable power supply
    """

    def __init__(self):
        self.ps = None                   # handler to the serial port
        self.logInterval = 0.100         # duration between logs, in s
        self.log = []                    # tuple (date(s), voltage ,current, actualVoltage, actualCurrent)
        self.voltageSetpoint = 0.0       # V
        self.currentSetpoint = 0.0       # I
        self.voltageOffset = 0.0
        self.currentOffset = 0.0
        
        self.mainThread = None           #Thread handler.
        self.dataLock = threading.Lock()
        self.run = False                 #thread is running

    def connectToSupply(self):
        self.ps = None
        try:
            import serial
            import serial.tools.list_ports
        except ImportError:
            print("The 'serial' python package is not installed");
            print("Please install first the package (Linux, Mac, Win, …)")
            print("here: https://pythonhosted.org/pyserial/index.html")
            sys.exit(1)
        #find ports...
        ports = serial.tools.list_ports.comports()
        devicesPS = [port.device for port in ports if port.product == 'USB Virtual COM']
        if len(devicesPS) != 1:
            if len(devicesPS) > 1:
                print("Too many power supplies detected!")
            else:
                print("No power supply detected!")
            sys.exit(1)
        #... and connect to it.
        try:
            self.ps = serial.Serial(port=devicesPS[0], baudrate=115200, timeout=1)
            #we flush the input buffer.
            # https://stackoverflow.com/questions/7266558/pyserial-buffer-wont-flush
            time.sleep(0.2)
            self.ps.reset_input_buffer()
            #no output for now
            self.setOutput(False)
        except serial.serialutil.SerialException:
            print('Serial line {0} not found'.format(device[0]))
            sys.exit(1)

    def checkconnected(self):
        if not self.ps:
            sys.stderr.write ("ERROR: you should first connect to the power supply")
            sys.exit(1)
        elif not self.ps.isOpen():
            sys.stderr.write ("ERROR: try to work on closed port "+self.ps.name()+"\n")
            sys.exit(1)

    def setVoltageOffset(self,offset):
        self.voltageOffset = offset

    def setCurrentOffset(self,offset):
        self.currentOffset = offset

    def setOperatingPoint(self,voltage, current):
        self.checkconnected()
        with self.dataLock:
            self.voltageSetpoint = voltage + self.voltageOffset
            self.currentSetpoint = current + self.currentOffset
        s='VSET1:'+str(voltage)+'\n'
        self.ps.write(s.encode())
        s='ISET1:'+str(current)+'\n'
        self.ps.write(s.encode())

    def getOperatingPoint(self):
        self.checkconnected()
        self.ps.flush()
        self.ps.write('VOUT1?\n'.encode())
        while self.ps.inWaiting() < 4: #wait response
            pass
        V = self.ps.read(self.ps.inWaiting())
        self.ps.write('IOUT1?\n'.encode())
        while self.ps.inWaiting() < 4: #wait response
            pass
        I = self.ps.read(self.ps.inWaiting())
        return (float(V),float(I))

    def reset(self):
        self.checkconnected()
        self.ps.write(b'*RST\n')

    def identification(self):
        self.checkconnected()
        self.ps.flush()
        self.ps.write('*IDN?\n'.encode())
        while self.ps.inWaiting() < 28: #wait response
            pass
        idn = self.ps.read(self.ps.inWaiting())
        print('power supply: '+idn.decode(),end='')

    def setOutput(self,state):
        self.checkconnected()
        self.ps.flush()
        if state:
            self.ps.write('OUT1\n'.encode())
        else:
            self.ps.write('OUT0\n'.encode())

    def showLogs(self):
        """ logs: time, Vcur,Icur,Vref,Iref
        """
        from matplotlib import pyplot as plt
        #It uses the starred expression to unpack the list.
        with self.dataLock:
            time,Vmes,Imes,Vref,Iref=zip(*self.log)
        plt.plot(time,Vmes,ls='-')
        plt.plot(time,Imes,ls='-')
        plt.plot(time,Vref,linestyle='dashed')
        plt.plot(time,Iref,linestyle='dashed')
        plt.xlabel('time')
        plt.ylabel('voltage/current')
        plt.show()

    def setLogInterval(self,duration):
        """ define the duration between 2 logs
        If the duration is too low, the thread witll go as fast as possible.
        """
        with self.dataLock:
            self.logInterval = duration

    def start(self, Vinit, Iinit):
        if self.mainThread:
            sys.stderr.write('ERROR: power supply already started!')
        else:
            # setup ..
            self.connectToSupply()
            self.setOperatingPoint(Vinit+self.voltageOffset,Iinit)
            self.setOutput(True)
            self.log = []
            # .. and run
            self.mainThread = threading.Thread(target=self.mainLoop)
            self.run = True
            self.mainThread.start()

    def stop(self):
        self.run = False

    def mainLoop(self):
        startDate = time.time()
        deadline = startDate+self.logInterval
        while self.run:
            #periodicity
            time.sleep(max(0,deadline-time.time()))
            deadline += self.logInterval
            #measure
            (Vcur,Icur) = self.getOperatingPoint()
            #log
            with self.dataLock:
                self.log.append((time.time()-startDate,Vcur,Icur,self.voltageSetpoint,self.currentSetpoint))
        #closing…
        self.setOutput(False)
        self.ps.close()
        self.mainThread = None
