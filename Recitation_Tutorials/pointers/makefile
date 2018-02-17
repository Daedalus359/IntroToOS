CC = gcc
OUT = deref.o
OUT1 = multi.o
OUT2 = byvalue.o
OUT3 = byref.o
SRC = deref.c
SRC1 = multi.c
SRC2 = byvalue.c
SRC3 = byref.c


all:	deref multi byvalue byref

deref:	
	$(CC) -o $(OUT) $(SRC)	
	chmod 755 $(OUT)

multi:	
	$(CC) -o $(OUT1) $(SRC1)	
	chmod 755 $(OUT1)

byvalue:	
	$(CC) -o $(OUT2) $(SRC2)	
	chmod 755 $(OUT2)

byref:	
	$(CC) -o $(OUT3) $(SRC3)	
	chmod 755 $(OUT3)
clean:
	rm -f $(OUT)
	rm -f $(OUT1)
	rm -f $(OUT2)
	rm -f $(OUT3)

