#pragma once
#include<string>
#include<iostream>
using namespace std;
// ����� ����������� ������� ������ ������ (��������� ������� ���-�� � ������ � ������)
class Notation
{
	int id_notation;//���������� ����� ������
	int id_child; // id ������
	int id_section;// id ������, ������� �� ��������
	double payment_made; // ������
	double arrears;// ����, ����������� ��� �������� ��������� �������� � ������

public:
	//��������� � cpp
	void Notation_Note();
	void WriteToFile();
    bool CheckPayment();
	void setID_not(int);
	void setID_child(int);
	void setID_sect(int);
	void setPayment(double);
	void setArrears(double);
	double getPayment();
	double getArrears();
	int getID_child();
	int getID_section();
	int getID_note();
};

