#pragma once
#include <vector>
#include <string>
using namespace std;
class TNode
{
protected:
	int problem; //��� ���� 0-���������,1-�������� ������
	bool type; //true-�������������� false-������������
	bool constant; //true - ��������� false - �����������
	bool state; // ��������� ������������ ���� ��� ���

	double value; //�������� ����

	int *child; // ���������� ������ ��������

	int num_var; //����� ����������
	int func; //��� �����������
	unsigned short int arn; //������� �����������
	int num_parent; //����� ������������� ����
	int n_child; //���-�� ��������
	int num_self; // ���� ����� ��� ������������� ����
	int num_layer; // ���� ����� ����

	string symbol;  //������ �����������
	string index; //���������� ������ ����
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

	void Set_symbol(int); //���������� ������
	void Set_index(string str) {index = str;};
	void Set_func(int n) {func = n;};

	void Add_index(string str) {index += str;};
};
class TNode_symbolic : public TNode
{
private:
	
	TNode_symbolic *argument;   //��������� �� ���� ��������

public:
	TNode_symbolic();
	~TNode_symbolic();
	TNode_symbolic(const TNode_symbolic&); //���������������
	TNode_symbolic& operator= (const TNode_symbolic&); // ����������� ����

	void Init(bool, int, int, int); // �������������

	
	void Get_result(vector<int *>&, int, int *); //�������� ������
	double Get_result(double *); //���������

	string Get_formula(string); // �������� ������� ���� ����� ��������

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

	TNode_DE *argument;   //��������� �� ���� ��������

public:
	TNode_DE();
	~TNode_DE();
	TNode_DE(const TNode_DE&); //���������������
	TNode_DE& operator= (const TNode_DE&); // ����������� ����

	void Init(bool, int, int, int); // �������������

	double Get_result(double *); //���������

	string Get_formula(string); // �������� ������� ���� ����� ��������

	int Get_n_heirs();

	void Set_argument(TNode_DE *);


};

double Sum(TNode_symbolic *, int *, int, double *);
double Minu(TNode_symbolic *, int *, int, double *);
double Multip(TNode_symbolic *, int *, int, double *);
double Divis(TNode_symbolic *, int *, int, double *);