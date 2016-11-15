all: openCV_STI

openCV_STI: main.o
	g++  -o openCV_STI main.cpp -lopencv_core -lopencv_highgui

clean:
	rm *.o