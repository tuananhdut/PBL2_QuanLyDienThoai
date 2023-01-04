#pragma once
#include <iostream>
using namespace std;
class date {
protected:
    int day;
    int month;
    int year;
public:
    date(int x=0, int y=0, int z=0);
    date(const date& x);
    ~date();
    void setday(int x);
    int getday();
    void setmonth(int x);
    int getmonth();
    void setyear(int x);
    int getyear();
    friend ostream& operator<<(ostream& output, date& x);
    friend istream& operator>>(istream& input, date& x);
    const date& operator = (const date& x);
    bool operator ==(const date& x);
};