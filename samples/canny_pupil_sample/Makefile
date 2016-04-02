CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)
export LDFLAGS1 += -L/usr/local/cuda/lib -lcufft -lnpps -lnppi -lnppc -lcudart -lrt -lpthread -lm -ldl
export LDFLAGS2 += -mfpu=neon

test: test.o; $(CXX) $< -o $@ $(LDFLAGS)

test.o: test.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

opti: optimized.cpp v4ldevice.cpp
	$(CXX) -Wall -g -O0 -o opencv-test optimized.cpp v4ldevice.cpp $(shell pkg-config opencv --cflags --libs libv4l2) $(LDFLAGS2)

opti.o: optimized.cpp v4ldevice.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f test.o video.o video test
