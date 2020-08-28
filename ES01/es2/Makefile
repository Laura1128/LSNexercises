CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o Vettore.o
	$(CC) Vettore.o random.o main.o -o main.exe
main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
Vettore.o : Vettore.C Vettore.h
	$(CC) -c Vettore.C -o Vettore.o $(CFLAGS)
clean :
	rm *.o main.exe seed.out
