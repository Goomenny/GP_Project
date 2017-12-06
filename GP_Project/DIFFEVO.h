#pragma once
#include <iostream>
#include <ctime>
#include "TTree.h"
#include <random> 
#define MAXPOP  500
#define MAXDIM  35
#define IM1 2147483563
#define IM2 2147483399
#define IMM1 (IM1 - 1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1 + IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0 - EPS)
using namespace std;
class TDE {
private:
	int   i, j, L, n;      // counting variables                 
	int   r1, r2, r3, r4;  // placeholders for random indexes    
	int   r5;              // placeholders for random indexes    
	int   D;               // Dimension of parameter vector      
	int   NP;              // number of population members       
	int   imin;            // index to member with lowest energy 
	int   refresh;         // refresh rate of screen output      
	int   strategy;        // choice parameter for screen output 
	int   gen, genmax, seed;
	long  nfeval;          // number of function evaluations     
	double trial_energy;    // buffer variable                    
	double inibound_h;      // upper parameter bound              
	double inibound_l;      // lower parameter bound              
	double tmp[MAXDIM], best[MAXDIM], bestit[MAXDIM]; // members  
	double energy[MAXPOP];  // obj. funct. values                 
	double F, CR;           // control variables of DE            
	double emin;            // help variables                     

	long  rnd_uni_init;
	double c[MAXPOP][MAXDIM], d[MAXPOP][MAXDIM];
	double oldarray[MAXPOP][MAXDIM];
	double newarray[MAXPOP][MAXDIM];
	double swaparray[MAXPOP][MAXDIM];
	double vars[7];

	double r;

	mt19937 randeng;
	

public:
	void Init(double(*evaluate)(double[], double *, int, long *), double *bias);
	int CopyVector(double a[], double b[]);
	int CopyArray(double dest[MAXPOP][MAXDIM], double src[MAXPOP][MAXDIM]);
	double Start_fast(double(*evaluate)(double[],double *, int, long *),double *bias, TTree_symbolic &tree );

	double *Get_bestx() { return best; };
};
double rnd_uni(long *idum);