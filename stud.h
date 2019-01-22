#ifndef STUD_HPP
#define STUD_HPP

#include <string>
#include <iostream>
#include <list>
#include <conio.h>
using namespace std;

class STUD // Содержит информацию о книгах
{
public:
	STUD(string a, string b, int c, int d, string e, int f, int g, int h);
	bool operator==(const STUD &st);
	string toString();

	void set_status(int status);
	void set_nameperson(string nameperson);
	void set_date(int date);
	void set_month(int month);
	void set_year(int year);

	int get_status();
	string get_person();
	int get_m();
	int get_f();
	int get_h();

private:
	string name_book, author;
	int cost;
	int status;
	string nameperson;
	int date, month, year;

};

#endif // STUD_H
