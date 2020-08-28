#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "Funzioni.h"

using namespace std;

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

   
   
   
   ofstream fileout("medie.txt");
   ofstream fileout2("incertezze.txt");
   ofstream fileoutI("medieI.txt");
   ofstream fileout2I("incertezzeI.txt");
   int M=10000;
   int N=100;
   int L=M/N;
   double r[M];
   double s[M];
   FunzioneBase *ACOS=new Arcos();

   for(int i=0; i<M; i++){
      r[i]=rnd.Rannyu();
      s[i]=rnd.AcceptReject(0., 1., M_PI/2., ACOS);		//genero numeri casuali distribuiti secondo la distribuzione p(x)=arcos(x)
      //cout<<"numeri casuali: "<<r[i]<<" "<<s[i]<<endl;
   };

   double ave[N];
   double av2[N];
   double sum_prog[N];
   double su2_prog[N];
   double err_prog[N];
   double aveI[N];
   double av2I[N];
   double sum_progI[N];
   double su2_progI[N];
   double err_progI[N];
   for(int i=0; i<N; i++){
	ave[i]=0;
	av2[i]=0;
	sum_prog[i]=0;
	su2_prog[i]=0;
	err_prog[i]=0;
        aveI[i]=0;
	av2I[i]=0;
	sum_progI[i]=0;
	su2_progI[i]=0;
	err_progI[i]=0;
   }
   double sum;
   double sumI;
   int k;
   for(int i=0; i<N; i++){		//con questo doppio ciclo calcolo le medie e le medie quadrate di ogni blocco
	sum=0;
	sumI=0;
	for(int j=0; j<L; j++){
		k=j+i*L;
		sum+=((M_PI)/2.)*cos(M_PI*r[k]/2.);		//sommo i valori di f(x)=(PI/2)cos(x*PI/2) dove x variabile distribuita uniformemente
		sumI+=((M_PI/2.)*cos(M_PI*s[k]/2.)/acos(s[k]));	//sommo i valori di g(x)=(PI/2)cos(x*PI/2)/arccos(x) dove x variabile distribuita secondo p(x)
	}
   
   ave[i]=sum/L;					//per ogni blocco calcolo la media
   aveI[i]=sumI/L;
   //cout<<"Medie: "<<endl;
   //cout<<ave[i]<<" "<<aveI[i]<<endl;
   av2[i]=pow(ave[i],2.);
   av2I[i]=pow(aveI[i],2.);
   }

   for(int i=0; i<N; i++){		//con questo doppio ciclo sommo progressivamente le medie e le medie quadrate per poter calcolare la varianza e quindi l'errore con la funzione error
	for(int j=0; j<i+1; j++){
	   sum_prog[i]+=ave[j];
	   su2_prog[i]+=av2[j];
	   sum_progI[i]+=aveI[j];
	   su2_progI[i]+=av2I[j];
	}
   sum_prog[i]/=(i+1);
   su2_prog[i]/=(i+1);
   sum_progI[i]/=(i+1);
   su2_progI[i]/=(i+1);
   fileout<<sum_prog[i]<<endl;			//stampo su file le stime dell'integrale ottenuto con il metodo delle medie a blocchi
   err_prog[i]=error(sum_prog, su2_prog, i);	//calcolo l'errore di ogni stima dell'integrale
   fileout2<<err_prog[i]<<endl;
   fileoutI<<sum_progI[i]<<endl;
   err_progI[i]=error(sum_progI, su2_progI, i);
   fileout2I<<err_progI[i]<<endl;
   }

   fileout.close();
   fileout2.close();
   fileoutI.close();
   fileout2I.close();
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



	
