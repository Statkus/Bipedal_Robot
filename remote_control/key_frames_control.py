#!/usr/bin/env python3

import serial
import tkinter as tk
import time

# Key frames
#frames = [[  53, -134,  190,  526, -380,   62, -132, -118,  294,  440,  -26,  -67], \
#          [ 254,   62,  442,  592, -380,  169, -118, -118,  294,  440,  -26,  -67], \
#          [ 371,  197,  442,  592, -380,  176,   33, -118,    0,  -33, -180,  -67], \
#          [ 386,   62,  442,  592, -380,  169,  271, -118,   25,  153,  -26,  -67], \
#          [ 350,  121,  442,  461, -380,  169,  121,  347,  -23,  153,  285,  118], \
#          [ 306,  109,  421,  461, -380,  169,  121,  347,  -23,  153,  285,  195], \
#          [ 180,  109,    0,  100, -130,  169,   50,  347, -200,    0,  200,   80], \
#\
#          [  67,   26, -440, -294,  118,  132,  -62,  380, -526, -190,  134,  -53], \
#          [  67,   26, -440, -294,  118,  118, -169,  380, -592, -442,  -62, -254], \
#          [  67, -180,   33,    0,  118,  -33, -176,  380, -592, -442, -197, -371], \
#          [  67,  -26, -153,  -25,  118, -271, -169,  380, -592, -442,  -62, -386], \
#          [-118, -285, -153,   23, -347, -121, -169,  380, -461, -442, -121, -350], \
#          [-195, -285, -153,   23, -347, -121, -169,  380, -461, -421, -109, -306], \
#          [ -80, -200,    0,  200, -347,  -50, -169,  130, -100,    0, -109, -180]]


frame_start_left = [53, -134, 190, 0, -380, 62, -132, -118, 294, 440, -26, -67]
frame_left_2 = [225, 345, 472, 165, 144, 67, -21, -500, 294, 440, -178, -2]
frame_left_3 = [438, 366, 373, 167, 435, 308, 176, -500, 294, 440, -269, 125]
frame_left_4 = [426, 345, 472, 165, 144, 215, 176, -500, -467, -375, -287, 139]
frame_left_5 = [423, 345, 472, -44, 211, 215, 333, 268, -236, -375, -287, 95]
frame_left_6 = [398, 345, 472, 165, 308, 215, 67, 268, 46, 30, 352, 169]
frame_left_7 = [67, 153, 30, 165, 287, 21, -35, 121, -56, -188, 26, 23]

frame_start_right = [-frame_start_left[11], \
                     -frame_start_left[10], \
                     -frame_start_left[9], \
                     -frame_start_left[8], \
                     -frame_start_left[7], \
                     -frame_start_left[6], \
                     -frame_start_left[5], \
                     -frame_start_left[4], \
                     -frame_start_left[3], \
                     -frame_start_left[2], \
                     -frame_start_left[1], \
                     -frame_start_left[0]];

frame_right_2 = [-frame_left_2[11], \
                 -frame_left_2[10], \
                 -frame_left_2[9], \
                 -frame_left_2[8], \
                 -frame_left_2[7], \
                 -frame_left_2[6], \
                 -frame_left_2[5], \
                 -frame_left_2[4], \
                 -frame_left_2[3], \
                 -frame_left_2[2], \
                 -frame_left_2[1], \
                 -frame_left_2[0]];

frame_right_3 = [-frame_left_3[11], \
                 -frame_left_3[10], \
                 -frame_left_3[9], \
                 -frame_left_3[8], \
                 -frame_left_3[7], \
                 -frame_left_3[6], \
                 -frame_left_3[5], \
                 -frame_left_3[4], \
                 -frame_left_3[3], \
                 -frame_left_3[2], \
                 -frame_left_3[1], \
                 -frame_left_3[0]];

frame_right_4 = [-frame_left_4[11], \
                 -frame_left_4[10], \
                 -frame_left_4[9], \
                 -frame_left_4[8], \
                 -frame_left_4[7], \
                 -frame_left_4[6], \
                 -frame_left_4[5], \
                 -frame_left_4[4], \
                 -frame_left_4[3], \
                 -frame_left_4[2], \
                 -frame_left_4[1], \
                 -frame_left_4[0]];

frame_right_5 = [-frame_left_5[11], \
                 -frame_left_5[10], \
                 -frame_left_5[9], \
                 -frame_left_5[8], \
                 -frame_left_5[7], \
                 -frame_left_5[6], \
                 -frame_left_5[5], \
                 -frame_left_5[4], \
                 -frame_left_5[3], \
                 -frame_left_5[2], \
                 -frame_left_5[1], \
                 -frame_left_5[0]];

frame_right_6 = [-frame_left_6[11], \
                 -frame_left_6[10], \
                 -frame_left_6[9], \
                 -frame_left_6[8], \
                 -frame_left_6[7], \
                 -frame_left_6[6], \
                 -frame_left_6[5], \
                 -frame_left_6[4], \
                 -frame_left_6[3], \
                 -frame_left_6[2], \
                 -frame_left_6[1], \
                 -frame_left_6[0]];

frame_right_7 = [-frame_left_7[11], \
                 -frame_left_7[10], \
                 -frame_left_7[9], \
                 -frame_left_7[8], \
                 -frame_left_7[7], \
                 -frame_left_7[6], \
                 -frame_left_7[5], \
                 -frame_left_7[4], \
                 -frame_left_7[3], \
                 -frame_left_7[2], \
                 -frame_left_7[1], \
                 -frame_left_7[0]];



frames = [frame_start_left, \
          frame_left_2, \
          frame_left_3, \
          frame_left_4, \
          frame_left_5, \
          frame_left_6, \
          frame_left_7, \
          frame_start_right, \
          frame_right_2, \
          frame_right_3, \
          frame_right_4, \
          frame_right_5, \
          frame_right_6, \
          frame_right_7]

current_frame = 0
nb_frames = 14
nb_steps = 10

def send_reset_values():
    global current_frame
    current_frame = 0

    print(frames[0])
    s1 = 1528 + frames[0][0]
    s2 = 1431 + frames[0][1]
    s3 = 1488 + frames[0][2]
    s4 = 1545 + frames[0][3]
    s5 = 1530 + frames[0][4]
    s6 = 1552 + frames[0][5]
    s7 = 1444 + frames[0][6]
    s8 = 1519 + frames[0][7]
    s9 = 1558 + frames[0][8]
    s10 = 1518 + frames[0][9]
    s11 = 1544 + frames[0][10]
    s12 = 1634 + frames[0][11]

    bytes_to_send = [10, 69, int(s1 % 256), \
                             int((s1 - (s1 % 256)) / 256), \
                             int(s2 % 256), \
                             int((s2 - (s2 % 256)) / 256), \
                             int(s3 % 256), \
                             int((s3 - (s3 % 256)) / 256), \
                             int(s4 % 256), \
                             int((s4 - (s4 % 256)) / 256), \
                             int(s5 % 256), \
                             int((s5 - (s5 % 256)) / 256), \
                             int(s6 % 256), \
                             int((s6 - (s6 % 256)) / 256), \
                             int(s7 % 256), \
                             int((s7 - (s7 % 256)) / 256), \
                             int(s8 % 256), \
                             int((s8 - (s8 % 256)) / 256), \
                             int(s9 % 256), \
                             int((s9 - (s9 % 256)) / 256), \
                             int(s10 % 256), \
                             int((s10 - (s10 % 256)) / 256), \
                             int(s11 % 256), \
                             int((s11 - (s11 % 256)) / 256), \
                             int(s12 % 256), \
                             int((s12 - (s12 % 256)) / 256), \
                             0]

    CRC = 0
    for i in range(2, 26):
        CRC = CRC ^ bytes_to_send[i]

    bytes_to_send[26] = int(CRC)

    #print (bytes_to_send)
    ser.write(bytes_to_send)
    current_frame_string.set("Frame: " + str(current_frame))

def send_values():
    global current_frame

    start_frame = frames[current_frame].copy()
    end_frame = frames[(current_frame + 1) % nb_frames].copy()
    steps = frames[current_frame].copy()

    for i in range(0, 12):
        steps[i] = (end_frame[i] - start_frame[i]) / nb_steps


    print(steps)
    current_step=start_frame.copy()

    for i in range(0, nb_steps):
        print(current_step)
        s1 = 1528 + current_step[0]
        s2 = 1431 + current_step[1]
        s3 = 1488 + current_step[2]
        s4 = 1545 + current_step[3]
        s5 = 1530 + current_step[4]
        s6 = 1552 + current_step[5]
        s7 = 1444 + current_step[6]
        s8 = 1519 + current_step[7]
        s9 = 1558 + current_step[8]
        s10 = 1518 + current_step[9]
        s11 = 1544 + current_step[10]
        s12 = 1634 + current_step[11]

        bytes_to_send = [10, 69, int(s1 % 256), \
                                 int((s1 - (s1 % 256)) / 256), \
                                 int(s2 % 256), \
                                 int((s2 - (s2 % 256)) / 256), \
                                 int(s3 % 256), \
                                 int((s3 - (s3 % 256)) / 256), \
                                 int(s4 % 256), \
                                 int((s4 - (s4 % 256)) / 256), \
                                 int(s5 % 256), \
                                 int((s5 - (s5 % 256)) / 256), \
                                 int(s6 % 256), \
                                 int((s6 - (s6 % 256)) / 256), \
                                 int(s7 % 256), \
                                 int((s7 - (s7 % 256)) / 256), \
                                 int(s8 % 256), \
                                 int((s8 - (s8 % 256)) / 256), \
                                 int(s9 % 256), \
                                 int((s9 - (s9 % 256)) / 256), \
                                 int(s10 % 256), \
                                 int((s10 - (s10 % 256)) / 256), \
                                 int(s11 % 256), \
                                 int((s11 - (s11 % 256)) / 256), \
                                 int(s12 % 256), \
                                 int((s12 - (s12 % 256)) / 256), \
                                 0]

        CRC = 0
        for i in range(2, 26):
            CRC = CRC ^ bytes_to_send[i]

        bytes_to_send[26] = int(CRC)

        #print (bytes_to_send)
        ser.write(bytes_to_send)

        for i in range(0, 12):
            current_step[i] = int(current_step[i] + steps[i])

        time.sleep(0.1)

    if current_frame < nb_frames - 1:
        current_frame += 1
    else:
        current_frame = 0

    current_frame_string.set("Frame: " + str(current_frame))



ser = serial.Serial('/dev/ttyUSB0', 115200)

root = tk.Tk()
root.title("Key frames controller")
root.geometry("300x100")

current_frame_string = tk.StringVar()
current_frame_string.set("Frame: " + str(current_frame))

l = tk.Label(root, textvariable = current_frame_string)
l.pack()

b = tk.Button(root, text="New key frame", command=send_values)
b.pack()

b2 = tk.Button(root, text="Reset", command=send_reset_values)
b2.pack()

tk.mainloop()

ser.close()
