CC=g++
FLAGS=-Wall -Werror
GL_FLAGS= -lGL -lglut -std=c++11

main: main.cpp viewport.o constants.h
	$(CC) $^ $(FLAGS) $(GL_FLAGS) -o $@

viewport.o: viewport.cpp viewport.h constants.h
	$(CC) -c $^ $(FLAGS) $(GL_FLAGS)

drawingPrem.o: drawingPrem.cpp viewport.o drawingPrem.h
	$(CC) -c $^ $(FLAGS) $(GL_FLAGS)

vector.o: vector.cpp vector.h
	$(CC) -c $^ $(FLAGS) $(GL_FLAGS)

.PHONY: clean

clean:
	rm -f *.o main
