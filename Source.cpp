#include<iostream>
#include"User.h"
#include<Windows.h>
int main() { 

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool choice = true;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t --- Добро пожаловать в наш детский центр ! --- " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	if (!CountUsers()) {
		Admin first_user;
		first_user.createFirstAdmin();
	}
	while (choice) {
		int entered_ch;
		cout << "\n\t\t\t\t\t**** ГЛАВНОЕ МЕНЮ ****\n\t  1 - Вход для зарегистрированных пользователей\n\t  2 - Зарегистрироваться\n\t  0 - Завершить работу\n\t  Ваш выбор - ";
		cin >> entered_ch;
		// проверка на ввод
		while (cin.fail() || (entered_ch>2 || entered_ch<0)) {
			cout << "    !!! Вы некорректно ввели значение !!!\n";
			cout << "    Исправьтесь - ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> entered_ch;
		}
		switch (entered_ch)
		{
			case 1:{
				int outcome=User::autorisation();// исход
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
				cout << "\t Попробуйте ещё раз !";
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