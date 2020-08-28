#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

//Questo programma utilizza l'algoritmo di Metropolis per campionare le densità di probabilità date dal modulo quadro della funzione d'onda dello stato fondamentale e dello stato 2p dell'atomo di idrogeno

using namespace std;

double error(double,double,int);
double Accettazione(double, double, double, double, double, double);
double Accettazione2(double, double, double, double, double, double);
 
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

 ofstream fileout("stato1s.dat");
 ofstream fileout2("stato2p.dat");
 ofstream filemisure;
 filemisure.open("misure1s.dat");
 ofstream filemisure2;
 filemisure2.open("misure2p.dat");
 
 
 int N=2000;		//lunghezza blocco
 int M=2000000;
 //int L=M/N;
 double x, y, z; 
 double xb, yb, zb;
 double ave_raggio, ave2_raggio, sum_prog=0, su2_prog=0, mediaq;
 double ave_raggioB, ave2_raggioB, sum_progB=0, su2_progB=0, mediaqB;

 int m = 0;
 double sum=0, sum2=0;
 double a=0.0529;	//raggio di Bohr
 double p, q, s, r;	//coordinate del punto di prova
 double pb, qb, sb; 
 double raggio;
 double raggio2;

 double alpha, alpha2;
 x=0;
 y=0;
 z=0;
 xb=0;
 yb=0;
 zb=5*a;


 int yes=0, nope=0;
 int yesb=0, nopeb=0;

	 for(int i=1; i<=M; i++){
		p=rnd.Rannyu(x-a, x+a);
		q=rnd.Rannyu(y-a, y+a);
		s=rnd.Rannyu(z-a, z+a);
		alpha=Accettazione(p, q, s, x, y, z);

		pb=rnd.Rannyu(xb-3*a, xb+3*a);
		qb=rnd.Rannyu(yb-3*a, yb+3*a);
		sb=rnd.Rannyu(zb-3*a, zb+3*a);
		alpha2=Accettazione2(pb, qb, sb, xb, yb, zb);
		
		r=rnd.Rannyu();
		if(r <= alpha){
			x=p;
			y=q;
			z=s;
			yes++;
			
		}else{
			nope++;
		}
		fileout << x <<" "<< y <<" "<< z <<endl;
		raggio=sqrt(pow(x,2.)+pow(y,2.)+pow(z,2.))/a;
	        sum+=raggio;
		if(r <= alpha2){
			xb=pb;
			yb=qb;
			zb=sb;
			yesb++;
		
		}else{
			nopeb++;
		}
		fileout2 << xb <<" "<< yb <<" "<< zb <<endl;
	        raggio2=sqrt(pow(xb,2.)+pow(yb,2.)+pow(zb,2.))/a;
	        sum2+=raggio2;

		 if(i%N == 0){
			ave_raggio=sum/N;
			sum_prog+=ave_raggio;
        		ave2_raggio=pow(ave_raggio,2);
			su2_prog+=ave2_raggio;
        		mediaq=su2_prog/(m+1);
			filemisure<<sum_prog/(m+1)<<" "<<error(sum_prog/(m+1), mediaq, m)<<endl;
			ave_raggioB=sum2/N;
			sum_progB+=ave_raggioB;
        		ave2_raggioB=pow(ave_raggioB,2);
			su2_progB+=ave2_raggioB;
        		mediaqB=su2_progB/(m+1);
			filemisure2<<sum_progB/(m+1)<<" "<<error(sum_progB/(m+1), mediaqB, m)<<endl;
			m++;
			sum=0;
			sum2=0;
		}
	}

   cout<<"STATO FONDAMENTALE:"<<endl;	
   cout<<"mossa accettata "<<yes<<" volte."<<endl;
   cout<<"mossa rifiutata "<<nope<<" volte"<<endl;
   cout<<"misura del raggio: "<<sum_prog/m<<", raggio atteso: "<<3./2.<<endl<<endl; 
   cout<<"STATO ECCITATO:"<<endl;	
   cout<<"mossa accettata "<<yesb<<" volte."<<endl;
   cout<<"mossa rifiutata "<<nopeb<<" volte"<<endl;
   cout<<"misura del raggio: "<<sum_progB/m<<", raggio atteso: "<<5<<endl<<endl; 
  
   fileout.close();
   fileout2.close();
   filemisure.close();
   filemisure2.close();
	

   return 0;
}

double Accettazione(double xp, double yp, double zp, double x, double y, double z){
        double a=0.0529;
	double r1=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	double r2=sqrt(pow(xp,2)+pow(yp,2)+pow(zp,2));
	double p1=(pow(a,-3)/M_PI)*exp(-2*r1/a);
	double p2=(pow(a,-3)/M_PI)*exp(-2*r2/a);
	
	if(p2<p1){
		 return p2/p1;
	}
	else{
		return 1;
	}
}

double Accettazione2(double xp, double yp, double zp, double x, double y, double z){
        double a=0.0529;
	double r1=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	double r2=sqrt(pow(xp,2)+pow(yp,2)+pow(zp,2));
	double p1=(pow(a,-5)/(8*M_PI))*pow(z,2)*exp(-r1/a);
	double p2=(pow(a,-5)/(8*M_PI))*pow(zp,2)*exp(-r2/a);
	
	if(p2<p1) {
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








