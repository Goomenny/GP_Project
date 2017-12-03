//---------------------------------------------------------------------------

#pragma hdrstop

#include "TGa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TGa::TGa():TGASetting(){
}
void TGa::Init(bool selfconfiguration,int size_of_population,int max_number_of_populations,int type_of_selection,int size_of_tour,
		int type_of_crossover,int type_of_mutation,double probability_of_mutation,vector< vector<double> > & limit,int dimension,double accuracy)
{

	first_solution=0;
	found = false;
	//Резервируем память для массивов с примененными операторами
	this->type_of_selection.reserve(size_of_population);
	this->size_of_tour.reserve(size_of_population);
	this->type_of_crossover.reserve(size_of_population);
	this->type_of_mutation.reserve(size_of_population);

	if (!selfconfiguration) {
	   for (int i = 0; i < size_of_population; i++) {
		 this->type_of_selection.push_back(type_of_selection);
		 this->size_of_tour.push_back(size_of_tour);
		 this->type_of_crossover.push_back(type_of_crossover);
		 this->type_of_mutation.push_back(type_of_mutation);
	   }
	}
	// Записываем остальные настройки
	this->selfconfiguration=selfconfiguration;
	this->size_of_population=size_of_population;
	this->max_number_of_populations=max_number_of_populations;
	this->dimension=dimension;
	this->probability_of_crossover=probability_of_crossover;
	this->probability_of_mutation=probability_of_mutation;

        this->dimension=dimension;

        double doubletmp;
                int inttmp;
                N=0;

                left_limit=new double[dimension];
                right_limit=new double[dimension];
                E=new double [dimension];

                N_var[0]=new int[dimension];
                N_var[1]=new int[dimension];


		//Задаем границы от -1 до +1 для всех размерностей
		for (int i = 0; i < dimension; i++) {
                    left_limit[i]=limit[i][0];
                    right_limit[i]=limit[i][1];
		  //проверяем на целочисленность N
		  doubletmp=log((right_limit[i]-left_limit[i])/(0.1*accuracy))/log(2.);
		  inttmp=doubletmp;
		  if (inttmp==doubletmp) //если N целое, то длина равна N, иначе округление от N+1
			N_var[1][i]=inttmp;
		  else N_var[1][i]=doubletmp+1;


		  if(i!=0) N_var[0][i]=N_var[0][i-1]+N_var[1][i-1];
			else N_var[0][i]=0;
		  E[i]=(right_limit[i]-left_limit[i])/(pow(2.,N_var[1][i])*0.1);
		  N+=N_var[1][i];
		}

                //Случайно инициализируем первое поколение
                last_population.Init(size_of_population,N,dimension);
                //Инициализируем место для следующиего поколения
                new_population.Init(size_of_population,N,dimension);

}
int TGa::Start_fast(TFuzzy & fuzzy,bool restart){
     fitness.clear();


         if (restart) {

           	for (int i=1; i < size_of_population; i++) {
		last_population.genotype[i].Init(N,dimension);
             }

             if (selfconfiguration) {
			//Сбрасываем вероятности выбора операторов
			Reset_probabilities();
			// Выбираем операторы для первой эволюции
			Select_operators();
                        }
         }




		   for (int i=0; i < max_number_of_populations+1; i++) {

			 last_population.Calculate_fitness(N_var,E,left_limit,fuzzy);
			 last_population.Find_best();

                         tmp.clear();
                         double sum=0;
                         for (int ind=0; ind<size_of_population; ind++) {
                             sum+=last_population.genotype[ind].fitness;
                         }

                         tmp.push_back(sum/size_of_population);
                         tmp.push_back(last_population.best_genotype.fitness);
                         fitness.push_back(tmp);

			 if (last_population.best_genotype.fitness==1&&found==false)
			 {
				first_solution=i;
				found = true;
				break;
			 }
                         if (i<max_number_of_populations) {

                             if (selfconfiguration && i!=0) {
                                            //Пересчитываем вероятности операторов
                                      Recount_probabilities(last_population);
                                      Select_operators();
                             }

			  last_population.Selection(selfconfiguration,type_of_selection,size_of_tour);
			  new_population.Evolve(last_population,type_of_crossover);
			  new_population.Mutate(type_of_mutation,probability_of_mutation);

			  last_population=new_population;
                      
                         }
		   }



		if (found)
           return 1;
		else
            return 0;
}
vector<double> TGa::Get_solution(){
   return last_population.best_genotype.value;
}
double TGa::Get_fitness(){
	return last_population.best_genotype.fitness;
}

int TGa::Get_first_solution(){
	if (found) {
	   return first_solution;
	}
	else
	{
		return 0;
    }

}

vector< vector<double> > TGa::Get_stats(){
	return fitness;
}

