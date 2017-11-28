#pragma once


#include "TemplateNode.h"
#include <vector>
#include <string>
using namespace std;
class TNode_symbolic : public TNode
{
private:
	int problem; //Тип узла 0-регрессия,1-нечеткая логика
	bool type; //true-функциональный false-терминальный
	bool constant; //true - константа false - перемеенная
	bool state; // Состояние просчитанный узел или нет


	int num_var; //Номер переменной
	int func; //Тип функционала
	unsigned short int arn; //Арность функционала
	int num_parent; //Номер родительского узла
	int n_child; //Кол-во потомков
	int num_self; // Свой номер для родительского узла
	int num_layer; // Свой номер слоя
	int *child; // Порядковые номера потомков

	double value; //Номер правила

	string symbol;  //Символ функционала
	string index; //Абсолютный индекс узла

	TNode_symbolic *argument;   //Указатель на слой потомков

public:
	TNode_symbolic();
	~TNode_symbolic();
	TNode_symbolic(const TNode_symbolic&); //Копиконструктор
	TNode_symbolic& operator= (const TNode_symbolic&); // Копирование узла

	void Init(bool, int, int, int); // Инициализация




	void Get_value(vector<int *>&, int, int *); //Нечеткая логика
	double Get_value(double *); //Регрессия

								//	double Get_val();          //Получить значение узла вторым способом

	string Get_formula(string); // Получить формулу узла через рекурсии


	double Get_value();

	void Set_argument(TNode_symbolic *);


	string Get_symbol();
	string Get_index() const;

	bool Get_type();
	int Get_num_layer() const;
	int Get_num_self();
	int Get_num_parent();
	int Get_child(int);
	int Get_n_child();
	int Get_n_heirs();
	int Get_arn();
	int Get_func();

	void Set_num_layer(int);
	void Set_num_self(int);
	void Set_num_parent(int);
	void Set_child(int, int);

	void Set_symbol(int); //Установить символ
	void Set_index(string);
	void Set_func(int);

	void Add_index(string);
};

class TNode_fuzzy : public TNode
{
public:

protected:
	int nod;
};
double Sum(TNode_symbolic *, int *, int, double *);
double Minu(TNode_symbolic *, int *, int, double *);
double Multip(TNode_symbolic *, int *, int, double *);
double Divis(TNode_symbolic *, int *, int, double *);