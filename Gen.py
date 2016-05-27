import serial
from Tkinter import *
import binascii
def gen(s):
    #os.remove("mine")      
    #f = open("mine" , 'w' )
    #s.write("0")
    acode = s.read(20*26)
    output = []
    string = ""
    #print code
    for line in range(20):
        #output.append([])
        string = ""
        for char_n in range(25):
            #print code[line*26+char_n]
            #a = bytes(code[line*26+char_n])
            a = (acode[line*26+char_n])
            #print a
            string += a
        #print string
        #print len(string)
        if string[0] == b'\x00':
            print "no append"
            pass
        else:
            output.append(string)
    print output
    return output
    #f.write(code)

#image_list = [fire , man , cannon , wall , if_pic , eles_pic, larger_pic]
def update_canvas(canvas , image_list , code): 
    #logo = PhotoImage(file="./images/Fire.pbm")
    canvas.delete("all")
    #fire = canvas.create_image( 70 , 320 , image = logo    )   
    fire = canvas.create_line( [70,70] , [320,320]  )   
    canvas.update()
