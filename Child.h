#pragma once
#include<iostream>
#include<string>
#include"Notation.h"
using namespace std;
extern bool check_str(string);
//��������� ���� ��������
struct dateOfBirth {
	string date;//���� �������� ����
	int day;//���� � ������������� �������
	int month;// ����� � ������������� �������
	int year; // ��� � ������������� �������
	int age;//�������
};
// ����� ��������������� ������
class Child
{
	int id;// ���������� �����
	string fullNameChild;// ��� ������
	string fullNameParent; // ��� ��������
    dateOfBirth date_of_birth_of_the_child; // ������ ��������� � ����� ��������
	string phoneNumber;// ���������� �����

public:
	// ��������� � ������� ����������� � cpp
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

