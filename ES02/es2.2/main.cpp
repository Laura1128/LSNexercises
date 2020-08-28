#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"


//3D Random walk in the continuum


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
 int N=100;
 int M=10000;
 int L=M/N;
 float x[M], y[M], z[M], d[M];
 double ave[N], av2[N], sum_prog[N], su2_prog[N], err_prog[N];
 double sum;
 int k;
 for(int i=0; i<M; i++){
	x[i]=0;
	y[i]=0;
	z[i]=0;
 }
 
 float r1, r2;
 for(int l=0; l<N; l++){

	 for(int i=0; i<M; i++){
		r1=rnd.Rannyu(0, 2*M_PI);
		r2=rnd.Rannyu(-1, 1);
		x[i]+=(cos(r1)*sqrt(1-pow(r2,2.)));
		y[i]+=(sin(r1)*sqrt(1-pow(r2,2.)));
		z[i]+=r2;
		d[i]=sqrt(pow(x[i],2)+pow(y[i],2)+pow(z[i],2));
		}

   	for(int h=0; h<N; h++){
		ave[h]=0;
		av2[h]=0;
		sum_prog[h]=0;
		su2_prog[h]=0;
		err_prog[h]=0;
	   }
  
        for(int g=0; g<N; g++){		
		sum=0;
		for(int j=0; j<L; j++){
		k=j+g*L;
		sum+=d[k];
	}
   
   ave[g]=sum/L;
   //cout<<"Medie: "<<endl;
   //cout<<ave[i]<<endl;
   av2[g]=pow(ave[g],2.);
   }

   for(int i=0; i<N; i++){		
	for(int j=0; j<i+1; j++){
	   sum_prog[i]+=ave[j];
	   su2_prog[i]+=av2[j];
	}
   sum_prog[i]/=(i+1);
   su2_prog[i]/=(i+1);
   err_prog[i]=error(sum_prog, su2_prog, i);
   if(i==N-1){
 	  fileout<<sum_prog[i]<<endl;
          fileout2<<err_prog[i]<<endl;
	}
   }
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









