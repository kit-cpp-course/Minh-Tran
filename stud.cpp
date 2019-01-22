#include "stud.h"
#include <iomanip>
#include <sstream>
//
STUD::STUD(
	string a,	//называние книги
	string b,	//автор
	int c, //цена
	int d, //статус книги (взята или нет)
	string e,	//имя читатели
	int f, //днеь взята
	int g, //месяц взята
	int h) //год взята
{
	name_book = a;
	author = b;
	cost = c;
	status = d;
	nameperson = e;
	date = f;
	month = g;
	year = h;
}
// Перегрузка оператора ==
bool STUD::operator == (const STUD &st)
{
	if (name_book == st.name_book && author == st.author)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Функция составления строки
string STUD::toString()
{
	stringstream s;
	if (status == 1)
	{
		s << left << setw(40) << name_book << setw(20) << author << setw(5) << cost << setw(5) << status << setw(10) << nameperson;
		if (date < 10)
		{
			s << "0" << date << ".";
		}
		else
		{
			s << date << ".";
		}
		if (month < 10)
		{
			s << "0" << month << ".";
		}
		else
		{
			s << month << ".";
		}
		if (year < 10)
		{
			s << "0" << year << endl;
		}
		else
		{
			s << year << endl;
		}
	}
	if (status == 0 || status == NULL)//
	{
		s << left << setw(40) << name_book << setw(20) << author << setw(5) << cost << setw(5) << "0" << setw(10) << "\"\"" << "0" << endl;
	}
	return s.str();
}

void STUD::set_status(int status)
{
	this->status = status;
}
void STUD::set_nameperson(string nameperson)
{
	this->nameperson = nameperson;
}
void STUD::set_date(int date)
{
	this->date = date;
}
void STUD::set_month(int month)
{
	this->month = month;
}
void STUD::set_year(int year)
{
	this->year = year;
}
string STUD::get_person()
{
	return this->nameperson;
}

int STUD::get_status()
{
	return this->status;
}
int STUD::get_m()
{
	return this->date;
}
int STUD::get_f()
{
	return this->month;
}
int STUD::get_h()
{
	return this->year;
}
