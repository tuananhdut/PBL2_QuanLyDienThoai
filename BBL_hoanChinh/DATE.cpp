#include "DATE.h"
#include <string>
#include <iostream>
using namespace std;

date::date(int x, int y, int z)
	:day(x),month(y),year(z)
{
}

date::date(const date& x)
{
	this->day = x.day;
	this->month = x.month;
	this->year = x.year;
}

date::~date()
{
}

void date::setday(int x)
{
	this->day = x;
}

int date::getday()
{
	return day;
}

void date::setmonth(int x)
{
	this->month = x;
}

int date::getmonth()
{
	return month;
}

void date::setyear(int x)
{
	this->year = x;
}

int date::getyear()
{
	return this->year;
}

const date& date::operator=(const date& x)
{
	if (this != &x) {
		this->day = x.day;
		this->month = x.month;
		this->year = x.year;
	}
	return *this;
}

bool date::operator==(const date& x)
{
	if (this->day == x.day && this->month == x.month && this->year == x.year) return 1;
	return 0;
}

ostream& operator<<(ostream& output, date &x)
{
	string s;
	s = to_string(x.day) + "/" + to_string(x.month) + "/" + to_string(x.year);
	output << s;
	//output << x.day << "/" << x.month << "/" << x.year;
	return output;
}

istream& operator>>(istream& input, date& x)
{
	char c;
//	cout << "nhap ngay :";
	input >> x.day;
	input >> c;
//	cout << "nhap thang :";
	input >> x.month;
	input >> c;
//	cout << "nhap nam :";
	input >> x.year;
	return input;
}
