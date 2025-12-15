from vpython import *
import serial
from time import *

arduino_obj = serial.Serial("COM4", 9600)
sleep(1)

while True:
    while arduino_obj.in_waiting == 0:
        pass
    
    data_read=arduino_obj.readline()
    data_read=str(data_read,'utf-8')
    data_read=data_read.strip('\r\n')
    data_read=data_read.split(" ")
    data_read=int(data_read[0])
    print(data_read)


    # value1=int(data_read[2])
    # print(value1)
    # value2=int(data_read[5])
    # print(value2)
    # value3=int(data_read[8])
    # print(value3)

    # value1=float(data_read[2])
    # print(value1)
    # value2=float(data_read[5])
    # print(value2)
    # value3=float(data_read[8])
    # print(value3)
    # print("the value is ",value1,"the value2 is ",value2,"the value3 is ",value3)



