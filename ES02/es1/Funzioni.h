#ifndef _Seno_h_
#define _Seno_h_

#include"FunzioneBase.h"

class Seno: public FunzioneBase{
public:
	Seno();
	~Seno();
	virtual double Eval(double x)const;
};

#endif

#ifndef _Coseno_h_
#define _Coseno_h_

#include"FunzioneBase.h"

class Coseno: public FunzioneBase{
public:
	Coseno();
	Coseno(double a);
	~Coseno();
	virtual double Eval(double x)const;
	/*virtual double Eval2(double x)const;
private:
	double _a;*/
};

#endif

#ifndef _Arcos_h_
#define _Arcos_h_

#include"FunzioneBase.h"

class Arcos: public FunzioneBase{
public:
	Arcos();
	~Arcos();
	virtual double Eval(double x)const;
};

#endif
