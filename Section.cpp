#include "Section.h"
//запись в секцию
bool  Section ::Entry_to_the_section() {
    string entered_name;
    cout << "\n\t\t   **** СЕКЦИИ ****";
    cout << "\n\t Введите название секции, в которую записан ребёнок\n";
    cout << "\t (Лёгкая атлетика, Тяжёлая атлетика, Бокс, Гимнастика, Танцы, Рисование, Шахматы, Вольная борьба)\n\t  Секция - ";
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
    cout << "\t Секция выбрана неправильно ! \n";
    return false;
}
//запись в файл
void Section::WriteToFile() {
    ofstream out;          // поток для записи
    out.open("Section.txt", ios::app); // окрываем файл для записи
    if (out.is_open())
    {
        out << this->id << endl;
        out << this->name << endl;
        out << this->section_cost<< endl;
   
    }
    out.close();
}
//изменить ID
void Section::setID(int new_id)
{
    this->id = new_id;
}
//изменить название секции
void Section::setName(string str)
{
    this->name = str;
}
//изменить стоимость секции
void Section::SetCosts( double new_costs)
{
    this->section_cost = new_costs;
}
//получить название секции
string Section:: getName() {
    return this->name;
}
//получить стоимость секции
double Section::getCosts() {
    return this->section_cost;
}
//получить ID секции
int Section::getID()
{
    return this->id;
}
