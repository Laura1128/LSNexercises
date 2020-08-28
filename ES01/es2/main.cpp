#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "Vettore.h"

using namespace std;


 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[5];
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

   ofstream fileout("uniforme.txt");
   ofstream fileout2("esponenziale.txt");
   ofstream fileout3("lorenziana.txt");
   ofstream fileoutA("uniformeA.txt");
   ofstream fileout2A("esponenzialeA.txt");
   ofstream fileout3A("lorenzianaA.txt");
   ofstream fileoutB("uniformeB.txt");
   ofstream fileout2B("esponenzialeB.txt");
   ofstream fileout3B("lorenzianaB.txt");
   ofstream fileoutC("uniformeC.txt");
   ofstream fileout2C("esponenzialeC.txt");
   ofstream fileout3C("lorenzianaC.txt");

   int M=1000000;
   unsigned int N=10000;
   
   Vettore U(M);
   for(int i=0; i<M; i++){
      U.SetComponent(i,rnd.Rannyu());
   };
   Vettore E(M);
   for(int i=0; i<M; i++){
      E.SetComponent(i,rnd.Exp(1.));
   };
   Vettore L(M);
   for(int i=0; i<M; i++){
      L.SetComponent(i,rnd.Lorentz(0.,1.));
   };

   for(int i=0; i<N; i++){
      fileout<<U.GetComponent(i)<<endl;
   };
   
   for(int i=0; i<N; i++){
      fileout2<<E.GetComponent(i)<<endl;
   };
   
   for(int i=0; i<N; i++){
      fileout3<<L.GetComponent(i)<<endl;
   };

  Vettore U_A=U.medie(N,2);
  for(int i=0; i<N; i++){
	fileoutA<<U_A.GetComponent(i)<<endl;
  }
  Vettore U_B=U.medie(N,10);
  for(int i=0; i<N; i++){
	fileoutB<<U_B.GetComponent(i)<<endl;
  }
  Vettore U_C=U.medie(N,100);
  for(int i=0; i<N; i++){
	fileoutC<<U_C.GetComponent(i)<<endl;
  }
  Vettore E_A=E.medie(N,2);
  for(int i=0; i<N; i++){
	fileout2A<<E_A.GetComponent(i)<<endl;
  }
  Vettore E_B=E.medie(N,10);
  for(int i=0; i<N; i++){
	fileout2B<<E_B.GetComponent(i)<<endl;
  }
  Vettore E_C=E.medie(N,100);
  for(int i=0; i<N; i++){
	fileout2C<<E_C.GetComponent(i)<<endl;
  }
  Vettore L_A=L.medie(N,2);
  for(int i=0; i<N; i++){
	fileout3A<<L_A.GetComponent(i)<<endl;
  }
  Vettore L_B=L.medie(N,10);
  for(int i=0; i<N; i++){
	fileout3B<<L_B.GetComponent(i)<<endl;
  }
   Vettore L_C=L.medie(N,100);
  for(int i=0; i<N; i++){
	fileout3C<<L_C.GetComponent(i)<<endl;
  }
   fileout.close();
   fileout2.close();
   fileout3.close();
   fileoutA.close();
   fileout2A.close();
   fileout3A.close();
   fileoutB.close();
   fileout2B.close();
   fileout3B.close();
   fileoutC.close();
   fileout2C.close();
   fileout3C.close();

   rnd.SaveSeed();
   return 0;
}










