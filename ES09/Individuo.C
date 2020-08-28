#include"Individuo.h"

Individuo::Individuo(){				//costruisco una matrice Nx2 inizializzata con 0.
	m_N=32;
	m_C=2;
	m_A.resize(m_N);
	for(int i=0; i<m_N; i++){
		m_A[i].resize(2);
	}
	for (int i=0; i<m_N; i++){
		for(int j=0; j<m_C; j++){
			m_A[i][j]=0.;
		}
	}
	srand(time(NULL));
}

Individuo::~Individuo(){
		
}

Individuo& Individuo::operator=(const Individuo& Ind){
	m_N = Ind.m_N;
	m_C = Ind.m_C;
	m_A.resize(m_N);
	for(int i=0; i<m_N; i++){
		m_A[i].resize(m_C);
	}
	for (int i=0; i<m_N; i++){
		for(int j=0; j<m_C; j++){
			m_A[i][j]=Ind.m_A[i][j];
		}
	}
	return *this;
}

void Individuo::SaveFirst(){
	m_x0=m_A[0][0];			//salvo le coordinate della prima città
	m_y0=m_A[0][1];
}

void Individuo::SetGene(int n, float x, float y){	//SetGene mi permette di inserire un elemento
	m_A[n][0]=x;
	m_A[n][1]=y;
}

float Individuo::GetComponent(int i, int j){
	float c = m_A[i][j];
	return c;
}


double Individuo::Fitness()const{
	float dist=0;
	for (int i=0; i<m_N-1; i++){
		 dist+=sqrt(pow(m_A[i][0]-m_A[i+1][0],2)+pow(m_A[i][1]-m_A[i+1][1],2));
	}
	dist+=sqrt(pow(m_A[m_N-1][0]-m_A[1][0],2)+pow(m_A[m_N-1][1]-m_A[1][1],2));
	return dist;
}

void Individuo::Stampa(){
	for(int i=0; i <m_N; i++){
		for (int j=0; j<m_C; j++){
			cout<<m_A[i][j]<<" ";
		}
	cout<<endl;
	}
}

void Individuo::PrintPath(int n){
	const string fileName = "BestPath";
	const string fileType = ".dat";
	stringstream ss;
	int num =n;
	ofstream Best;
	ss<<fileName<<num<<fileType;
	Best.open(ss.str().c_str());
	for(int i=0; i <m_N; i++){
		for (int j=0; j<m_C; j++){
			Best<<m_A[i][j]<<" ";
		}
	Best<<endl;
	}
	Best.close();
}

bool Individuo:: Check(){
	if(m_A[0][0]!=m_x0 or m_A[0][1]!=m_y0){
		cout<<"errore: primo gene diverso da quello atteso"<<endl;
		return 0;
	}
	for(int i=0; i<m_N-1; i++){
		for(int j=i+1; j<m_N; j++){
			if(m_A[i][1]==m_A[j][1]){
			cout<<"errore:lo stesso gene appare piu volte"<<endl;
			return 0;
			}
		}
	}
	return 1;
}


void Individuo::MutationA(float a){
	float r = ((float)rand())/(float)RAND_MAX;
	if(r<a){
		int v = rand()%(m_N-1) +1;
		int u = rand()%(m_N-1) +1;
		Permuta(v,u);
	}
}

void Individuo::Permuta(int v, int r){
	vector < vector <float> > New = m_A;
	float a= m_A[v][0];
	float b= m_A[v][1];
	New[v][0]=m_A[r][0];
	New[v][1]=m_A[r][1];
	New[r][0]=a;
	New[r][1]=b;
	m_A=New;
}



void Individuo::MutationB(float b){
	float r = ((float)rand())/(float)RAND_MAX;
	if(r<b){
		vector < vector <float> > Old = m_A;
		vector < vector <float> > New = m_A;
		int v = rand()%(m_N-1) +1;	//scelgo la posizione della prima città da spostare
		int r = rand()%(m_N-2) +1;	//quante città contigue spostare
		int q = rand()%(m_N-2) +1;	//di quante posizioni si spostano
		for(int j=v; j<v+r; j++){
			New[Pbc(j+q)][0]=Old[Pbc(j)][0];
			New[Pbc(j+q)][1]=Old[Pbc(j)][1];
		}
		for(int j=Pbc(v+r); j<Pbc(v+r)+m_N-1-r; j++){
			New[Pbc(j+q)][0]=Old[Pbc(j)][0];
			New[Pbc(j+q)][1]=Old[Pbc(j)][1];
		}
	m_A=New;
	}
}


void Individuo::MutationC(float c){
	float r = ((float)rand())/(float)RAND_MAX;
	if(r<c){
		vector < vector <float> > Old = m_A;
		vector < vector <float> > New = m_A;
		int v = rand()%(m_N-1) +1;	//scelgo la posizione della prima città da spostare
		int r = rand()%(m_N-2)/2 +1;	//numero di città da permutare
		for(int j=v; j<v+r; j++){
			Permuta( Pbc(j),Pbc(j+r));
		}
	}
}

void Individuo::MutationD(float d){
	float r = ((float)rand())/(float)RAND_MAX;
	if(r<d){
		vector < vector <float> > Old = m_A;
		vector < vector <float> > New = m_A;
		int v = rand()%(m_N-1) +1;	//scelgo la posizione della prima città 
		int r = rand()%(m_N-1) +1;	//quante città contigue invertire
		int n=1;
		for(int j=v; j<v+r; j++){
			New[Pbc(j)][0]=Old[Pbc(v+r-n)][0];
			New[Pbc(j)][1]=Old[Pbc(v+r-n)][1];
			n++;
		}
	m_A=New;
	}
}


int Individuo:: Pbc(int j){
		
	int s = int(j/m_N);
	j=j-s*((m_N)-1);
	if(j>=m_N){j=Pbc(j);}
	return j;
	
}




void Individuo:: Crossover(Individuo G, int v, float r){
	vector < vector <float> >  A = m_A;
	if(r<0.8){	
		for(int i=0; i<v; i++){
			for(int j=0; j<m_N; j++){
				if(A[i][0]==G.GetComponent(j,0)){			
					G.SetGene(j,9.,9.);
					break;
				}
			}
		}
		for(int i=v; i<m_N; i++){
			for(int j=0; j<m_N; j++){
				if(G.GetComponent(j,0)!=9.){
					A[i][0]=G.GetComponent(j,0);
					A[i][1]=G.GetComponent(j,1);
					G.SetGene(j,9.,9.);
					break;
				}
			}
		}
	}
	m_A = A;
}











