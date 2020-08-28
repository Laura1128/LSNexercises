#include"Vettore.h"
#include<cmath>


Vettore::Vettore(){
	m_N=0;
	m_v=0;
	m_media=false;
}

Vettore::Vettore(unsigned int N){
	m_N=N;
	m_media=false;
	m_v=new double[m_N];
	for(int i=0; i<m_N; i++){
		m_v[i]=0;
	}
}

Vettore::~Vettore(){
	delete[] m_v;
}

//implementazione dei metodi
void Vettore::SetComponent(unsigned int k, double x){
	if(k>(m_N-1)){
		std::cerr<<"Il vettore ha solo "<<m_N<<" componenti!"<<endl;
	}
	else{
		 m_v[k]=x;
	}
	
}
double Vettore::GetComponent(unsigned int k)const{
	double y=0;
	if(k>(m_N-1)){
		std::cerr<<"Il vettore ha solo "<<m_N<<" componenti!"<<endl;
	}
	else{
		y=m_v[k];
	}
	return y;
}

//implementazione del copy constructor
Vettore::Vettore(const Vettore& V){
	m_N=V.m_N;
	m_v=new double[m_N];
	for(int i=0; i<m_N;i++) m_v[i]=V.m_v[i];
}
//implementazione dell'operatore di assegnazione
Vettore& Vettore::operator=(const Vettore& V){
	m_N=V.m_N;
	if(m_v) delete[] m_v;	//perchè questa condizione??
	m_v=new double[m_N];
	for(int i=0; i<m_N; i++) m_v[i]=V.m_v[i];
	return *this;
}


Vettore Vettore::Medieablocchi(unsigned int N){
        m_Nblocchi=N;
	int L=m_N/N;
	int k;
	float sum;
	Vettore ave(N), av2(N), sum_prog(N), su2_prog(N), err_prog(N);
	 for(int g=0; g<N; g++){		//con questo doppio ciclo calcolo le medie e le medie quadrate di ogni blocco
		sum=0;
		for(int j=0; j<L; j++){
		k=j+g*L;
		sum+=m_v[k];
		}
        ave.SetComponent(g,sum/L);
	av2.SetComponent(g,pow(sum/L,2));
	}

	for(int i=0; i<N; i++){		//con questo doppion ciclo sommo progressivamente le medie e le medie quadrate per poter calcolare la varianza e quindi l'errore con la funzione error
	for(int j=0; j<i+1; j++){
	   sum_prog.SetComponent(i,sum_prog.GetComponent(i)+ave.GetComponent(j));
	   su2_prog.SetComponent(i,su2_prog.GetComponent(i)+av2.GetComponent(j));
	}
       sum_prog.SetComponent(i,sum_prog.GetComponent(i)/(i+1));
       su2_prog.SetComponent(i,su2_prog.GetComponent(i)/(i+1));
	}
   m_media=true;
   return sum_prog;
}


Vettore Vettore::Incertezze(){
	
	unsigned int N=m_Nblocchi;
	int L=m_N/N;
	int k;
	float sum;
	Vettore ave(N), av2(N), sum_prog(N), su2_prog(N), err_prog(N);
	if (m_media==false){
		cout<<"Prima è necessario calcolare le medie con il metodo Medieablocchi"<<endl;
	}
	else{
		
		 for(int g=0; g<N; g++){		//con questo doppio ciclo calcolo le medie e le medie quadrate di ogni blocco
			sum=0;
				for(int j=0; j<L; j++){
				k=j+g*L;
				sum+=m_v[k];
				}
        	ave.SetComponent(g,sum/L);
		av2.SetComponent(g,pow(sum/L,2));
		}
	
		for(int i=0; i<N; i++){		//con questo doppion ciclo sommo progressivamente le medie e le medie quadrate per poter calcolare la varianza e quindi l'errore con la funzione error
		for(int j=0; j<i+1; j++){
			   sum_prog.SetComponent(i,sum_prog.GetComponent(i)+ave.GetComponent(j));
			   su2_prog.SetComponent(i,su2_prog.GetComponent(i)+av2.GetComponent(j));
		}
   		sum_prog.SetComponent(i,sum_prog.GetComponent(i)/(i+1));
   		su2_prog.SetComponent(i,su2_prog.GetComponent(i)/(i+1));
   
   		if(i==0){err_prog.SetComponent(i,0);}
 	        else{
		        err_prog.SetComponent(i,sqrt((su2_prog.GetComponent(i)-pow(sum_prog.GetComponent(i),2.))/i));
   		}
		}
		} 
   
   	return err_prog;
}	

	
