#pragma once
#include<iostream>
#include<string>
#include"Notation.h"
using namespace std;
extern bool check_str(string);
//структура даты рождения
struct dateOfBirth {
	string date;//дата встроком виде
	int day;//день в целочисленном формате
	int month;// месяц в целочисленном формате
	int year; // год в целочисленном формате
	int age;//возраст
};
// класс демонстрирующий ребёнка
class Child
{
	int id;// уникальный номер
	string fullNameChild;// фио ребёнка
	string fullNameParent; // фио родителя
    dateOfBirth date_of_birth_of_the_child; // данные связанные с датой рождения
	string phoneNumber;// телефонный номер

public:
	// пояснения к методам расположены в cpp
	void Child_Note();
	int getAge();
	void convertDate();
	friend bool checkDate(int&, int&, int&);
	friend class Notation;
	void WriteToFile();
	void setID(int new_id);
	void setName_child(string str);
	void setName_parent(string str);
	void setDate(string str);
	void setPhone(string str);
	void setAge(int);
	string getNameChild();
	string getNameParent();
	string getDate();
	int getID();
	int returnAge();
	string getPhone();
};

