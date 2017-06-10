des: des.o des_util.o
	gcc -o des -g des.o des_util.o -lcrypto -lm

des.o: des.c
	gcc -g -c -Wall des.c 

des_utlil.o: des_util.c
	gcc -g -c -Wall des_util.c

clean:
	rm -f *.o des
