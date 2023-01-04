#include "DT.h"
#include <iostream>
#include "DATE.h"
#include "KieuDT.h"
#include<Windows.h>
#include <iomanip>
using namespace std;

void denxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


DT::DT(DT& x)
{
	this->seri = x.seri;
	this->daban = x.daban;
	this->kieu = x.kieu;
	this->Pnext = x.Pnext;
}

DT::DT()
{
	seri = "";
	daban = false;
	this->Pnext = NULL;
	this->kieu = "";

}

void DT::setDaBan()
{
	daban = 1;
}

void DT::getKieuDT()
{
	cout << "ma kieu" << this->Pnext->data.getMaKieu()<<endl;
	cout << "ma Nha San xuat" << this->Pnext->data.getNhaSanXuat() << endl;
	cout << " gia ban" << this->Pnext->data.getGiaBan() << endl;
	cout << "thoi gian bao hanh" << this->Pnext->data.getTGBaoHanh() << endl;
}

string DT::getKieu()
{
	return this->kieu;
}

bool DT::getDaBan()
{
	return daban;
}

string DT::getseri()
{
	return seri;
}

string DT::getNSX()
{
	return this->Pnext->data.getNhaSanXuat();
}

void DT::setPnext(NODE<KieuDT>* p)
{
	this->Pnext = p;
}

NODE<KieuDT>* DT::getPnext()
{
	return this->Pnext;
}



const DT& DT::operator=(const DT& x)
{
	if (this != &x) {
		this->seri = x.seri;
		this->daban = x.daban;
		this->Pnext = x.Pnext; 
		this->kieu = x.kieu;
	}
	return *this;
}


istream& operator>>(istream& in, DT& x)
{
	in >> x.seri;
	in >> x.kieu;
	in >> x.daban;
	return in;
}

ostream& operator<<(ostream& out, DT& x)
{
	out <<"   "<<setw(25) << left << x.seri << "|   " << setw(28) << x.kieu;
	return out;
}

void DT::nhapTable() {
	denxy(72, 6);
	cin >> seri;
	denxy(72, 9);
	cin >> kieu;
}

void DT::themvaofile(ostream& out)
{
	out << endl;
	out << this->seri << endl;
	out << this->kieu<<endl;
	out << this->daban;
}
