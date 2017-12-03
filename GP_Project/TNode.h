#pragma once
#include <vector>
#include <string>
using namespace std;
class TNode
{
protected:
	int problem; //Тип узла 0-регрессия,1-нечеткая логика
	bool type; //true-функциональный false-терминальный
	bool constant; //true - константа false - перемеенная
	bool state; // Состояние просчитанный узел или нет

	double value; //Значение узла

	int *child; // Порядковые номера потомков

	int num_var; //Номер переменной
	int func; //Тип функционала
	unsigned short int arn; //Арность функционала
	int num_parent; //Номер родительского узла
	int n_child; //Кол-во потомков
	int num_self; // Свой номер для родительского узла
	int num_layer; // Свой номер слоя

	string symbol;  //Символ функционала
	string index; //Абсолютный индекс узла
public:


	string Get_symbol() { return symbol;	};
	string Get_index() const { return index; };

	bool Get_type() {return type; };
	int Get_num_layer() const {	return num_layer;};
	int Get_num_self() {return num_self;};
	int Get_num_parent() {	return num_parent;};
	int Get_child(int i) {return child[i];};
	int Get_n_child() {	return n_child;};
	int Get_arn() {	return arn;};
	int Get_func() {return func;};
	double Get_value() {return value;};

	void Set_num_layer(int n) {num_layer = n;};
	void Set_num_self(int n) {num_self = n;};
	void Set_num_parent(int n) {num_parent = n;};
	void Set_child(int i, int n) {child[i] = n; };

	void Set_symbol(int); //Установить символ
	void Set_index(string str) {index = str;};
	void Set_func(int n) {func = n;};

	void Add_index(string str) {index += str;};
};
class TNode_symbolic : public TNode
{
private:
	
	TNode_symbolic *argument;   //Указатель на слой потомков

public:
	TNode_symbolic();
	~TNode_symbolic();
	TNode_symbolic(const TNode_symbolic&); //Копиконструктор
	TNode_symbolic& operator= (const TNode_symbolic&); // Копирование узла

	void Init(bool, int, int, int); // Инициализация

	
	void Get_result(vector<int *>&, int, int *); //Нечеткая логика
	double Get_result(double *); //Регрессия

	string Get_formula(string); // Получить формулу узла через рекурсии

	int Get_n_heirs();

	void Set_argument(TNode_symbolic *);
	
	
};

class TNode_fuzzy : public TNode
{
public:

protected:
	int nod;
};

class TNode_DE : public TNode
{
private:

	TNode_DE *argument;   //Указатель на слой потомков

public:
	TNode_DE();
	~TNode_DE();
	TNode_DE(const TNode_DE&); //Копиконструктор
	TNode_DE& operator= (const TNode_DE&); // Копирование узла

	void Init(bool, int, int, int); // Инициализация

	double Get_result(double *); //Регрессия

	string Get_formula(string); // Получить формулу узла через рекурсии

	int Get_n_heirs();

	void Set_argument(TNode_DE *);


};


//---------------------------------------------------------------------------
template < class Node >
double Sum(Node *argument, int *index, int size, double *gvar) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += argument[index[i]].Get_result(gvar);
	}
	return sum;
}
//---------------------------------------------------------------------------
template < class Node >
double Minu(Node *argument, int *index, int size, double *gvar) {
	return argument[index[0]].Get_result(gvar) - argument[index[1]].Get_result(gvar);
}
//---------------------------------------------------------------------------
template < class Node >
double Multip(Node *argument, int *index, int size, double *gvar) {
	double mult = 1;
	for (int i = 0; i < size; i++) {
		mult *= argument[index[i]].Get_result(gvar);
	}
	return mult;
}
//---------------------------------------------------------------------------
template < class Node >
double Divis(Node *argument, int *index, int size, double *gvar) {
	if (argument[index[1]].Get_result(gvar) != 0) 	return argument[index[0]].Get_result(gvar) / argument[index[1]].Get_result(gvar);
	else   									return argument[index[0]].Get_result(gvar);
}
//---------------------------------------------------------------------------