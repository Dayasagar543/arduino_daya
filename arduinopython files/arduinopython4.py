from vpython import *
import serial
from time import *


arduino_obj=serial.Serial("com4",9600)
sleep(1)
while True:
    while arduino_obj.in_waiting==0:
        pass
    data_red=arduino_obj.readline()
    data_red=str(data_red,'utf-8')
