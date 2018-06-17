#!/usr/bin/env python3

import serial
import tkinter as tk

def send_values(self):
    b = bytes([10, 69, int(s1.get()*0.255), \
                       int(s2.get()*0.255), \
                       int(s3.get()*0.255), \
                       int(s4.get()*0.255), \
                       int(s5.get()*0.255), \
                       int(s6.get()*0.255), \
                       int(s7.get()*0.255), \
                       int(s8.get()*0.255), \
                       int(s9.get()*0.255), \
                       int(s10.get()*0.255), \
                       int(s11.get()*0.255), \
                       int(s12.get()*0.255)])
    print (b)
    ser.write(b)



ser = serial.Serial('/dev/ttyUSB0', 115200)

root = tk.Tk()
root.title("Servo slider controller")

servo_name=tk.Label(root, text="Servo 1")
servo_name.pack()

s1 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s1.set(500)
s1.pack()

servo_name=tk.Label(root, text="Servo 2")
servo_name.pack()

s2 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s2.set(500)
s2.pack()

servo_name=tk.Label(root, text="Servo 3")
servo_name.pack()

s3 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s3.set(500)
s3.pack()

servo_name=tk.Label(root, text="Servo 4")
servo_name.pack()

s4 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s4.set(500)
s4.pack()

servo_name=tk.Label(root, text="Servo 5")
servo_name.pack()

s5 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s5.set(500)
s5.pack()

servo_name=tk.Label(root, text="Servo 6")
servo_name.pack()

s6 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s6.set(500)
s6.pack()

servo_name=tk.Label(root, text="Servo 7")
servo_name.pack()

s7 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s7.set(500)
s7.pack()

servo_name=tk.Label(root, text="Servo 8")
servo_name.pack()

s8 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s8.set(500)
s8.pack()

servo_name=tk.Label(root, text="Servo 9")
servo_name.pack()

s9 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s9.set(500)
s9.pack()

servo_name=tk.Label(root, text="Servo 10")
servo_name.pack()

s10 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s10.set(500)
s10.pack()

servo_name=tk.Label(root, text="Servo 11")
servo_name.pack()

s11 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s11.set(500)
s11.pack()

servo_name=tk.Label(root, text="Servo 12")
servo_name.pack()

s12 = tk.Scale(root, from_=0, to=1000, length=600, orient=tk.HORIZONTAL, command=send_values)
s12.set(500)
s12.pack()

tk.mainloop()

ser.close()
