#include<iostream>
#include"User.h"
#include<Windows.h>
int main() { 

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool choice = true;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t --- ����� ���������� � ��� ������� ����� ! --- " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	if (!CountUsers()) {
		Admin first_user;
		first_user.createFirstAdmin();
	}
	while (choice) {
		int entered_ch;
		cout << "\n\t\t\t\t\t**** ������� ���� ****\n\t  1 - ���� ��� ������������������ �������������\n\t  2 - ������������������\n\t  0 - ��������� ������\n\t  ��� ����� - ";
		cin >> entered_ch;
		// �������� �� ����
		while (cin.fail() || (entered_ch>2 || entered_ch<0)) {
			cout << "    !!! �� ����������� ����� �������� !!!\n";
			cout << "    ����������� - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> entered_ch;
		}
		switch (entered_ch)
		{
			case 1:{
				int outcome=User::autorisation();// �����
				if (outcome == 1) { 
				User *admin;
				Admin obj;
				admin = &obj;
				admin->provide_menu();
			    }
				if (outcome == 2) {
				User *employee;
				Employee obj; 
				employee = &obj;
				employee->provide_menu();
			    }
				if (outcome == -1) {
				cout << "\t ���������� ��� ��� !";
			    }
		    }
			  break;
			case 2:{
				Employee employee;
				employee.Register();
		    }
			  break;
			case 0:{
				choice = false;
			}
			  break;
			default:
			  break;
		}
	}
	return 0;
}