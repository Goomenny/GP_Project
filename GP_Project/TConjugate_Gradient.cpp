//---------------------------------------------------------------------------

#pragma hdrstop

#include "TConjugate_Gradient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
vector<double> TConjugateGradient::Start(TFuzzy & fuzzy,vector<double> & Xo,double e1,double e2,int M){



        double fx=0;
        double fn=0;
        double norm_grad=0;
        double norm_grad_last=0;
        double Bk_last=0;
        dX=0.0000001;
	this->e1=e1;
        this->e2=e2;
        this->M=M;
        this->X=Xo;
        int flag=0;

        dk.reserve(X.size());
        dk_last.reserve(X.size());
        grad_X.reserve(X.size());
        for (int k=0; k<M; k++) {
            fuzzy.Set_k(X);
            fx=fuzzy.f()/100000.; //вычисляем f(x) 1 раз
            // ШАГ 3 Вычисляем градиент
            grad_X.clear();

            norm_grad=0;
            for (int i=0; i < X.size(); i++) {
               grad_X.push_back(-fx);

               X[i]+=dX;

               fuzzy.Set_k(X);

               grad_X[i]+=fuzzy.f()/100000.;
               grad_X[i]/=dX;
               norm_grad+=grad_X[i]*grad_X[i];

               X[i]-=dX;


            }
            //ШАГ 4 проверка условия градиент = 0

            norm_grad=pow(norm_grad,0.5);
            //Если градиент  = 0 то прерываем работу
            if (norm_grad< e1) {
           	Xnew=X;
            	break;
            }
            //ШАГ 5
            if (k!=0)
            {
              //ШАГ 7
              Bk_last=pow(norm_grad,2.)/pow(norm_grad_last,2.);
              //ШАГ 8
              for (int i=0; i < dk.size(); i++) dk[i]=-grad_X[i]+Bk_last*dk_last[i];

            }
            else
            {   //ШАГ 6
              	for (int i=0; i < dk.size(); i++) dk[i]=-grad_X[i];
            }
            //ШАГ 9,10

           Xnew=Golden_ratio(fuzzy);

            norm_grad_last=norm_grad;
            dk_last=dk;
            //Проверяем условия остановки
            norm_grad=0;
            for (int i = 0; i < grad_X.size(); i++) {
            	norm_grad+=pow(X[i]-Xnew[i],2.);
            }


            if (pow(norm_grad,0.5)<e2){
                fuzzy.Set_k(Xnew);
            	fn=fuzzy.f(); //вычисляем f(x) 1 раз
            	if (fabs(fx-fn)<e2){
                    flag++;
                    if (flag>1)
                     	break;
                }

            }
            X=Xnew;

        }


  return Xnew;
}
vector<double> TConjugateGradient::Golden_ratio(TFuzzy &fuzzy){
double t1=0;
double t2=0;
double a=0;
double b=0.01;
double g=0.00001;
vector<double> Xnew1(X.size());
vector<double> Xnew2(X.size());
double f1=0;
double f2=0;

t1=b-((b-a)/1.6180339887);

           if (fabs(a-t1)<fabs(b-t1))
           	t2=b-fabs(a-t1);
           else
           	t2=a+fabs(b-t1);

        for (int i=0; i < 1; i++) {

        	Get_newX(Xnew1,t1);
                Get_newX(Xnew2,t2);
                fuzzy.Set_k(Xnew1);
                f1=fuzzy.f();

                fuzzy.Set_k(Xnew2);
                f2=fuzzy.f();


                if (t1<t2) {
                   if (f1<=f2){
                         b=t2;
                         t2=t1;
                   }
                   else {
                        a=t1;
                        t1=t2;
                   }
                }
                else
                        if (f1<=f2){
                           a=t2;
                           t2=t1;
                        }
                        else {
                         b=t1;
                         t1=t2;
                        }

           if (fabs(a-t1)<fabs(b-t1))
           t2=b-fabs(a-t1);
           else
           t2=a+fabs(b-t1);

           if ((b-a)>g) i--;
        }


        if (f1<=f2)
        {
	return Xnew1;
        }
 	else
        {
	return Xnew2;
        }
}

void TConjugateGradient::Get_newX(vector<double> &Xnew,double tk){
	Xnew.clear();
	for (int v=0;v<X.size();v++)
		Xnew.push_back(X[v]+tk*dk[v]);

}


