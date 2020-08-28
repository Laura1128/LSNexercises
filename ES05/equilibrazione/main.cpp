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
 ofstream filer("raggio_istantaneo1s.dat");
 ofstream filer2("raggio_istantaneo2p.dat");
 
 int M=2000;
 float c, d;
 /*cout<<"inserisci un fattore moltiplicativo per lo stato fondamentale"<<endl;
 cin>>d;
 cout<<"inserisci un fattore moltiplicativo per lo stato eccitato"<<endl;
 cin>>c;*/
 double x, y, z; 
 double xb, yb, zb;
 c=3;
 d=1;

 
 double a=0.0529;	//raggio di Bohr
 double p, q, s, r;	//coordinate del punto di prova
 double pb, qb, sb; 

 double alpha, alpha2;
 x=0;
 y=20*a;
 z=10*a;
 xb=0;
 yb=20*a;
 zb=40*a;


 int yes=0, nope=0;
 int yesb=0, nopeb=0;

//Devo impostare la T(x/y) in modo da ottenere il 50% di mosse accettate e il 50% di mosse rifiutate
	 for(int i=1; i<=M; i++){
		p=rnd.Rannyu(x-d*a, x+d*a);
		q=rnd.Rannyu(y-d*a, y+d*a);
		s=rnd.Rannyu(z-d*a, z+d*a);
		alpha=Accettazione(p, q, s, x, y, z);

		pb=rnd.Rannyu(xb-c*a, xb+c*a);
		qb=rnd.Rannyu(yb-c*a, yb+c*a);
		sb=rnd.Rannyu(zb-c*a, zb+c*a);
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
		
	       
		if(r <= alpha2){
			xb=pb;
			yb=qb;
			zb=sb;
			yesb++;
		
		}else{
			nopeb++;
		}
		fileout2 << xb <<" "<< yb <<" "<< zb <<endl;
	        filer<<sqrt(pow(x,2.)+pow(y,2.)+pow(z,2.))/a<<endl;
		filer2<<sqrt(pow(xb,2.)+pow(yb,2.)+pow(zb,2.))/a<<endl;
	     

	}
   cout<<endl;
   cout<<"STATO FONDAMENTALE:"<<endl;
   cout<<"E stato usato il fattore "<<d<<endl;	
   cout<<"mossa accettata "<<yes<<" volte."<<endl;
   cout<<"mossa rifiutata "<<nope<<" volte"<<endl;
   cout<<"Accettazione: "<<(yes/float(yes+nope))<<endl;
   cout<<"misura del raggio raggio atteso: "<<3./2.<<endl;
   cout<<"si consiglia di usare il fattore d fra 6/5 e 5/4 "<<endl<<endl; 
   cout<<"STATO ECCITATO:"<<endl;
   cout<<"E stato usato il fattore "<<c<<endl;	
   cout<<"mossa accettata "<<yesb<<" volte."<<endl;
   cout<<"mossa rifiutata "<<nopeb<<" volte"<<endl;
   cout<<"Accettazione: "<<(yesb/float(yesb+nopeb))<<endl;
   cout<<"misura del raggio atteso: "<<5<<endl;
   cout<<"si consiglia di usare il fattore c=3"<<endl;

   fileout.close();
   fileout2.close();
   filer.close();
   filer2.close();  

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








