//---------------------------------------------------------------------------

#pragma hdrstop

#include "TGAPopulation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TGAPopulation::TGAPopulation(){
 size_of_population=0;
 genotype=0;
 tour=0;
parent[0]=0;
parent[1]=0;
proportional_probability=0;
rank_probability=0;
}
//---------------------------------------------------------------------------
__fastcall TGAPopulation::~TGAPopulation(){
delete []genotype;
for (int i=0; i < 2; i++)
delete []parent[i];
delete []tour;
delete []proportional_probability;
delete []rank_probability;

}
//---------------------------------------------------------------------------
__fastcall TGAPopulation::TGAPopulation(const TGAPopulation &other){

	this->best_genotype=other.best_genotype; 	// Лучший индивид
	this->size_of_population=other.size_of_population; //Размер популяции

	this->genotype=new TGenotype[size_of_population];
	this->proportional_probability=new double[size_of_population];
	this->rank_probability=new double[size_of_population];
	this->tour=new int[size_of_population];

  for (int i=0; i < 2; i++) {
	parent[i]=new int[size_of_population];
  }

  for (int i=0; i < this->size_of_population; i++) {
	this->genotype[i]=other.genotype[i];
  }

}
//---------------------------------------------------------------------------
TGAPopulation& TGAPopulation::operator=(const TGAPopulation  &other ){

	delete []genotype;
	delete []parent[0];
	delete []parent[1];
	delete []tour;
	delete []proportional_probability;
	delete []rank_probability;

	this->best_genotype=other.best_genotype; 	// Лучший индивид
	this->size_of_population=other.size_of_population; //Размер популяции

	this->genotype=new TGenotype[size_of_population];
	this->proportional_probability=new double[size_of_population];
	this->rank_probability=new double[size_of_population];
	this->tour=new int[size_of_population];

  for (int i=0; i < 2; i++) {
	parent[i]=new int[size_of_population];
  }

  for (int i=0; i < this->size_of_population; i++) {
	this->genotype[i]=other.genotype[i];
  }
  return *this;
}
//---------------------------------------------------------------------------
void TGAPopulation::Init(int size_of_population,int N,int dimension){
  this->size_of_population=size_of_population;

  genotype=new TGenotype[size_of_population];
  proportional_probability=new double[size_of_population];
  rank_probability=new double[size_of_population];
  tour=new int[size_of_population];
  for (int i=0; i < 2; i++) {
	parent[i]=new int[size_of_population];
  }

  for (int i=0; i < size_of_population; i++) {
	genotype[i].Init(N,dimension);
  }


}
//---------------------------------------------------------------------------
void TGAPopulation::Calculate_fitness(int *N_var[2],double *E,double *left_limit,TFuzzy &fuzzy){

	for (int i = 0; i < size_of_population; i++) {
        	genotype[i].Get_value(N_var,E,left_limit);
                fuzzy.Set_k(genotype[i].value);
		genotype[i].fitness=1/(1+fuzzy.f());
	}
}
//Пропорциональная селекция
void TGAPopulation::Proportional_selection()
{
	  double sum=0; //Сумма всех пригодностей
	  for (int i = 0; i < size_of_population; i++) {
		 sum+=genotype[i].fitness;
	  }
	  for (int i = 0; i < size_of_population; i++) {
		 proportional_probability[i]=genotype[i].fitness/sum;
	  }

}
//---------------------------------------------------------------------------
//Ранговая селекция
void TGAPopulation::Rank_selection()
{   /* Можно ускорить, убрать объявление и удаление)
(С одинаковым fitness разная вероятность, НУЖНО усреднять) */
	double *fitness_tmp=new double[size_of_population];
	int *num_gen=new int[size_of_population];
	int h = size_of_population/2;

	for (int i = 0; i < size_of_population; i++)
	{
		  fitness_tmp[i]=genotype[i].fitness;
		  num_gen[i]=i;
	}

	 //Сортировка массива методом Шелла
		while (h>0)
		{
				for (int i=0; i<size_of_population-h; i++)
				{
						int j = i;

						while (j>=0)
						{
								if (fitness_tmp[j] > fitness_tmp[j+h])
								{
										double tmp;
										int tmp_num;
										tmp = fitness_tmp[j];
										tmp_num = num_gen[j];
										fitness_tmp[j] = fitness_tmp[j+h];
										num_gen[j] = num_gen[j+h];
										fitness_tmp[j+h] = tmp;
										num_gen[j+h] = tmp_num;
										j = j-h;
								}
								else j--;
						}

				}
				h = h/2;
		}

	for (int i = 0; i < size_of_population; i++) {
	   rank_probability[num_gen[i]]=2.*(i+1)/(size_of_population*(size_of_population+1));
   }

   delete [] fitness_tmp;
   delete [] num_gen;

}
//---------------------------------------------------------------------------
int TGAPopulation::Get_parent(int type_of_selection,int size_of_tour)
{
double ran,sum=0;;
bool flag=false;
int num_max=0;

	if (type_of_selection<2) {
         switch (type_of_selection) {
			case 0:  //Пропорциональная селекция
				ran=rand()%10000;
			   ran/=10000.;
			   for (int i=0; i < size_of_population; i++)
				{
				 sum+=proportional_probability[i];
				 if (sum>ran)
					return i;
				}
				break;
			case 1: //Ранговая селекция
				ran=rand()%10000;
			   ran/=10000.;
			   for (int i=0; i < size_of_population; i++)
				{
				 sum+=rank_probability[i];
				 if (sum>ran)
					return i;
				}
				break;
		}

	}else {
				 //Турнирная селекция /* TODO : Переписать через вектора (для неповторяющегося выбора) */
		for (int i=0; i < size_of_tour; i++)
		{
		 do
		 { tour[i]=rand()%size_of_population;
		   flag=false;
		  for (int k = 0; k < i; k++) {
			  if (tour[i]==tour[k]) flag=true;
		  }
		 }while(flag);

		}
		num_max=tour[0];

		for (int i=1; i < size_of_tour; i++)
			if (genotype[tour[i]].fitness>genotype[num_max].fitness)
				num_max=tour[i];

	   return num_max;
    }


}
//---------------------------------------------------------------------------
void TGAPopulation::Selection(bool selfconfiguration,const vector<int> &type_of_selection,const vector<int> &size_of_tour){

	if (selfconfiguration) {
		Proportional_selection();
		Rank_selection();
	} else {

		if(type_of_selection[0]==0)
		Proportional_selection();
		else if (type_of_selection[0]==1)
		Rank_selection();

	}

	for (int i=0; i < size_of_population; i++) {

		parent[0][i]=Get_parent(type_of_selection[i],size_of_tour[i]);
		do
		{
		parent[1][i]=Get_parent(type_of_selection[i],size_of_tour[i]);
		}
		while (parent[0][i]==parent[1][i]);

	}



}
//Получение потомка
void TGAPopulation::Evolve(const TGAPopulation &last_population,const vector<int> &type_of_crossover){

  this->genotype[0]=last_population.best_genotype;
	for (int i=1; i < size_of_population; i++) {
        //Скрещиваем
	   this->genotype[i].Crossover(type_of_crossover[i],last_population.genotype[last_population.parent[0][i]],last_population.genotype[last_population.parent[1][i]]);
	}

}
void TGAPopulation::Find_best(){
int n_best=0;

for (int i = 1; i < size_of_population; i++)
   if (genotype[n_best].fitness<genotype[i].fitness) n_best=i;
   best_genotype=genotype[n_best];
}
void TGAPopulation::Mutate(const vector<int> &type_of_mutation,double probability_of_mutation){

	for (int i=1; i < size_of_population; i++) {
	   genotype[i].Mutate(type_of_mutation[i],probability_of_mutation);
	}
}
