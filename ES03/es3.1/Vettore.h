#ifndef _Vettore_h_
#define _Vettore_h_

#include<iostream>
using namespace std;

class Vettore{
public:
	Vettore();		//costruttore di default
	Vettore(unsigned int N);//costruttore con dimensione del vettore
	~Vettore();		//distruttore

	unsigned int GetN() const {return m_N;}
	void SetComponent(unsigned int, double);
	double GetComponent(unsigned int) const;

	Vettore(const Vettore&);		//copy constructor
	Vettore& operator=(const Vettore&);	//overloading dell'operatore di assegnazione

	Vettore Medieablocchi(unsigned int N);
	Vettore Incertezze();

protected:
	unsigned int m_N;	//dimensione del vettore
	double* m_v;		//puntatore a double
	unsigned int m_Nblocchi;
	bool m_media;
};

#endif
