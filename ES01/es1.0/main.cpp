#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

//Questo programma calcola il valor medio della distribuzione uniforme fra 0 e 1

using namespace std;

double error(double*,double*,int);
 
int main (int argc, char *argv[]){

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

   
   rnd.SaveSeed();
   
   ofstream fileout("medie.txt");
   ofstream fileout2("incertezze.txt");
   int M=100000;			//numero di lanci
   int N=100;				//numero di lanci per blocco
   int L=M/N;
   double r[M];

   for(int i=0; i<M; i++){
      r[i]=rnd.Rannyu();
   };

   double ave[N], av2[N], sum_prog[N], su2_prog[N], err_prog[N];
   for(int i=0; i<N; i++){
	ave[i]=0;
	av2[i]=0;
	sum_prog[i]=0;
	su2_prog[i]=0;
	err_prog[i]=0;
   }
   double sum;
   int k;
   for(int i=0; i<N; i++){		//con questo doppio ciclo calcolo le medie e le medie quadrate di ogni blocco
	sum=0;
	for(int j=0; j<L; j++){
		k=j+i*L;
		sum+=r[k];
	}
   
   ave[i]=sum/L;
   av2[i]=pow(ave[i],2.);
   }

   for(int i=0; i<N; i++){		//con questo doppio ciclo sommo progressivamente le medie e le medie quadrate per poter calcolare la varianza e quindi l'errore con la funzione error
	for(int j=0; j<i+1; j++){
	   sum_prog[i]+=ave[j];
	   su2_prog[i]+=av2[j];
	}
   sum_prog[i]/=(i+1);
   su2_prog[i]/=(i+1);
   fileout<<sum_prog[i]<<endl;
   err_prog[i]=error(sum_prog, su2_prog, i);
   fileout2<<err_prog[i]<<endl;
   }

   fileout.close();
   fileout2.close();
 
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



	
