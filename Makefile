CXX   	= g++
LINK   	= g++

LIBS  	=  -Wall -L/Developer/NVIDIA/CUDA-6.5/lib
LDFLAGS = `pkg-config --libs opencv` -lopencv_gpu -stdlib=libstdc++
CFLAGS  = `pkg-config --cflags opencv` -I./include -stdlib=libstdc++

TARGETS	= stereo_calib app 

all: $(TARGETS)

app: app.o params.o cam.o pair.o
	$(LINK) $(LIBS) -o $@ params.o cam.o pair.o $< $(LDFLAGS)

stereo_calib: stereo_calib.o
	$(LINK) $(LIBS) -o $@ $< $(LDFLAGS)

params.o: params.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) 

cam.o: cam.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) 

pair.o: pair.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) 

stereo_calib.o: stereo_calib.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) 

.cpp.o:$($@:.o=.cpp)
	$(CXX) -c -o $@ $< $(CFLAGS)

#	@echo target is $@, source is $<

clean:
	rm -f *.o *~
	rm -f $(TARGETS)

#g++ -L/Developer/NVIDIA/CUDA-6.5/lib stereo_match.cpp -o ~/Projects/3Dify/bin/osx_stereo_match `pkg-config --cflags --libs opencv` -lopencv_gpu -stdlib=libstdc++

#g++ -o CamTest main.cpp -Wl,-rpath,. -L. -lCamCore
