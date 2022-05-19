#pragma once
#include<string>
#include<iostream>
using namespace std;
// класс реализующий учётную запись центра (связывает воедино инф-ию о ребёнке и секции)
class Notation
{
	int id_notation;//уникальный номер записи
	int id_child; // id ребёнка
	int id_section;// id секции, которую он посещает
	double payment_made; // оплата
	double arrears;// долг, высчитанный как разность стоимости обучения и оплаты

public:
	//пояснения в cpp
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

