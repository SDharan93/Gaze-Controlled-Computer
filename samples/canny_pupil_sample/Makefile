CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

test: test.o; $(CXX) $< -o $@ $(LDFLAGS)

test.o: test.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f test.o video.o video test
