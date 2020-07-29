
# This makefile might be too complicated
# It might need restructuring in the future
# The project will decide as we go on.

# The compiler
COMPILER=g++

# The object files that matchBox depends on.
OBJS=build/main.o build/board.o build/game.o

# default: matchBox

# default rule
matchBox: $(OBJS)
	$(COMPILER) -o bin/matchBox $(OBJS)

# rules for all object files
build/main.o: tests/main.cpp include/board.h include/game.h
	$(COMPILER) -c -o build/main.o tests/main.cpp

build/board.o: src/board.cpp include/board.h
	$(COMPILER) -c -o build/board.o src/board.cpp

build/game.o: src/game.cpp include/game.h include/board.h 
	$(COMPILER) -c -o build/game.o src/game.cpp

.PHONY: clean
clean:
	rm $(OBJS)
	rm bin/matchBox
