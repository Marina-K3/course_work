#define _CRT_SECURE_NO_WARNINGS
#include "Child.h"
#include<fstream>
//���������� �������
 extern bool check_str(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (int(s[i]) > 33 && int(s[i]) < 191)// ��� ASCII-���� ����/������
        {
            cout << "\t\t����������� ������� ������ !!!!!!\n";
            return false;
        }
    }
    return true;
}
int Child:: getAge() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int age;

    age = (ltm->tm_year + 1900) - date_of_birth_of_the_child.year;
    if (date_of_birth_of_the_child.month > ltm->tm_mon + 1)
        age--;
    else if ((date_of_birth_of_the_child.month == ltm->tm_mon + 1) && (date_of_birth_of_the_child.day > ltm->tm_mday))
        age--;

    return age;
}
bool checkDate(int &day, int &month, int &year) {
    
    //�������� ������
    if (month < 1 || month>12) {
        cout << "\t\t�� ����������� ����� ����� (�� 1 �� 12)\n\t\t ����������� - ";
        cin >> month;
        while (cin.fail()) {
            cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
            cout << "\t\t����������� - ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> month;
        }
        return false;
    }
    //�������� ����
    if (year < 2004 || year>2018) {
        cout << "\t\t�� ����������� ����� ��� (�� 2004 �� 2018)\n\t\t ����������� - ";
        cin >> year;
        while (cin.fail()) {
            cout << "\t\t !!! �� ����������� ����� �������� !!!\n";
            cout << "\t\t ����������� - ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> year;
        }
        return false;
    }
    //�������� ���
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day <= 31 && day >= 1) {}
        else {
            cout << "\t\t�� ����������� ����� ���� � ����� ������ (�� 1 �� 31)";
            cin >> day;
            while (cin.fail()) {
                cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
                cout << "\t\t����������� - ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> day;
            }
            return false;
        }
    }
    else {
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day <= 30 && day > 1) {}
            else {
                cout << "\t\t�� ����������� ����� ���� � ����� ������ (�� 1 �� 30)";
                cin >> day;
                while (cin.fail()) {
                    cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
                    cout << "\t\t����������� - ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> day;
                }
                return false;
            }
        }
        else if (month == 2) {
            if ((year == 2004 || year == 2008 || year == 2012 || year == 2016) && (day<1 || day>29)) {
                cout << "\t\t�� ����������� ����� ���� � ������� (�� 1 �� 29)";
                cin >> day;
                while (cin.fail()) {
                    cout << "\t\t!!! �� ����������� ����� �������� !!!\n";
                    cout << "\t\t����������� - ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> day;
                }
                return false;
            }
            if ((year != 2004 && year != 2008 && year != 2012 && year != 2016) && (day<1 || day>28)) {
                cout << "\t\t�� ����������� ����� ���� � ������� (�� 1 �� 28)";
                cin >> day;
                return false;
            }
        }
    }
    return true;
}
//��������� ������ ��� �������� � �������������� �������� ����, ������ � ����
void Child:: convertDate() {
    int count_point=0;
    for (int i = 0; i < date_of_birth_of_the_child.date.size(); i++) {
        if (date_of_birth_of_the_child.date[i] == '.') count_point++;
    }
    while (count_point != 2) {
        cout << "\t\t�� ����������� ����� ���� �������� (������ - 01.01.2015).\n\t\t������� ������ - ";
        getchar();
        getline(cin, date_of_birth_of_the_child.date);
        count_point = 0;
        for (int i = 0; i < date_of_birth_of_the_child.date.size(); i++) {
            if (date_of_birth_of_the_child.date[i] == '.') count_point++;
        }
    }
    string strYear, strMonth, strDay;
    int i = 0;
    while (date_of_birth_of_the_child.date[i] != '.' && date_of_birth_of_the_child.date[i] != '\0') {
        strDay.push_back(date_of_birth_of_the_child.date[i]);
        i++;
    }
    i++;
    while (date_of_birth_of_the_child.date[i] != '.' && date_of_birth_of_the_child.date[i] != '\0') {
        strMonth.push_back(date_of_birth_of_the_child.date[i]);
        i++;
    }
    i++;
    while (date_of_birth_of_the_child.date[i] != '.' && date_of_birth_of_the_child.date[i] != '\0') {
        strYear.push_back(date_of_birth_of_the_child.date[i]);
        i++;
    }
    int day, month, year;
    day=atoi(strDay.c_str());
    month=atoi(strMonth.c_str());
    year=atoi(strYear.c_str());
   
    while(!checkDate(day, month, year)){
        checkDate(day, month, year);
    }
    this->date_of_birth_of_the_child.day = day;
    this->date_of_birth_of_the_child.month = month;
    this->date_of_birth_of_the_child.year = year;
    this->date_of_birth_of_the_child.age = getAge();

    //����� �������� ���������� ������� �������� ���� � ������
    string d, m;
    strDay.clear();
    strMonth.clear();
    strYear.clear();
    strYear = to_string(year);
    this->date_of_birth_of_the_child.date.clear();
    if(day/10==0) strDay.push_back('0');
    d = to_string(day);
    strDay = strDay + d + '.';
    if (month / 10 == 0) strMonth.push_back('0');
    m = to_string(month);
    strMonth = strMonth + m + '.';
    this->date_of_birth_of_the_child.date = strDay + strMonth + strYear;
}
//���������� � ����
void Child::WriteToFile() {
    ofstream out;          // ����� ��� ������
    out.open("Children.txt", ios::app); // �������� ���� ��� ������
    if (out.is_open())
    {
        out << this->id << endl;
        out << this->fullNameChild << endl;
        out << this->fullNameParent<< endl;
        out << this->date_of_birth_of_the_child.date << endl;
        out << this->date_of_birth_of_the_child.age<< endl;
        out << this->phoneNumber << endl;
      
    }
    out.close();
}
//�������� �� ���� ����������� ������
bool check_phone(string s) {
    for (int i = 0; i < s.size(); i++) {
        if ((int(s[i]) < 48 || int(s[i]) >58))// ��� ASCII-���� ����
        {
            if (s[i] != '+' && s[i] != ')' && s[i] != '(' && s[i] != '-')
            {
                cout << "\t\t����� ������ ����������� !!!!\n";
                return false;
            }
          
        }
    }
    return true;
}
//�������� ������ � ������
void Child::Child_Note() {
    srand(time(NULL));
    cout << "\t\t������� ��� ������ - ";
    getline(cin, this->fullNameChild);
    while (!check_str(this->fullNameChild)) {
        cout << "\t\t������� ��� ������ - ";
        getline(cin, this->fullNameChild);
    }
    cout << "\t\t������� ��� �������� - ";
    getline(cin, this->fullNameParent);
    while (!check_str(this->fullNameParent)) {
        cout << "\t\t������� ��� �������� - ";
        getline(cin, this->fullNameParent);
    }
    cout << "\t\t������� ���� �������� ������ - ";
    cin >> date_of_birth_of_the_child.date;
    cout << "\t\t������� ���������� ����� �������� - ";
    cin >>this->phoneNumber;
    while (!check_phone(this->phoneNumber)) {
        cout << "\t\t����������� - ";
        cin >> this->phoneNumber;
    }
    this->id = rand()%200;
    
}
//�������� ID
void Child::setID(int new_id) {
    this->id = new_id;
}
//�������� ��� ������
void Child::setName_child(string str) {
    this->fullNameChild = str;
}
//�������� ��� ��������
void Child::setName_parent(string str) {
    this->fullNameParent = str;
}
//�������� ����
void Child::setDate(string str) {
    this->date_of_birth_of_the_child.date = str;
    convertDate();
}
// �������� ����� ��������
void Child::setPhone(string str) {
    this->phoneNumber = str;
}
//�������� �������
void Child::setAge(int age) {
    this->date_of_birth_of_the_child.age = age;
}
//�������� ��� ������
string Child:: getNameChild(){
    return this->fullNameChild;
}
//�������� ��� ��������
string Child::getNameParent(){
    return this->fullNameParent;
}
//�������� ���� ��������
string Child::getDate(){
    return this->date_of_birth_of_the_child.date;
}
//�������� ID
int Child::getID()
{
    return this->id;
}
// ���������� �������
int Child::returnAge() {
    return this->date_of_birth_of_the_child.age;
}
//�������� ����� ��������
string Child::getPhone(){
    return this->phoneNumber;
}