#include "HoaDon.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
using namespace std;


void HDxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


int hoadon::demhd = -1;
hoadon::hoadon()
{
	demhd++;
	maHD = "";
	maKH = "";
	ngaylap = date(0, 0, 0);
	sosanpham = 0;
	dt = new string [0];
}

hoadon::hoadon(hoadon& x)
{
	maKH = x.maHD;
	maHD = x.maHD;
	ngaylap = x.ngaylap;
	sosanpham = x.sosanpham;
	dt = new string[x.sosanpham];
	for (int i = 0; i < x.sosanpham; i++) {
		dt[i] = x.dt[i];
	}
}

hoadon::hoadon(int x)
{
	maHD = "";
	maKH = "";
	ngaylap = date(0, 0, 0);
	sosanpham = x;
	dt = new string[x];
	for (int i = 0; i < x; i++) {
		dt[i] = "";
	}
}

hoadon::~hoadon()
{
	delete[] dt;
	demhd--;
}

void hoadon::inngay(ostream& out)
{
	out << ngaylap;
}

string hoadon::getDT(int x)
{
	return dt[x];
}

int hoadon::getsosanpham()
{
	return sosanpham;
}

string hoadon::getmaHD()
{
	return maHD;
}

string hoadon::getMaKH()
{
	return maKH;
}



date hoadon::getNgayLap()
{
	return ngaylap;
}

void hoadon::inHoaDon(ostream &out)
{
	out << maHD<<endl;
	out << maKH<<endl;
	out << ngaylap << endl;
	out << sosanpham<<endl;
	for (int i = 0; i < sosanpham; i++) {
		out << this->dt[i]<<endl;
	}
}

void hoadon::nhaptablehd()
{
	this->maHD = "MHD" + string(5 - to_string(demhd).length(), '0') + to_string(demhd);
	HDxy(72, 13);
	cin >> this->ngaylap;
	HDxy(72, 16);
	cin >> this->sosanpham;
	dt = new string[sosanpham];
	for (int i = 0; i < sosanpham; i++) {
		HDxy(50,20+i);
		cout << "NHAP SERI "<<i+1<<"            : ";
		cin >> dt[i];
	}
}

void hoadon::nhapvaofile(ostream& out,string s)
{
	out << endl;
	out << maHD << endl;
	out << s << endl;
	out << ngaylap<<endl;
	out << sosanpham;
	for (int i = 0; i < sosanpham; i++) {
		out << endl;
		out << dt[i];
	}
}

//const hoadon& hoadon::operator=(const hoadon& x)
//{
//	if (this != &x) {
//		delete[] dt;
//		sosanpham = x.sosanpham;
//		dt = new string[sosanpham];
//		for (int i = 0; i < x.sosanpham; i++) this->dt[i] = x.dt[i];
//	}
//	return *this;
//}

istream& operator>>(istream& in, hoadon& x)
{
	in >>x.maHD;
	in >> x.maKH;
	in >> x.ngaylap;
	in >> x.sosanpham;
	x.dt = new string[x.sosanpham];
	for (int i = 0; i < x.sosanpham; i++) {
		in >> x.dt[i];
	}
	return in;
}

ostream& operator<<(ostream& out, hoadon& x)
{
	out << setw(15) << left << x.maHD << "| " << setw(15) << left << x.maKH << "| " << setw(17) << left << x.ngaylap << "| " << setw(5) << left << x.sosanpham;
	/*out << x.maHD << endl;
	out << x.maKH << endl;
	out << x.ngaylap << endl;
	out << x.sosanpham << endl;
	for (int i = 0; i < x.sosanpham; i++) {
		out << x.dt[i]<<endl;
	}*/
	return out;
}
