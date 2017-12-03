//---------------------------------------------------------------------------

#pragma hdrstop

#include "TTruck.h"
//---------------------------------------------------------------------------
#pragma once
TTruck::TTruck(){

    var.push_back(0);
    var.push_back(0);
    var.push_back(0);
    var.push_back(0);
   Reset();
}

 void TTruck::Calculate_O (double F)
{


    Y0 = O;
    Z0 = O_l;
    // Считаем 2 дифуру (угол)
    //-------
    k1 = step * f(Y0, Z0, F);
    q1 = step * g(Y0, Z0, F);

    k2 = step * f(Y0 + q1 / 2.0, Z0 + k1 / 2.0, F);
    q2 = step * g(Y0 + q1 / 2.0, Z0 + k1 / 2.0, F);

    k3 = step * f(Y0 + q2 / 2.0, Z0 + k2 / 2.0, F);
    q3 = step * g(Y0 + q2 / 2.0, Z0 + k2 / 2.0, F);

    k4 = step * f(Y0 + q3, Z0 + k3,F);
    q4 = step * g(Y0 + q3, Z0 + k3,F);

    O_l = Z0 + (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
    O = Y0 + (q1 + 2.0*q2 + 2.0*q3 + q4) / 6.0;

    if (O>M_PI) O=-2*M_PI+O;
    if (O<-M_PI) O=2*M_PI+O;

    O_ll=f(O,O_l,F);
    X_ll=fx(O,O_l,O_ll,F);
    X_l+=X_ll*step;
    X+=X_l*step+(X_ll* step*step/2);

    var[0]=X;
    var[1]=X_l;
    var[2]=O;
    var[3]=O_l;
}
/**
* функции, которые получаются из системы
*/
inline double TTruck::f(double o,double o_l,double F){

	return	(m*ga*sin(o) - cos(o)*(F + mb*l*pow(o_l, 2)*sin(o))) / ((4 / 3)*m*l - mb*l*pow(cos(o), 2));
}
inline double TTruck::g(double o,double o_l,double F){
	return o_l;
}
//---------------------------------------------------------------------------
// функция для рассчета ускорения тележки
inline double TTruck::fx(double o,double o_l,double o_ll,double F)
{
	return (F+mb*l*(pow(o_l,2)*sin(o)-o_ll*cos(o)))/m;
}
void TTruck::Reset(){
    ga=9.81; // Ускорение свободного падения
    O=-M_PI/10.; // Угол маятника O
    O_l=0;  //Угловая скорость маятника O'
    O_ll=0; //Угловое ускорни маятника O''
    l=2; //Длина маятника
    m=5;  //Общася масса тележки и маятника M
    mb=1; //Масса маятника Mb
    X=0; //Положение тележки X
    X_l=0; //Скорость тележки X'
    X_ll=0; //Ускорение тележки X''

    step=0.01;
    tim=0;
    tim1=0;

    var[0]=X;
    var[1]=X_l;
    var[2]=O;
    var[3]=O_l;

}
double TTruck::Get_X(){
	return var[0];
}
double TTruck::Get_O(){
	return var[2];
}
double TTruck::Get_l(){
	return l;
}
double TTruck::Get_varsize(){
	return var.size();
}
void TTruck::Set_var(vector<double> & newvar){

   var=newvar;

   X=var[0];

   X_l=var[1];

   O=var[2];

   O_l=var[3];

   X_ll=0;
   O_ll=0;


}
