#ifndef _Individuo_h
#define _Individuo_h_

#include <vector>
#include<cmath>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

class Individuo{
public:
	Individuo();
	~Individuo();
	//Individuo(const Individuo&);

	Individuo& operator=(const Individuo&);

	double Fitness() const;
	void Stampa();
	void PrintPath(int);
	void SetGene(int, float, float);
	// GetGene(int, float, float);
	float GetComponent(int,int);

	bool Check();
	
	void SaveFirst();

	void MutationA(float);
	void MutationB(float);
	void MutationC(float);
	void MutationD(float);
	void Crossover(Individuo, int, float);


private:
	vector < vector <float> > m_A; 
	float m_x0, m_y0;
	int m_N;
	int m_C;
	int Pbc(int);
	void Permuta(int,int);

	
};

#endif
