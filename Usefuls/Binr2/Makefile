CC = gcc
CFLAGS  = -I inc
SRC = src/main.c src/binr2.c
EXE = binr2  

all: $(EXE)

$(EXE):
	$(CC) $(CFLAGS) $(SRC) -o $@
        

clean:
	rm -rf $(EXE)