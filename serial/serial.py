# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import serial
import time
ser = serial.Serial("com4", 38400);
data1 = "office1"
data2 = "office2"
data3 = "offic12"
while True:
    ser.write(data1.encode());
    time.sleep(0.2)
    ser.write(data2.encode());
    time.sleep(0.2)
    ser.write(data3.encode())