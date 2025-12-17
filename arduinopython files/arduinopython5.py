from vpython import *
import serial
from  time  import *
import numpy as np


arrow_length=5
arrow_width=.09

object_serial=serial.Serial("COM4",9600)
# label_values=label(text="0V",color=color.yellow,pos=vector(0,1,0))
label_values=label(text="0V",color=color.yellow,pos=vector(0,1.7,0))
label_values.border=False
label.width=5
label.height=5
voltage_Reader_needle=arrow(length=arrow_length,shaftwidth=arrow_width,color=color.red,axis=vector(-1,0,0))

# box
xbox=15
ybox=6
zbox=0.5

background_box=box(color=color.white,size=vector(xbox,ybox,zbox),pos=vector(0,3,-2))
sleep(1)

while True:
    while object_serial.in_waiting==0:
         pass
   
    data_packet=object_serial.readline()
    data_packet=str(data_packet,"utf-8")
    data_packet=data_packet.strip('\r\n')
    data_packet=float(data_packet)
    data_packet=np.round(data_packet,2)
#     print(data_packet)
    angle=-2*np.pi/3069*data_packet+5*np.pi/6
    voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)
    voltage=(5./1023.)*data_packet
    voltage=np.round(voltage,2)
    print(voltage)
    label_values.text=str(voltage)
    label_values.pos=vector(cos(angle),sin(angle),0)

    
#     print("the voltage is",voltage)

#     for angle in np.linspace(5*np.pi/6,np.pi/6,150):
#          rate(10)
#      #     label_values.text=voltage
#          voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)

#     for angle in np.linspace(np.pi/6,5*np.pi/6,150):
#          rate(10)
#      #     label_values.text=voltage
#          voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)
    
#     for angle in np.linspace(0,np.pi,150):
#          rate(10)
#          voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)

   
    # for angle in np.linspace(np.pi,0,150):
    #      rate(10)
    #      voltage_Reader_needle.axis=vector(arrow_length*cos(angle),arrow_length*sin(angle),0)
       

     