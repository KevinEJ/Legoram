import game

import Tkinter as tk
def keypress(event):
    if event.keysym == 'Return':
        root.destroy()
root = tk.Tk()
print "Press Enter to start:"
root.bind_all('<Key>', keypress)
# don't show the tk window
root.withdraw()
root.mainloop()

stop = False
while not stop:
	game = reload(game)
	stop = game.run()


