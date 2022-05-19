#include "Section.h"
//������ � ������
bool  Section ::Entry_to_the_section() {
    string entered_name;
    cout << "\n\t\t   **** ������ ****";
    cout << "\n\t ������� �������� ������, � ������� ������� ������\n";
    cout << "\t (˸���� ��������, ������ ��������, ����, ����������, �����, ���������, �������, ������� ������)\n\t  ������ - ";
    getline(cin, entered_name);
    string sec_name_from_file, newLine;
    double costs_from_file;
    int id_from_file;
    ifstream f;
    f.open("Section.txt", ios::in);
    while (f >> id_from_file && getline(f, newLine) && getline(f, sec_name_from_file) && f >> costs_from_file) {
        if (sec_name_from_file == entered_name) {
            this->id = id_from_file;
            this->name = sec_name_from_file;
            this->section_cost = costs_from_file; 
            return true;
        }
    }
    f.close();
    cout << "\t ������ ������� ����������� ! \n";
    return false;
}
//������ � ����
void Section::WriteToFile() {
    ofstream out;          // ����� ��� ������
    out.open("Section.txt", ios::app); // �������� ���� ��� ������
    if (out.is_open())
    {
        out << this->id << endl;
        out << this->name << endl;
        out << this->section_cost<< endl;
   
    }
    out.close();
}
//�������� ID
void Section::setID(int new_id)
{
    this->id = new_id;
}
//�������� �������� ������
void Section::setName(string str)
{
    this->name = str;
}
//�������� ��������� ������
void Section::SetCosts( double new_costs)
{
    this->section_cost = new_costs;
}
//�������� �������� ������
string Section:: getName() {
    return this->name;
}
//�������� ��������� ������
double Section::getCosts() {
    return this->section_cost;
}
//�������� ID ������
int Section::getID()
{
    return this->id;
}
