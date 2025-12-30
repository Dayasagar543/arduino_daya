from vpython import *
import serial
import time 
import numpy as np


#null dimentions or position
origin=0
#arduino object
# arduino_Data=serial.Serial("COM4",9600)

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
    # while arduino_Data.in_waiting==0:
        pass