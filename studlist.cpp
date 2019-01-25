
#include "studlist.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "windows.h"

using namespace std;

#define cp_inp SetConsoleCP(1251)		// Для русифицированного ввода с консоли
#define cp_outp SetConsoleCP(866)		// Для русифицированного вывода на консоль

// Функция печати. Содержит итератор, счетчик, функцию класса STUD toString.
void STUDLIST::prn()
{
	int q = 0;
	for (it = begin(); it != end(); ++it)
	{
		q = q + 1;
		cout << q << ". " << it->toString() << endl;
	}
	cout << endl;
}

// Функция занесения новой книги в список с проверкой повторного введения
void STUDLIST::push_back(const STUD &st)			// Добавляемая книга
{
	for (it = this->begin(); it != this->end(); ++it)
	{
		if (*it == st)
			return;
	}
	list <STUD>::push_back(st);
}

// Функция поиска должников
STUDLIST STUDLIST::find_dolg(				//найти должников
	int date2,		//день надо сдать
	int month2,		//месяц надо сдать
	int year2)			//	год надо сдать
{
	STUDLIST rez;
	for (it = begin(); it != end(); it++)
	{
		if (it->get_status() != 0)
		{
			if (year2 == it->get_h())		// сравнение дат.
			{
				if (month2 == it->get_f())
				{
					if (date2 >= it->get_m()) rez.push_back(*it);
				}
				if (month2>it->get_f()) rez.push_back(*it);
			}
			if (year2>it->get_h()) rez.push_back(*it);
		}
	}
	return rez;
}
//поиск взятели
int STUDLIST::findperson(string x)
{
	STUDLIST::iterator it;
	int add = 0;
	for (it = begin(); it != end(); it++)
	{
		if (x == it->get_person())
		{
			add = add + 1;
		}
	}
	return add;
}

// Функция редактирования
void STUDLIST::editbook(int n)
{
	int status;                //информации книги (взятие было или нет)
	string nameperson;       //имя взятели
	int date,					// день сдачи
		month,					//месяц сдачи
		year;					// год сдачи
	STUDLIST::iterator itt;
	itt = begin();
	advance(itt, n - 1);		// Постановка иттератора на заданный элемент
	STUDLIST::iterator it;
	for (it = begin(); it != end(); it++)
	{
		if (it == itt)		// Условие установки иттератора it на том же что и иттератор itt (т.е. найден нужный элемент studlist)
		{
			cout << "Enter new book information (only 0 or 1): ";
			cin >> status;
			if (status<0 || status>1)
			{
				cout << "Error 5. Input error, check status value (only 0 or 1)" << endl;
				break;
			}
			itt->set_status(status);
			if (status == 0)
			{
				nameperson = "";
				date = 0;
				month = 0;
				year = 0;
				itt->set_nameperson(nameperson);
				itt->set_date(date);
				itt->set_month(month);
				itt->set_year(year);
			}
			if (status == 1)
			{
				cout << "Enter name borrower: " << endl;
				cp_inp;
				cin.ignore();
				getline(cin, nameperson);
				cp_outp;
			inputtime:		cout << "Enter day: " << endl;
				cin >> date;
				cout << "enter month: " << endl;
				cin >> month;
				cout << "enter year (00-20): " << endl;
				cin >> year;
				if (!cin || year<00 || year >20 || month>12 || month <1 || date>31 || date<1)
				{
					cout << "Error 7: Error entering book information. Enter again: " << endl;
					goto inputtime;
				}
				if ((month == 4 && date>30) || (month == 6 && date>30) || (month == 8 && date>30) || (month == 10 && date>30) || (month == 12 && date>30) || (month == 2 && date>28))
				{
					cout << "Error entering book information. Enter again: " << endl;
					goto inputtime;
				}
				itt->set_nameperson(nameperson);
				itt->set_date(date);
				itt->set_month(month);
				itt->set_year(year);
			}
		}
	}
}
