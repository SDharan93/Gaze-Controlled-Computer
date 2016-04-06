CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)
export LDFLAGS1 += -L/usr/local/cuda/lib -lcufft -lnpps -lnppi -lnppc -lcudart -lrt -lpthread -lm -ldl
export LDFLAGS2 += -mfpu=neon

test: test.o; $(CXX) $< -o $@ $(LDFLAGS)

test.o: capstone_test.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

thresh: thresh.o; $(CXX) $< -o $@ $(LDFLAGS)

thresh.o: thresh.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

cam: camshift.o; $(CXX) $< -o $@ $(LDFLAGS)

cam.o: camshift.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

gabor: gabor.o; $(CXX) $< -o $@ $(LDFLAGS)

gabor.o: gabor.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f test
