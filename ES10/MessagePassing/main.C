#include "Individuo.h"
#include "random.h"
#include "mpi.h"
#include <iostream>
#include<fstream>
#include<sstream>
#include <vector>
#include <cmath>

//Travelling Salesman Problem - Algoritmo Genetico parallelizzato con librerie MPI

using namespace std;

void Ordina(Individuo Ind[], int D);


int main(int argc, char* argv[]){

   int size, rank;
   MPI_Init(&argc,&argv);			//inizializza l'ambiente MPI
   MPI_Comm_size(MPI_COMM_WORLD, &size);	//ritorna il numero di processi
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);	//ritorna il rank del processo entro il gruppo MPI_COMM_WORLD
   

   Random rnd;
   int seed[4];
   int p1, p2, p3, p4, p5, p6, p7, p8;
   ifstream Primes("Primes"); if (Primes.is_open()){
	Primes >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8;
	
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



	cout<<"Costruisco la generazione 0"<<endl;
	int N=32;				//numero di città
	int M=100;				//numero di individui
	Individuo Generazione[M];	//vettore di M individui
	
	for(int i=0; i<N; i++){			//carico il primo individuo con città situate all'interno di un quadrato
		float r = rnd.Rannyu();
		float s = rnd.Rannyu();
		Generazione[0].SetGene(i, r, s);
	}

/*	int k;
	for(int i=0; i<N; i++){			//carico il primo individuo con città situate su una circonferenza
		float r = rnd.Rannyu(-1.,1.);
		float w = rnd.Rannyu();
		if (w<0.5){k=1;}
		else{k=-1;}
		float s = (1-pow(r,2))*k;
		Generazione[0].SetGene(i, r, s);
	}
*/	
	for (int i=1; i<M; i++){
		Individuo Old=Generazione[i-1];
		Old.SaveFirst();
		Old.MutationA(0.3);
		Old.MutationB(0.3);
		Old.MutationC(0.3);
		Old.MutationD(0.3);
		if(Old.Check()){
			Generazione[i]=Old;
		}
		else{cout<<"non copio!"<<endl;}
	}					//Ho generato la Generazione Zero a partire dal primo individuo
	
	
	Ordina(Generazione, M);


	if (rank==1){
        	p1=p3;
		p2=p4;
	}
	   if (rank==2){
        	p1=p5;
		p2=p6;
	}
	   if (rank==3){
        	p1=p7;
		p2=p8;
	}

	rnd.SetRandom(seed,p1,p2);

	int u=0;
	float somma = 0;
	const string name = "BestFitSquare";
	stringstream ss;
	ss<<name<<rank;
	ofstream BestFit;
//	ofstream FitMedio;
//	FitMedio.open("FitMedioCircle.dat");
	BestFit.open(ss.str().c_str());
	BestFit<<u<<" "<<Generazione[0].Fitness()<<endl;

	int nrun=300;
	int Nmigr =0;
	Individuo GenerazioneOld[M];
	Individuo GenerazioneNew[M];	
	
	for(int i=0; i<M; i++){
		GenerazioneOld[i]=Generazione[i];
	}

	for(int u=1; u<nrun; u++){
		
		Individuo Best1 = GenerazioneOld[0];
		Individuo Best2 = GenerazioneOld[1];

		for(int i=0; i<M; i++){
		GenerazioneNew[i]=GenerazioneOld[i];
		}
	
		for(int g=8; g<M; g=g+2){	
			float v1 = rnd.Rannyu();
			int j1 = int(M*pow(v1,2.));
			float v2 = rnd.Rannyu();
			int j2 = int(M*pow(v2,2.));
			Individuo P1 = GenerazioneOld[j1];
			Individuo P2 = GenerazioneOld[j2];
			P1.SaveFirst();
			P1.MutationA(0.1);
			P1.MutationB(0.1);
			P1.MutationC(0.1);
			P1.MutationD(0.1);
			P2.SaveFirst();
			P2.MutationA(0.1);
			P2.MutationB(0.1);
			P2.MutationC(0.1);
			P2.MutationD(0.1);
			int v = rnd.Randint(1, N-2);
			float pE = rnd.Rannyu();
			float pF = rnd.Rannyu();
		
			Individuo E = P1;
			Individuo F = P2;		
			E.Crossover(F,v,pE);
			F.Crossover(P1,v,pF);
			if(E.Check() && F.Check()){
				GenerazioneNew[g]=E;
				GenerazioneNew[g+1]=F;
			}
		}

		Ordina(GenerazioneNew, M);
		for (int k=0; k<M/2; k++){
			somma+=GenerazioneNew[k].Fitness();
		}
		
		if(u%50==0){	
			Nmigr++;
			float coordinate[256];					//i quattro nodi si scambiano il loro miglior percorso
			float Best[256];
			int co=0;
			cout<<"Migrazione n "<<Nmigr<<endl;
			for(int i=0; i<4; i++){
				for(int t=0; t<32; t++){
					coordinate[co]=GenerazioneNew[i].GetComponent(t,0);
					coordinate[co+1]=GenerazioneNew[i].GetComponent(t,1);
					co=co+2;
				}
			}
			MPI_Allgather(coordinate,64, MPI_FLOAT, Best,64, MPI_FLOAT, MPI_COMM_WORLD);
			co=0;
			for(int i=0; i<4; i++){
				for(int t=0; t<32; t++){
					GenerazioneNew[i].SetGene(t, Best[co],Best[co+1]);
					co=co+2;
				}
			}
		}
		Ordina(GenerazioneNew, M);
//		FitMedio<<u<<" "<<somma/(M/2.)<<endl;
		somma=0;
		BestFit<<u<<" "<<GenerazioneNew[0].Fitness()<<endl;

			
		for(int i=0; i<M; i++){
			GenerazioneOld[i]=GenerazioneNew[i];
			}
	}


	cout<<"Fitness della Generazione n"<<endl;
	for (int i=0; i<M; i++){ 
		cout<<GenerazioneNew[i].Fitness()<<endl;
	}
	BestFit.close();
//	FitMedio.close();
	Individuo Best = GenerazioneNew[0];
	
	Best.PrintPath(rank);


	
	MPI_Finalize();				//termina i processi MPI
			
	return 0;
  }

		

void Ordina(Individuo Ind[], int D){ 
	for (int i=0; i<D; i++) {
		for (int j=i+1; j<D; j++) {
			Individuo A=Ind[i];
			Individuo B=Ind[j];
			if (B.Fitness() < A.Fitness()) {
				Ind[i]=B;
				Ind[j]=A;
			}
		}
	}
}


























