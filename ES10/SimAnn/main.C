#include "Individuo.h"
#include "random.h"
#include <iostream>
#include<fstream>
#include <vector>
#include <cmath>

//Traveling Salesman Problem - Simulated Annealing 

using namespace std;

int main(){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

	cout<<" - - - - - - - - - - - - - - - - - - - - - - - - "<<endl<<endl;
	cout<<"Traveling Salesman Problem - Simulated Annealing"<<endl<<endl;
	int num;
	cout<<"Digitare 1 per città distribuite lungo una circonferenza, 2 per città situate all'interno di un quadrato."<<endl;
	cin>>num;
	int N=32;				//numero di città
	int M=50;
	int L=64;
	float accepted=0;
	float attempted=0;
	Individuo Path;
	float T, beta, Acc;
	float energy_new, energy_old;
	
	
	
	if(num==1){
		cout<<"Città situate su una circonferenza"<<endl<<endl;
		int k;
		for(int i=0; i<N; i++){			//carico l'individuo con città situate su una circonferenza
			float r = rnd.Rannyu(-1.,1.);
			float w = rnd.Rannyu();
			if (w<0.5){k=1;}
			else{k=-1;}
			float s = (1-pow(r,2))*k;
			Path.SetGene(i, r, s);
		}
	}else if(num==2){
		cout<<"Città situate all'interno di un quadrato"<<endl;
		for(int i=0; i<N; i++){			//carico l'individuo con città situate all'interno di un quadrato
			float r = rnd.Rannyu();
			float s = rnd.Rannyu();
			Path.SetGene(i, r, s);
		}
	}else {cout<<"Numero non valido"<<endl;
		return 0;
	}
	cout<<"Costruisco il primo percorso"<<endl<<endl;
	ofstream BestFit;
	if(num==1){
		BestFit.open("CircleMetropolis.dat");
	}else{ 
		BestFit.open("SquareMetropolis.dat");
	}
	cout<<"Fitness percorso iniziale: "<<Path.Fitness()<<endl<<endl;
	int u=0;
	BestFit<<u<<" "<<Path.Fitness()<<endl;
	T=1.27;
	for(int l=1; l<L; l++){
		accepted=0;
		attempted=0;
		T=T-0.02;
		cout<<"T: "<<T<<endl;
		M=M+2*l;	
		for (int i=1; i<M; i++){
			
			beta=1/T;
			float p=rnd.Rannyu();
			Individuo Old = Path;
			energy_old=Old.Fitness();
			
			Old.SaveFirst();
			Old.MutationA(0.4);
			Old.MutationB(0.4);
			Old.MutationC(0.4);
			Old.MutationD(0.4);
			energy_new=Old.Fitness();
			if(energy_new - energy_old < 0) {Acc=1.;}
			else {Acc=exp(-beta*(energy_new - energy_old));}
		
			if(Acc>=p){
				if(Old.Check()){
					Path = Old;
					accepted++;
				}	
			}
			attempted++;
			u++;
			BestFit<<u<<" "<<Path.Fitness()<<endl;
			
		}					
	
		cout<<"acceptance rate : "<<accepted/attempted<<endl;
		cout<<"Fitness: "<<Path.Fitness()<<endl<<endl;
		cout<<"-----------------------------------------------"<<endl<<endl;
	}	
		
	BestFit.close();
	Path.PrintPath(num);
	
	

       return 0;
}
		


























