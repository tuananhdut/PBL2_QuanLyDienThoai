#pragma once
#include <iostream>
using namespace std;
class KieuDT {
private:
	string MaKieu;
	string NhaSanXuat;
	int GiaBan;
	int TGBaoHanh;  //tinh bang thang
public:
	~KieuDT();
	KieuDT(KieuDT& x);
	string getMaKieu();
	int getTGBaoHanh();
	string getNhaSanXuat();
	int getGiaBan();
	KieuDT(string Ma = "", string hang = "", int gia = 0,int tgbh=0);
	friend istream& operator>>(istream& in, KieuDT& x);
	friend ostream& operator<<(ostream& out, KieuDT& x);
	void nhapTableKieuDT();
	void nhapfileKieuDT(ostream& out);
};