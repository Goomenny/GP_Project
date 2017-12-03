#include "TSetting.h"

TSetting::TSetting(){;
	n_selections=5;
	n_crossovers=2;
	n_mutations=3;
}
//---------------------------------------------------------------------------
void TSetting::Reset_probabilities(){

	for (int i=0; i < n_selections; i++){
		selection_probabilities[i]=1./n_selections;
		average_fitness_selection[i]=0;
	}

	for (int i=0; i < n_crossovers; i++){
		crossover_probabilities[i]=1./n_crossovers;
		average_fitness_crossover[i]=0;
	}

	for (int i=0; i < n_mutations; i++){
		mutation_probabilities[i]=1./n_mutations;
		average_fitness_mutation[i]=0;
	}

}
//---------------------------------------------------------------------------

void TSetting::Recount_probabilities(vector<double> fitness){

	double edge=0.1;
	double extra_probability=0;
	int n_max=0;

		//	Вычисляем средние пригодности
		Calculate_average_fitness(fitness);
	
		 //Пересчитываем вероятности типов селекции
		for (int i= 0; i < n_selections; i++) {

			if (average_fitness_selection[i]>average_fitness_selection[n_max]) n_max=i;


			if (selection_probabilities[i]==edge)
				selection_probabilities[i]=edge;

			else if (selection_probabilities[i]<edge+1./(n_selections*max_number_of_populations)&&selection_probabilities[i]>edge){

						extra_probability+=selection_probabilities[i]-edge;
						selection_probabilities[i]=edge;

					}else  if (selection_probabilities[i]>edge+1./(n_selections*max_number_of_populations)){

								extra_probability+=1./(n_selections*max_number_of_populations);
								selection_probabilities[i]-=1./(n_selections*max_number_of_populations);

						   }
		}

		selection_probabilities[n_max]+=extra_probability;
		extra_probability=0;
		n_max=0;
		//Пересчитываем вероятности типов скрещивания
		for (int i= 0; i < n_crossovers; i++) {

			if (average_fitness_crossover[i]>average_fitness_crossover[n_max]) n_max=i;


			if (crossover_probabilities[i]==edge)
				crossover_probabilities[i]=edge;

			else if (crossover_probabilities[i]<edge+1./(n_crossovers*max_number_of_populations)&&crossover_probabilities[i]>edge){

						extra_probability+=crossover_probabilities[i]-edge;
						crossover_probabilities[i]=edge;

					}else  if (crossover_probabilities[i]>edge+1./(n_crossovers*max_number_of_populations)){

								extra_probability+=1./(n_crossovers*max_number_of_populations);
								crossover_probabilities[i]-=1./(n_crossovers*max_number_of_populations);

						   }
		}

		crossover_probabilities[n_max]+=extra_probability;
		extra_probability=0;
		n_max=0;
		//Пересчитываем вероятности типов мутации
		for (int i= 0; i < n_mutations; i++) {

			if (average_fitness_mutation[i]>average_fitness_mutation[n_max]) n_max=i;


			if (mutation_probabilities[i]==edge)
				mutation_probabilities[i]=edge;

			else if (mutation_probabilities[i]<edge+1./(n_mutations*max_number_of_populations)&&mutation_probabilities[i]>edge){

						extra_probability+=mutation_probabilities[i]-edge;
						mutation_probabilities[i]=edge;

					}else  if (mutation_probabilities[i]>edge+1./(n_mutations*max_number_of_populations)){

								extra_probability+=1./(n_mutations*max_number_of_populations);
								mutation_probabilities[i]-=1./(n_mutations*max_number_of_populations);

						   }
		}

		mutation_probabilities[n_max]+=extra_probability;
}
//---------------------------------------------------------------------------
void TSetting::Calculate_average_fitness(vector<double> fitness){

vector<int> amount_selection(n_selections,0);
vector<int> amount_crossover(n_crossovers,0);
vector<int> amount_mutation(n_mutations,0);

	 //Подсчитываем сколько раз применялся каждый из операторов
	 for (int i=1; i < size_of_population; i++) {  // !!Внимание клонирование не отключать, или изменить на i=0

		amount_selection[type_of_selection[i]]++;
		amount_crossover[type_of_crossover[i]]++;
		amount_mutation[type_of_mutation[i]]++;

	 }

		for (int i=0; i < n_selections; i++){

		average_fitness_selection[i]=0;
	}

	for (int i=0; i < n_crossovers; i++){

		average_fitness_crossover[i]=0;
	}

	for (int i=0; i < n_mutations; i++){

		average_fitness_mutation[i]=0;
	}

	//Вычисляем среднюю пригодность для каждого из типов операторов
	for (int i=1; i < size_of_population; i++){ // !!Внимание клонирование не отключать, или изменить на i=0
	
		if (amount_selection[type_of_selection[i]]!=0)
		 average_fitness_selection[type_of_selection[i]]+= fitness[i] /amount_selection[type_of_selection[i]];

		if (amount_crossover[type_of_crossover[i]]!=0)
		 average_fitness_crossover[type_of_crossover[i]]+= fitness [i]/amount_crossover[type_of_crossover[i]];
	 
		if (amount_mutation[type_of_mutation[i]]!=0)
		 average_fitness_mutation[type_of_mutation[i]]+=fitness[i]/amount_mutation[type_of_mutation[i]];
	}

}
void TSetting::Select_operators(){


double ran=0,sum=0;

   for (int i=0; i < size_of_population; i++) {
	   
		ran=rand()%10000;
		ran/=10000.;
		sum=0;
		for (int j=0; j < n_selections; j++){
		 sum+=selection_probabilities[j];
		 if (sum>ran)
			{
			type_of_selection[i]=j;
			break;
			}

		}

	   ran=rand()%10000;
	   ran/=10000.;
	   sum=0;
		for (int j=0; j < n_crossovers; j++){
		 sum+=crossover_probabilities[j];
		 if (sum>ran)
			{
			type_of_crossover[i]=j;
			break;
			}

		}

	   ran=rand()%10000;
	   ran/=10000.;
	   sum=0;
		for (int j=0; j < n_mutations; j++){
		 sum+=mutation_probabilities[j];
		 if (sum>ran)
			{
			type_of_mutation[i]=j;
			break;
			}

		}

		// В случае турнирной устанавливаем размеры турниров
		if (type_of_selection[i]==2){

			 size_of_tour[i]=2;

		}else 	if (type_of_selection[i]==3){


				  size_of_tour[i]=5;
				} 
				else if (type_of_selection[i]==4)
				{
				  size_of_tour[i]=9;
				}

   }

		
}

