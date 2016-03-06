CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

crop: crop.o; $(CXX) $< -o $@ $(LDFLAGS)

test.o: crop.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f crop.o crop
