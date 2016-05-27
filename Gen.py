import serial
from Tkinter import *

def gen():
    s = serial.Serial("COM3" , 9600)
    f = open("mine" , 'w' )
    code = s.read(20*26)
    for line in range(20):
        for char_n in range(25):
            f.write(code[line*26+char_n])
            #if code[line*26+char_n] != '\n':
            #    f.write(code[line*26+char_n])
            #else:
            #    f.write(code[line*26+char_n])
            #    break
    return code
    #f.write(code)

#image_list = [fire , man , cannon , wall , if_pic , eles_pic, larger_pic]
def update_canvas(canvas , image_list , code): 
    #logo = PhotoImage(file="./images/Fire.pbm")
    canvas.delete("all")
    fire = canvas.create_image( 70 , 320 , image = logo    )   
    #fire = canvas.create_line( [70,70] , [320,320]  )   
    canvas.update()
