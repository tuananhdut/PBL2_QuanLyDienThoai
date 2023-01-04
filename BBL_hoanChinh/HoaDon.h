#pragma once
#include <iostream>
#include "DT.h"
#include "DATE.h"
#include "KhachHang.h"
using namespace std;
class hoadon {
	static int demhd;
	string maHD;
	string maKH;
	date ngaylap;
	int sosanpham;
	string* dt;
public:
	hoadon();
	hoadon(hoadon& x);
	hoadon(int x);
	~hoadon();
	void inngay(ostream& out);
	string getDT(int x);
	int getsosanpham();
	string getmaHD();
	string getMaKH();
	date getNgayLap();
	void inHoaDon(ostream &out);
	void nhaptablehd();
	void nhapvaofile(ostream& out,string s);
	//const hoadon& operator = (const hoadon& x);
	friend istream& operator >>(istream& in, hoadon& x);
	friend ostream& operator <<(ostream& out, hoadon& x);
};