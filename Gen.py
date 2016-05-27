import serial

def gen():
    s = serial.Serial("COM1" , 9600)
    f = open("mine" , 'w' )
    while(True):
        flag = s.read(1)
        if flag == True:
            code = s.read(20*25)
            break
    for line in range(20):
        for char_n in range(26):
            if code[line*26+char_n] != '\n':
                f.write(code[line*26+char_n])
            else:
                f.write(code[line*26+char_n])
                break
    #f.write(code)
