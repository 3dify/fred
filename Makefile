CXX   	= g++
LINK   	= g++

LIBS  	=  -Wall -L/Developer/NVIDIA/CUDA-6.5/lib
LDFLAGS = `pkg-config --libs opencv` -lopencv_gpu -stdlib=libstdc++
CFLAGS  = `pkg-config --cflags opencv` -I./include -stdlib=libstdc++

TARGETS	= stereo_calib app 

all: $(TARGETS)

app: app.o params.o calibration.o pointcloud.o 
	$(LINK) $(LIBS) -o bin/$@ tmp/params.o tmp/calibration.o tmp/pointcloud.o tmp/$< $(LDFLAGS)

stereo_calib: stereo_calib.o
	$(LINK) $(LIBS) -o bin/$@ tmp/$< $(LDFLAGS)

app.o: app.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

params.o: params.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

calibration.o: calibration.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

pointcloud.o: pointcloud.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

cam.o: cam.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

pair.o: pair.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

stereo_calib.o: stereo_calib.cpp
	$(CXX) -c -o tmp/$@ $< $(CFLAGS) 

#	@echo target is $@, source is $<

clean:
	rm -f *.o *~
	rm -f $(TARGETS)

