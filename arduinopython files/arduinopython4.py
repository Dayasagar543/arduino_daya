from vpython import *
import serial
from time import *


tube=cylinder(radius=0.7,length=0.01,color=color.red,axis=vector(0,1,0))
label_voltage=label(text="5 volts",box=False,pos=vector(0,0.5,0))
label_voltage.color=color.cyan
arduino_obj=serial.Serial("COM4",9600)
sleep(1)

while True:
    while arduino_obj.in_waiting==0:
        pass

    data_red=arduino_obj.readline()
    data_red=str(data_red,'utf-8')
    data_red=data_red.strip('\r\n')
    data_red=int(data_red)
    # print(data_red)
    voltage=(5./1023.)*data_red
    voltage=round(voltage,2)
   
    # print("voltage is ",voltage)
    if voltage==0:
        voltage=0.001
    tube.length=voltage
    label_voltage.text=str(voltage)


