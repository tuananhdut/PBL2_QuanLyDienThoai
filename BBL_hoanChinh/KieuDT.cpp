#include"KieuDT.h"
#include <string>
#include <iostream>
//#include "ThuVien.h"
#include <Windows.h>
#include <iomanip>
using namespace std;

void toxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

KieuDT::KieuDT(KieuDT& x)
{
	MaKieu = x.MaKieu;
	NhaSanXuat = x.NhaSanXuat;
	GiaBan = x.GiaBan;
	TGBaoHanh = x.TGBaoHanh;
}

KieuDT::~KieuDT()
{
}

string KieuDT::getMaKieu() {
	return MaKieu;
}

int KieuDT::getTGBaoHanh()
{
	return TGBaoHanh;
}

string KieuDT::getNhaSanXuat()
{
	return NhaSanXuat;
}

int KieuDT::getGiaBan()
{
	return GiaBan;
}

KieuDT::KieuDT(string Ma, string hang, int gia, int tgbh)
	:MaKieu(Ma),NhaSanXuat(hang),GiaBan(gia),TGBaoHanh(tgbh)
{
}



void KieuDT::nhapTableKieuDT()
{
	toxy(72, 6);
	cin >> MaKieu;
	toxy(72, 9);
	cin >> NhaSanXuat;
	toxy(72, 12);
	cin >> GiaBan;
	toxy(72, 15);
	cin >> TGBaoHanh;
}

void KieuDT::nhapfileKieuDT(ostream& out) {
	out << endl;
	out << MaKieu << endl;
	out << NhaSanXuat << endl;
	out << GiaBan << endl;
	out << TGBaoHanh;
}





istream& operator>>(istream& in, KieuDT& x) {
	in >> x.MaKieu;
	in >> x.NhaSanXuat;
	in >> x.GiaBan;
	in >> x.TGBaoHanh;
	in.ignore();
	return in;
}

ostream& operator<<(ostream& out, KieuDT& x) {
	out <<setw(18)<<left<<x.MaKieu<<"| " << setw(18) << left << x.GiaBan<<"| " << setw(13) << left << x.NhaSanXuat<<"| " << setw(5) << left << x.TGBaoHanh;
	return out;
}