//---------------------------------------------------------------------------

#ifndef TConjugate_GradientH
#define TConjugate_GradientH
#include "TFuzzy.h"
#include <vector>
#include <math.h>
using namespace std;
//---------------------------------------------------------------------------
class TConjugateGradient
{

private:
        vector<double> X;            //Текущее значение вектора параметров
        vector<double> Xnew;
        double dX;
        vector<double> grad_X;       //Градиент
        double e1;                   //Точность по значению ц.ф.
        double e2;                   //Точность по значению параметрам
        int M;                       //Предельное кол-во итераций

        vector<double> dk;
        vector<double> dk_last;


public:
	vector<double> Start(TFuzzy &,vector<double> &,double,double, int);
        vector<double> Golden_ratio(TFuzzy &);
        void Get_newX(vector<double> &,double);



};
#endif
