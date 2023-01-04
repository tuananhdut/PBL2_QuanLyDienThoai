#pragma once
#include <iostream>
using namespace std;
class khachhang {
	static int demma;
	string maKH;
	string tenKH;
	string sdt;
	int damua;
public:
	khachhang();
	~khachhang();
	int getdemma();
	string gettenKH();
	string getmaKH();
	string getSDT();
	void nhapvaofile(ostream& out);
	void nhapTableKhachHang();
	const khachhang& operator = (const khachhang& x);
	bool operator ==(const khachhang& x);
	friend istream& operator >>(istream& in, khachhang& x);
	friend ostream& operator<<(ostream& out, khachhang& x);
};