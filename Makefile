SRC = *.c
CC  = /usr/bin/gcc
CC_FLAGS = -Wall -Wextra -g -O3
LD_FLAGS = -lSDL2 -lSDL_image -lm -pthread
EXE = raycaster

all : $(SRC)
	$(CC) $(SRC) $(CC_FLAGS) $(LD_FLAGS) -o $(EXE)

run :
	/bin/bash $(EXE)
