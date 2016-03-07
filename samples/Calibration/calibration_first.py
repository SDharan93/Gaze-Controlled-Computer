#!/usr/bin/python

from tkinter import *

#this class contains the simple GUI that will be used for calibration. The purpose of this GUI is to instruct the user to look at each
#corner of the screen and click.   The GUI will display a pic at each corner, and provide written instrctions for the user to follow
class Calibration_GUI():

        root = Tk()
        root.configure(bg="white")  #making the background color white

        Frame_left = Frame(root, bg = "white")   #making a Frame for pics on LEFT Corners
        Frame_right = Frame (root, bg = "white") #making a Frame for pics on RIGHT Corners

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

        Frame_left.pack(side = LEFT, fill=BOTH)  #packing the LEFT frame left
        Frame_right.pack(side = RIGHT, fill=BOTH) #packing the RIGHT frame right

        #*** Providing Instructions for the user***
        instruction = []
        instruction.append("Initiating Calibration,   Click to proceed")
        instruction.append("Look at the TOP LEFT corner and left-click")
        instruction.append("Look at the TOP RIGHT corner and left-click")
        instruction.append("Look at the BOTTOM LEFT corner and left-click")
        instruction.append("Look at the BOTTOM RIGHT corner and left-click")
        instruction.append("CALIBRATION COMPLETE, left-click to exit")

        counter =1;


        Frame_text = Frame(root, bg = "white")
        lbl_text = Label(Frame_text, text = instruction[0] , bg = "white", font = "Helvetica 16 bold")
        lbl_text.pack()
        Frame_text.pack(side = TOP, expand = YES)  #placing the label right in the middle of the screen

        #** Mouse clicks **
        def leftClick (event, counter):
            counter = counter +1
            return counter

        lbl_text.config(text = instruction[counter])
        click_frame = Frame(root, width = 300, height = 300)
        click_frame.bind("<Button-1>", leftClick())
        click_frame.pack()



        root.mainloop() #keeping the GUI visible



#excecuting the Calibration_GUI
run = Calibration_GUI()
