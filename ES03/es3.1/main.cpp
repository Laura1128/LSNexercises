#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "Vettore.h"

//Plain Vanilla Option Pricing

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

 ofstream fileout("Calldiretta.txt");
 ofstream fileout2("Calldiscr.txt");
 ofstream fileoutP("Putdiretta.txt");
 ofstream fileoutP2("Putdiscr.txt");
 ofstream fileoutI("IncertezzeC1.txt");
 ofstream fileoutI2("IncertezzeC2.txt");
 ofstream fileoutIP("IncertezzeP1.txt");
 ofstream fileoutIP2("IncertezzeP2.txt");
 int N=100;		//numero di blocchi
 int M=10000;		//numero di lanci
 Vettore Ccall(M), Cput(M), Sd(N), Cdcall(M), Cdput(M);
 Vettore medieCall(N), mediePut(N), medieCalld(N), mediePutd(N), IncC1(N), IncC2(N), IncP1(N), IncP2(N);
 float S;		//asset price
 float S0=100;		//asset price at t=0
 float T=1;		//delivery time
 float K= 100;		//strike price
 float r=0.1;		//risk-free interest rate
 float Sigma=0.25;	//volatility

 float t=0.01;
 
 float p, pn;
 

	 for(int i=0; i<M; i++){						//numero esperimenti
		p=rnd.Gauss(0.,1.);						//genero un numero casuale distribuito normalmente
		S=S0 * exp((r-pow(Sigma,2)/2)*T + Sigma*sqrt(T)*p);		//faccio una stima del prezzo al tempo T
                
		if(S>K) {
			Ccall.SetComponent(i,exp(-r*T)*(S-K));
			Cput.SetComponent(i,0);
		}
		else {
			Cput.SetComponent(i,exp(-r*T)*(K-S));
			Ccall.SetComponent(i,0);
		}
		Sd.SetComponent(0,S0 * exp((r-pow(Sigma,2)/2)*t + Sigma*sqrt(t)*p));
		for(int y=1; y<N; y++){							//ciclo interno per simulare il prezzo al variare del tempo
			pn=rnd.Gauss(0.,1.);
			Sd.SetComponent(y,Sd.GetComponent(y-1) * exp((r-pow(Sigma,2)/2)*t + Sigma*sqrt(t)*pn));		//stimo il prezzo a tempi discreti 
		}
	        if(Sd.GetComponent(N-1)>K) { 
			Cdcall.SetComponent(i,exp(-r*T)*(Sd.GetComponent(N-1)-K));
			Cdput.SetComponent(i,0);
		}
		else { 
			Cdcall.SetComponent(i,0);
			Cdput.SetComponent(i,exp(-r*T)*(K-Sd.GetComponent(N-1)));
		}
		
	}
   	
  medieCall=Ccall.Medieablocchi(N);
  mediePut=Cput.Medieablocchi(N);
  medieCalld=Cdcall.Medieablocchi(N);
  mediePutd=Cdput.Medieablocchi(N);
  IncC1=Ccall.Incertezze();
  IncC2=Cdcall.Incertezze();
  IncP1=Cput.Incertezze();
  IncP2=Cdput.Incertezze();
  

  for(int i=0; i<N; i++){
   fileout<<medieCall.GetComponent(i)<<endl;
   fileoutP<<mediePut.GetComponent(i)<<endl;
   fileout2<<medieCalld.GetComponent(i)<<endl;
   fileoutP2<<mediePutd.GetComponent(i)<<endl;
   fileoutI<<IncC1.GetComponent(i)<<endl;
   fileoutIP<<IncP1.GetComponent(i)<<endl;
   fileoutI2<<IncC2.GetComponent(i)<<endl;
   fileoutIP2<<IncP2.GetComponent(i)<<endl;


   }
   

   fileout.close();
   fileout2.close();
   fileoutP.close();
   fileoutP2.close();
   fileoutI.close();
   fileoutI2.close();
   fileoutIP.close();
   fileoutIP2.close();

   return 0;
}







