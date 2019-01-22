// Для работы со списком книг
#ifndef STUDLIST_HPP
#define STUDLIST_HPP
#include <list>
#include "stud.h"
using namespace std;

class STUDLIST : public list <STUD>
{
	STUDLIST::iterator it;
public:
	void prn();	//печать картотеки.
	void push_back(const STUD &st);		//добавить новую книгу
	STUDLIST find_dolg(int date2, int month2, int year2);  // Поиск должников
	void editbook(int n);		// Редактирование данных
	int findperson(string x);	//кто уже взял книги.
};

#endif
