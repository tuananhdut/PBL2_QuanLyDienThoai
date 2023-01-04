#pragma once
#include <iostream>
#include "list.h"

using namespace std;
class DT {
	string seri;
	bool daban;
	string kieu;
	NODE<KieuDT>* Pnext;
public:
	DT(DT& x);
	DT();
	void setDaBan();
	void getKieuDT();//in thong tin kieu dt;
	string getKieu();
	bool getDaBan();
	string getseri();
	string getNSX();
	void setPnext(NODE<KieuDT>* p);
	NODE<KieuDT>* getPnext();
	const DT& operator =(const DT& x);
	friend istream& operator>>(istream& in, DT& x);
	friend ostream& operator <<(ostream& out, DT& x);
	void nhapTable();
	void themvaofile(ostream& out);
};