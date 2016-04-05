CC=g++
FLAGS=-Wall -Werror
GL_FLAGS= -lGL -lglut -std=c++11

COMMON_COMMAND=$(CC) -c $^ $(FLAGS) $(GL_FLAGS)

main: main.cpp viewport.o constants.h vector.o canvas.o circle.o drawingPrem.o
	$(CC) $^ $(FLAGS) $(GL_FLAGS) -o $@

viewport.o: viewport.cpp viewport.h constants.h
	$(CC) -c $^ $(FLAGS) $(GL_FLAGS)

vector.o: vector.cpp vector.h
	$(CC) -c $^ $(FLAGS) $(GL_FLAGS)

canvas.o: canvas.cpp canvas.h viewport.o shape.h
	$(COMMON_COMMAND)

circle.o: circle.cpp circle.h shape.h viewport.o
	$(COMMON_COMMAND)
drawingPrem.o: drawingPrem.cpp drawingPrem.h viewport.o
	$(COMMON_COMMAND)
&.o: &.cpp &.h
	$(CC) -c $^ $(FLAGS) $(GL_FLAGS)
.PHONY: clean

clean:
	rm -f *.o main
