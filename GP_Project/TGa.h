//---------------------------------------------------------------------------

#ifndef TGaH
#define TGaH
#include "TGAPopulation.h"
#include "TGASetting.h"
//---------------------------------------------------------------------------
class TGa : public TGASetting
{
private:
	TGAPopulation last_population;
	TGAPopulation new_population;
	TGAPopulation temp_population;

	int first_solution;
	bool found;

        double *left_limit,*right_limit;
	//Точность поиска
	double *E;
	//Длина бинарной строки
	int N;
        //Длина бинарной строки для переменной
	int *N_var[2];

        int dimension;

        vector< vector<double> > fitness;
        vector<double> tmp;


public:
	__fastcall TGa();

	void Init(bool,int,int,int,int,int,int,double,vector< vector<double> > &,int, double);  //Инициализация

	int Start_fast(TFuzzy &,bool);
	vector<double> Get_solution();
	double Get_fitness();

	int Get_first_solution();

        vector< vector<double> > Get_stats();


};
#endif
