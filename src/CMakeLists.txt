#make sure to add your code here...
#creates an executable in build called gaze_contoller -- we need a better name
ADD_EXECUTABLE(gaze_controller pupil_detect.hpp pupil_detect.cpp v4ldevice.cpp v4ldevice.h main.cpp detect.hpp detect.cpp pupilLoc.hpp pupilLoc.cpp constants.hpp)
#links the OpenCV library with the executable
TARGET_LINK_LIBRARIES(gaze_controller ${OpenCV_LIBS})

#Example code for testing purposes.
ADD_EXECUTABLE(example example.cpp)
TARGET_LINK_LIBRARIES(example ${OpenCV_LIBS})


ADD_EXECUTABLE(cursor cursor_coordinates.cpp cursor_coordinates.hpp Calibration.hpp Calibration.cpp Gaze_main.cpp pupil_detect.hpp pupil_detect.cpp v4ldevice.cpp v4ldevice.h detect.hpp detect.cpp pupilLoc.hpp pupilLoc.cpp constants.hpp)
#links the OpenCV library with the executable
TARGET_LINK_LIBRARIES(cursor ${OpenCV_LIBS})
