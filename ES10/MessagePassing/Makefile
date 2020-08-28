
all: GeneticAlgorithm

GeneticAlgorithm: main.o Individuo.o random.o
	mpicxx main.o Individuo.o random.o -o GeneticAlgorithm 

main.o: main.C Individuo.h random.h  
	mpicxx -c main.C -o main.o 

Individuo.o: Individuo.C Individuo.h random.h   
	g++ -c Individuo.C -o Individuo.o

random.o : random.cpp random.h
	g++ -c random.cpp -o random.o





