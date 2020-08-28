#include"Vettore.h"


Vettore::Vettore(){
	m_N=0;
	m_v=0;
}

Vettore::Vettore(unsigned int N){
	m_N=N;
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

Vettore Vettore::medie(unsigned int N, int S){	//aggiungere un controllo
	Vettore r(N);
	int u=0;
	for(int i=0; i<N; i++){
		double somma=0;
		for(int j=u; j<u+S; j++){
			somma+=m_v[j];
		}
		r.SetComponent(i,somma/S);
		u=(i+1)*S;
	}
	return r;
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
	
