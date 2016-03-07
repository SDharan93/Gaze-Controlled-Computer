#!/usr/bin/python
from tkinter import *
from instructions import Instructions

class gui_window():
    def __init__(self):
        self.counter = 0
        self.message = "Hello"

        gui_window.OpenWindow(self)



    def OpenWindow(self):

        self.root = Tk()
        self.root.configure(bg="white")  #making the background color white


        Frame_left = Frame(self.root, bg = "white")   #making a Frame for pics on LEFT Corners
        Frame_right = Frame (self.root, bg = "white") #making a Frame for pics on RIGHT Corners

        img = []        #a list of images
        lbl_img = []   # a list of lables for the images

        for i in range(0,4):
            filename = str(i) + ".gif"   #the filename for the 4 pics.    gif because tkinter only accepts this format
            img.append(PhotoImage(file = filename))     #loading all four images

                #packing the 4 labels to LEFT or RIGHT frame
            if ((i == 0) or (i == 2)):
                lbl_img.append(Label(Frame_left, image = img[i]))
            else:
                lbl_img.append(Label(Frame_right,image = img[i]))



        for i in range (0,4):  #packing the lables TOP or BOTTOM in the two frames
            if (i < 2):
                lbl_img[i].pack(side = TOP, anchor = W, fill = X)
            else :
                lbl_img[i].pack(side = BOTTOM, anchor = W, fill = X)

            lbl_img[i].grid_remove()


        Frame_left.pack(side = LEFT, fill=BOTH)  #packing the LEFT frame left
        Frame_right.pack(side = RIGHT, fill=BOTH) #packing the RIGHT frame right

        Frame_text = Frame(self.root, bg = "white")

        self.lbl_text = Label(Frame_text, text = self.message , bg = "white", font = "Helvetica 16 bold")
        self.lbl_text.pack()

        Frame_text.pack(side = TOP, expand = YES)  #placing the label right in the middle of the screen

        def leftClick(event):
            instruct = Instructions()
            if (self.counter < 6):
                self.message = instruct.get_instrct(self.counter)
                self.counter = self.counter + 1
                self.lbl_text.config(text = self.message)

            else:
                sys.exit(0)


        click_frame = Frame(self.root, width = 300, height = 300)
        click_frame.bind("<Button-1>", leftClick)


        click_frame.pack()

        self.root.mainloop() #keeping the GUI visible


run = gui_window()
