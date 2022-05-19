#include "User.h"
#include"Notation.h"
#include"Section.h"
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<iostream>
#include<algorithm>
//���������� �������
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
//���������� �������������
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
// �����������
long int hashFunction(string key) {
	long int hashCode = 0;
	for (int i = 0; i < key.length(); i++) {
		hashCode += key[i] * pow(PRIME_CONST, i);
	}
	return hashCode;
}
// ��������� ���������� � ������ � ������� : ����, ������, ������
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
//��������� ������� ������� � �����������
void Admin::ReadToUsers(vector<Employee>&employees, vector<Admin>&admins) {
	string login, line, adm = "�����", us = "������������";
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
//�������� �����
void User::setLogin(string u)
{
	this->login = u;
}
//�������� ����
void User::setRole(int role)
{
	this->role = role;
}
//������ ������� �������
void User::setAccess(int access)
{
	this->access = access;
}
//������ ������
void User::setPassword(long int k)
{
	this->hash_password = k;
}
//���������� �����
string User::getLogin()
{
	return this->login;
}
//���������� ������
long int User::getPassword()
{
	return this->hash_password;
}
//�������� �����������
bool mySortBySurname(Child child_a, Child child_b);
//���������� �� ��������
void sortBySurname(vector <Child>& children) // ����������
{
	sort(children.begin(), children.end(), mySortBySurname);
}
//�������� �����������
bool mySortByAge(Child child_a, Child child_b);
//���������� �� ��������
void sortByAge(vector <Child>& children) // ����������
{
	sort(children.begin(), children.end(), mySortByAge);
}
//���������� ���������� �� ��������
bool mySortBySurname(Child child_a, Child child_b) // �������-����������
{
	return child_a.getNameChild() < child_b.getNameChild(); // �� ��������
}
//���������� ���������� �� �������� (����������)
bool mySortByAge(Child child_a, Child child_b) // �������-����������
{
	return child_a.getAge() < child_b.getAge(); // �� ���������� ��������
}
//�������� �����������
bool mySortByArrears(Notation note_a, Notation note_b);
//���������� �� �������� �����
void sortByArrears(vector <Notation>& notes) // ����������
{
	sort(notes.begin(), notes.end(), mySortByArrears);
}
//���������� ���������� �� �������� �����
bool mySortByArrears(Notation note_a, Notation note_b) // �������-����������
{
	return note_a.getArrears() > note_b.getArrears(); // �� �������� �����
}
//�������� �����������
bool mySortByAge_decrease(Child child_a, Child child_b);
//���������� �� �������� (�� ����������)
void sortByAge_decrease(vector <Child>& children) // ����������
{
	sort(children.begin(), children.end(), mySortByAge_decrease);
}
//���������� ���������� �� �������� (�� ����������)
bool mySortByAge_decrease(Child child_a, Child child_b) {
	return child_a.getAge() > child_b.getAge();
}
//�������� �������-�����������
bool mySortBySection(Notation a, Notation b);
//��������� �� �������
void sortBySection(vector <Notation>& notes) // ����������
{
	sort(notes.begin(), notes.end(), mySortBySection);
}
//���������� ���������� �� �������
bool mySortBySection(Notation a, Notation b) {
	return a.getID_section()<b.getID_section();
}
//������� - �������������� �������
void User::Individual_task()
{
	if (CountNotes) {
		cout << "\n\n          �������������� �������\n";
		cout << "\t 1 - ������� ��������� � ������� �������� �����\n\t 2 - ������� ���������� � ������� ���������� �������� �����\n\t  ��� ����� - ";
		int choice;
		cin >> choice;
		while (cin.fail() || (choice > 2 || choice < 1)) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
			std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
				<< " |���������| ������ | ���� || \n";
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
			std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
				<< " |���������| ������ | ���� || \n";
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
	}else cout << "     ��� �������";
}
//���������� ���������� � �����
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
		std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
			<< " |���������| ������ | ���� || \n";
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
	else cout << "     ��� �������";
}
//������ � ���� ��������
void User::WriteToFile() {
	ofstream out;          // ����� ��� ������
	out.open("Users.txt", ios::app); // �������� ���� ��� ������
	if (out.is_open())
	{
		out <<this->login<<endl;
		out << this->hash_password << endl;
		out << this->role << endl;
		out << this->access << endl;
	}
	out.close();
}
// �����������
int User:: autorisation(){
	string login, password;
	long int hash_password;
	std::cout << "\n\t*****~~~~~~~~~~~~~~~~~~~~~~~*****" << endl;
	std::cout << "\t  ������� �����: ";
	getchar();
	getline(cin, login);
	while (login.size() < 4 || login.size() > 22) {
		cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
		getline(cin,login);
	}
	std::cout << "\t  ��� ������ : ";
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
			std::cout << "\t|| ����������� ������ ������� ||\n\t|| �� ����� ��� ������������� || \n";
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			return 1;
		}
		if (hash_password == file_pass && login == file_log && role == 0 && access == 1) {
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			std::cout << "\t|| ����������� ������ ������� ||\n\t|| �� ����� ��� ���������    ||\n";
			cout << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			return 2;
		}
		if (hash_password == file_pass && login == file_log && role == 0 && access == 0) {
			std::cout << " ----#### ����������� ������ �������, �� ��� �� ������������ ������ ###----\n";
			return 0;
		}
	}
	f.close();
	return -1;
}
//�������� ������ �������� ����������
void Employee::CreateNew() {
	cout << "\n  *** ���������� ������� ������ ��������***\n";
	std::cout << "\t ������� ����� - ";
	getchar();
	getline( cin,this->login);
	while (this->login.size() < 4 || this->login.size() > 22) {
		cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
		getline(cin, this->login);
	}
	std::cout << "\t ������� ������ - ";
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
// �������� ������ �������� ������
void Admin::CreateNew() {
	cout << "\n  *** ���������� ������� ������ ��������***\n";
	std::cout << "\t ������� ����� - ";
	getchar();
	getline(cin, this->login);
	while (this->login.size() < 4 || this->login.size() > 22) {
		cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
		getline(cin, this->login);
	}
	std::cout << "\t ������� ������ - ";
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
//������� ��� ������ � ��������� �������������
void Admin::work_with_user_accounts()
{
	int cycle = 1;
	int choice;
	while (cycle) {
		cout << "\n-----------------------------------------------------------";
		std::cout << "\n    ������ � �������� �������� �������������\n";
		std::cout << "\t 1 - ��������\n\t 2 - ����������\n\t 3 - ��������������\n\t 4 - ��������\n\t 5 - �������������� �������\n\t 0 - �e������� �����\n\t ��� ����� - ";
		cin >> choice;
		while (cin.fail() || (choice > 5 || choice < 0)) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
			else cout << "   �������� ���������� - ���������������� ������ ��!";
			break;
		case 5: if (CountUsers() != 1) {
			show_users();
			string login;
			Employee obj;
			std::cout << "\t ������� ����� ������������: ";
			getchar();
			getline(cin, login);
			while (login.size() < 4 || login.size() > 22) {
				cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
				getline(cin, login);
			}
			obj.setLogin(login);
			grant_access(obj);
		} else cout << "   �������������� ������� ���������� - ���������������� ������ ��!";
		}
	}
}
//������������� �������
void Admin::Edit_Account() {

	show_users();
	vector<Admin>admins;
	vector<Employee>employees;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins);
	int number;
	std::cout << "\n\t������� ����� ������������� ������ - ";
	std::cin >> number;
	while (cin.fail() || (number > employees.size()+admins.size() || number <= 0)) {
		std::cout << "\t  !!! �� ����������� ����� �������� !!!\n";
		std::cout << "\t  ����������� - ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> number;
	}
		if (number <= employees.size()) {
			number = number - 1;
			int choice;
			std::cout << "\t������ ������ :\n   login - 1 ,\n   password - 2 ,\n   �� - 3\n   ������ - 4\n  ��� ����� - ";
			std::cin >> choice;
			while (cin.fail() || (choice > 4 || choice < 0)) {
				std::cout << "\t  !!! �� ����������� ����� �������� !!!\n";
				std::cout << "\t  ����������� - ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cin >> choice;
			}
			if (choice == 1) {
				string newlogin;
				std::cout << "   ������� ����� login: ";
				getchar();
				getline(cin, newlogin);
				while (newlogin.size() < 4 || newlogin.size() > 22) {
					cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
					getline(cin, newlogin);
				}
				employees[number].setLogin(newlogin);
				std::cout << "   ��������� ������ �������\n";
			}
			if (choice == 2) {
				string password;
				std::cout << "   ������� ����� ������: ";
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
				std::cout << "   ��������� ������ �������\n";
			}
			if (choice == 3) {
				string newlogin;
				std::cout << "   ������� ����� login: ";
				getchar();
				getline(cin, newlogin);
				while (newlogin.size() < 4 || newlogin.size() > 22) {
					cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
					getline(cin, newlogin);
				}
				employees[number].setLogin(newlogin);
				string password;
				std::cout << "   ������� ����� ������: ";
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
				std::cout << "   ��������� ������ �������\n";
			}
		}
		else {
			
				number = number - 1;
				std::cout << "\t��� �������������� ������� ������� ��������������� �� ������ ������ ����������� �� ������\n";
				number -= employees.size();
				string key;
				std::cout << "\t����������� ������ : ";
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
					std::cout << "\t������������� ������ �������\n";
					int choice;
					std::cout << "\t������ ������ :\n   login - 1 ,\n   password - 2 ,\n   �� - 3\n  ������ - 4\n    ��� ����� - ";
					cin >> choice;
					while (cin.fail() || (choice > 4 || choice < 1)) {
						cout << "\t  !!! �� ����������� ����� �������� !!!\n";
						cout << "\t  ����������� - ";
						cin.clear();
						cin.ignore(1000, '\n');
						cin >> choice;
					}
					if (choice == 1) {
						string newlogin;
						getchar();
						std::cout << "    ������� ����� login: ";
						getline(cin, newlogin);
						while (newlogin.size() < 4 || newlogin.size() > 22) {
							cout << "\t �� ����������� ������� ����� ��� ���� �������� (4 - 22)\n\t ����������� - ";
							getline(cin, newlogin);
						}
						if (check_uniqueness(newlogin)) {
							admins[number].setLogin(newlogin);
						}
						else cout << "  ���� ����� ��� ����� !";
					}
					if (choice == 2) {
						string password;
						std::cout << "    ������� ����� ������: ";
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
						std::cout << "    ��������� ������ �������\n";
					}
					if (choice == 3) {
						string newlogin;
						getchar();
						std::cout << "    ������� ����� login: ";
						getline(cin, newlogin);
						while (newlogin.size() < 4 || newlogin.size() > 22) {
							cout << "\t �� ����������� ������� ����� �������� (4 - 22)\n\t ����������� - ";
							getline(cin, newlogin);
						}
						admins[number].setLogin(newlogin);

						string password;
						std::cout << "    ������� ����� ������: ";
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
						std::cout << "\n   ��������� ������ �������\n";
					}
					if (choice == 4) {

					}
				}
				else {
					std::cout << "    ������������� ������ ��������� !!!\n";
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
//������� ������
void Admin::Delete_account()
{
	show_users();
	std::cout << "\n  ��� ������ ����������� ���� ������: ";
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
			std::cout << "\n\t ������������� ������ �������\n";
			int number;
			std::cout << "\t ������� ����� ��������� ������ - ";
			cin >> number;
			while (cin.fail() || (number > admins.size()+employees.size() || number< 0)) {
				cout << "\t  !!! �� ����������� ����� �������� !!!\n";
				cout << "\t  ����������� - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> number;
			}
			if (number <= employees.size()) {
				number = number - 1;
				employees.erase(employees.begin() + number);
				std::cout << "\t �� ������ �������\n";
			}
			else {
				number = number - 1;
				number -= employees.size();
				if (admins[number].getPassword()!=hash_password) {
					std::cout << "\t  ������� ������ ��������������, ��� ������ ������ �������\n";
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
						std::cout << "\n\t  ������ � �������� ��� ������������\n";
						admins.erase(admins.begin() + number);
						std::cout << "\t  �� ������ �������\n";
					}
				}
				else {
					std::cout << "\n\t  ������ ������� ���� �������!!!!\n";
				}
			}
		}
	}
	if (flag == 0) {
		cout << "\t  !!!������������� ��������� ���������!!!\n";
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
		std::cout << "\t ����� ������ �� ������ �� �������? - ";
		std::cin >> number;
		while (cin.fail() || number<1 || number>notes.size()) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
		std::cout << "\t  �� ������ �������\n";
	}else cout << "\n      ��� �������";
}
//������������� ��-�� �������� ������ (������)
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
		cout << "\t  ����� ������ �� ������ �� ���������������? - ";
		cin >> number;
		while (cin.fail() || (number > notes.size() || number < 1)) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> number;
		}
		number = number - 1;
		string choice;
		cout << "\t ������� ������ ����������� ���������� �� ��������\n";
		cout << "\t ���������� ������������� ��� �������? - ";
		cin >> choice;
		if (choice == "��") {
			std::string name_child;
			std::cout << "  ������� ����� ��� - ";
			getchar();
			std::getline(std::cin, name_child);
			children[number].setName_child(name_child);
		}
		std::cout << "  ���������� ������������� ��� ��������? - ";
		std::cin >> choice;
		if (choice == "��") {
			string name_parent;
			cout << "  ������� ����� ��� - ";
			getchar();
			getline(cin, name_parent);
			children[number].setName_child(name_parent);
		}
		std::cout << "  ���������� ������������� ���� ��������? - ";
		std::cin >> choice;
		if (choice == "��") {
			string date;
			cout << "  ������� ����� ���� �������� - ";
			getchar();
			getline(cin, date);
			children[number].setDate(date);
			children[number].convertDate();
		}
		std::cout << "  ���������� ������������� ����� ��������? - ";
		std::cin >> choice;
		if (choice == "��") {
			string phone;
			cout << "  ������� ����� ����� �������� - ";
			getchar();
			getline(cin, phone);
			children[number].setPhone(phone);
		}
		std::cout << "  ���������� ������������� ���������� ������? - ";
		std::cin >> choice;
		if (choice == "��") {
			bool choice = true;
			while (choice) {
				string entered_name;
				cout << "\n\t\t   **** ������ ****";
				cout << "\n\t ������� �������� ������, � ������� ������� ������\n";
				cout << "\t (˸���� ��������, ������ ��������, ����, ����������, �����, ���������, �������, ������� ������)\n\t  ������ - ";
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
							cout << "\t\t����a������ - ";
							int payment;
							getchar();
							cin >> payment;
							while (cin.fail()) {
								cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
								cout << "\t\t����������� - ";
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
		std::cout << "  ���������� ������������� �������� ������? - ";
		std::cin >> choice;
		if (choice == "��") {
			std::cout << "  ������� ����� ����� - ";
			double payment;
			std::cin >> payment;
			while (cin.fail()) {
				cout << "\t  !!! �� ����������� ����� �������� !!!\n";
				cout << "\t  ����������� - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> payment;
			}
			notes[number].setPayment(payment);
			while (!notes[number].CheckPayment()) {
				double pay;
				std::cout << "\t ����a������ - ";
				std::cin >> pay;
				while (cin.fail()) {
					cout << "\t  !!! �� ����������� ����� �������� !!!\n";
					cout << "\t  ����������� - ";
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
		std::cout << "\t �� ������ �������\n";
	}else cout << "     ��� �������";
}
void Admin::createFirstAdmin()
{
	int choice;
	cout << "\t\t �� ������ ������������ !\n\t\t������� ������� ��� ��� ��������������?\n\t\t1 - �� 0 - ���\n\t\t��� ����� - ";
	cin >> choice;
	while (cin.fail() || (choice > 1 || choice < 0)) {
		cout << "\t  !!! �� ����������� ����� �������� !!!\n";
		cout << "\t  ����������� - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}
	if (choice == 1) {
		Admin obj;
		obj.CreateNew();
		Add(obj);
	}
	cout << "\t\t ������ �� ������ ���������� ��� ������������������ ������������\n\t\t��� ������� ������� ���������� ��� ����� �����������";
}
//������� ��� ������ � ����� �������� ������
void Admin::work_with_childrens_centr()
{
	int cycle = 1;
	while (cycle) {
		std::cout << "\n\n      *** ������ � ������� �������� ������ ****\n\t  1 - ��������\n\t  2 - ����������\n\t  3 - ��������������\n\t  4 - ��������\n\t  5 - �������������� �������\n\t  6 - �����\n\t  7 - ����������\n\t  0 - ��������� �����\n";
		int choice;
		std::cout << "\t  ��� ����� - ";
		cin >> choice;
		while (cin.fail() || choice<0 || choice>7) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
//������������ ��������� �������������
void Admin::show_users()
{
	string us = "���������", adm = "�����";
	vector<Admin>admins;
	vector<Employee>employees;
	employees.reserve(CountUsers());
	admins.reserve(CountUsers());
	ReadToUsers(employees, admins); 
	int j = 1;
	std::cout << "\n             ***** ������������ *****\n\n";
	if(employees.size())cout << "                �����              ����   ������\n";
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
//�������������� ������� ������������
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
			std::cout << "\t �� ������ �������\n";
			flag = 1;
		}
	}
	if (flag == 0) {
		std::cout << "\t �������� �� ���� �����������\n";
		std::cout << "\t ���-�� ����� �� ��� (��� �� ���������� ������ ������������, ��� � ���� ��� ��� ������, ��� �� �������� ������������ ������ ��������������)\n";
	}
}
//���������� ����������
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
//���������� ��������������
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
	std::cout << "\t ���� ������ �������� :\n     ������������ - 1 ,\n     ����� - 2,\n     ������ - 3\n     ��� ����� - ";
	cin >> choice1;
	while (cin.fail() || (choice1 > 3 || choice1 < 1)) {
		cout << "\t  !!! �� ����������� ����� �������� !!!\n";
		cout << "\t  ����������� - ";
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
		else cout << "\t  ���� ����� �����\t  � ���������� ��������";
	}
	if (choice1 == 2) {
		Admin obj;
		obj.CreateNew();
		if (check_uniqueness(obj.getLogin())) {
			Add(obj);
		}
		else cout << "\t  ���� ����� �����\t  � ���������� ��������";
	}
}
//�����������
void Employee::Register() {
	string login, password;
	long int hash_password;
	std::cout << "\n\t*****~~~~~~~~~~~~~~~~~~~~~~~*****" << endl;
	std::cout << "\t  ������� �����: ";
	getchar();
	getline(cin, login);
	while (login.size() < 4 || this->login.size() > 22) {
		cout << "\t �� ����������� ������� ����� ��� ���� �������� (4 - 22)\n\t ����������� - ";
		getline(cin, login);
	}
	std::cout << "\t  ��� ������ : ";
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
		std::cout << "\n   �� ����������������, �� ��� ���������� ��������� �������������� ������� �� ��������������\n";
	}
	else cout << "\n   � ���������, ���� ����� ��� �����\n ��� ���� ���������� �����";
}
//���� ������������
void Employee::provide_menu() {
	int cycle = 1;
	while (cycle) {
		std::cout << "\n      ***���� ����������***\n    1 - ��������\n    2 - �������������� �������\n    3 - �����\n    4 - ����������\n    0 - ��������� �����\n";
		int choice;
		std::cout << "    ��� ����� - ";
		cin >> choice;
		while (cin.fail() || choice < 0 || choice>4) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
//���� ������
void Admin::provide_menu() {
	int choice, cycle=1;
	while (cycle) {
		std::cout << "\n       ***���� ��������������***\n";
		std::cout << "    1 - ������ � �������� �������� �������������\n    2 - ������ � ������� �������� ������\n    0 - ��������� �����\n    ��� ����� - ";
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
// �����
void User::Find() {
	if (CountNotes) {
		cout << "\t �� ������ ���� ����� ���� ����� ?\n   1 - �� ������� \n   2 - �� �������� \n   3 - �� ������ \n   ��� ����� - ";
		int choice;
		cin >> choice;
		while (cin.fail() || choice < 1 || choice>3) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
			cout << "     *** ����� �� ������� ***\n";
			cout << "   ������� ������� (� �. �.) - ";
			string surname;
			cin >> surname;
			while (!check_str(surname)) {
				cout << "\t ����������� �������, ����������� - ";
				cin >> surname;
			}
			for (int i = 0; i < children.size(); i++) {
				if (children[i].getNameChild().substr(0, surname.size()) == surname) {
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
						<< " |���������| ������ | ���� || \n";
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
				cout << "   ������ � ����� �������� ������� �� ����\n";
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
			cout << "     *** ����� �� ���������� ��������� ***\n";
			cout << "\t ������� ������� - ";
			int age;
			cin >> age;
			int flag = 0;
			while (cin.fail() || age < 4 || age>18) {
				cout << "\t  !!! �� ����������� ����� �������� !!!\n";
				cout << "\t  ����������� - ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> age;
			}
			for (int i = 0; i < children.size(); i++) {
				if (children[i].getAge() == age) {
					flag = 1;
					std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
						<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
						<< " |���������| ������ | ���� || \n";
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
				cout << "   ������ � ����� ��������� ������� �� ����\n";
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
			cout << "     *** ����� �� ������� ***\n";
			cout << "\t ������� �������� ������, � ������� ������� ������\n";
			cout << "\t (˸���� ��������, ������ ��������, ����, ����������, �����, ���������, �������, ������� ������)\n  ������ - ";
			getchar();
			getline(cin, entered_name);
			while (!check_str(entered_name)) {
				cout << "\t  ����� ����������� � �������� ! ������� ������  - ";
				getline(cin, entered_name);
			}
			for (int i = 0; i < sections.size(); i++) {
				if (entered_name == sections[i].getName()) {
					search_id = sections[i].getID();
				}
			}
			if (search_id == 0) {
				cout << "\t �� �����  �������������� ������";
			}
			else {
				for (int i = 0; i < sections.size(); i++) {
					if (search_id == sections[i].getID()) {
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
							<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
							<< " |���������| ������ | ���� || \n";
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
	}else cout << "     ��� �������";
}
// ���������
void User::Sort()
{
	if (CountNotes) {
		int choice;
		cout << "\t ** ���� ���������� **\n   1 - �� ��������\n   2 - �� ��������\n   3 - �� �������\n   ��� ����� - ";
		cin >> choice;
		while (cin.fail() || choice < 1 || choice>3) {
			cout << "\t  !!! �� ����������� ����� �������� !!!\n";
			cout << "\t  ����������� - ";
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
			std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
				<< " |���������| ������ | ���� || \n";
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
			std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
				<< " |���������| ������ | ���� || \n";
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
			std::cout << "|| � |         ��� �������               |             ��� ��������          |���� ��������|  ������� |     �������     |     ������    "
				<< " |���������| ������ | ���� || \n";
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
	}else cout << "     ��� �������";

}
int User::getAccess()
{
	return this->access;
}

