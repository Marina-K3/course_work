#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include"Notation.h"
using namespace std;
class Section
{ 
	int id;//���������� ����� ������
	string name;//�������� ������
	double section_cost;//��������� ��������
public:
	//��������� � cpp
	bool Entry_to_the_section();
	void WriteToFile();
	friend class Notation;
	void setID(int);
	void setName(string);
	void SetCosts(double);
	string getName();
	double getCosts();
	int getID();
};
