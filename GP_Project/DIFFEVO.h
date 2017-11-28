#pragma once
#include <iostream>
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
	float trial_energy;    // buffer variable                    
	float inibound_h;      // upper parameter bound              
	float inibound_l;      // lower parameter bound              
	float tmp[MAXDIM], best[MAXDIM], bestit[MAXDIM]; // members  
	float energy[MAXPOP];  // obj. funct. values                 
	float F, CR;           // control variables of DE            
	float emin;            // help variables                     

	long  rnd_uni_init;
	float c[MAXPOP][MAXDIM], d[MAXPOP][MAXDIM];
	float oldarray[MAXPOP][MAXDIM];
	float newarray[MAXPOP][MAXDIM];
	float swaparray[MAXPOP][MAXDIM];

	float rnd_uni(long *idum);
	float r;
public:
	void Init(float(*evaluate)(int, float[], long *));
	int CopyVector(float a[], float b[]);
	int CopyArray(float dest[MAXPOP][MAXDIM], float src[MAXPOP][MAXDIM]);
	float Start_fast(float(*evaluate)(int, float[], long *));


};