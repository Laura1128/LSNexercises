CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o funzioni.o
	$(CC) funzioni.o random.o main.o -o main.exe
main.o : main.C
	$(CC) -c main.C -o main.o $(CFLAGS)
funzioni.o: Funzioni.C Funzioni.h FunzioneBase.h
	$(CC) -c Funzioni.C -o funzioni.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main.exe seed.out
