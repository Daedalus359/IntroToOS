CC = gcc
OUT = pipe_double.o
OUT1 = unix_pipe.o
SRC = pipe_double.c
SRC1 = unix_pipe.c


all:	double pipe

double:	
	$(CC) -o $(OUT) $(SRC)	
	chmod 755 $(OUT)

pipe:	
	$(CC) -o $(OUT1) $(SRC1)	
	chmod 755 $(OUT1)

clean:
	rm -f $(OUT)
	rm -f $(OUT1)

