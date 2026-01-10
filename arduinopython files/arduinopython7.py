from vpython import *
import serial
import time 
import numpy as np

time.sleep(1)
#arduino object
# arduino_Data=serial.Serial("COM4",9600)
arduino_Data=serial.Serial("COM3",9600)

#null dimentions or position
origin=0

# thermometer bulb and the bar for temperature measuremnet
opacity=0.2

#bulb
outer_bulb_radius=1
bulb=sphere(pos=vector(origin,origin,origin),color=color.white,radius=outer_bulb_radius,opacity=opacity)
inner_bulb_radius=0.8
bulb=sphere(pos=vector(origin,origin,origin),color=color.red,radius=inner_bulb_radius)

#cylinder
cylinder_length=6
outer_cylinder_radius=.5
inner_cylinder_radius=.3
axis_value=1
ypos=0.0
outer_cylinder=cylinder(pos=vector(origin,ypos,origin),color=color.white,length=cylinder_length,radius=outer_cylinder_radius,axis=vector(origin,axis_value,origin),opacity=opacity)

temperature_thermo=1
thermo_cylinder=cylinder(pos=vector(origin,ypos,origin),color=color.red,length=temperature_thermo,radius=inner_cylinder_radius,axis=vector(origin,axis_value,origin))
time.sleep(1)
while True :
    while arduino_Data.in_waiting==0:
        pass
    data_packet=arduino_Data.readline()
    data_packet = data_packet.decode('utf-8', errors='ignore')
    data_packet=data_packet.strip("\r\n")
    data_packet=data_packet.split(" ")
    
    # print(data_packet) 
    print(data_packet)
    
    # reading the temperature for the string and typecasting the numerical values to float
    temperature_thermo=1                                                                                        
    temperature_c=data_packet[5]
    temperature_c=float(temperature_c)
    temperature_f=float(data_packet[11])
    humidity=float(data_packet[15])
    
    #input temperature formual for temperature reading
    input_temperature=(5/115)*temperature_f+1
    input_temperature=round(input_temperature,2)
    # print(input_temperature)
    thermo_cylinder.length=input_temperature
    thermo_cylinder.length=round(thermo_cylinder.length,2)
    # print(thermo_cylinder.length)
    
    
    #printing the value of the serial data
    # print("the temperature is centigrade is "+temperature_c)
    # print("the temperature is farenite is "+ str(temperature_f))
    # print("the humidity is "+str(humidity))
   
