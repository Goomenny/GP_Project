#pragma once
#include "math.h"
#include "TNode.h"
#include "TemplateTree.h"
#include "TFuzzy.h"
class TTree_symbolic : public TTree<TNode_DE>
{

private:
	double meansquare; //Квадратичная ошибка

	//DE
	double meanresult; //Среднее решение
public:
	TTree_symbolic();
	~TTree_symbolic();
	TTree_symbolic(const TTree_symbolic &); //Копиконструктор
	//TTree_symbolic& operator=(const TTree_symbolic &); //Копирование дерева

	void Calculate_fitness(double **, double *, int, double); //Установить пригодность дерева (выборка и размер выборки)
	void Mutate(int, double); //Мутировать с вероятностью
	string Get_formula(); // Получить формулу дерева через рекурсии
	double Get_meansquare() { return meansquare; };
	
	inline double Get_result(double *); 	//Получить значение дерева через рекурсии регрессия

	//DE
	void Calculate_fitness(); //Вычислить пригодность дерева
	double Get_meanresult() { return meanresult; };
	void Set_fitness(double newfitness) { fitness = newfitness; };

};

class TTree_fuzzy : public TTree<TNode_symbolic>
{

private:
	vector< vector<int> > rules; //База правил



public:
	TTree_fuzzy();
	~TTree_fuzzy();
	TTree_fuzzy(const TTree_fuzzy &); //Копиконструктор
	TTree_fuzzy& operator=(const TTree_fuzzy &); //Копирование дерева

	void Mutate(int, double); //Мутировать с вероятностью

	void Calculate_fitness(TFuzzy&);
	vector< vector<int> > Get_rules();
	void Get_result(const vector<int>&); 	//Получить значение дерева через рекурсии
	vector< vector<int> > Decart(int *[], int);

	

};

double Func(double *, int);