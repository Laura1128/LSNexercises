#include"Funzioni.h"
#include"FunzioneBase.h"
#include<cmath>

Seno::Seno(){}

Seno::~Seno(){}

double Seno::Eval(double x)const{
	return sin(x);
}

Coseno::Coseno(){}

Coseno::~Coseno(){}

double Coseno::Eval(double x)const{
	return cos(x);
}

Arcos::Arcos(){}

Arcos::~Arcos(){}

double Arcos::Eval(double x)const{
	return acos(x);
}
