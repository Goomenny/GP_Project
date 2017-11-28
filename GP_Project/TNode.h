#pragma once


#include "TemplateNode.h"
#include <vector>
#include <string>
using namespace std;
class TNode_symbolic : public TNode
{
private:
	int problem; //��� ���� 0-���������,1-�������� ������
	bool type; //true-�������������� false-������������
	bool constant; //true - ��������� false - �����������
	bool state; // ��������� ������������ ���� ��� ���


	int num_var; //����� ����������
	int func; //��� �����������
	unsigned short int arn; //������� �����������
	int num_parent; //����� ������������� ����
	int n_child; //���-�� ��������
	int num_self; // ���� ����� ��� ������������� ����
	int num_layer; // ���� ����� ����
	int *child; // ���������� ������ ��������

	double value; //����� �������

	string symbol;  //������ �����������
	string index; //���������� ������ ����

	TNode_symbolic *argument;   //��������� �� ���� ��������

public:
	TNode_symbolic();
	~TNode_symbolic();
	TNode_symbolic(const TNode_symbolic&); //���������������
	TNode_symbolic& operator= (const TNode_symbolic&); // ����������� ����

	void Init(bool, int, int, int); // �������������




	void Get_value(vector<int *>&, int, int *); //�������� ������
	double Get_value(double *); //���������

								//	double Get_val();          //�������� �������� ���� ������ ��������

	string Get_formula(string); // �������� ������� ���� ����� ��������


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

	void Set_symbol(int); //���������� ������
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