The file gaze_to_cursor.o contains an algorithm that should output cursor x and y based on the pupil location.

The input is a black image with white dot that represents the center of the pupil.

To run, type make, and then ./gaze

This algorithm identifies the location of the white dot in the image.Then using the scaling factor, it identifies where the user is looking on the monitor. The scaling factor is calculated using the screen resolution, which provides the number of pixel horizontally and vertically on the monitor. These pixel counts must be verified in the code to get accurate results.

For testing purposes, gaze_to_cursor.o creates 250 by 250 black image with a white dot (1 pixel) randomly placed.  This image currently serves as the input.  


Future steps:
Currently the algorithm divides the image into 10px by 10px grid, the necessity of this step must be verified.
This algorithm needs to be tested with the actual pupil image -> the pupil may not be represented as a single pixel, thus the searching method should be modified to accommodate for this.
