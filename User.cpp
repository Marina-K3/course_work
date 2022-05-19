#include "User.h"
#include"Notation.h"
#include"Section.h"
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include<algorithm>
//количество записей
int CountNotes()
{   
	string line;
	ifstream notation;
	notation.open("Notation.txt", ios::in);
	int i = 0;
	while (getline(notation, line)) {
		i++;
	}
	return i;
}
//количество пользователей
extern int CountUsers() {
	string line;
	ifstream notation;
	notation.open("Users.txt", ios::in);
	int i = 0;
	while (getline(notation, line)) {
		i++;
	}
	return i/4;
};
bool check_uniqueness(string entered_login) {
	string login, newline;
	long int hash_password;
	int role, access;
	int i = 0, j = 0;
	ifstream f;
	f.open("Users.txt", ios::in);
	while (getline(f, login) && f >> hash_password && getline(f, newline) && f >> role && getline(f, newline) && f >> access && getline(f, newline)) {
		if (entered_login == login) {
			return false;
		}
	}
	return true;
}
// хэширование
long int hashFunction(string key) {
	long int hashCode = 0;
	for (int i = 0; i < key.length(); i++) {
		hashCode += key[i] * pow(PRIME_CONST, i);
	}
	return hashCode;
}
// прочитать информацию о центре в вектора : дети, секции, записи
int User::ReadToVectorsData(vector<Notation>&notes,
vector<Child> &children,
vector<Section> &sections) {
	
	long int id_not, id_child_from_not, id_sect_from_not, age, id_child, id_sec;
	double arrears, payment, costs;
	string name_sect, name_child, name_parent, date, phone, line;

	ifstream notation;
	notation.open("Notation.txt", ios::in);
	int i = 0;

	while (notation >> id_not && notation >> id_child_from_not
		&& notation >> id_sect_from_not && notation >> arrears && notation >> payment && getline(notation, line)) {

		ifstream child;
		child.open("Children.txt", ios::in);

		while (child >> id_child && getline(child, line) && getline(child, name_child)
			&& getline(child, name_parent) && getline(child, date) && child >> age && getline(child, line) && getline(child, phone)) {
			if (id_child == id_child_from_not) {

				ifstream sect;
				sect.open("Section.txt", ios::in);

				while (sect >> id_sec && getline(sect, line) && getline(sect, name_sect) && sect >> costs && getline(sect, line)) {

					if (id_sect_from_not == id_sec) {
						Child child;
						Notation note;
						Section section;
						notes.push_back(note);
						children.push_back(child);
						sections.push_back(section);

						notes[i].setID_not(id_not);
						notes[i].setID_child(id_child_from_not);
						notes[i].setID_sect(id_sect_from_not);
						notes[i].setArrears(arrears);
						notes[i].setPayment(payment);

						children[i].setID(id_child);
						children[i].setName_child(name_child);
						children[i].setName_parent(name_parent);
						children[i].setDate(date);
						children[i].setAge(age);
						children[i].setPhone(phone);

						sections[i].setName(name_sect);
						sections[i].setID(id_sec);
						sections[i].SetCosts(costs);

						i++;
					}
				}
				sect.close();
			}
		}
		child.close();

	}

	notation.close();
	return 0;

}
//заполняет вектора админов и сотрудников
void Admin::ReadToUsers(vector<Employee>&employees, vector<Admin>&admins) {
	string login, line, adm = "админ", us = "пользователь";
	long int hash_password;
	int role, access;
	int i = 0, j = 0;
	ifstream f;
	f.open("Users.txt", ios::in);
	while (getline(f, login) && f >> hash_password && getline(f, line) && f >> role && getline(f, line) && f >> access && getline(f, line)) {
		if (role == 0) {
			Employee employee;
			employees.push_back(employee);
			employees[j].setLogin(login);
			employees[j].setPassword(hash_password);
			employees[j].setAccess(access);
			employees[j].setRole(role);
			j++;
		}
		if (role == 1) {
			Admin admin;
			admins.push_back(admin);
			admins[i].setLogin(login);
			admins[i].setPassword(hash_password);
			admins[i].setAccess(access);
			admins[i].setRole(role);
			i++;
		}
		
	}
	f.close();
}
//поменять логин
void User::setLogin(string u)
{
	this->login = u;
}
//поменять роль
void User::setRole(int role)
{
	this->role = role;
}
//меняет уровень доступа
void User::setAccess(int access)
{
	this->access = access;
}
//меняет пароль
void User::setPassword(long int k)
{
	this->hash_password = k;
}
//возвращает логин
string User::getLogin()
{
	return this->login;
}
//возвращает пароль
long int User::getPassword()
{
	return this->hash_password;
}
//прототип компаратора
bool mySortBySurname(Child child_a, Child child_b);
//сортировка по алфавиту
void sortBySurname(vector <Child>& children) // сортировка
{
	sort(children.begin(), children.end(), mySortBySurname);
}
//прототип компаратора
bool mySortByAge(Child child_a, Child child_b);
//сортировка по возрасту
void sortByAge(vector <Child>& children) // сортировка
{
	sort(children.begin(), children.end(), mySortByAge);
}
//компаратор сортировки по алфавиту
bool mySortBySurname(Child child_a, Child child_b) // функция-компаратор
{
	return child_a.getNameChild() < child_b.getNameChild(); // по алфавиту
}
//компаратор сортировки по возрасту (увеличение)
bool mySortByAge(Child child_a, Child child_b) // функция-компаратор
{
	return child_a.getAge() < child_b.getAge(); // по увеличению возраста
}
//прототип компаратора
bool mySortByArrears(Notation note_a, Notation note_b);
//сортировка по велечине долга
void sortByArrears(vector <Notation>& notes) // сортировка
{
	sort(notes.begin(), notes.end(), mySortByArrears);
}
//компаратор сортировки по величине долга
bool mySortByArrears(Notation note_a, Notation note_b) // функция-компаратор
{
	return note_a.getArrears() > note_b.getArrears(); // по убыванию долга
}
//прототип компаратора
bool mySortByAge_decrease(Child child_a, Child child_b);
//сортировка по возрасту (по уменьшению)
void sortByAge_decrease(vector <Child>& children) // сортировка
{
	sort(children.begin(), children.end(), mySortByAge_decrease);
}
//компаратор сортировки по возрасту (по уменьшению)
bool mySortByAge_decrease(Child child_a, Child child_b) {
	return child_a.getAge() > child_b.getAge();
}
//прототип функции-компаратора
bool mySortBySection(Notation a, Notation b);
//сортиовка по секциям
void sortBySection(vector <Notation>& notes) // сортировка
{
	sort(notes.begin(), notes.end(), mySortBySection);
}
//компаратор сортировки по секциям
bool mySortBySection(Notation a, Notation b) {
	return a.getID_section()<b.getID_section();
}
//функция - индивидуальное задание
void User::Individual_task()
{
	if (CountNotes) {
		cout << "\n\n          ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ\n";
		cout << "\t 1 - Вывести должников в порядке убывания долга\n\t 2 - Вывести информацию в порядке увеличения возраста детей\n\t  Ваш выбор - ";
		int choice;
		cin >> choice;
		while (cin.fail() || (choice > 2 || choice < 1)) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
		if (choice == 1) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			sortByArrears(notes);
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
				<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			for (int i = 0; i < notes.size(); i++) {
				for (int k = 0; k < children.size(); k++) {
					if (children[k].getID() == notes[i].getID_child()) {

						std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
							<< children[k].getNameChild() << "|" << setw(35) << children[k].getNameParent() << "|"
							<< setw(13) << children[k].getDate() << "|" << setw(10) << children[k].returnAge() << "|" << setw(13) << children[k].getPhone();
						for (int b = 0; b < sections.size(); b++) {
							if (notes[i].getID_section() == sections[b].getID() && children[k].getID() == notes[i].getID_child()) {

								std::cout << "|" << setw(16) << sections[b].getName() << "|" << setw(9) << sections[b].getCosts() << "|"
									<< setw(8) << notes[i].getPayment() << "|" << setw(6) << notes[i].getArrears() << "||" << endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
									<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								break;
							}
						}
					}

				}

			}
		}
		if (choice == 2) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			sortByAge(children);
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
				<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			for (int i = 0; i < children.size(); i++) {
				for (int k = 0; k < notes.size(); k++) {
					if (children[i].getID() == notes[k].getID_child()) {

						std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
							<< children[i].getNameChild() << "|" << setw(35) << children[i].getNameParent() << "|"
							<< setw(13) << children[i].getDate() << "|" << setw(10) << children[i].returnAge() << "|" << setw(13) << children[i].getPhone();
						for (int b = 0; b < sections.size(); b++) {
							if (notes[k].getID_section() == sections[b].getID() && children[i].getID() == notes[k].getID_child()) {

								std::cout << "|" << setw(16) << sections[b].getName() << "|" << setw(9) << sections[b].getCosts() << "|"
									<< setw(8) << notes[k].getPayment() << "|" << setw(6) << notes[k].getArrears() << "||" << endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
									<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								break;
							}
						}
					}

				}

			}
		}
	}else cout << "     НЕТ ЗАПИСЕЙ";
}
//отобразить информацию о детях
void User::DisplayChild() {
	if (CountNotes) {
		vector<Child>children;
		vector<Section>sections;
		vector<Notation>notes;
		children.reserve(CountNotes());
		sections.reserve(CountNotes());
		notes.reserve(CountNotes());
		ReadToVectorsData(notes, children, sections);
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
			<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;



		for (int i = 0; i < notes.size(); i++) {
			for (int k = 0; k < children.size(); k++) {
				if (children[k].getID() == notes[i].getID_child()) {

					std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
						<< children[k].getNameChild() << "|" << setw(35) << children[k].getNameParent() << "|"
						<< setw(13) << children[k].getDate() << "|" << setw(10) << children[k].returnAge() << "|" << setw(13) << children[k].getPhone();
					for (int b = 0; b < sections.size(); b++) {
						if (notes[i].getID_section() == sections[b].getID() && children[k].getID() == notes[i].getID_child()) {

							std::cout << "|" << setw(16) << sections[b].getName() << "|" << setw(9) << sections[b].getCosts() << "|"
								<< setw(8) << notes[i].getPayment() << "|" << setw(6) << notes[i].getArrears() << "||" << endl;
							std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
								<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
							break;
						}
					}
				}

			}

		}
	}
	else cout << "     НЕТ ЗАПИСЕЙ";
}
//запись в файл аккаунта
void User::WriteToFile() {
	ofstream out;          // поток для записи
	out.open("Users.txt", ios::app); // окрываем файл для записи
	if (out.is_open())
	{
		out <<this->login<<endl;
		out << this->hash_password << endl;
		out << this->role << endl;
		out << this->access << endl;
	}
	out.close();
}
// авторизация
int User:: autorisation(){
	string login, password;
	long int hash_password;
	std::cout << "\n\t*****~~~~~~~~~~~~~~~~~~~~~~~*****" << endl;
	std::cout << "\t  Введите логин: ";
	getchar();
	getline(cin, login);
	while (login.size() < 4 || login.size() > 22) {
		cout << "\t Вы используете слишком много символов (4 - 22)\n\t Исправьтесь - ";
		getline(cin,login);
	}
	std::cout << "\t  Ваш пароль : ";
	char cInput;
	while ((cInput = _getch()) != '\r' && password.size()<22)
	{
		if ((int)cInput != 8) {
			password.push_back(cInput);
			_putch('*');
		}
		if ((int)cInput == 8) {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.pop_back();
			}
		}
	}
	std::cout << "\n\t*****~~~~~~~~~~~~~~~~~~~~~~~*****\n" << endl;

	hash_password = hashFunction(password);
	string file_log, newLine;
	long int file_pass;
	int role, access;
	ifstream f;
	f.open("Users.txt", ios::in);
	while (getline(f, file_log) && f >> file_pass && getline(f, newLine) && f >> role && getline(f, newLine) && f >> access && getline(f, newLine)) {

		if (hash_password == file_pass && login == file_log && role == 1 && access == 1) {
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			std::cout << "\t|| Авторизация прошла успешно ||\n\t|| Вы вошли как администратор || \n";
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			return 1;
		}
		if (hash_password == file_pass && login == file_log && role == 0 && access == 1) {
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			std::cout << "\t|| Авторизация прошла успешно ||\n\t|| Вы вошли как сотрудник    ||\n";
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			return 2;
		}
		if (hash_password == file_pass && login == file_log && role == 0 && access == 0) {
			std::cout << " ----#### Авторизация прошла успешно, но вам не предоставлен доступ ###----\n";
			return 0;
		}
	}
	f.close();
	return -1;
}
//создание нового аккаунта сотрудника
void Employee::CreateNew() {
	cout << "\n  *** Заполнение учётных данных аккаунта***\n";
	std::cout << "\t Введите логин - ";
	getchar();
	getline( cin,this->login);
	while (this->login.size() < 4 || this->login.size() > 22) {
		cout << "\t Вы используете слишком много символов (4 - 22)\n\t Исправьтесь - ";
		getline(cin, this->login);
	}
	std::cout << "\t Введите пароль - ";
	string password;
	char cInput;
	while ((cInput = _getch()) != '\r' && password.size()<22)
	{
		if ((int)cInput != 8) {
			password.push_back(cInput);
			_putch('*');
		}
		if ((int)cInput == 8) {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.pop_back();
			}
		}
	}
	this->hash_password = hashFunction(password);
	this->access = 0;
	this->role = 0;
}
// создание нового аккаунта админа
void Admin::CreateNew() {
	cout << "\n  *** Заполнение учётных данных аккаунта***\n";
	std::cout << "\t Введите логин - ";
	getchar();
	getline(cin, this->login);
	while (this->login.size() < 4 || this->login.size() > 22) {
		cout << "\t Вы используете слишком много символов (4 - 22)\n\t Исправьтесь - ";
		getline(cin, this->login);
	}
	std::cout << "\t Введите пароль - ";
	string password;
	char cInput;
	while ((cInput = _getch()) != '\r' && password.size() < 22)
	{
		if ((int)cInput != 8) {
			password.push_back(cInput);
			_putch('*');
		}
		if ((int)cInput == 8) {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.pop_back();
			}
		}
	}
	
		this->hash_password = hashFunction(password);
		this->access = 1;
		this->role = 1;
	
}
//функция для работы с акаунтами пользователей
void Admin::work_with_user_accounts()
{
	int cycle = 1;
	int choice;
	while (cycle) {
		cout << "\n-----------------------------------------------------------";
		std::cout << "\n    Работа с учётными записями пользователей\n";
		std::cout << "\t 1 - просмотр\n\t 2 - добавление\n\t 3 - редактирование\n\t 4 - удаление\n\t 5 - предоставление доступа\n\t 0 - вeрнуться назад\n\t ваш выбор - ";
		cin >> choice;
		while (cin.fail() || (choice > 5 || choice < 0)) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
		switch (choice) {
		case 0:
			cycle = 0;
			break;
		case 1:
				show_users();
			break;
		case 2: 
				Add_account();
			break;
		case 3: 
			if(CountUsers)
			Edit_Account();
			break;
		case 4: 
			if (CountUsers() != 1)
			Delete_account();
			else cout << "   Удаление невозможно - зарегистрированы только вы!";
			break;
		case 5: if (CountUsers() != 1) {
			show_users();
			string login;
			Employee obj;
			std::cout << "\t Введите логин пользователя: ";
			getchar();
			getline(cin, login);
			while (login.size() < 4 || login.size() > 22) {
				cout << "\t Вы используете слишком много сомволов (4 - 22)\n\t Исправьтесь - ";
				getline(cin, login);
			}
			obj.setLogin(login);
			grant_access(obj);
		} else cout << "   предоставление доступа невозможно - зарегистрированы только вы!";
		}
	}
}
//редактировать аккаунт
void Admin::Edit_Account() {

	show_users();
	vector<Admin>admins;
	vector<Employee>employees;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins);
	int number;
	std::cout << "\n\tвведите номер редактируемой записи - ";
	std::cin >> number;
	while (cin.fail() || (number > employees.size()+admins.size() || number <= 0)) {
		std::cout << "\t  !!! Вы некорректно ввели значение !!!\n";
		std::cout << "\t  Исправьтесь - ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> number;
	}
		if (number <= employees.size()) {
			number = number - 1;
			int choice;
			std::cout << "\tбудете менять :\n   login - 1 ,\n   password - 2 ,\n   всё - 3\n   ничего - 4\n  ваш выбор - ";
			std::cin >> choice;
			while (cin.fail() || (choice > 4 || choice < 0)) {
				std::cout << "\t  !!! Вы некорректно ввели значение !!!\n";
				std::cout << "\t  Исправьтесь - ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cin >> choice;
			}
			if (choice == 1) {
				string newlogin;
				std::cout << "   введите новый login: ";
				getchar();
				getline(cin, newlogin);
				while (newlogin.size() < 4 || newlogin.size() > 22) {
					cout << "\t Вы используете слишком много сомволов (4 - 22)\n\t Исправьтесь - ";
					getline(cin, newlogin);
				}
				employees[number].setLogin(newlogin);
				std::cout << "   изменение прошло успешно\n";
			}
			if (choice == 2) {
				string password;
				std::cout << "   введите новый пароль: ";
				char cInput;
				while ((cInput = _getch()) != '\r' && password.size()<22)
				{
					if ((int)cInput != 8) {
						password.push_back(cInput);
						_putch('*');
					}
					if ((int)cInput == 8) {
						if (!password.empty()) {
							std::cout << "\b \b";
							password.pop_back();
						}
					}
				}
				employees[number].setPassword(hashFunction(password));
				std::cout << "   изменение прошло успешно\n";
			}
			if (choice == 3) {
				string newlogin;
				std::cout << "   введите новый login: ";
				getchar();
				getline(cin, newlogin);
				while (newlogin.size() < 4 || newlogin.size() > 22) {
					cout << "\t Вы используете слишком много сомволов (4 - 22)\n\t Исправьтесь - ";
					getline(cin, newlogin);
				}
				employees[number].setLogin(newlogin);
				string password;
				std::cout << "   введите новый пароль: ";
				char cInput;
				while ((cInput = _getch()) != '\r' && password.size()<22)
				{
					if ((int)cInput != 8) {
						password.push_back(cInput);
						_putch('*');
					}
					if ((int)cInput == 8) {
						if (!password.empty()) {
							std::cout << "\b \b";
							password.pop_back();
						}
					}
				}
				employees[number].setPassword(hashFunction(password));
				std::cout << "   изменение прошло успешно\n";
			}
		}
		else {
			
				number = number - 1;
				std::cout << "\tДля редактирования учётных записей администраторов вы должны будете подтвердить их пароли\n";
				number -= employees.size();
				string key;
				std::cout << "\tПодтвердите пароль : ";
				char cInput;
				while ((cInput = _getch()) != '\r' && key.size() < 22)
				{
					if ((int)cInput != 8) {
						key.push_back(cInput);
						_putch('*');
					}
					if ((int)cInput == 8) {
						if (!key.empty()) {
							std::cout << "\b \b";
							key.pop_back();
						}
					}
				}
				long int hash_password = hashFunction(key);

				if (hash_password == admins[number].getPassword()) {
					std::cout << "\tподтверждение прошло успешно\n";
					int choice;
					std::cout << "\tбудете менять :\n   login - 1 ,\n   password - 2 ,\n   всё - 3\n  ничего - 4\n    ваш выбор - ";
					cin >> choice;
					while (cin.fail() || (choice > 4 || choice < 1)) {
						cout << "\t  !!! Вы некорректно ввели значение !!!\n";
						cout << "\t  Исправьтесь - ";
						cin.clear();
						cin.ignore(1000, '\n');
						cin >> choice;
					}
					if (choice == 1) {
						string newlogin;
						getchar();
						std::cout << "    введите новый login: ";
						getline(cin, newlogin);
						while (newlogin.size() < 4 || newlogin.size() > 22) {
							cout << "\t Вы используете слишком много или мало символов (4 - 22)\n\t Исправьтесь - ";
							getline(cin, newlogin);
						}
						if (check_uniqueness(newlogin)) {
							admins[number].setLogin(newlogin);
						}
						else cout << "  Этот логин уже занят !";
					}
					if (choice == 2) {
						string password;
						std::cout << "    введите новый пароль: ";
						char cInput;
						while ((cInput = _getch()) != '\r' && password.size() < 22)
						{
							if ((int)cInput != 8) {
								password.push_back(cInput);
								_putch('*');
							}
							if ((int)cInput == 8) {
								if (!password.empty()) {
									std::cout << "\b \b";
									password.pop_back();
								}
							}
						}
						admins[number].setPassword(hashFunction(password));
						std::cout << "    изменение прошло успешно\n";
					}
					if (choice == 3) {
						string newlogin;
						getchar();
						std::cout << "    введите новый login: ";
						getline(cin, newlogin);
						while (newlogin.size() < 4 || newlogin.size() > 22) {
							cout << "\t Вы используете слишком много сомволов (4 - 22)\n\t Исправьтесь - ";
							getline(cin, newlogin);
						}
						admins[number].setLogin(newlogin);

						string password;
						std::cout << "    введите новый пароль: ";
						char cInput;
						while ((cInput = _getch()) != '\r' && password.size() < 22)
						{
							if ((int)cInput != 8) {
								password.push_back(cInput);
								_putch('*');
							}
							if ((int)cInput == 8) {
								if (!password.empty()) {
									std::cout << "\b \b";
									password.pop_back();
								}
							}
						}
						admins[number].setPassword(hashFunction(password));
						std::cout << "\n   изменение прошло успешно\n";
					}
					if (choice == 4) {

					}
				}
				else {
					std::cout << "    подтверждение прошло неуспешно !!!\n";
				}
			
		}
		ofstream f1;
		f1.open("Users.txt", ios::out);
		f1.clear();
		for (int i = 0; i < employees.size(); i++) {
			employees[i].WriteToFile();
		}
		for (int i = 0; i < admins.size(); i++) {
			admins[i].WriteToFile();
		}
	
}
//удалить аккаун
void Admin::Delete_account()
{
	show_users();
	std::cout << "\n  Для начала подтвердите свой пароль: ";
	string key;
	char cInput;
	while ((cInput = _getch()) != '\r' && key.size()<22)
	{
		if ((int)cInput != 8) {
			key.push_back(cInput);
			_putch('*');
		}
		if ((int)cInput == 8) {
			if (!key.empty()) {
				std::cout << "\b \b";
				key.pop_back();
			}
		}
	}
	long int hash_password = hashFunction(key);
	vector<Admin>admins;
	vector<Employee>employees;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins);
	int flag = 0;
	for (int i = 0; i < admins.size(); i++) {
		if (admins[i].getPassword() == hash_password) {
			flag = 1;
			std::cout << "\n\t Подтверждение прошло успешно\n";
			int number;
			std::cout << "\t Введите номер удаляемой записи - ";
			cin >> number;
			while (cin.fail() || (number > admins.size()+employees.size() || number< 0)) {
				cout << "\t  !!! Вы некорректно ввели значение !!!\n";
				cout << "\t  Исправьтесь - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> number;
			}
			if (number <= employees.size()) {
				number = number - 1;
				employees.erase(employees.begin() + number);
				std::cout << "\t Всё прошло отлично\n";
			}
			else {
				number = number - 1;
				number -= employees.size();
				if (admins[number].getPassword()!=hash_password) {
					std::cout << "\t  Введите пароль администратора, чью запись хотите удалить\n";
					string key1;
					char cInput;
					while ((cInput = _getch()) != '\r' && key1.size()<22)
					{
						if ((int)cInput != 8) {
							key1.push_back(cInput);
							_putch('*');
						}
						if ((int)cInput == 8) {
							if (!key1.empty()) {
								std::cout << "\b \b";
								key1.pop_back();
							}
						}
					}
					long int hash_password1 = hashFunction(key1);
					if (hash_password1 == admins[number].getPassword()) {
						std::cout << "\n\t  доступ к удалению вам предоставлен\n";
						admins.erase(admins.begin() + number);
						std::cout << "\t  Всё прошло отлично\n";
					}
				}
				else {
					std::cout << "\n\t  Нельзя удалять свой аккаунт!!!!\n";
				}
			}
		}
	}
	if (flag == 0) {
		cout << "\t  !!!Подтверждение оказалось неудачным!!!\n";
	}
	ofstream f1;
	f1.open("Users.txt", ios::out);
	f1.clear();
	for (int i = 0; i < employees.size(); i++) {
		employees[i].WriteToFile();
	}
	for (int i = 0; i < admins.size(); i++) {
		admins[i].WriteToFile();
	}

}
void Admin::Delete_note()
{
	if (CountNotes) {
		DisplayChild();
		vector<Child>children;
		vector<Section>sections;
		vector<Notation>notes;
		children.reserve(CountNotes());
		sections.reserve(CountNotes());
		notes.reserve(CountNotes());
		ReadToVectorsData(notes, children, sections);
		int number;
		std::cout << "\t Какую запись вы хотели бы удалить? - ";
		std::cin >> number;
		while (cin.fail() || number<1 || number>notes.size()) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> number;
		}
		number = number - 1;
		notes.erase(notes.begin() + number);
		children.erase(children.begin() + number);
		ofstream f1;
		f1.open("Notation.txt", ios::out);
		f1.clear();

		ofstream f;
		f.open("Children.txt", ios::out);
		f.clear();
		for (int i = 0; i < notes.size(); i++) {
			notes[i].WriteToFile();
		}
		for (int i = 0; i < children.size(); i++) {
			children[i].WriteToFile();
		}
		std::cout << "\t  Всё прошло отлично\n";
	}else cout << "\n      НЕТ ЗАПИСЕЙ";
}
//редактировать ин-фу детского центра (запись)
void Admin::EditData()
{
	if (CountNotes) {
		DisplayChild();
		vector<Child>children;
		vector<Section>sections;
		vector<Notation>notes;
		children.reserve(CountNotes());
		sections.reserve(CountNotes());
		notes.reserve(CountNotes());
		ReadToVectorsData(notes, children, sections);
		int number;
		cout << "\t  Какую запись вы хотели бы отредактировать? - ";
		cin >> number;
		while (cin.fail() || (number > notes.size() || number < 1)) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> number;
		}
		number = number - 1;
		string choice;
		cout << "\t Введите заново необходимую информацию об учащемся\n";
		cout << "\t Необходимо редактировать ФИО ученика? - ";
		cin >> choice;
		if (choice == "да") {
			std::string name_child;
			std::cout << "  Введите новое ФИО - ";
			getchar();
			std::getline(std::cin, name_child);
			children[number].setName_child(name_child);
		}
		std::cout << "  Необходимо редактировать ФИО родителя? - ";
		std::cin >> choice;
		if (choice == "да") {
			string name_parent;
			cout << "  Введите новое ФИО - ";
			getchar();
			getline(cin, name_parent);
			children[number].setName_child(name_parent);
		}
		std::cout << "  Необходимо редактировать дату рождения? - ";
		std::cin >> choice;
		if (choice == "да") {
			string date;
			cout << "  Введите новую дату рождения - ";
			getchar();
			getline(cin, date);
			children[number].setDate(date);
			children[number].convertDate();
		}
		std::cout << "  Необходимо редактировать номер телефона? - ";
		std::cin >> choice;
		if (choice == "да") {
			string phone;
			cout << "  Введите новый номер телефона - ";
			getchar();
			getline(cin, phone);
			children[number].setPhone(phone);
		}
		std::cout << "  Необходимо редактировать посещаемую секцию? - ";
		std::cin >> choice;
		if (choice == "да") {
			bool choice = true;
			while (choice) {
				string entered_name;
				cout << "\n\t\t   **** СЕКЦИИ ****";
				cout << "\n\t Введите название секции, в которую записан ребёнок\n";
				cout << "\t (Лёгкая атлетика, Тяжёлая атлетика, Бокс, Гимнастика, Танцы, Рисование, Шахматы, Вольная борьба)\n\t  Секция - ";
				getchar();
				getline(cin, entered_name);
				string sec_name_from_file, newLine;
				double costs_from_file;
				int id_from_file;
				ifstream f;
				f.open("Section.txt", ios::in);
				while (f >> id_from_file && getline(f, newLine) && getline(f, sec_name_from_file) && f >> costs_from_file) {
					if (sec_name_from_file == entered_name) {
						notes[number].setID_sect(id_from_file);
						while (!notes[number].CheckPayment()) {
							cout << "\t\tИспрaвьтесь - ";
							int payment;
							getchar();
							cin >> payment;
							while (cin.fail()) {
								cout << "\t\t!!! Вы некорректно ввели значение !!!\n";
								cout << "\t\tИсправьтесь - ";
								cin.clear();
								cin.ignore(1000, '\n');
								cin >>payment;
							}
							notes[number].setPayment(payment);
						}
						notes[number].setArrears(costs_from_file -notes[number].getPayment());
						choice = false;
					}
				}
				f.close();
			}
		}
		std::cout << "  Необходимо редактировать внесённую оплату? - ";
		std::cin >> choice;
		if (choice == "да") {
			std::cout << "  Внесите новую плату - ";
			double payment;
			std::cin >> payment;
			while (cin.fail()) {
				cout << "\t  !!! Вы некорректно ввели значение !!!\n";
				cout << "\t  Исправьтесь - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> payment;
			}
			notes[number].setPayment(payment);
			while (!notes[number].CheckPayment()) {
				double pay;
				std::cout << "\t Испрaвьтесь - ";
				std::cin >> pay;
				while (cin.fail()) {
					cout << "\t  !!! Вы некорректно ввели значение !!!\n";
					cout << "\t  Исправьтесь - ";
					cin.clear();
					cin.ignore(1000, '\n');
					cin >> pay;
				}
				notes[number].setPayment(pay);
			}
			notes[number].setArrears(sections[number].getCosts() - notes[number].getPayment());
		}
		ofstream f1;
		f1.open("Notation.txt", ios::out);
		f1.clear();

		ofstream f;
		f.open("Children.txt", ios::out);
		f.clear();
		for (int i = 0; i < notes.size(); i++) {
			notes[i].WriteToFile();
		}
		for (int i = 0; i < children.size(); i++) {
			children[i].WriteToFile();
		}
		std::cout << "\t Всё прошло отлично\n";
	}else cout << "     НЕТ ЗАПИСЕЙ";
}
void Admin::createFirstAdmin()
{
	int choice;
	cout << "\t\t Вы первый пользователь !\n\t\tДавайте запишем вас как администратора?\n\t\t1 - да 0 - нет\n\t\tваш выбор - ";
	cin >> choice;
	while (cin.fail() || (choice > 1 || choice < 0)) {
		cout << "\t  !!! Вы некорректно ввели значение !!!\n";
		cout << "\t  Исправьтесь - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}
	if (choice == 1) {
		Admin obj;
		obj.CreateNew();
		Add(obj);
	}
	cout << "\t\t Теперь вы можете продолжить как зарегестрированный пользователь\n\t\tили создать аккаунт сотрудника при новой регистрации";
}
//функция для работы с инфой детского центра
void Admin::work_with_childrens_centr()
{
	int cycle = 1;
	while (cycle) {
		std::cout << "\n\n      *** Работа с данными детского центра ****\n\t  1 - просмотр\n\t  2 - добавление\n\t  3 - редактирование\n\t  4 - удаление\n\t  5 - индивидуальное задание\n\t  6 - поиск\n\t  7 - сортировка\n\t  0 - вернуться назад\n";
		int choice;
		std::cout << "\t  Ваш выбор - ";
		cin >> choice;
		while (cin.fail() || choice<0 || choice>7) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
		switch (choice) {
		case 1:
			DisplayChild(); 
			break;
		case 2:
			cout << "\n";
			getchar();
			Notation obj;
			obj.Notation_Note();
			obj.WriteToFile();
			break;
		case 3: EditData();
			break;
		case 4: Delete_note();
			break;
		case 5:
			Individual_task();
			break;
		case 6: Find();
			break;
		case 7: Sort();
			break;
		case 0:
			cycle = 0;
			break;
		}
	}
}
//демонстрация аккаунтов пользователей
void Admin::show_users()
{
	string us = "сотрудник", adm = "админ";
	vector<Admin>admins;
	vector<Employee>employees;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins); 
	int j = 1;
	std::cout << "\n             ***** ПОЛЬЗОВАТЕЛИ *****\n\n";
	if(employees.size())cout << "                Логин              Роль   Доступ\n";
	std::cout << "------------------------------------------------\n";
	for (int i = 0; i < employees.size(); i++) {
			std::cout <<"|" <<setw(5)<< j << "|" << setw(20) << employees[i].getLogin() << "|" << setw(14) << us << "|";
			if (employees[i].getAccess() == 1) cout <<setw(4)<< "+" << "|\n";
			if (employees[i].getAccess() == 0) cout << setw(4) << "-" << "|\n";
			std::cout << "------------------------------------------------\n";
			j++;
	}
	for( int i=0; i<admins.size(); i++){
			std::cout <<"|"<<setw(5) << j << "|" << setw(20) << admins[i].getLogin() << "|" << setw(14) << adm << "|\n";
			j++;
		    std::cout << "------------------------------------------------\n";
	}
}
//предоставление доступа пользователю
void Admin::grant_access(Employee& obj)
{
	int flag = 0;
	vector<Employee>employees;
	vector<Admin> admins;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins);
	for (int i = 0; i < employees.size(); i++) {
		if (employees[i].getLogin() == obj.getLogin() && employees[i].getAccess()==0) {
			employees[i].setAccess(1);
			ofstream f1;
			f1.open("Users.txt", ios::out);
			f1.clear();
			for (int i = 0; i < employees.size(); i++) {
				employees[i].WriteToFile();
			}
			for (int i = 0; i < admins.size(); i++) {
				admins[i].WriteToFile(); 
			}
			std::cout << "\t Всё прошло отлично\n";
			flag = 1;
		}
	}
	if (flag == 0) {
		std::cout << "\t Операция не была произведена\n";
		std::cout << "\t Что-то пошло не так (или не существует такого пользователя, или у него уже был доступ, или вы пытались предоставить доступ администратору)\n";
	}
}
//добавление сотрудника
void Admin::Add(Employee &obj)
{
	vector<Employee>employees;
	vector<Admin> admins;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins);
	employees.push_back(obj);
	ofstream f1;
	f1.open("Users.txt", ios::out);
	f1.clear();
	for (int i = 0; i < employees.size(); i++) {
		employees[i].WriteToFile();
	}
	for (int i = 0; i < admins.size(); i++) {
		admins[i].WriteToFile();
	}
}
//добавление администратора
void Admin::Add(Admin &obj)
{
	vector<Employee>employees;
	vector<Admin> admins;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins);
	admins.push_back(obj);
	ofstream f1;
	f1.open("Users.txt", ios::out);
	f1.clear();
	for (int i = 0; i < employees.size(); i++) {
		employees[i].WriteToFile();
	}
	for (int i = 0; i < admins.size(); i++) {
		admins[i].WriteToFile();
	}
}
void Admin::Add_account()
{
	int choice1;
	std::cout << "\t Кого хотите добавить :\n     пользователь - 1 ,\n     админ - 2,\n     никого - 3\n     ваш выбор - ";
	cin >> choice1;
	while (cin.fail() || (choice1 > 3 || choice1 < 1)) {
		cout << "\t  !!! Вы некорректно ввели значение !!!\n";
		cout << "\t  Исправьтесь - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice1;
	}
	if (choice1 == 1) {
		Employee obj;
		obj.CreateNew();
		if (check_uniqueness(obj.getLogin())) {
			obj.setAccess(1);
			Add(obj);
		}
		else cout << "\t  Этот логин занят\t  В добавлении отказано";
	}
	if (choice1 == 2) {
		Admin obj;
		obj.CreateNew();
		if (check_uniqueness(obj.getLogin())) {
			Add(obj);
		}
		else cout << "\t  Этот логин занят\t  В добавлении отказано";
	}
}
//регистрация
void Employee::Register() {
	string login, password;
	long int hash_password;
	std::cout << "\n\t*****~~~~~~~~~~~~~~~~~~~~~~~*****" << endl;
	std::cout << "\t  Введите логин: ";
	getchar();
	getline(cin, login);
	while (login.size() < 4 || this->login.size() > 22) {
		cout << "\t Вы используете слишком много или мало символов (4 - 22)\n\t Исправьтесь - ";
		getline(cin, login);
	}
	std::cout << "\t  Ваш пароль : ";
	char cInput;
	while ((cInput = _getch()) != '\r' && password.size()<22)
	{
		if ((int)cInput != 8) {
			password.push_back(cInput);
			_putch('*');
		}
		if ((int)cInput == 8) {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.pop_back();
			}
		}
	}
	std::cout << "\n\t*****~~~~~~~~~~~~~~~~~~~~~~~*****\n" << endl;
	hash_password = hashFunction(password);
	this->access = 0;
	this->role = 0;
	this->login = login;
	this->hash_password = hash_password;
	if (check_uniqueness(this->login)) {
		WriteToFile();
		std::cout << "\n   Вы зарегистрированы, но Вам необходимо дождаться предоставления доступа от администратора\n";
	}
	else cout << "\n   К сожалению, этот логин уже занят\n Вам надо попытаться снова";
}
//меню пользователя
void Employee::provide_menu() {
	int cycle = 1;
	while (cycle) {
		std::cout << "\n      ***МЕНЮ СОТРУДНИКА***\n    1 - просмотр\n    2 - индивидуальное задание\n    3 - поиск\n    4 - сортировка\n    0 - вернуться назад\n";
		int choice;
		std::cout << "    Ваш выбор - ";
		cin >> choice;
		while (cin.fail() || choice < 0 || choice>4) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
		switch (choice) {
		case 1:
			DisplayChild();
			break;
		case 2:
			Individual_task();
			break;
		case 3: Find();
			break;
		case 4: Sort();
			break;
		case 0:
			cycle = 0;
			break;
		}
	}
}
//меню админа
void Admin::provide_menu() {
	int choice, cycle=1;
	while (cycle) {
		std::cout << "\n       ***МЕНЮ АДМИНИСТРАТОРА***\n";
		std::cout << "    1 - работа с учётными записями пользователей\n    2 - работа с данными детского центра\n    0 - вернуться назад\n    Ваш выбор - ";
		cin >> choice;
		switch (choice) {
		case 0: cycle = 0;
			break;
		case 1: work_with_user_accounts();
			break;
		case 2: work_with_childrens_centr();
			break;
		
		}
	}
}
// поиск
void User::Find() {
	if (CountNotes) {
		cout << "\t По какому полю будет идти поиск ?\n   1 - По фамилии \n   2 - По возрасту \n   3 - По секции \n   Ваш выбор - ";
		int choice;
		cin >> choice;
		while (cin.fail() || choice < 1 || choice>3) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
		if (choice == 1) {
			int flag = 0;
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			cout << "     *** Поиск по фамилии ***\n";
			cout << "   Введите фамилию (в И. п.) - ";
			string surname;
			cin >> surname;
			while (!check_str(surname)) {
				cout << "\t Некорректно введено, исправьтесь - ";
				cin >> surname;
			}
			for (int i = 0; i < children.size(); i++) {
				if (children[i].getNameChild().substr(0, surname.size()) == surname) {
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
						<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
						<< children[i].getNameChild() << "|" << setw(35) << children[i].getNameParent() << "|"
						<< setw(13) << children[i].getDate() << "|" << setw(10) << children[i].returnAge() << "|" << setw(13) << children[i].getPhone();
					std::cout << "|" << setw(16) << sections[i].getName() << "|" << setw(9) << sections[i].getCosts() << "|"
						<< setw(8) << notes[i].getPayment() << "|" << setw(6) << notes[i].getArrears() << "||" << endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					flag = 1;

				}
			}
			if (flag == 0) {
				cout << "   Никого с такой фамилией найдено не было\n";
			}
		}
		if (choice == 2) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			cout << "     *** Поиск по возрастной категории ***\n";
			cout << "\t Введите возраст - ";
			int age;
			cin >> age;
			int flag = 0;
			while (cin.fail() || age < 4 || age>18) {
				cout << "\t  !!! Вы некорректно ввели значение !!!\n";
				cout << "\t  Исправьтесь - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> age;
			}
			for (int i = 0; i < children.size(); i++) {
				if (children[i].getAge() == age) {
					flag = 1;
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
						<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
						<< children[i].getNameChild() << "|" << setw(35) << children[i].getNameParent() << "|"
						<< setw(13) << children[i].getDate() << "|" << setw(10) << children[i].returnAge() << "|" << setw(13) << children[i].getPhone();
					std::cout << "|" << setw(16) << sections[i].getName() << "|" << setw(9) << sections[i].getCosts() << "|"
						<< setw(8) << notes[i].getPayment() << "|" << setw(6) << notes[i].getArrears() << "||" << endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

				}
			}
			if (flag == 0) {
				cout << "   Никого с таким возрастом найдено не было\n";
			}
		}
		if (choice == 3) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			string entered_name;
			int search_id = 0, num_sec = 0;
			cout << "     *** Поиск по секциям ***\n";
			cout << "\t Введите название секции, в которую записан ребёнок\n";
			cout << "\t (Лёгкая атлетика, Тяжёлая атлетика, Бокс, Гимнастика, Танцы, Рисование, Шахматы, Вольная борьба)\n  Секция - ";
			getchar();
			getline(cin, entered_name);
			while (!check_str(entered_name)) {
				cout << "\t  Цифры неприемлемы в названии ! Введите заново  - ";
				getline(cin, entered_name);
			}
			for (int i = 0; i < sections.size(); i++) {
				if (entered_name == sections[i].getName()) {
					search_id = sections[i].getID();
				}
			}
			if (search_id == 0) {
				cout << "\t Вы ввели  несуществующую секцию";
			}
			else {
				for (int i = 0; i < sections.size(); i++) {
					if (search_id == sections[i].getID()) {
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
							<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
							<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
							<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
							<< children[i].getNameChild() << "|" << setw(35) << children[i].getNameParent() << "|"
							<< setw(13) << children[i].getDate() << "|" << setw(10) << children[i].returnAge() << "|" << setw(13) << children[i].getPhone();
						std::cout << "|" << setw(16) << sections[i].getName() << "|" << setw(9) << sections[i].getCosts() << "|"
							<< setw(8) << notes[i].getPayment() << "|" << setw(6) << notes[i].getArrears() << "||" << endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
							<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

					}
				}
			}
		}
	}else cout << "     НЕТ ЗАПИСЕЙ";
}
// сортирвка
void User::Sort()
{
	if (CountNotes) {
		int choice;
		cout << "\t ** Меню сортировки **\n   1 - по алфавиту\n   2 - по возрасту\n   3 - по секциям\n   ваш выбор - ";
		cin >> choice;
		while (cin.fail() || choice < 1 || choice>3) {
			cout << "\t  !!! Вы некорректно ввели значение !!!\n";
			cout << "\t  Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> choice;
		}
		if (choice == 1) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			sortBySurname(children);
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
				<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			for (int i = 0; i < children.size(); i++) {
				for (int k = 0; k < notes.size(); k++) {
					if (children[i].getID() == notes[k].getID_child()) {
						std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
							<< children[i].getNameChild() << "|" << setw(35) << children[i].getNameParent() << "|"
							<< setw(13) << children[i].getDate() << "|" << setw(10) << children[i].returnAge() << "|" << setw(13) << children[i].getPhone();
						for (int b = 0; b < sections.size(); b++) {
							if (notes[k].getID_section() == sections[b].getID() && children[i].getID() == notes[k].getID_child()) {

								std::cout << "|" << setw(16) << sections[b].getName() << "|" << setw(9) << sections[b].getCosts() << "|"
									<< setw(8) << notes[k].getPayment() << "|" << setw(6) << notes[k].getArrears() << "||" << endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
									<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								break;
							}
						}
					}

				}

			}

		}
		if (choice == 2) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			sortByAge_decrease(children);
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
				<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			for (int i = 0; i < children.size(); i++) {
				for (int k = 0; k < notes.size(); k++) {
					if (children[i].getID() == notes[k].getID_child()) {

						std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
							<< children[i].getNameChild() << "|" << setw(35) << children[i].getNameParent() << "|"
							<< setw(13) << children[i].getDate() << "|" << setw(10) << children[i].returnAge() << "|" << setw(13) << children[i].getPhone();
						for (int b = 0; b < sections.size(); b++) {
							if (notes[k].getID_section() == sections[b].getID() && children[i].getID() == notes[k].getID_child()) {

								std::cout << "|" << setw(16) << sections[b].getName() << "|" << setw(9) << sections[b].getCosts() << "|"
									<< setw(8) << notes[k].getPayment() << "|" << setw(6) << notes[k].getArrears() << "||" << endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
									<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								break;
							}
						}
					}

				}

			}

		}
		if (choice == 3) {
			vector<Child>children;
			vector<Section>sections;
			vector<Notation>notes;
			children.reserve(CountNotes());
			sections.reserve(CountNotes());
			notes.reserve(CountNotes());
			ReadToVectorsData(notes, children, sections);
			sortBySection(notes);
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			std::cout << "|| № |         ФИО РЕБЁНКА               |             ФИО РОДИТЕЛЯ          |ДАТА РОЖДЕНИЯ|  ВОЗРАСТ |     ТЕЛЕФОН     |     СЕКЦИЯ    "
				<< " |СТОИМОСТЬ| ОПЛАТА | ДОЛГ || \n";
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
				<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			for (int i = 0; i < notes.size(); i++) {
				for (int k = 0; k < children.size(); k++) {
					if (children[k].getID() == notes[i].getID_child()) {

						std::cout << "||" << setw(3) << i + 1 << "|" << setw(35)
							<< children[k].getNameChild() << "|" << setw(35) << children[k].getNameParent() << "|"
							<< setw(13) << children[k].getDate() << "|" << setw(10) << children[k].returnAge() << "|" << setw(13) << children[k].getPhone();
						for (int b = 0; b < sections.size(); b++) {
							if (notes[i].getID_section() == sections[b].getID() && children[k].getID() == notes[i].getID_child()) {

								std::cout << "|" << setw(16) << sections[b].getName() << "|" << setw(9) << sections[b].getCosts() << "|"
									<< setw(8) << notes[i].getPayment() << "|" << setw(6) << notes[i].getArrears() << "||" << endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
									<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								break;
							}
						}
					}

				}

			}
		}
	}else cout << "     НЕТ ЗАПИСЕЙ";

}
int User::getAccess()
{
	return this->access;
}

