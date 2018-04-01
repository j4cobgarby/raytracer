SRC = *.c
CC  = /usr/bin/gcc
CC_FLAGS = -Wall -Wextra -Ofast
LD_FLAGS = -lSDL2 -lm -pthread
EXE = raycaster

all : $(SRC)
	$(CC) $(SRC) $(CC_FLAGS) $(LD_FLAGS) -o $(EXE)

run :
	/bin/bash $(EXE)
