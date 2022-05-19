#include"Child.h"
#include"Section.h"
#include<fstream>
//��������� ������� �����
bool Notation:: CheckPayment()
{
	
	string sec_name_from_file, newLine;
	double costs_from_file, price=0;
	int id_from_file;
	ifstream f;
	f.open("Section.txt", ios::in);
	while (f >> id_from_file && getline(f, newLine) && getline(f, sec_name_from_file) && f >> costs_from_file) {
		if (id_from_file == this->id_section && (this->payment_made<= costs_from_file && this->payment_made>=0)) {
			return true;
		}
		if (id_from_file == this->id_section)
			price = costs_from_file;
	}
	f.close();
	cout << "\t\t�������� ����� ������� (�������� ������, ��� ��������� �������� !)\n";
	cout << "\t\t�� ��������� ������ ���� ������ " << price << endl;
	return false;
}
//�������� ������ � ������
void Notation::Notation_Note() {
	cout << "\n";
	srand(time(NULL));
	Child child;
	child.Child_Note();
	child.convertDate();
	child.WriteToFile();

	getchar();
	Section section;
	while(!section.Entry_to_the_section()){}


	this->id_notation = rand()%200;
	this->id_child = child.id;
	this->id_section = section.id;
	cout << "\t\t������� �������� ����� �� �������� - ";
	cin >> this->payment_made;
	while (cin.fail()) {
		cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
		cout << "\t\t����������� - ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> this->payment_made;
	}
	while(!CheckPayment()){
		cout << "\t\t����a������ - ";
		getchar();
		cin >> this->payment_made;
		while (cin.fail()) {
			cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
			cout << "\t\t����������� - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> this->payment_made;
		}
	}
	this->arrears = section.section_cost - this->payment_made;
	
} 
//�������� � ����
void Notation::WriteToFile() {
	ofstream out;
	out.open("Notation.txt", ios::app); // �������� ���� ��� ������
	if (out.is_open())
	{
		out << this->id_notation << " ";
		out << this->id_child << " ";
		out << this->id_section<< " ";
		out << this->arrears << " ";
		out << this->payment_made << endl;
	}
	out.close();
}
//�������� id ������
void Notation::setID_not(int new_ID) { this->id_notation = new_ID; }
//�������� id ������
void Notation::setID_child(int new_ID){ this->id_child = new_ID; }
//�������� id ������
void Notation::setID_sect(int new_ID){ this->id_section = new_ID; }
// �������� �������� �����
void Notation::setPayment(double new_Payment){ this->payment_made = new_Payment; }
//�������� ����
void Notation::setArrears(double new_Arrears){ this->arrears = new_Arrears; }
// �������� �����
double Notation::getPayment() {
	return this->payment_made;
}
//�������� ����
double Notation::getArrears() {
	return this->arrears;
}
//�������� id ������
int Notation::getID_child()
{
	return this->id_child;
}
//�������� id ������
int Notation::getID_section()
{
	return this->id_section;
}
//�������� id ������
int Notation::getID_note()
{
	return this->id_notation;
}

