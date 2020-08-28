//parameters, observables
const int m_props=1000;
int n_props;
int iv,ik,it,ie;
double stima_pot, stima_kin, stima_etot, stima_temp;
double walker[1000];

// averages
double acc,att;
double blk_av[m_props],blk_norm;
double glob_av[m_props],glob_av2[m_props];
double err_gdir, stima_gdir, err_pot, err_kin, err_temp, err_etot;


//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part],xold[m_part],yold[m_part],zold[m_part];
double vx[m_part],vy[m_part],vz[m_part];

// thermodynamical state
int npart;
double energy,temp,vol,rho,box,rcut;

// simulation
int nstep, iprint, seed, nblk,nbins, igofr;
double delta;
bool restart;
double bin_size, deltaV;

//functions
void Input(void);
void Move(void);
void SetConf(void);
void ConfPreFinal(void);
void ConfFinal(void);
void ConfXYZ(int);
void Measure(void);
void Accumulate(void);
void Averages(int);
void Reset(int);
double Error(double, double, int);
double Force(int, int);
double Pbc(double);
