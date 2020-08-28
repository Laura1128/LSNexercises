#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;

//Test del chi quadrato
 
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
   
   ofstream fileout("chiquadrati.txt");
   
   int M=1000000;
   int N=100;
   int L=M/N;
   double r[M];
   double media=0;

   for(int i=0; i<M; i++){  //riempio un vettore con M numeri casuali tra 0 e 1
      r[i]=rnd.Rannyu();
   };

   double frequenze[N];     //definisco un vettore atto a contenere le frequenze misurate
   int k=0;
   int b;
   double chi;

   for(int a=0; a<N; a++){	//100 test del chi-quadro

	   for(int i=0; i<N; i++){
		frequenze[i]=0;
   	   }
   	   chi=0;

  	   for(int i=0; i<L; i++){		
	
			b=k+i;
			for(int l=0; l<N; l++){
				if (l*0.01<=r[b] && r[b]<(l+1)*0.01){
					frequenze[l]++;
					break;
				}
			}
  	  }
  	  for(int i=0; i<N; i++){
	 	chi+=pow((frequenze[i]-(L/N)),2.);
   	  }

   	  fileout<<chi/(L/N)<<endl;
   	  media+=chi/(L/N);
   	  k+=10000;
   }
   cout<<"La media dei chi quadrati è: "<<media/100.<<endl;
   fileout.close();
   
   return 0;
}






	
