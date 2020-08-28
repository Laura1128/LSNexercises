CC = g++
CFLAGS = -Wall -O3 --std=c++11

Monte_Carlo_ISING_1D.exe : main_Ising1D.o random.o
	$(CC) random.o main_Ising1D.o -o Monte_Carlo_ISING_1D.exe
main_Ising1D.o : main_Ising1D.cpp
	$(CC) -c main_Ising1D.cpp -o main_Ising1D.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o Monte_Carlo_ISING_1D.exe
