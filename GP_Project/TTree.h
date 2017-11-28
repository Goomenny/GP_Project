#pragma once

#include "TNode.h"
#include "TemplateTree.h"

#include "TFuzzy.h"
class TTree_symbolic : public TTree<TNode_symbolic>
{

private:
	double x = 7;

	

	double meansquare; //������������ ������

public:
	TTree_symbolic();
	~TTree_symbolic();
	TTree_symbolic(const TTree_symbolic &); //���������������
	//TTree_symbolic& operator=(const TTree_symbolic &); //����������� ������

	void Calculate_fitness(double **, double *, int, double); //���������� ����������� ������ (������� � ������ �������)
	void Mutate(int, double); //���������� � ������������
	string Get_formula(); // �������� ������� ������ ����� ��������
	double Get_meansquare();
	inline double Get_result(double *); 	//�������� �������� ������ ����� �������� ���������

	void Set(double i) { x = i * 3; }
	double Get() { return x; }




};
class TTree_fuzzy : public TTree<TNode_symbolic>
{

private:
	vector< vector<int> > rules; //���� ������

	double x = 7;

public:
	TTree_fuzzy();
	~TTree_fuzzy();
	TTree_fuzzy(const TTree_fuzzy &); //���������������
	TTree_fuzzy& operator=(const TTree_fuzzy &); //����������� ������

	void Mutate(int, double); //���������� � ������������

	void Calculate_fitness(TFuzzy&);
	vector< vector<int> > Get_rules();
	void Get_result(const vector<int>&); 	//�������� �������� ������ ����� ��������
	vector< vector<int> > Decart(int *[], int);


	void Set(double i) { x = i * 3; }
	double Get() { return x; }


	

};

double Func(double *, int);