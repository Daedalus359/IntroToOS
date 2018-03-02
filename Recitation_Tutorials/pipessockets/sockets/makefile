CC = gcc
OUT = client.o
OUT1 = server.o
SRC = client.c
SRC1 = server.c


all:	client server

client:	
	$(CC) -o $(OUT) $(SRC)	
	chmod 755 $(OUT)

server:	
	$(CC) -o $(OUT1) $(SRC1)	
	chmod 755 $(OUT1)

clean:
	rm -f $(OUT)
	rm -f $(OUT1)

