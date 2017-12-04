#include "TTree.h"
TTree_symbolic::TTree_symbolic() {
	meansquare = 0;

}
//---------------------------------------------------------------------------

TTree_symbolic::~TTree_symbolic() {

}
//---------------------------------------------------------------------------

TTree_symbolic::TTree_symbolic(const TTree_symbolic &other) {


	this->meansquare = other.meansquare;
}
//---------------------------------------------------------------------------
/*TTree_symbolic& TTree_symbolic::operator=(const TTree_symbolic &other) {//перегрузка оператора присваивания

	if (this == &other)
		return *this; // присвоение самому себе, ничего делать не надо

	this->meansquare = other.meansquare;

	return *this;
}*/
//---------------------------------------------------------------------------
void TTree_symbolic::Calculate_fitness(double **var, double *y, int size, double max_min) {
	fitness = 0;
	meansquare = 0;
	for (int i = 0; i < size; i++) {
		fitness += pow(y[i] - Get_result(var[i]), 2);
		meansquare += fabs(y[i] - Get_result(var[i]));
	}
	meansquare = double(meansquare / (size*max_min));
	fitness = size / (size + fitness);
}

string TTree_symbolic::Get_formula() {
	return node[0][0].Get_formula(node[0][0].Get_symbol());
}
inline double TTree_symbolic::Get_result(double *gvar) {
	return node[0][0].Get_result(gvar);
}
void TTree_symbolic::Calculate_fitness()
{
	//test.Calculate(this);

	//fitness = test.Get_reliability();
	//meanresult = test.Get_meanresult();
}
void TTree_symbolic::Mutate(int type_of_mutation, double probability_of_mutation) {
	double ran = 0;
	int last_func = 0;
	int a[3] = { 0,1,2 }, b[1] = { 3 };
	switch (type_of_mutation) {
	case 0:
		probability_of_mutation = 1. / (5 * deep);
		break;
	case 1:
		probability_of_mutation = 1. / deep;
		break;
	case 2:
		probability_of_mutation = 5. / deep;
		break;
	case 3:
		break;
	}
	for (int i = 0; i < deep; i++) {
		for (int j = 0; j < n_node[i]; j++) {
			if (node[i][j].Get_type()) {
				last_func = node[i][j].Get_func();
				ran = rand() % 100001;
				ran /= 100000.;
				if (probability_of_mutation>ran) {

					while (node[i][j].Get_func() == last_func) {
						if (last_func != 3) {
							node[i][j].Set_func(a[rand() % 3]);
						}
						else {
							node[i][j].Set_func(b[rand() % 1]);
						}
					}

					node[i][j].Set_symbol(node[i][j].Get_func());
				}
			}
		}
	}
}
//---------------------------------------------------------------------------


TTree_fuzzy::TTree_fuzzy() {

}
//---------------------------------------------------------------------------

TTree_fuzzy::~TTree_fuzzy() {

}
//---------------------------------------------------------------------------

TTree_fuzzy::TTree_fuzzy(const TTree_fuzzy &other) {


	this->rules = other.rules;
}
//---------------------------------------------------------------------------
TTree_fuzzy& TTree_fuzzy::operator=(const TTree_fuzzy &other) {//перегрузка оператора присваивания

	if (this == &other)
		return *this; // присвоение самому себе, ничего делать не надо

	this->rules = other.rules;

	return *this;
}
//---------------------------------------------------------------------------

vector<vector<int>> TTree_fuzzy::Get_rules()
{
	return rules;
}
void TTree_fuzzy::Calculate_fitness(TFuzzy & fuzzy)
{
	Get_result(fuzzy.n_terms);
	fuzzy.Set_rules(Get_rules());
	fitness = 1 / (1 + fuzzy.f());
}
vector< vector <int> > TTree_fuzzy::Decart(int *rule_index[], int num_term)
{
	vector < vector<int> > sets;
	vector <int> tmp;
	vector< vector <int> > res;

	for (int i = 0; i < n_var; i++) {

		tmp.clear();
		tmp.reserve(rule_index[1][i] - rule_index[0][i]);
		for (int v = rule_index[0][i]; v < rule_index[1][i]; v++) {     //Сбрасываем начальные и конечные значения
			tmp.push_back(v);
		}
		sets.push_back(tmp);
	}
	int const n = sets.size();
	vector<int> counter(n, 0); // счётчик размером с количество множеств

	bool carry = false; // флаг переноса
	while (!carry)
	{
		// формируем произведение множеств
		vector<int> carthesian(n);
		for (int i = 0; i != n; ++i) carthesian[i] = sets[i][counter[i]];
		//Вставляем номер выходного терма
		carthesian.push_back(num_term);
		//Добавляем правило в общий список новых правил
		res.push_back(carthesian);

		// выполняем инкремент счётчика - поразрядно, начиная с младшего (первого) разряда
		carry = true;
		for (int i = 0; i != n && carry; ++i)
		{
			int& cell = counter[i];
			++cell;
			carry = cell == sets[i].size(); // у каждого разряда - свой предел
			if (carry) cell = 0;
		}
		// если перенос вылетел за пределы счётчика - значит, он перекрутился
	}
	return res;
}

void TTree_fuzzy::Get_result(const vector<int>& n_terms) {
	rules.clear();

	int tmp = 0;

	vector< vector<int> > new_rules; //Массив добавляемых правил в терминльном узле

	vector<int> operations;    //Вектор с операциями %x%y
	int *rule_index[2];     //Начальные и конечные значения термов по переменным
	for (int i = 0; i < 2; i++) {
		rule_index[i] = new int[n_var];
	}



	for (int i = 1; i < deep; i++) {
		for (int j = 0; j < n_node[i]; j++) {

			if (!node[i][j].Get_type()) { //Если узел терминальный

				for (int v = 0; v < n_var; v++) {     //Сбрасываем начальные и конечные значения
					rule_index[0][v] = 0;
					rule_index[1][v] = n_terms[v];
				}

				int num_parent = node[i][j].Get_num_parent();        //Номер родителя
				operations.clear();      //Очищаем операции
				for (int i2 = i - 1; i2 >= 0; i2--) {    //Проходим цепочку вверх собирая операции
					operations.push_back(node[i2][num_parent].Get_func());
					num_parent = node[i2][num_parent].Get_num_parent();
				}

				for (int i2 = 0; i2 < i; i2++) {  //Производим деление термов

					if (node[i][j].Get_index()[i2 + 1] - '0' == 0)   //Если левый узел
					{
						rule_index[1][operations[operations.size() - 1 - i2]] -= (rule_index[1][operations[operations.size() - 1 - i2]] - rule_index[0][operations[operations.size() - 1 - i2]]) / 2;
					}
					else
					{
						//tmp-кол-во термов для деления
						tmp = (rule_index[1][operations[operations.size() - 1 - i2]] - rule_index[0][operations[operations.size() - 1 - i2]]);

						if (tmp % 2 == 0) // Если термов четное число
						{
							rule_index[0][operations[operations.size() - 1 - i2]] += tmp / 2;
						}
						else
						{
							if (tmp != 1) {
								rule_index[0][operations[operations.size() - 1 - i2]] += tmp / 2 + 1;
							}
							else
							{
								//Приравниваем начало к концу => 0 новых правил
								rule_index[0][operations[operations.size() - 1 - i2]] = rule_index[1][operations[operations.size() - 1 - i2]];
								break;
							}

						}
					}

				}

				int n_rules = 1;
				for (int v = 0; v < n_var; v++) { //Считаем кол-во правил

					n_rules *= rule_index[1][v] - rule_index[0][v];
				}
				if (n_rules>0) {


					new_rules = Decart(rule_index, node[i][j].Get_value());
					rules.insert(rules.end(), new_rules.begin(), new_rules.end());
				}
			}

		}
	}

	for (int i = 0; i < 2; i++) {
		delete[]rule_index[i];
	}


}

void TTree_fuzzy::Mutate(int type_of_mutation, double probability_of_mutation) {
	double ran = 0;
	int last_func = 0;

	switch (type_of_mutation) {
	case 0:
		probability_of_mutation = 1. / (5 * deep);
		break;
	case 1:
		probability_of_mutation = 1. / deep;
		break;
	case 2:
		probability_of_mutation = 5. / deep;
		break;
	case 3:
		break;
	}
	for (int i = 0; i < deep; i++) {
		for (int j = 0; j < n_node[i]; j++) {
			if (node[i][j].Get_type()) {
				last_func = node[i][j].Get_func();
				ran = rand() % 100001;
				ran /= 100000.;
				if (probability_of_mutation>ran) {

					while (node[i][j].Get_func() == last_func) {
						node[i][j].Set_func(rand() % n_var);
					}

					node[i][j].Set_symbol(node[i][j].Get_func());
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
double Func(double *var, int num_func) {

	switch (num_func) {
	case 0:
		return var[0] * var[0] + var[1] * var[1];
		break;
	case 1:
		return sin(var[0]);
		break;
	case 2:
		return 8 + 0.1*pow(var[0], 2) + 0.1*pow(var[1], 2) - 4 * (cos(0.8*var[0]) + cos(0.8*var[1]));
		break;
	}




}

