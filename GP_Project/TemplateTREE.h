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
	Node **node; //������ �����

	int deep; // ������� ������� ������
	int max_deep; //���-�� �����
	int *n_node; //���-�� ����� �� ����
	int n_var;    //����������� ���������� (�������� ������)

	double fitness; //����������� ������



public:
	TTree<Node>();
	~TTree<Node>();
	TTree<Node>(const TTree<Node> &); //���������������
	TTree<Node>& operator=(const TTree<Node> &); //����������� ������

	void Init(int, int, int, int); //������������� ������
	bool Crossover(int, const TTree<Node>&, const TTree<Node>&); //����������� �������� (��������, ������ ������, ������� ����� �����������)



	inline bool SubTree(const Node&, const Node&); //��������� �������� �� ������ ���� ���������� �������
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
TTree<Node>& TTree<Node>::operator=(const TTree<Node> &other) {//���������� ��������� ������������

	if (this == &other)
		return *this; // ���������� ������ ����, ������ ������ �� ����


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
	int sum = 0;//��������� �����
	int actual_deep;
	int di;
	Crossover_index index = Get_crossover_index(type_of_crossover, origin, other);


	if (index.ready) {



		/*int iorigin=rand()%(origin.deep-1)+1;
		int jorigin=rand()%origin.n_node[iorigin];


		int iother=rand()%other.deep;
		int jother=rand()%other.n_node[iother]; */
		di = index.iother - index.iorigin; // �������� �����

		actual_deep = (index.iorigin + 1) + other.node[index.iother][index.jother].Get_n_heirs();

		if (origin.deep>actual_deep)
			actual_deep = origin.deep;    //���� ������� ������� ��������� ������ ������ �� ��������� ��� �������

		if (actual_deep <= origin.max_deep)
		{
			for (int i = 0; i < this->deep; i++)
				delete[] node[i];
			delete[] node;
			delete[] n_node;

			int jn = 0; // ��������� �� ����� ������ ������
			bool crossed = false; // ��������� �� ���� ���� ��� ���

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
				this->node[in] = new Node[this->n_node[in]]; //�������� ������ ��� ����� ����
				crossed = false;
				jn = 0;
				if (in<origin.deep) //���� ������� ������ origin ������ ��� ������� ����
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
				//��������� ���� �� ������ ����� (������� ���� ����������� � �����������)
				for (int s = 0; s < this->n_node[in - 1]; s++) {   //���� �� ����� ������������� ����

					this->node[in - 1][s].Set_argument(this->node[in]);  //��������� �� ���� � ���������
					for (int c = 0; c < this->node[in - 1][s].Get_n_child(); c++) {  //���� �� �������� ����������� ����

						this->node[in][sum + c].Set_num_parent(s);     // ������������� ����� ������������� ����
						this->node[in][sum + c].Set_num_self(c); // ������������� ���� �����
						this->node[in][sum + c].Set_index(this->node[in - 1][s].Get_index());
						this->node[in][sum + c].Add_index(to_string(this->node[in][sum + c].Get_num_self())); //��������� ���������� ������
						this->node[in][sum + c].Set_num_layer(in); //�������������� ����� ����
						this->node[in - 1][s].Set_child(c, sum + c); //���������� ������� ��������
					}
					sum += this->node[in - 1][s].Get_n_child();   //���������� ���-�� ���������� ����� �� ����
				}



				//������������ ����������� ���-�� ����� �� ���� ����
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
	int sum = 0;//��������� �����


	n_var = gn_var;
	max_deep = gmaxdeep;
	n_node = new int[max_deep];
	node = new Node *[max_deep];
	n_node[0] = 1; //�� 1 ���� ������ 1 ����(������)
	node[0] = new Node[1];  //������� ������
	node[0][0].Init(true, rand() % 2, n_var, inheriters);
	node[0][0].Set_num_layer(0);
	node[0][0].Set_num_self(0);
	node[0][0].Set_index("0");
	n_node[1] = node[0][0].Get_n_child(); //������ ������� �������� � �����

	for (int i = 1; i < max_deep; i++) {
		node[i] = new Node[n_node[i]]; //��������� ���� � ���������

		sum = 0;
		//��������� ���� �� ������ ����� (������� ���� ����������� � �����������)
		for (int s = 0; s < n_node[i - 1]; s++) {   //���� �� ����� ������������� ����

			node[i - 1][s].Set_argument(node[i]);  //��������� �� ���� � ���������
			for (int c = 0; c < node[i - 1][s].Get_n_child(); c++) {  //���� �� �������� ����������� ����

				if (i + 1 != max_deep) {
					if (growth == 0) 		node[i][sum + c].Init(true, rand() % 4, n_var, inheriters); //������ ����
					else 		   	node[i][sum + c].Init(rand() % 2, rand() % 4, n_var, inheriters); //�������� ����
				}
				else 				node[i][sum + c].Init(false, NULL, n_var, inheriters); //������� ����

				node[i][sum + c].Set_num_parent(s);     // ������������� ����� ������������� ����
				node[i][sum + c].Set_num_self(c); // ������������� ���� �����
				node[i][sum + c].Set_index(node[i - 1][s].Get_index());
				node[i][sum + c].Add_index(to_string(node[i][sum + c].Get_num_self())); //��������� ���������� ������
				node[i][sum + c].Set_num_layer(i); //�������������� ����� ����
				node[i - 1][s].Set_child(c, sum + c); //���������� ������� ��������
			}
			sum += node[i - 1][s].Get_n_child();   //���������� ���-�� ���������� ����� �� ����
		}
		//������������ ����������� ���-�� ����� �� ���� ����
		if (i + 1 != max_deep) {
			sum = 0;
			for (int j = 0; j < n_node[i]; j++) {
				sum += node[i][j].Get_n_child();
			}
			this->n_node[i + 1] = sum;
			if (this->n_node[i + 1] == 0) break;
		}


	}

	//������� ���������� ������� ������
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
		index.iother = rand() % other.deep;  //����� ������� �������� ���� � �������� ���������
		index.jother = rand() % other.n_node[index.iother];
		index.ready = true;
	}
	else {
		vector<int> iorigin;
		vector<int> jother;
		vector<int> iother;
		vector<int> jorigin;

		for (int i = 0; i < origin.deep; i++) { //���� �� ����� origin
			if (i<other.deep)   //���� ���� ���������� ���� � ����� ��������
				for (int jor = 0; jor < origin.n_node[i]; jor++) {  //���� �� ����� � origin ����� ������ �� ����
					for (int jot = jor; jot < other.n_node[i]; jot++) {  //���� �� ���� other ��������� �������� �� �� ����� ��� jor
						if (origin.node[i][jor].Get_index() == other.node[i][jot].Get_index() && origin.node[i][jor].Get_type() == true && other.node[i][jot].Get_type() == true && origin.node[i][jor].Get_arn() == other.node[i][jot].Get_arn()) {
							for (int jorc = 0; jorc < origin.node[i][jor].Get_n_child(); jorc++) {
								iorigin.push_back(i + 1);
								jorigin.push_back(origin.node[i][jor].Get_child(jorc));
							}
							for (int jotc = 0; jotc < other.node[i][jot].Get_n_child(); jotc++) {
								iother.push_back(i + 1);
								jother.push_back(other.node[i][jot].Get_child(jotc));
							}

							break; //��������� ���� ��� ����� ���� ��� ������� ����, ��������� � ���� ���� � origin
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
			index.ready = false; //���� ��� ������ ����
		}

	}

	return index;

}
//---------------------------------------------------------------------------
