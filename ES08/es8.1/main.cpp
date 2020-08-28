#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"



//Questo programma utilizza l'algoritmo di Metropolis per campionare la densità di probabilità data dal modulo quadro della funzione di prova PsiTrial, quindi calcola il valore di aspettazione per H
using namespace std;

double mu=0.81;
double sigma=0.62; 

double error(double,double,int);
double Accettazione(double,double);

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

 ofstream fileout;
 fileout.open("H.dat");
 ofstream fileisto;
 fileisto.open("istogramma.dat");
 int N=10000;		//nunero step per blocco
 int M=1000000;		//numero passi
 //int L=M/N;
 double x;
 double r;
 
 double ave_Eloc, ave2_Eloc, sum_prog=0, su2_prog=0, mediaq;


 int m = 0;
 double sum=0;
 double p;

 double bin;
  
 double Eloc, V, PsiT;
 double istogramma[100];
 for(int i=0; i<100; i++){
	istogramma[i]=0;
 }
 double a=1.7;   //delta accettazione
 double a1, a2;
 double alpha;
 x=1.;		//punto di partenza
 
 float accepted=0, attempted=0;

	 for(int i=1; i<=M; i++){		//Metropolis
		p=rnd.Rannyu(x-a, x+a);
		alpha=Accettazione(x,p);
		r=rnd.Rannyu();
		//double norma=sqrt(M_PI)*3*sigma;
		if(r <= alpha){
			x=p;
			accepted++;
			
		}
		attempted++;
		V=pow(x,4)-(2.5)*pow(x,2);		//potenziale
		a1=pow((x-mu)/sigma,2.);
		a2=pow((x+mu)/sigma,2.);
		PsiT=exp(-a1/2.)+exp(-a2/2.);	//funzione d'onda di prova
		bin=(4.)/100;
		for (int l=0; l<100; l++){
			if(-2+l*bin<x && x<-2+(l+1)*bin){istogramma[l]++;}
		}
		Eloc=(-0.5*((a1-1)*exp(-a1/2.)+(a2-1)*exp(-a2/2.))/(sigma*sigma)+V*PsiT)/(PsiT);
	        sum+=Eloc;

		 if(i%N == 0){
			ave_Eloc=sum/N;
			sum_prog+=ave_Eloc;
        		ave2_Eloc=pow(ave_Eloc,2);
			su2_prog+=ave2_Eloc;
        		mediaq=su2_prog/(m+1);
			fileout<<sum_prog/(m+1)<<" "<<error(sum_prog/(m+1), mediaq, m)<<endl;
			m++;
			sum=0;
		}
	}

    for(int i=0; i<100; i++){
	fileisto<<istogramma[i]<<endl;
    }

   cout<<"Funzione d'onda di prova:"<<endl;	
   cout<<"Parametri sigma: "<<sigma<<" e mu: "<<mu<<endl;
   cout<<"accettazione "<<accepted/attempted<<endl;
   
   cout<<"valore di aspettazione dell'hamiltoniana: "<<sum_prog/m<<endl<<endl; 
   
   fileout.close();
   fileisto.close();
  

   return 0;
}

double Accettazione(double xp, double x){
	

	//double norma=sqrt(M_PI)*3*sigma;
	double p1=pow(exp(-pow((xp-mu)/sigma,2)/2)+exp(-pow((xp+mu)/sigma,2)/2),2);	//vecchio
	double p2=pow(exp(-pow((x-mu)/sigma,2)/2)+exp(-pow((x+mu)/sigma,2)/2),2);		//nuovo
	
	if(p2<p1){
		 return p2/p1;
	}
	else{
		return 1;
	}
}



double error(double AV, double AV2, int l){
	if (l==0){
		return 0;
	}
	else{
		return sqrt((AV2-pow(AV,2.))/l);
	}
}








