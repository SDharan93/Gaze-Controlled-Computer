#make sure to add your code here...
#creates an executable in build called gaze_contoller -- we need a better name
ADD_EXECUTABLE(gaze_controller example.cpp)

#links the OpenCV library with the executable
TARGET_LINK_LIBRARIES(gaze_controller ${OpenCV_LIBS})
