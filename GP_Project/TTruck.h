//---------------------------------------------------------------------------

#ifndef TTruckH
#define TTruckH
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
 class TTruck
 {
 friend class TFuzzy;
 private:
 	double ga; // Ускорение свободного падения
        double O; // Угол маятника O
        double O_l;  //Угловая скорость маятника O'
        double O_ll; //Угловое ускорни маятника O''
        double l; //Длина маятника
        double m;  //Общася масса тележки и маятника M
        double mb; //Масса маятника Mb
        double X; //Положение тележки X
        double X_l; //Скорость тележки X'
        double X_ll; //Ускорение тележки X''

        double 	step; //Шаг интегрирования
        double tim;
        double tim1;

        double k1, k2, k3, k4;
    	double q1, q2, q3, q4,Z0,Z1,Y1,Y0;

        

 public:
     TTruck();

     void Calculate_O(double);
     inline double f(double,double,double);
     inline double g(double,double,double);
     inline double fx(double,double,double,double);
     void Reset();
     double Get_X();
     double Get_O();
     double Get_l();
     double Get_varsize();
     void Set_var(vector<double> &);
	 vector<double> var;

 };
 #endif
