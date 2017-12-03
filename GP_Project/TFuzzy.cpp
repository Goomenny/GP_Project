//---------------------------------------------------------------------------

#pragma hdrstop

#include "TFuzzy.h"
//---------------------------------------------------------------------------
#pragma once
TFuzzy::TFuzzy(){
     a=1000;
     ki.push_back(0.5);
     ki.push_back(0);
     ki.push_back(1);
     ki.push_back(0);

     ErrorN=0;
}
void TFuzzy::Init(int n_var,int *n_terms,vector<double> & edge){
	this->n_var=n_var;
	this->n_terms.clear();
	this->n_terms.reserve(n_var+1);
  for (int i=0; i < n_var+1; i++) {
     this->n_terms.push_back(n_terms[i]);
  }


  vector<double> ik;

  this->edge=edge;



  k.clear();
  k.reserve(n_var+1);

  for (int i=0; i< n_var+1; i++) {
	    ik.clear();
            ik.reserve((n_terms[i]-2)*4+4);
            double tmp=-edge[i];
            ik.push_back(tmp);
            ik.push_back(tmp);

            for (int j=0; j<(n_terms[i]-2)*4+4; j++) {
            	if (j%4==0)tmp+=edge[i]*2./(n_terms[i]-1);
		ik.push_back(tmp);

            }
            ik.push_back(edge[i]);
            ik.push_back(edge[i]);

            k.push_back(ik);

  }

  mk = new double*[k.size()];

  for (int i = 0; i < k.size(); i++)
  {
	  mk[i] = new double[k[i].size()];
	  for (int j = 0; j < k[i].size(); j++)
	  {
		  mk[i][j] = k[i][j];
	  }
  }


}
void TFuzzy::Set_truck(TTruck &truck){
	this->truck=truck;
}
double TFuzzy::Fuzzy_output(const vector<double>&var){

    double tmpd=0;
    double F=0;
    double sum_ch=0,sum_zn=0;
    vector<double> output_term(n_terms[var.size()]);

    truth.clear();

    truth.reserve(var.size());

	for (int v=0; v < var.size() ; v++) {
            vector<double> temp;
            temp.reserve(n_terms[v]);
            for (int j=0; j < n_terms[v]; j++) {
            	temp.push_back(Terms(var[v],j,k[v]));
            }
            truth.push_back(temp);
        }

        for (int i = 0; i < rules.size(); i++) {

        	tmpd = truth[0][rules[i][0]];

        	for (int j = 1; j < var.size(); j++) {
			tmpd=min(tmpd,truth[j][rules[i][j]]);
                }

               output_term[rules[i][var.size()]]=max(tmpd,output_term[rules[i][var.size()]]);

        }

       tmpd=0;
       for (int i=0; i < output_term.size(); i++)	tmpd+=output_term[i];
       if (tmpd!=0) {

            for (double z=-edge[n_var]; z <=edge[n_var]; z+=fabs(k[var.size()][0]-k[var.size()][k[var.size()].size()-1])/1000.) {
                tmpd=0;
                for (int i=0; i < output_term.size(); i++) {
                	tmpd=max(tmpd,min(output_term[i],Terms(z,i,k[var.size()])));
                }
                sum_zn+=tmpd;
                sum_ch+=tmpd*z;
            }
             if (sum_zn>0)
             return F=sum_ch*1000./sum_zn;
             else
             {
                ErrorK=k;
                ErrorRules=rules;
                ErrorVar=var;
                ErrorN++;
              	return 0;
             }
       } else return 0;

}
//Три терма
double TFuzzy::Three_terms(double var,int n, double k){
    if (n==2)
    {
       if (var > k)
       		return 1;
       else
                if (var < 0)
                        return 0;
                else
                	return var/k;
    }
    else
        if (n==0)
        {
            if (var > 0)
                    return 0;
            else
                    if (var < -k)
                            return 1;
                    else
                            return -var / k;
        }
        else
        {
                if (var > k || var < -k)
                	return 0;
                else
                    if (var >0)
                    	return (-var+k)/k;
                    else
                    	return (var+k)/k;
        }

}
double TFuzzy::Terms(double var, int n, const vector<double> &k){

        if (n==0) {

            if (var < k[0])
                    return 1;
            else
                    if (var > k[2])
                            return 0;
                    else    if (k[2]-k[0]==0)
                    		return 1;
                            else
                            	return 1-(var-k[0])/(k[2]-k[0]);  /* TODO : k[0] и k[2] не могут быть равны, добавить условие чтобы возвращался 0 или 1 */

       } else if (n==(k.size()-4)/4+2-1) {

                if (var > k[k.size()-1])
                	return 1;
                else
                	if (var < k[k.size()-3])
                		return 0;
                	else    if (k[k.size()-1]-k[k.size()-3]==0)
                    			return 1;
                            	else
                			return (var-k[k.size()-3])/(k[k.size()-1]-k[k.size()-3]);

              }else {

              	int i=n*4-3;
                if (var<k[i]||var>k[i+5]) {
                    return 0;
                }
                else if(var>k[i+2]&&var<k[i+3]){
                        return 1;
                }else if (var<k[i+2]) {
                	if (k[i]-k[i+2]==0)
                    		return 1;
                        else
                          return 1-(var-k[i+2])/(k[i]-k[i+2]);
                      }else{
                          if (k[i+3]-k[i+5]==0)
                    		return 1;
                          else
                          return (var-k[i+5])/(k[i+3]-k[i+5]);
                      }

              }

}
double TFuzzy::f(){

double F=0;
double A=0;
double B=0;
double C=0;
double sumF=0;
int sq=0;
for (int t=0; t < 2; t++) {

    F=0;
    A=0;
    B=0;
    C=0;
   // truck.O=(-M_PI/5.)+(2*M_PI/5.)*t;
  // truck.O+=2.5*180*t/M_PI;
  	truck.O+=t*fabs(2*M_PI/100.);
//	truck.O *= -1.;
  for (sq=1; sq <= a; sq++) {
     truck.Calculate_O(Fuzzy_output(truck.var));

     for (int i=0; i < truck.var.size(); i++) {
     	A+=fabs(ki[i]*truck.var[i]/edge[i]);
     }
      C+=fabs(ki[0]*truck.var[0]/edge[0])+fabs(ki[2]*truck.var[2]/edge[2]);

     if (  fabs(truck.var[0])>3 || fabs(truck.var[2])>M_PI/2.) {
      break;
     }
  }
  truck.Reset();

  F=0.5*a/sq;

  if (sq<a) {
    B=pow(a-sq,1.1);
  }
  else {
    B=0;
  }

  C/=double(a);

  sumF+=F+A+B+C;
}

  return  sumF/11.;
 /*
  double sumshtraf=0;
   for (int i=0; i<17; i++) {


        double shtraf=1000;
       truck.O+=2.5*180*i/M_PI;

      for (; shtraf >0;  shtraf--) {

          truck.Calculate_O(Fuzzy_output(truck.var));

          if ( fabs(truck.var[2])>(M_PI/6.)|| fabs(truck.var[0])>2 ) {
           break;
         }
      }
         truck.Reset();

      sumshtraf+=shtraf;
  }

  return sumshtraf/170000.;    */

}
void TFuzzy::Set_k(const vector<double> &newk){

	vector<double> ik;
        int iter=0;
        this->k.clear();
        this->k.reserve(n_var+1);

	for (int v=0; v < n_var+1; v++) {

            ik.clear();
            ik.reserve((n_terms[v]-2)*4+4);

            for (int i=0; i < (n_terms[v]-2)*4+4; i++,iter++) {
              ik.push_back(newk[iter]);
            }

            int *index= new int[ik.size()];

            int h = ik.size()/2;

            for (int i = 0; i < ik.size(); i++)
            {
                      index[i]=i;
            }

             //Сортировка массива методом Шелла
                    while (h>0)
                    {
                                    for (int i=0; i<ik.size()-h; i++)
                                    {
                                                    int j = i;

                                                    while (j>=0)
                                                    {
                                                                    if (ik[j] > ik[j+h])
                                                                    {
                                                                                    double tmp;
                                                                                    int tmp_index;
                                                                                    tmp = ik[j];
                                                                                    tmp_index = index[j];
                                                                                    ik[j] = ik[j+h];
                                                                                    index[j] = index[j+h];
                                                                                    ik[j+h] = tmp;
                                                                                    index[j+h] = tmp_index;
                                                                                    j = j-h;
                                                                    }
                                                                    else j--;
                                                    }

                                    }
                                    h = h/2;
                    }


            for (int i=0; i < ik.size(); i+=2) {

                if (index[i+1]<index[i]) {

                    swap(ik[i],ik[i+1]);

                }

            }
           /*
            for (int i=3; i < ik.size()-3; i+=4) {
               ik[i+1]=ik[i];
            }   */
           k.push_back(ik);
           delete []index;
	}


}
void TFuzzy::Set_rules(const vector< vector<int> >& newrules){
   rules.clear();
   rules=newrules;
}
