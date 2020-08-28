#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"


using namespace std;

	//Simulazione dell'esperimento di Buffon

double error(double*,double*,int);
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("primes");
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

  double l=2.;		//lunghezza dell'ago
  double D =2.4;	//distanza tra le righe 
   
   
   ofstream fileout("medie.txt");
   ofstream fileout2("incertezze.txt");
   int M=10000;
   int N=100;
   int L=M/N;

   double ave[N];
   double av2[N];
   double sum_prog[N];
   double su2_prog[N];
   double err_prog[N];
 
   for(int i=0; i<N; i++){
	ave[i]=0;
	av2[i]=0;
	sum_prog[i]=0;
	su2_prog[i]=0;
	err_prog[i]=0;
 
   }
   float Nhit, Nthrows;

  
   for(int i=0; i<N; i++){		//con questo doppio ciclo calcolo le medie e le medie quadrate di ogni blocco
	Nhit=0;
	Nthrows=0;
	for(int j=0; j<L; j++){
		
		double x = rnd.Rannyu(0.,(D/2.));
		double theta = rnd.AcceptReject_Angle();
		//double theta = rnd.Rannyu(0., M_PI);
		if(x<(l/2.)*sin(theta)){
			Nhit++;
			Nthrows++;
		}
		else{Nthrows++;}		
	
	}
   
   ave[i]=2*(l/D)/float(Nhit/Nthrows);					//per ogni blocco calcolo la media
   av2[i]=pow(ave[i],2.);
      
   }

   for(int i=0; i<N; i++){		//con questo doppion ciclo sommo progressivamente le medie e le medie quadrate per poter calcolare la varianza e quindi l'errore con la funzione error
	for(int j=0; j<i+1; j++){
	   sum_prog[i]+=ave[j];
	   su2_prog[i]+=av2[j];
	   
	}
   sum_prog[i]/=(i+1);
   su2_prog[i]/=(i+1);
   fileout<<sum_prog[i]<<endl;			//stampo su file le stime dell'integrale ottenuto con il metodo delle medie a blocchi
   err_prog[i]=error(sum_prog, su2_prog, i);	//calcolo l'errore di ogni stima dell'integrale
   fileout2<<err_prog[i]<<endl;
   
  
   }

   fileout.close();
   fileout2.close();
 
   rnd.SaveSeed();
 
   return 0;
}


double error(double* AV, double* AV2, int l){
	if (l==0){
		return 0;
	}
	else{
		return sqrt((AV2[l]-pow(AV[l],2.))/l);
	}
}



	
