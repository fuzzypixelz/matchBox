
# This makefile might be too complicated
# It might need restructuring in the future
# The project will decide as we go on.

# The compiler
COMPILER=g++

# The object files that matchBox depends on.
OBJS=build/main.o build/board.o

# default: matchBox

# default rule
matchBox: $(OBJS)
	$(COMPILER) -o bin/matchBox $(OBJS)

# rules for all object files
build/main.o: include/board.h

build/board.o: include/board.h 

.PHONY: clean
clean:
	rm $(OBJS)
	rm bin/main
