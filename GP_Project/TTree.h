#pragma once

#include "TNode.h"
#include "TemplateTree.h"

#include "TFuzzy.h"
class TTree_symbolic : public TTree<TNode_symbolic>
{

private:
	double x = 7;

	

	double meansquare; //Квадратичная ошибка

public:
	TTree_symbolic();
	~TTree_symbolic();
	TTree_symbolic(const TTree_symbolic &); //Копиконструктор
	//TTree_symbolic& operator=(const TTree_symbolic &); //Копирование дерева

	void Calculate_fitness(double **, double *, int, double); //Установить пригодность дерева (выборка и размер выборки)
	void Mutate(int, double); //Мутировать с вероятностью
	string Get_formula(); // Получить формулу дерева через рекурсии
	double Get_meansquare();
	inline double Get_result(double *); 	//Получить значение дерева через рекурсии регрессия

	void Set(double i) { x = i * 3; }
	double Get() { return x; }




};
class TTree_fuzzy : public TTree<TNode_symbolic>
{

private:
	vector< vector<int> > rules; //База правил

	double x = 7;

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


	void Set(double i) { x = i * 3; }
	double Get() { return x; }


	

};

double Func(double *, int);