CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

gaze: gaze_to_cursor.o; $(CXX) $< -o $@ $(LDFLAGS)

test.o: gaze_to_cursor.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f gaze_to_cursor.o gaze_to_cursor
