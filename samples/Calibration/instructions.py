
 #this class contains all the instructions that are to be given to the user, and will be called by the gui_window
class Instructions():
      def __init__(self):
          self.instruction = []
          self.instruction.append("Initiating Calibration,   Click to proceed")
          self.instruction.append("Look at the TOP LEFT corner and left-click")
          self.instruction.append("Look at the TOP RIGHT corner and left-click")
          self.instruction.append("Look at the BOTTOM LEFT corner and left-click")
          self.instruction.append("Look at the BOTTOM RIGHT corner and left-click")
          self.instruction.append("CALIBRATION COMPLETE, left-click to exit")

      def get_instrct(self, num):
          return (self.instruction[num])
