#include "TNode.h"

TNode_symbolic::TNode_symbolic() {
	state = NULL;
	constant = NULL;
	type = NULL;

	num_var = NULL;

	value = NULL;

	func = NULL;
	arn = NULL;
	num_parent = NULL;
	n_child = NULL;
	child = 0;
	argument = 0;
	num_self = NULL;
	symbol = "";
	index = "";
}
//---------------------------------------------------------------------------
TNode_symbolic::TNode_symbolic(const TNode_symbolic &other) {
	this->state = other.state;
	this->constant = other.constant;
	this->type = other.type;

	this->num_var = other.num_var;

	this->value = other.value;
	this->func = other.func;
	this->arn = other.arn;
	this->num_parent = other.num_parent;
	this->n_child = other.n_child;
	this->num_self = other.num_self;
	this->num_layer = other.num_layer;
	this->argument = 0;
	//	if (type)
	{
		this->symbol = other.symbol;
		this->index = other.index;
	}
	this->child = new int[this->n_child];

	for (int i = 0; i < this->n_child; i++) {
		this->child[i] = other.child[i];
	}



}
//---------------------------------------------------------------------------
TNode_symbolic& TNode_symbolic::operator=(const TNode_symbolic &other) {//перегрузка оператора присваивания

	if (this == &other)
		return *this; // присвоение самому себе, ничего делать не надо

	delete[] child;

	this->state = other.state;
	this->constant = other.constant;
	this->type = other.type;

	this->num_var = other.num_var;

	this->value = other.value;
	this->func = other.func;
	this->arn = other.arn;
	this->num_parent = other.num_parent;
	this->n_child = other.n_child;
	this->num_self = other.num_self;
	this->num_layer = other.num_layer;
	this->argument = 0;
	//	if (type)
	{
		this->symbol = other.symbol;
		this->index = other.index;
	}
	this->child = new int[this->n_child];

	for (int i = 0; i < this->n_child; i++) {
		this->child[i] = other.child[i];
	}
	return *this;

}
//---------------------------------------------------------------------------
void TNode_symbolic::Init(bool gtype, int gfunc, int gn_var, int inheriters) {

	state = false;
	type = gtype;
	func = rand() % gn_var;
	if (type)
	{

		n_child = 2; //Бинарное дерево
		arn = 2;


		child = new int[n_child];

		Set_symbol(func);

	}
	else
	{
		n_child = 0;
		arn = 0;

		if (true)
			//Регрессия
		{
			constant = rand() % 2;
			n_child = 0;
			arn = 0;

			if (constant) {

				value = rand() % 20001 / 10000. - 1;

			}
			else {
				value = NULL;
				num_var = rand() % gn_var;
			}
		}
		else if (problem == 1)
		{
			//Нечеткая логика
			value = rand() % inheriters;

			num_var = value;
		}
	}


}
//---------------------------------------------------------------------------
void TNode_symbolic::Set_symbol(int gfunc) {

	switch (gfunc) {
	case 0:
		symbol = "+";
		break;
	case 1:
		symbol = "-";
		break;
	case 2:
		symbol = "*";
		break;
	case 3:
		symbol = "/";
		break;
	}
}
//---------------------------------------------------------------------------
__fastcall TNode_symbolic::~TNode_symbolic() {
	delete[] child;
}
//---------------------------------------------------------------------------
int TNode_symbolic::Get_n_heirs() {

	if (type) {
		int max = 0, tmp = 0;

		for (int i = 0; i < n_child; i++) {
			tmp = argument[child[i]].Get_n_heirs();
			if (tmp>max)
				max = tmp;
		}

		return max + 1;

	}
	else return 0;

}
//---------------------------------------------------------------------------
//Нечеткая логика
void TNode_symbolic::Get_value(vector<int *>& rules, int n_vars, int *n_terms) {

	if (type) {

		for (int i = 0; i < n_child; i++)
		{
			argument[child[i]].Get_value(rules, n_vars, n_terms);
		}


	}
	else
	{

		int *a = new int[n_vars];
		a[0] = num_layer;
		a[1] = num_self;
		a[2] = num_layer + num_self;
		rules.push_back(a);

	}
}
//---------------------------------------------------------------------------
//Регрессия
double TNode_symbolic::Get_value(double *gvar) {
	if (type) {

		switch (func) {
		case 0:
			value = Sum(argument, child, n_child, gvar);
			break;
		case 1:
			value = Minu(argument, child, n_child, gvar);
			break;
		case 2:
			value = Multip(argument, child, n_child, gvar);
			break;
		case 3:
			value = Divis(argument, child, n_child, gvar);
			break;
		}
	}
	else if (!constant) {
		value = gvar[num_var];
	}

	return value;

}
//---------------------------------------------------------------------------
string TNode_symbolic::Get_formula(string gsymbol) {
	string formula; //Формула данного узла
	if (type) {
		if (num_layer != 0)	formula = "(";
		for (int i = 0; i < n_child; i++) {
			formula += argument[child[i]].Get_formula(argument[child[i]].symbol);
			if (i<n_child - 1) formula += gsymbol;
		}
		if (num_layer != 0) formula += ")";


	}
	else
		if (constant) {
			if (value<0)
			{
				formula += "(";
				formula += to_string(value);
				formula += ")";
			}
			else formula = to_string(value);
		}
		else
		{
			formula = "x";
			formula += to_string(num_var);
		}

	return formula;

}

string TNode_symbolic::Get_symbol()
{
	return symbol;
}

double TNode_symbolic::Get_value()
{
	return value;
}

string TNode_symbolic::Get_index() const
{
	return index;
}

int TNode_symbolic::Get_num_layer() const
{
	return num_layer;
}

void TNode_symbolic::Set_num_layer(int n)
{
	num_layer = n;
}

int TNode_symbolic::Get_num_self()
{
	return num_self;
}

void TNode_symbolic::Set_num_self(int n)
{
	num_self = n;
}

int TNode_symbolic::Get_func()
{
	return func;
}

void TNode_symbolic::Set_func(int n)
{
	func = n;
}

int TNode_symbolic::Get_num_parent()
{
	return num_parent;
}

void TNode_symbolic::Set_num_parent(int n)
{
	num_parent = n;
}

int TNode_symbolic::Get_n_child()
{
	return n_child;
}

bool TNode_symbolic::Get_type()
{
	return type;
}

int TNode_symbolic::Get_child(int i)
{
	return child[i];
}

void TNode_symbolic::Set_child(int i, int n)
{
	child[i] = n;
}

int TNode_symbolic::Get_arn()
{
	return arn;
}

void TNode_symbolic::Set_argument(TNode_symbolic *arg)
{
	argument = arg;
}

void TNode_symbolic::Set_index(string str)
{
	index = str;
}

void TNode_symbolic::Add_index(string str)
{
	index += str;
}

//---------------------------------------------------------------------------
double Sum(TNode_symbolic *argument, int *index, int size, double *gvar) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += argument[index[i]].Get_value(gvar);
	}
	return sum;
}
//---------------------------------------------------------------------------
double Minu(TNode_symbolic *argument, int *index, int size, double *gvar) {
	return argument[index[0]].Get_value(gvar) - argument[index[1]].Get_value(gvar);
}
//---------------------------------------------------------------------------
double Multip(TNode_symbolic *argument, int *index, int size, double *gvar) {
	double mult = 1;
	for (int i = 0; i < size; i++) {
		mult *= argument[index[i]].Get_value(gvar);
	}
	return mult;
}
//---------------------------------------------------------------------------
double Divis(TNode_symbolic *argument, int *index, int size, double *gvar) {
	if (argument[index[1]].Get_value(gvar) != 0) 	return argument[index[0]].Get_value(gvar) / argument[index[1]].Get_value(gvar);
	else   									return argument[index[0]].Get_value(gvar);
}
//---------------------------------------------------------------------------