#include "KhachHang.h"
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;
void KHxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

int khachhang::demma = -1;
khachhang::khachhang()
{
	demma++;
	maKH = "";
	tenKH = "";
	sdt = "";
	damua = 0;
}

khachhang::~khachhang()
{
	demma--;
}

int khachhang::getdemma()
{
	return demma;
}

string khachhang::gettenKH()
{
	return tenKH;
}


string khachhang::getmaKH()
{
	return this->maKH;
}

string khachhang::getSDT()
{
	return sdt;
}

void khachhang::nhapvaofile(ostream& out)
{
	out << endl;
	out << this->maKH<<endl;
	out << this->tenKH<<endl;
	out << this->sdt;
}

void khachhang::nhapTableKhachHang()
{
	KHxy(72, 7);
	getline(cin, tenKH);
	KHxy(72, 10);
	cin >> sdt;
	maKH = "MKH" + string(5 - to_string(demma).length(), '0') + to_string(demma);
	cin.ignore();
}

const khachhang& khachhang::operator=(const khachhang& x)
{
	if (this != &x) {
		maKH = x.maKH;
		tenKH = x.tenKH;
		sdt = x.sdt;
		damua = x.damua;
	}
	return *this;
}

bool khachhang::operator==(const khachhang& x)
{
	if (this->sdt == x.sdt && this->tenKH == x.tenKH) return true;
	return false;
}

istream& operator>>(istream& in, khachhang& x)
{
	in >> x.maKH;
	in.ignore();
	getline(in, x.tenKH);
	in >> x.sdt;
	in.ignore();
	return in;
}

ostream& operator<<(ostream& out, khachhang& x)
{
	out << "bien dem" << x.demma << endl;
	out << x.maKH<<endl;
	out << x.tenKH<<endl;
	out << x.sdt<<endl;
	out << x.damua << endl;
	return out;
}
