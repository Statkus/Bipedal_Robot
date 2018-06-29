#!/usr/bin/env python3

import serial
import tkinter as tk

def send_values(self):
    S1 = 1528 + s1.get()
    S2 = 1431 + s2.get()
    S3 = 1488 + s3.get()
    S4 = 1545 + s4.get()
    S5 = 1530 + s5.get()
    S6 = 1552 + s6.get()
    S7 = 1444 + s7.get()
    S8 = 1519 + s8.get()
    S9 = 1558 + s9.get()
    S10 = 1518 + s10.get()
    S11 = 1544 + s11.get()
    S12 = 1634 + s12.get()

    sliders = [s1.get(), \
               s2.get(), \
               s3.get(), \
               s4.get(), \
               s5.get(), \
               s6.get(), \
               s7.get(), \
               s8.get(), \
               s9.get(), \
               s10.get(), \
               s11.get(), \
               s12.get()]

    print(sliders)

    bytes_to_send = [10, 69, int(S1 % 256), \
                             int((S1 - (S1 % 256)) / 256), \
                             int(S2 % 256), \
                             int((S2 - (S2 % 256)) / 256), \
                             int(S3 % 256), \
                             int((S3 - (S3 % 256)) / 256), \
                             int(S4 % 256), \
                             int((S4 - (S4 % 256)) / 256), \
                             int(S5 % 256), \
                             int((S5 - (S5 % 256)) / 256), \
                             int(S6 % 256), \
                             int((S6 - (S6 % 256)) / 256), \
                             int(S7 % 256), \
                             int((S7 - (S7 % 256)) / 256), \
                             int(S8 % 256), \
                             int((S8 - (S8 % 256)) / 256), \
                             int(S9 % 256), \
                             int((S9 - (S9 % 256)) / 256), \
                             int(S10 % 256), \
                             int((S10 - (S10 % 256)) / 256), \
                             int(S11 % 256), \
                             int((S11 - (S11 % 256)) / 256), \
                             int(S12 % 256), \
                             int((S12 - (S12 % 256)) / 256), \
                             0]

    CRC = 0
    for i in range(2, 26):
        CRC = CRC ^ bytes_to_send[i]

    bytes_to_send[26] = int(CRC)

    print(bytes_to_send)
    ser.write(bytes_to_send)

def set_from_text():
    string_values = e.get()

    string_values = string_values.replace("[", "")
    string_values = string_values.replace("]", "")
    string_values = string_values.replace(" ", "")

    values_list = [int(e) if e.isdigit() else e for e in string_values.split(',')]

    s1.set(values_list[0])
    s2.set(values_list[1])
    s3.set(values_list[2])
    s4.set(values_list[3])
    s5.set(values_list[4])
    s6.set(values_list[5])
    s7.set(values_list[6])
    s8.set(values_list[7])
    s9.set(values_list[8])
    s10.set(values_list[9])
    s11.set(values_list[10])
    s12.set(values_list[11])

ser = serial.Serial('/dev/ttyUSB0', 115200)

root = tk.Tk()
root.title("Servo slider controller")

servo_name=tk.Label(root, text="Servo 1")
servo_name.pack()

s1 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s1.set(0)
s1.pack()

servo_name=tk.Label(root, text="Servo 2")
servo_name.pack()

s2 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s2.set(0)
s2.pack()

servo_name=tk.Label(root, text="Servo 3")
servo_name.pack()

s3 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s3.set(0)
s3.pack()

servo_name=tk.Label(root, text="Servo 4")
servo_name.pack()

s4 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s4.set(0)
s4.pack()

servo_name=tk.Label(root, text="Servo 5")
servo_name.pack()

s5 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s5.set(0)
s5.pack()

servo_name=tk.Label(root, text="Servo 6")
servo_name.pack()

s6 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s6.set(0)
s6.pack()

servo_name=tk.Label(root, text="Servo 7")
servo_name.pack()

s7 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s7.set(0)
s7.pack()

servo_name=tk.Label(root, text="Servo 8")
servo_name.pack()

s8 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s8.set(0)
s8.pack()

servo_name=tk.Label(root, text="Servo 9")
servo_name.pack()

s9 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s9.set(0)
s9.pack()

servo_name=tk.Label(root, text="Servo 10")
servo_name.pack()

s10 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s10.set(0)
s10.pack()

servo_name=tk.Label(root, text="Servo 11")
servo_name.pack()

s11 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s11.set(0)
s11.pack()

servo_name=tk.Label(root, text="Servo 12")
servo_name.pack()

s12 = tk.Scale(root, from_=-500, to=500, length=600, orient=tk.HORIZONTAL, command=send_values)
s12.set(0)
s12.pack()

e = tk.Entry(root)
e.pack()

b = tk.Button(root, text="Write value", width=20, command=set_from_text)
b.pack()

tk.mainloop()

ser.close()
