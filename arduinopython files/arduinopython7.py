from vpython import *
import serial
import time 
import numpy as np

time.sleep(2)
#arduino object
arduino_Data=serial.Serial("COM4",9600)

#null dimentions or position
origin=0

# thermometer bulb and the bar for temperature measuremnet
opacity=0.2

#bulb
outer_bulb_radius=1
bulb=sphere(pos=vector(origin,origin,origin),color=color.white,radius=outer_bulb_radius,opacity=opacity)
inner_bulb_radius=0.6
bulb=sphere(pos=vector(origin,origin,origin),color=color.red,radius=inner_bulb_radius)

#cylinder
cylinder_length=5
outer_cylinder_radius=.5
inner_cylinder_radius=.3
axis_value=1
ypos=0.0
outer_cylinder=cylinder(pos=vector(origin,ypos,origin),color=color.white,length=cylinder_length,radius=outer_cylinder_radius,axis=vector(origin,axis_value,origin),opacity=opacity)
thermo_cylinder=cylinder(pos=vector(origin,ypos,origin),color=color.red,length=cylinder_length,radius=inner_cylinder_radius,axis=vector(origin,axis_value,origin))

while True :
    while arduino_Data.in_waiting==0:
        pass
    data_packet=arduino_Data.readline()
    data_packet = data_packet.decode('utf-8', errors='ignore')
    data_packet=data_packet.strip("\r\n")
    data_packet=data_packet.split(" ")
    temperature_c=data_packet[5]
    print(temperature_c)
    temperature_f=data_packet[11]
    print(temperature_f)
    humidity=data_packet[15]
    print(humidity)

    # print(data_packet)