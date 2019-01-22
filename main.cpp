#include <conio.h>
#include "stud.h"
#include "studlist.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include "stdio.h"

using namespace std;

#define cp_inp SetConsoleCP(1251)	// Для русифицированного ввода с консоли
#define cp_outp SetConsoleCP(866)	// Для русифицированного вывода на консоль

int main(void)
{
	setlocale(LC_ALL, "RUS");
	int a;	// Номер пункта меню
	string name_book, author; //называние книги, автор
	int cost, status;		//цена и инфор.
	string nameperson;	//кто взял
	int date, month, year;	//дата сдачи
	STUDLIST std, rez, lst_dolg; //списки
	STUDLIST::iterator itt;
	fstream dol;
	string str;	 // Строка для работы со стринговым потоком в case 1
	int q = 0;	// Нумерация в списке
	int size = 0;	// Количества элеметов в studlist
	int n = 0;	// Номер строки для case 3
	int nomer = 0; // Номера строки в case 3


	while (true)
	{
		setlocale(LC_ALL, ".1251");
		cout << "\n\n";
		cout << "List of operations to manage the program: \n" << endl;

		cout << "1. Initial entry of data from a file (data.txt) \n"
			"2. Entering new data from the keyboard \n"
			"3. Correction of the data of the file (for the subject of taking and passing the book) \n"
			"4. Printing the file on the screen and in the file (result.txt) \n"
			"5. Deleting data from the file \n"
			"6. Search and print debtors (by date) \n"
			"7. Exit \n";
		cout << endl;
		cout << "\n Specify the operation\nSelect please! ";
		cin >> a;
		while (!cin || a>7 || a<1)
		{
			cout << "Error 1. Error selecting operation. Enter a number from 1 to 7: ";
			cin.clear();
			//flushall();
			cin >> a;
		}

		switch (a)
		{
		case 1:	//Первоначальной занесение данных из файла
		{
					ifstream in("data.txt", ios::in);  // файл ввода
					if (!in) // проверяем на Ошибку открытия
					{
						cout << "Error 2. Error opening data.txt input file";
						getch(); // нужно нажать ENTER для продолжения работы
						break;
					}
					stringstream str;
					do
					{
						int i = 0, // счетчик
							chet = 0; //счетчик запятых и ковычек (все знаки)
						string n_1,  // вся строка
							n_2; // только Название
						in >> ws; // пропускаем все пробелы
						getline(in, n_1); // получаем строку из файла data.txt в строковую переменную n_1
						if (n_1 == "")		// В файле пустая строка
							continue;

						// получаем название книги, даже если оно пишется через пробел
						do
						{
							n_2 += n_1[i];
							if (n_1[i] == '"')
								chet++; // счетчик ковычек
							i++;
						} while (chet != 2); // когда было уже две ковычки - название сохраняется

						name_book = n_2;    // в переменную name_book;
						n_2 = "";   // "очищаем" переменную
						while (n_1[i] == ' ')  // пропускаем все пробелы в строке
							i++;

						// получаем имя Автора, даже если оно пишется через пробел и с точками
						do
						{
							n_2 += n_1[i];
							if (n_1[i] == '.')
								chet++;
							i++;
						} while (chet != 4); // когда наткнулись на 2 точки - запоминаем ФИО

						author = n_2;
						n_2 = "";     // "очищаем" переменную
						while (n_1[i] == ' ')   // пропускаем все пробелы в строке
							i++;

						// получаем цену в строковую переменную
						do
						{
							n_2 += n_1[i];
							i++;
						} while (i < n_1.size());

						str << n_2;   // переводим stringstream
						str >> cost;  // переводим string
						if (cost<0)
						{
							cout << " The price should be more than 0. Check the input file. " << endl;
							break;
						}
						std.push_back(STUD(name_book,author,cost,NULL,"",NULL,NULL,NULL));
						name_book = "";
						author = "";
						cost = 0;
						status = 0;
						nameperson = "";
						date = 0;
						month = 0;
						year = 0;
						str.clear();
					}

					while (!in.eof());
					if (!std.empty())
					{
						cout << "Operation №1 performed: Initial data entry from file \n";
						std.prn();
						break;
					}
					else
					{
						cout << "Error 3. The file is empty" << endl;
						break;
					}

					in.close();
					break;
		}

		case 2:	// Занесение новых данных с клавиатуры
		{
					string name_book, author;
					int cost;
					setlocale(LC_ALL, ".1251");
					cout << "Enter the name of the book (necessary in quotes): ";
					cp_inp;
					cin.ignore();
					getline(cin, name_book);
					cp_outp;
					cout << "Enter author's name: ";
					cp_inp;
					getline(cin, author);
					cp_outp;
					cout << "Enter the price of the book (>0): ";
					cin >> cost;
					if (cost<0)
					{
						cout << " the price should be more than 0. check the input file. " << endl;
						break;
					}
					std.push_back(STUD(name_book, author, cost, 0, "", 0, 0, 0));
					cout << "\n\n";
					cout << "the books were in the library: \n\n";
					std.prn();
					getch();
					break;
		}

		case 3:	// Корректировка данных
		{
					if (std.empty())
					{
						cout << "The list is empty" << endl;
						break;
					}
					for (itt = std.begin(); itt != std.end(); itt++)
					{
						size++;
					}
					cout << "Enter the sequence number of the row you want to edit.\nRow №" << endl;
					cin >> n;
					while (!cin || n>size || n<1)
					{
						cout << "Error 4: input error, check input data" << endl;
						cin.clear();
						//flushall();
						cout << "Enter the sequence number of the row you want to edit\nRow №" << endl;
						cin >> n;
					}
					std.editbook(n);		// Функция редактирования данных
					cout << "books in the library: \n\n";
					std.prn();
					getch();
					break;
		}

		case 4:
			if (std.empty())
			{
				cout << "filing cabinets are empty" << endl;
				break;
			}
			cout << "Operation completed №4: file cabinets: \n\n";
			std.prn();

			dol.open("result.txt", ios::out);
			if (!dol)
			{
				cout << "Error 8. Error opening result.txt file" << endl;
				getch();
				break;
			}
			dol << "file cabinets:\n\n";
			for (itt = std.begin(); itt != std.end(); itt++)
			{
				q = q + 1;
				dol << q << ". " << itt->toString() << endl;
			}

			if (!dol) // Проверка потока занесения списка должников в файл
			{
				cout << "Error 9. Error in writing data to file";
				break;
			}
			dol << endl;
			dol.clear();
			dol.close();
			if (!dol)
			{
				cout << "Error 10. Error closing file " << endl;
				break;
			}
			break;

		case 5:
		{
				  if (std.empty())
				  {
					  cout << " filing cabinets are empty" << endl;
					  break;
				  }
				  cout << "Enter the row number you want to delete. \n Row №";
				  cin >> nomer;
				  for (itt = std.begin(); itt != std.end(); itt++)				// Цикл для измерения размера studlist
				  {
					  size++;
				  }
				  while (!cin || nomer>size || nomer<1)
				  {
					  cout << "\nError 11. Error entering the row number, check the input data";
					  cin.clear();
					  //flushall();
					  cout << "\n Enter the row number you want to delete. \n Row №";
					  cin >> nomer;
				  }
				  itt = std.begin();
				  advance(itt, nomer - 1);	// Постановка иттератора на элемент (строку), находящийся под необходимым номером
				  std.erase(itt);	// Удвление элемента (строки), на который указывает иттератор
				  if (std.empty())
				  {
					  cout << "\n картотеки пусты" << endl;
					  break;
				  }
				  cout << "\n Operation completed №5: Data deleted. Edited file cabinets:" << endl;
				  std.prn();
				  size = 0;
				  break;
		}

		case 6:	// Поиск и печать на экран должников
		{
					int date2, month2, year2;
					if (std.empty())
					{
						cout << "\n filing cabinets are empty" << endl;
						break;
					}
				inputtest:		cout << " enter the time in which you want to pass the book: " << endl;
					cout << "enter day: ";
					cin >> date2;
					cout << "enter month: ";
					cin >> month2;
					cout << "enter year: ";
					cin >> year2;
					if (!cin || month2>12 || month2 <1 || date2>31 || date2<1)
					{
						cout << "Error input time. Enter again: " << endl;
						goto inputtest;
					}
					if ((month2 == 4 && date2>30) || (month2 == 6 && date2>30) || (month2 == 8 && date2>30) || (month2 == 10 && date2>30) || (month2 == 12 && date2>30) || (month2 == 2 && date2>28))
					{
						cout << "Error input time. Enter again: " << endl;
						goto inputtest;
					}
					lst_dolg = std.find_dolg(date2, month2, year2);	// В список должников передаются значения с помощью функции поиска должников
					if (lst_dolg.empty())
					{
						cout << "\n No debtors" << endl;
						break;
					}
					cout << "Operation №6 completed: List of debtors:\n";
					lst_dolg.prn();
					break;
		}
		case 7: exit(1);
		}
	}
	return 0;
}
