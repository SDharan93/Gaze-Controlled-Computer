#This is the calibration UI for the Gaze detection system. This UI tells the user to look at each corner, in the order of TOP LEFT
#TOP RIGHT, BOTTOM RIGHT, and BOTTOM RIGHT, and then leftclick to proceed. This UI will also display a small circle at the corner the user is supposed to be looking at
#after all the steps have been completed, the program will exit automatically. The UI can be exited if user right clicks

#!/usr/bin/python
from tkinter import *
from instructions import Instructions #Instructions class contains written instructions for the user

class gui_window():
    def __init__(self):  #this constructor initiates the GUI window

        self.root = Tk()
        self.root.configure(bg="white")  #making the background color white
        self.root.overrideredirect(True)  #making the window full screen
        self.root.geometry("{0}x{1}+0+0".format(self.root.winfo_screenwidth(), self.root.winfo_screenheight()))

        self.counter = 0  #a counter that is used to display the correct instruction
        self.message = "Initiating Calibration,   Click to proceed" #the string that contains the user's instruction

        #Making Frames for LEFT and RIGHT corners and
            #diving these frame into rows and columns to make the pics appear and dissaper smoothly
        Frame_left = Frame(self.root, bg = "white")
        Frame_left.rowconfigure(1, minsize = 18)
        Frame_left.rowconfigure(2, minsize = (self.root.winfo_screenheight())-50)
        Frame_left.rowconfigure(3, minsize = 18)
        
        Frame_right = Frame (self.root, bg = "white")
        Frame_right.rowconfigure(1, minsize = 18)
        Frame_right.rowconfigure(2, minsize = (self.root.winfo_screenheight())-50)
        Frame_right.rowconfigure(3, minsize = 18)


        #Frame used to cotnain the label holding the user's instruction
        Frame_text = Frame(self.root, bg = "white")

        img = []   #a list for the images
        self.lbl_img = []   # a list of lables for the images

        #loading the four file images (gif because tkinter only likes that) into lbl_img
        for i in range(0,4):
            filename = str(i) + ".gif"
            img.append(PhotoImage(file = filename))     #loading all four images

            #packing the 4 labels to LEFT or RIGHT frame
            if ((i == 0) or (i == 3)):
                self.lbl_img.append(Label(Frame_left, image = img[i]))
            else:
                self.lbl_img.append(Label(Frame_right,image = img[i]))

        #placing the img labels in rows 1 or 3 in LEFT and RIGHT Frames
        for i in range (0,4):
            if (i < 2):
                self.lbl_img[i].grid(row=1, column = 1)
            else :
                self.lbl_img[i].grid(row =3, column =1)

        #packing the LEFT frame to the very left of the window
        Frame_left.pack(side = LEFT, fill=BOTH)
        #packing the RIGHT frame to the very right of the window
        Frame_right.pack(side = RIGHT, fill=BOTH)

        #label that holds the user's instructions.  self.message is dynamic, will change based on click
        self.lbl_text = Label(Frame_text, text = self.message , bg = "white", font = "Helvetica 16 bold")
        self.lbl_text.pack()
        #placing the label right in the middle of the screen
        Frame_text.pack(side = TOP, expand = YES)

        #This inner functions handles all leftClick functionality, such as changing instructions, and placing/removing corner pics
        def leftClick(event):
            #Instrctions() class stores all the instructions for the user
            instruct = Instructions()

            #checks if anymore instructions are available, if not exit program
            if (self.counter < instruct.get_instrctSize()):
                #stores the new instruction that is to be displayed on screen, and updates the lbl_text
                self.message = instruct.get_instrct(self.counter)
                self.lbl_text.config(text = self.message)

                #hiding all the corner pics, and then displaying the one at the corner the user should look at
                for i in range(0,4):
                    self.lbl_img[i].grid_remove()
                if (self.counter <4):
                    self.lbl_img[self.counter].grid()

                self.counter = self.counter + 1
            else:
                #closes the program after calibrtion is finished
                sys.exit(0)

        def closeWindow(event): #closes the program if rightclicked
            sys.exit(0)

        #Handling left mouse click events anywhwere on the screen
        self.root.bind("<Button-1>", leftClick)
        #Right click to close the calibration window
        self.root.bind("<Button-3>", closeWindow)



        #keeping the GUI visible in continous loop
        self.root.mainloop()


run = gui_window()
