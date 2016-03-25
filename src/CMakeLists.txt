#make sure to add your code here...
#creates an executable in build called gaze_contoller -- we need a better name
ADD_EXECUTABLE(gaze_controller main.cpp detect.hpp detect.cpp preproc.hpp preproc.cpp postproc.hpp postproc.cpp)
#links the OpenCV library with the executable
TARGET_LINK_LIBRARIES(gaze_controller ${OpenCV_LIBS})

#Example code for testing purposes.
ADD_EXECUTABLE(example example.cpp)
TARGET_LINK_LIBRARIES(example ${OpenCV_LIBS})


