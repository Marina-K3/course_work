#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"Notation.h"
#include"Child.h"
#include"Section.h"
#define PRIME_CONST 11// константа для хэширования
using namespace std;
// класс демонстрирующий пользователя центра
class User
{
protected:
	string login;//логин пользователя
	long int hash_password;//хэшированный пароль
	int role;//роль в системе
	int access;//уровень доступа
public:
	//пояснения в cpp
	static int autorisation();
	virtual void provide_menu()=0;
	void WriteToFile();
	void DisplayChild();
	int ReadToVectorsData(vector<Notation>& notes,
		vector<Child>& children,
		vector<Section>& sections);
	friend int CountNotes();
	friend bool check_uniqueness(string entered_login);
	void setLogin(string);
	void setRole(int);
	void setAccess(int);
	void setPassword(long int);
	string getLogin();
	long int getPassword();
	void Individual_task();
	void Find();
	void Sort();
	int getAccess();

};
class Employee;

class Admin : public User {
	friend long int hashFunction(string);
public:
	void provide_menu();
	void ReadToUsers(vector<Employee>& employees, vector<Admin>& admins);
	void CreateNew();
	void work_with_user_accounts();
	void work_with_childrens_centr();
	void show_users();
	void grant_access(Employee &obj);
	friend int CountUsers();
	void Add(Employee&);
	void Add(Admin &);
	void Add_account();
	void Edit_Account();
	void Delete_account();
	void Delete_note();
	void EditData();
	void createFirstAdmin();
	
};
class Employee : public User {
	friend long int hashFunction(string);
public:
	void Register();
	void CreateNew();
	void provide_menu();
	
};
extern int CountUsers();