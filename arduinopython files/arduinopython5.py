from vpython import *
import serial
from  time  import *
import numpy as np


arrow_length=5
arrow_width=.09

object_serial=serial.Serial("COM4",9600)
# label_values=label(text="values",color=color.green)
voltage_Reader_needle=arrow(length=arrow_length,shaftwidth=arrow_width,color=color.red,axis=vector(-1,0,0))
sleep(1)

while True:
    while object_serial.in_waiting==0:
         pass
     
    data_packet=object_serial.readline()
    data_packet=str(data_packet,"utf-8")
    data_packet=data_packet.strip('\r\n')
    print(data_packet)
    voltage=(5./1023.)*data_packet

    for angle in np.linspace(0,np.pi,150):
         rate(10)
         voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)

   
    # for angle in np.linspace(np.pi,0,150):
    #      rate(10)
    #      voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)
       

     