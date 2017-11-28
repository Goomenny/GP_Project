//---------------------------------------------------------------------------

#ifndef TFuzzyH
#define TFuzzyH
#include "TTruck.h"
#include <vector>
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
//---------------------------------------------------------------------------
class TFuzzy
{
friend class TTree_fuzzy;

private:
    int n_var; // Кол-во входных переменных   (параметров системы)
    vector< vector<double> > k; //Параметры лингвистических переменных [номер переменной][коэффициент]
	double **mk;
    vector<double> edge;
    int a;     //Макс число шагов при тестировании
    vector<double> ki; //Уровень значимости i-го параметра системы
    double pic;//Текущее значение i-го параметра системы;
    double pim;//Максимальное реально достигаемое значение i-го параметра системы;
    vector< vector<int> > rules;
    vector<int> n_terms;
    vector< vector<double> > truth;
    TTruck truck;

    vector< vector<double> > ErrorK;
    vector< vector<int> > ErrorRules;
    vector< double> ErrorVar;
    int ErrorN;

public:
    TFuzzy();
    void Init(int,int *,vector<double> &);
    void Set_truck(TTruck &);
    double Fuzzy_output(const vector<double>&);
    double Three_terms(double,int,double);
    double f();
    double Terms(double, int,const vector<double> &);
    void Set_k(const vector<double> &);
    void Set_rules(const vector< vector<int> >&);
};
#endif
