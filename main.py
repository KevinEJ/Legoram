import game
import time
import Tkinter as tk
from Gen import *

def keypress(event):
    if event.keysym == 'Return':
        root.destroy()
root = tk.Tk()
print "Press Enter to start:"
root.bind_all('<Key>', keypress)
# don't show the tk window
#root.withdraw()

clock = tk.Label(root, font=('times', 20, 'bold'), bg='green')
clock.pack()

canvas = tk.Canvas(root , width = 1000 , height = 1000)
canvas.pack()

#fire = PhotoImage(file="./images/Fire.pbm")
#man = PhotoImage(file="./images/man.pbm")
#cannon = PhotoImage(file="./images/cannon.pbm")
#wall = PhotoImage(file="./images/wall.pbm")
#if_pic = PhotoImage(file="./images/if.pbm")
#else_pic = PhotoImage(file="./images/else.pbm")
#larger_pic = PhotoImage(file="./images/larger.pbm")
#image_list = [fire , man , cannon , wall , if_pic , eles_pic, larger_pic]
image_list = []
s = serial.Serial("COM3" , 9600)
code = ['']
def update_clock():    
    global code
    now = time.strftime("%H:%M:%S")
    clock.configure(text=now)
    code = gen(s)
    #code = "QQ"
    #print code
    update_canvas(canvas, image_list, code)
    root.after(100, update_clock)

update_clock()

root.mainloop()

stop = False


##############################
#         main loop          #
##############################
while not stop:

	#generate() here


	game = reload(game)
	stop = game.run(code , s )


