#pragma once

struct Crossover_index
{
	int iorigin;
	int jorigin;
	int iother;
	int jother;
	bool ready;
};

template<class Node>
class TTree
{

protected:
	Node **node; //Массив узлов

	int deep; // Текущая глубина дерева
	int max_deep; //Кол-во слоев
	int *n_node; //Кол-во узлов на слое
	int n_var;    //Размерность переменных (решаемой задачи)

	double fitness; //Пригодность дерева



public:
	TTree<Node>();
	~TTree<Node>();
	TTree<Node>(const TTree<Node> &); //Копиконструктор
	TTree<Node>& operator=(const TTree<Node> &); //Копирование дерева

	void Init(int, int, int, int); //Инициализация дерева
	bool Crossover(int, const TTree<Node>&, const TTree<Node>&); //Скрещивание деревьев (оригинал, второе дерево, индексы узлов скрещивания)



	inline bool SubTree(const Node&, const Node&); //Проверяем является ли первый узел поддеревом второго
	Crossover_index Get_crossover_index(int, const TTree<Node>&, const TTree<Node>&);

	double Get_fitness();

	int Get_deep();



};
//---------------------------------------------------------------------------

template<class Node>
TTree<Node>::TTree() {
	node = 0;
	fitness = 0;
	deep = 0;
	max_deep = 0;
	n_node = 0;
}
//---------------------------------------------------------------------------
template<class Node>
TTree<Node>::~TTree() {

	//Form1->Memo1->Lines->Add("Deleted");
	for (int i = 0; i < deep; i++)
		delete[] node[i];
	delete[] node;
	delete[] n_node;
}
//---------------------------------------------------------------------------
template<class Node>
TTree<Node>::TTree(const TTree<Node> &other) {

	this->n_var = other.n_var;
	this->deep = other.deep;
	this->max_deep = other.max_deep;
	this->n_node = new int[deep];
	this->node = new Node *[deep];
	this->fitness = other.fitness;

	for (int i = 0; i < deep; i++) {
		this->n_node[i] = other.n_node[i];
		this->node[i] = new Node[this->n_node[i]];
	}

	for (int i = 0; i < this->deep; i++) {
		for (int j = 0; j < n_node[i]; j++) {

			this->node[i][j] = other.node[i][j];

			if (this->node[i][j].Get_type()) this->node[i][j].Set_argument(this->node[i + 1]);
			else this->node[i][j].Set_argument(0);
		}
	}


}
//---------------------------------------------------------------------------
template<class Node>
TTree<Node>& TTree<Node>::operator=(const TTree<Node> &other) {//перегрузка оператора присваивания

	if (this == &other)
		return *this; // присвоение самому себе, ничего делать не надо


	for (int i = 0; i < this->deep; i++)
		delete[] node[i];
	delete[] node;
	delete[] n_node;



	this->n_var = other.n_var;
	this->deep = other.deep;
	this->max_deep = other.max_deep;
	this->n_node = new int[deep];
	this->node = new Node *[deep];
	this->fitness = other.fitness;


	for (int i = 0; i < deep; i++) {
		this->n_node[i] = other.n_node[i];
		this->node[i] = new Node[this->n_node[i]];
	}

	for (int i = 0; i < this->deep; i++) {
		for (int j = 0; j < n_node[i]; j++) {

			this->node[i][j] = other.node[i][j];

			if (this->node[i][j].Get_type()) this->node[i][j].Set_argument(this->node[i + 1]);
			else this->node[i][j].Set_argument(0);
		}
	}



	return *this;
}
//---------------------------------------------------------------------------
template<class Node>
bool TTree<Node>::Crossover(int type_of_crossover, const TTree<Node> &origin, const TTree<Node> &other) {
	bool success = true;
	if (this == &origin || this == &other)
		return success = false;
	int sum = 0;//Временная сумма
	int actual_deep;
	int di;
	Crossover_index index = Get_crossover_index(type_of_crossover, origin, other);


	if (index.ready) {



		/*int iorigin=rand()%(origin.deep-1)+1;
		int jorigin=rand()%origin.n_node[iorigin];


		int iother=rand()%other.deep;
		int jother=rand()%other.n_node[iother]; */
		di = index.iother - index.iorigin; // Разность слоев

		actual_deep = (index.iorigin + 1) + other.node[index.iother][index.jother].Get_n_heirs();

		if (origin.deep>actual_deep)
			actual_deep = origin.deep;    //Если глубина старого основного дерева больше то оставляем его глубину

		if (actual_deep <= origin.max_deep)
		{
			for (int i = 0; i < this->deep; i++)
				delete[] node[i];
			delete[] node;
			delete[] n_node;

			int jn = 0; // Итерратор по узлам нового дерева
			bool crossed = false; // Скрестили ли этот слой или нет

			this->n_var = other.n_var;
			this->deep = actual_deep;
			this->max_deep = origin.max_deep;
			this->n_node = new int[this->deep];
			this->n_node[0] = 1;
			for (int i = 1; i < this->deep; i++) {
				this->n_node[i] = 0;
			}

			this->node = new Node *[this->deep];
			this->fitness = 0;
			this->node[0] = new Node[1];
			this->node[0][0] = origin.node[0][0];

			this->n_node[1] = this->node[0][0].Get_n_child();

			for (int in = 1; in < this->deep; in++) {
				this->node[in] = new Node[this->n_node[in]]; //Выделяем память под новый слой
				crossed = false;
				jn = 0;
				if (in<origin.deep) //Если глубина дерева origin Больше чем текущий слой
				{
					for (int jor = 0; jor < origin.n_node[in]; jor++) {

						if (!SubTree(origin.node[in][jor], origin.node[index.iorigin][index.jorigin])) {
							this->node[in][jn] = origin.node[in][jor];
							jn++;
						}
						else if (!crossed&&other.deep>in + di)
						{
							for (int jo = 0; jo < other.n_node[in + di]; jo++) {
								if (SubTree(other.node[in + di][jo], other.node[index.iother][index.jother])) {
									this->node[in][jn] = other.node[in + di][jo];
									jn++;
								}
							}
							crossed = true;
						}


					}
				}
				else if (other.deep>in + di) {
					for (int jo = 0; jo < other.n_node[in + di]; jo++) {
						if (SubTree(other.node[in + di][jo], other.node[index.iother][index.jother])) {
							this->node[in][jn] = other.node[in + di][jo];
							jn++;
						}
					}
				}

				sum = 0;
				//Связываем узлы на разных слоях (текущий слой привязываем к предыдущему)
				for (int s = 0; s < this->n_node[in - 1]; s++) {   //Идем по узлам родительского слоя

					this->node[in - 1][s].Set_argument(this->node[in]);  //Указываем на слой с потомками
					for (int c = 0; c < this->node[in - 1][s].Get_n_child(); c++) {  //Идем по потомкам конкретного узла

						this->node[in][sum + c].Set_num_parent(s);     // Устанавливаем номер родительского узла
						this->node[in][sum + c].Set_num_self(c); // Устанавливаем свой номер
						this->node[in][sum + c].Set_index(this->node[in - 1][s].Get_index());
						this->node[in][sum + c].Add_index(to_string(this->node[in][sum + c].Get_num_self())); //Формируем абсолютный индекс
						this->node[in][sum + c].Set_num_layer(in); //Устанавиливаем номер слоя
						this->node[in - 1][s].Set_child(c, sum + c); //Записываем индексы потомков
					}
					sum += this->node[in - 1][s].Get_n_child();   //Записываем кол-во пройденных узлов на слое
				}



				//Подсчитываем необходимое кол-во узлов на след слое
				if (in + 1 != deep) {
					sum = 0;
					for (int j = 0; j < this->n_node[in]; j++) {
						sum += this->node[in][j].Get_n_child();
					}
					this->n_node[in + 1] = sum;
				}

				if (this->n_node[in + 1] == 0) {
					this->deep = in + 1;
					break;
				}
			}

		}
		else success = false;
	}
	else success = false;


	return success;
}
//---------------------------------------------------------------------------
template<class Node>
void TTree<Node>::Init(int gmaxdeep, int gn_var, int growth, int inheriters) {
	int sum = 0;//Временная сумма


	n_var = gn_var;
	max_deep = gmaxdeep;
	n_node = new int[max_deep];
	node = new Node *[max_deep];
	n_node[0] = 1; //на 1 слое всегда 1 узел(корень)
	node[0] = new Node[1];  //Создаем корень
	node[0][0].Init(true, rand() % 4, n_var, inheriters);
	node[0][0].Set_num_layer(0);
	node[0][0].Set_num_self(0);
	node[0][0].Set_index("0");
	n_node[1] = node[0][0].Get_n_child(); //Узнаем сколько потомков у корня

	for (int i = 1; i < max_deep; i++) {
		node[i] = new Node[n_node[i]]; //Добавляем слой с потомками

		sum = 0;
		//Связываем узлы на разных слоях (текущий слой привязываем к предыдущему)
		for (int s = 0; s < n_node[i - 1]; s++) {   //Идем по узлам родительского слоя

			node[i - 1][s].Set_argument(node[i]);  //Указываем на слой с потомками
			for (int c = 0; c < node[i - 1][s].Get_n_child(); c++) {  //Идем по потомкам конкретного узла

				if (i + 1 != max_deep) {
					if (growth == 0) 		node[i][sum + c].Init(true, rand() % 4, n_var, inheriters); //Полный рост
					else 		   	node[i][sum + c].Init(rand() % 2, rand() % 4, n_var, inheriters); //Неполный рост
				}
				else 				node[i][sum + c].Init(false, NULL, n_var, inheriters); //Крайний слой

				node[i][sum + c].Set_num_parent(s);     // Устанавливаем номер родительского узла
				node[i][sum + c].Set_num_self(c); // Устанавливаем свой номер
				node[i][sum + c].Set_index(node[i - 1][s].Get_index());
				node[i][sum + c].Add_index(to_string(node[i][sum + c].Get_num_self())); //Формируем абсолютный индекс
				node[i][sum + c].Set_num_layer(i); //Устанавиливаем номер слоя
				node[i - 1][s].Set_child(c, sum + c); //Записываем индексы потомков
			}
			sum += node[i - 1][s].Get_n_child();   //Записываем кол-во пройденных узлов на слое
		}
		//Подсчитываем необходимое кол-во узлов на след слое
		if (i + 1 != max_deep) {
			sum = 0;
			for (int j = 0; j < n_node[i]; j++) {
				sum += node[i][j].Get_n_child();
			}
			this->n_node[i + 1] = sum;
			if (this->n_node[i + 1] == 0) break;
		}


	}

	//Считаем актуальную глубину дерева
	for (int i = 0; i < max_deep; i++) {
		if (n_node[i] == 0) {
			deep = i;
			break;
		}
		else if (i == max_deep - 1) {
			deep = max_deep;
		}

	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
template<class Node>
inline bool TTree<Node>::SubTree(const Node &subnode, const Node &node) {
	return subnode.Get_index().substr(0, node.Get_num_layer() + 1) == node.Get_index();
}




template<class Node>
double TTree<Node>::Get_fitness()
{
	return fitness;
}
template<class Node>
int TTree<Node>::Get_deep()
{
	return deep;
}


//---------------------------------------------------------------------------
template<class Node>
Crossover_index TTree<Node>::Get_crossover_index(int type_of_crossover, const TTree<Node>& origin, const TTree<Node>& other) {
	Crossover_index index;



	if (type_of_crossover == 0) {

		index.iorigin = rand() % (origin.deep - 1) + 1;
		index.jorigin = rand() % origin.n_node[index.iorigin];
		index.iother = rand() % other.deep;  //Можем выбрать корневой узел в качестве поддерева
		index.jother = rand() % other.n_node[index.iother];
		index.ready = true;
	}
	else {
		vector<int> iorigin;
		vector<int> jother;
		vector<int> iother;
		vector<int> jorigin;

		for (int i = 0; i < origin.deep; i++) { //Идем по слоям origin
			if (i<other.deep)   //Если есть одинаковый слой в обоих деревьях
				for (int jor = 0; jor < origin.n_node[i]; jor++) {  //Идем по узлам в origin будем искать им пару
					for (int jot = jor; jot < other.n_node[i]; jot++) {  //Идем по узам other проверяем является ли он парой для jor
						if (origin.node[i][jor].Get_index() == other.node[i][jot].Get_index() && origin.node[i][jor].Get_type() == true && other.node[i][jot].Get_type() == true && origin.node[i][jor].Get_arn() == other.node[i][jot].Get_arn()) {
							for (int jorc = 0; jorc < origin.node[i][jor].Get_n_child(); jorc++) {
								iorigin.push_back(i + 1);
								jorigin.push_back(origin.node[i][jor].Get_child(jorc));
							}
							for (int jotc = 0; jotc < other.node[i][jot].Get_n_child(); jotc++) {
								iother.push_back(i + 1);
								jother.push_back(other.node[i][jot].Get_child(jotc));
							}

							break; //Прерываем если уже нашли пару для данного узла, переходим к след узлу в origin
						}
					}
				}
		}
		if (iorigin.size() != 0) {
			int num = rand() % iorigin.size();
			index.iorigin = iorigin[num];
			index.jorigin = jorigin[num];

			num = rand() % iother.size();

			index.iother = iother[num];
			index.jother = jother[num];

			index.ready = true;
		}
		else {
			index.ready = false; //Если нет общего поля
		}

	}

	return index;

}
//---------------------------------------------------------------------------
