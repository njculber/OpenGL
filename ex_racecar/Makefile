SOURCE = racecar.cpp ../lib/program.cpp ../lib/lib.cpp ../lib/camera.cpp ../lib/neil_math.cpp
CC = g++
CFLAGS = -Wall -Wextra -pedantic -framework OpenGL -framework GLUT -lGLEW -lglfw
OBJECT = main

default:
	$(CC) -o $(OBJECT) $(SOURCE) $(CFLAGS)

clean:
	rm -f $(OBJECT)
