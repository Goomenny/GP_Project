//---------------------------------------------------------------------------

#pragma hdrstop

#include "TGenotype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
double func(const vector<double>& value){


double VHML_Result=0;
for (int i=0;i<value.size();i++)
VHML_Result+=pow(value[i],2.);
//VHML_Result+=value[i]*value[i]-10.*cos(2.*M_PI*value[i]);
//VHML_Result+=10*value.size();
return VHML_Result;

}

void TGenotype::Init(int N,int dimension){
 fitness=0;
 this->dimension=dimension;
 gen.clear();
 gen.reserve(N);

 for (int i=0; i<N; i++) {
     gen.push_back(rand()%2);
 }
}
void TGenotype::Get_value(int *N_var[2],double *E,double *left_limit){

	value.clear();
        value.reserve(dimension);
        int tmp=0;
        for (int n_var=0; n_var < dimension; n_var++) {

            tmp=0;


            for (int i = 0; i < N_var[1][n_var]; i++) {
               tmp+=gen[N_var[0][n_var]+i]*pow(2,N_var[1][n_var]-i-1.);
             }
            value.push_back(left_limit[n_var]+tmp*E[n_var]*0.1);
         }

}
void TGenotype::Calculate_fitness(){

	fitness=1/(1+func(value));

}
void TGenotype::Crossover(int type_of_crossover,const TGenotype &origin,const TGenotype &other){


	int dot[2];
	int num=0;
	double rnd;
	bool cross=false;
	//Вероятность скрещивания
		switch (type_of_crossover) {/* TODO : ОШИБКА ВЕРОЯТНОСТЬ И ТИП ЭТО РАЗНОЕ */
		case 0:
				rnd=rand()%10001;
				rnd/=10000.;
				if (rnd<0.65) cross=true;
				break;
		case 1:
				rnd=rand()%10001;
				rnd/=10000.;
				if (rnd<0.95) cross=true;
				break;
		case 2:
				cross=true;
				break;
		case 3: 	cross=false;
				break;
	}
	//Определяем точки скрещивания
	if (cross) {


            switch (type_of_crossover) {
                    case 0:
                                    dot[0]=rand()%(origin.gen.size()-1)+1;
                                    dot[1]=dot[0];
                                    break;
                    case 1:
                                    dot[0]=rand()%(origin.gen.size()-1)+1;
                                    do dot[1]=rand()%(origin.gen.size()-1)+1;
                                    while (dot[0]==dot[1]);
                                    break;
                    case 2:
                                    for (int i = 0; i < origin.gen.size(); i++)
                                    if (i%2==0) {
                                       this->gen[i]=origin.gen[i];
                                    }
                                    else{
                                        this->gen[i]=other.gen[i];
                                    }

                                    break;
            }
            //Скрещиваем
            for (int i = 0; i < origin.gen.size(); i++)
            {
                    if (i!=dot[0]&&i!=dot[1])
                    	if (num==0) {
                          this->gen[i]=origin.gen[i];
                        }
                        else{
                          this->gen[i]=other.gen[i];
                        }

                    else
                    {
                        if (num==0)
                            num=1;
                        else
                            num=0;
                        if (num==0) {
                          this->gen[i]=origin.gen[i];
                        }
                        else{
                          this->gen[i]=other.gen[i];
                        }
                    }

            }
	}
	else
        	if (rand()%2==0) {

			this->gen=origin.gen;
                }
                else{
			this->gen=other.gen;
                }

}
void TGenotype::Mutate(int type_of_mutation,double probability_of_mutation){
double ran=0;

	switch (type_of_mutation) {
		case 0:
				probability_of_mutation=1./(5*gen.size());
				break;
		case 1:
				probability_of_mutation=1./gen.size();
				break;
		case 2:
				probability_of_mutation=5./gen.size();
				break;
	}
   for (int i=0; i < gen.size(); i++)
	{ 	ran=rand()%10001;
		ran/=10000.;
	 if (probability_of_mutation>ran)
		if(gen[i]==0) gen[i]=1;
		else gen[i]=0;
	}

}
