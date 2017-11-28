//---------------------------------------------------------------------------

#ifndef TGenotypeH
#define TGenotypeH
#include <vector>
#include <math.h>
using namespace std;
//---------------------------------------------------------------------------
class TGenotype
{
friend class TGAPopulation;
friend class TGa;
friend class TGASetting;
private:
	double fitness;
        int dimension;
        vector<int> gen;
        vector<double> value;

public:
	void Init(int,int);
        void Get_value(int *[],double *,double *);
        void Calculate_fitness();
        void Crossover(int,const TGenotype &,const TGenotype &);
        void Mutate(int,double);

};
#endif
