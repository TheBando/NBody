CC = g++

LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ = $(TARGET).o CelestialBody.o Universe.o
DEPS =
LIBS =
TARGET = Nbody



all: $(TARGET)

$(TARGET): $(TARGET).o CelestialBody.o Universe.o
	g++ $(TARGET).o Universe.o CelestialBody.o -o $(TARGET) $(LFLAGS) 

$(TARGET).o: $(TARGET).cpp
	g++ -c $(TARGET).cpp

Universe.o: Universe.cpp
	g++ -c Universe.cpp

CelestialBody.o: CelestialBody.cpp
	g++ -c CelestialBody.cpp


clean:
	rm $(OBJ)