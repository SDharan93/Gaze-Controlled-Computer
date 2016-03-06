
The folder "cropping" contains the code that detects face and eye using HAAR cascades.  The code is designed to operate with a still image of the face or to use  the live stream of a face from the webcam.  The output for a still image is a still image of the eye that is zoomed 2x, while the output for a live feed is the cropped feed of the eye, zoomed 2x.  

Issues:
    -> the cascade switches between the left and the right eye, and thus the output stream window size is rapidly and noticeably resizing.
