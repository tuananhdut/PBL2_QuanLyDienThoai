#include <iostream>
#include "list.h"
#include "list.cpp"
#include "HoaDon.h"
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include "DATE.h"

using namespace std;
#define KEY_NONE	-1
#define colortitle 100

class listKieuDT : public list<KieuDT> {
public:
	NODE<KieuDT>* kiemtra(string s);
	void setDT(DT& x);
	void XuatKieuDTtheohang(string const& s,int x);
};

class listDT : public list<DT> {
public:
	void lienketKieuDT(listKieuDT& l);		//lien ket DT voi KieuDT va xoa cac nodeDT ko duoc lien ket
	void xuatKieu(listKieuDT& l);		//xuat ra thong tin kieu cua DT
	void xuatDTchuaban(int x);	// xuat dien thoai theo hang;
	NODE<DT> *timkiemtheoSERI(string s);
};


class listHD : public list<hoadon> {
public:

	void tim_theoMaKH(khachhang& x);
	void xuat_HD_theongay(date& s,int x);
	NODE<hoadon> *tim_HD_theoMaHD(string x);
};

NODE<hoadon> *listHD::tim_HD_theoMaHD(string x) {
	NODE<hoadon>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getmaHD() == x) {
			return p;
		}
	}
	return NULL;
}

class listKH : public list<khachhang> {
public:

	NODE<khachhang> *timKHBangMaKH(string x);
	NODE<khachhang>* KiemTraKH(khachhang const& x);
};

NODE<khachhang>* listKH::timKHBangMaKH(string x)
{
	NODE<khachhang>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getmaKH() == x) {
			return p;
		}
	}
	return NULL;
}

NODE<khachhang>* listKH::KiemTraKH(khachhang const& x)
{
	NODE<khachhang>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data == x) {
			return p;
		}
	}
	return NULL;
}


listKieuDT l_KieuDT;
listDT l_DT;
listKH l_KH;
listHD l_HD;


// thiet lap hight <=50 va width<=120 cho console
void SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}



// thiet lap console voi Screen Buffer Size (toan bo map)
void SetScreenBufferSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}



// thiet lap ko cho nguoi dung thay doi kich thuoc console
void DisableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}



// an hien thanh cuon 0: an; 1:hien;
void ShowScrollbar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}



// vo hieu hoa cac nut Minimize Maximize va close
void DisableCtrButton(bool Close, bool Min, bool Max)
{
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}


// di chuyen contro chuot

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

// 
void set_color(int code) {	
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, code);
}


void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void XuLyLuaChonMenu(int x);

void row(int y, int color) {
	char a = 179;
	set_color(color);
	gotoxy(42, y);
	cout << setw(76) << " ";
	gotoxy(42, y + 1);
	cout << setw(76) << " ";
	gotoxy(42, y + 2);
	cout << setw(76) << " ";
}

void XoaManHinh() {
	set_color(1);
	for (int i = 1; i <= 34; i++) {
		gotoxy(41, i);
		for (int j = 1; j <= 78; j++) cout << " ";
	}
}

void ThemThanhCong() {
	XoaManHinh();
	set_color(180);
	gotoxy(60, 10); cout << "                                     ";
	gotoxy(60, 11); cout << "                                     ";
	gotoxy(60, 12); cout << "       BAN DA THEM THANH CONG        ";
	gotoxy(60, 13); cout << "                                     ";
	gotoxy(60, 14); cout << "                                     ";
}

void ThemThatBai() {
	XoaManHinh();
	set_color(180);
	gotoxy(60, 10); cout << "                                     ";
	gotoxy(60, 11); cout << "                                     ";
	gotoxy(60, 12); cout << "             THEM THAT BAI           ";
	gotoxy(60, 13); cout << "                                     ";
	gotoxy(60, 14); cout << "                                     ";
}

void center(int x, int y, int width, int color, string s = "") {
	set_color(color);
	gotoxy(x, y);
	if ((width - s.length()) % 2 == 1) {
		for (int i = 0; i <= (width - s.length()) / 2; i++) cout << " ";
		cout << s;
		for (int i = 0; i <= (width - s.length()) / 2; i++) cout << " ";
	}
	else {
		for (int i = 1; i <= (width - s.length()) / 2; i++) cout << " ";
		cout << s;
		for (int i = 0; i <= (width - s.length()) / 2; i++) cout << " ";
	}
}

void MiniTable(int x, int y, int color, int width, int height = 3) {
	set_color(color);
	gotoxy(x, y);
	char c = 218; cout << c;
	c = 196;  for (int i = 1; i < width - 1; i++) cout << c;
	c = 191;  cout << c;
	c = 179;
	for (int i = 1; i < height; i++) {
		gotoxy(x, y + i);
		cout << c;
		gotoxy(x + width - 1, y + i);
		cout << c;
	}
	gotoxy(x, y + height - 1);
	c = 192;
	cout << c;
	c = 196;
	for (int i = 1; i < width - 1; i++) cout << c;
	c = 217;
	cout << c;
	gotoxy(x + 1, y + 1);

}

void Ve_lai(int x, int color) {
	set_color(color);
	switch (x)
	{
	case 1: {
		gotoxy(1, 9); cout << "1.        THEM KIEU DIEN THOAI         ";
		break;
	}
	case 2: {
		gotoxy(1, 10); cout << "2.         THEM DIEN THOAI             ";
		break;
	}
	case 3: {
		gotoxy(1, 11); cout << "3.           LAP HOA DON               ";
		break;
	}
	case 4: {
		gotoxy(1, 12); cout << "4.     DANH SACH HOA DON TRONG NGAY    ";
		break;
	}
	case 5: {
		gotoxy(1, 13); cout << "5.    TIM HOA DON BANG MA KHACH HANG   ";
		break;
	}
	case 6: {
		gotoxy(1, 14); cout << "6.    DANH SACH DIEN THOAI CHUA BAN    ";
		break;
	}
	case 7: {
		gotoxy(1, 15); cout << "7.        TIM KIEM DT THEO HANG        ";
		break;
	}
	}
}

void table(int width, int height, int y = 40) {
	char ch = 219;
	for (int i = 0; i < width; i++) {
		cout << ch;
	}
	for (int i = 0; i < height; i++) {
		gotoxy(0, i);
		cout << ch;
		gotoxy(width - 1, i);
		cout << ch;
		gotoxy(y, i);
		cout << ch;
	}
	gotoxy(0, height);
	for (int i = 0; i < width; i++) {
		cout << ch;
	}
	gotoxy(0, 5);
	for (int i = 0; i < y; i++) {
		cout << ch;
	}
	/*for (int i = 1; i < 15; i++) {

	}*/
	gotoxy(15, 1);
	set_color(2);
	cout << "HUONG DAN";
	gotoxy(4, 2);
	cout << "SU DUNG PHIM MUI TEN DE DI CHUYEN";
	gotoxy(4, 3);
	cout << "ESC:Thoat              ENTER:Chon";
	set_color(132);
	gotoxy(1, 6); cout << "                                       ";
	gotoxy(1, 7); cout << "                 MENU                  ";
	gotoxy(1, 8); cout << "                                       ";
	set_color(6);
	gotoxy(1, 9); cout << "1.        THEM KIEU DIEN THOAI         ";
	gotoxy(1, 10); cout << "2.         THEM DIEN THOAI             ";
	gotoxy(1, 11); cout << "3.           LAP HOA DON               ";
	gotoxy(1, 12); cout << "4.     DANH SACH HOA DON TRONG NGAY    ";
	gotoxy(1, 13); cout << "5.    TIM HOA DON BANG MA KHACH HANG   ";
	gotoxy(1, 14); cout << "6.    DANH SACH DIEN THOAI CHUA BAN    ";
	gotoxy(1, 15); cout << "7.        TIM KIEM DT THEO HANG        ";
	gotoxy(1, 16); cout << "                                       ";
	gotoxy(1, 17); cout << "                                       ";
	gotoxy(1, 18); cout << "                                       ";
	gotoxy(1, 19); cout << "                                       ";
	gotoxy(1, 20); cout << "                                       ";
	gotoxy(1, 21); cout << "                                       ";
	gotoxy(1, 22); cout << "                                       ";
	gotoxy(1, 23); cout << "                                       ";
	gotoxy(1, 24); cout << "                                       ";
	gotoxy(1, 25); cout << "                                       ";
	gotoxy(1, 26); cout << "                                       ";
	gotoxy(1, 27); cout << "                                       ";
	gotoxy(1, 28); cout << "                                       ";
	gotoxy(1, 29); cout << "                                       ";
	gotoxy(1, 30); cout << "                                       ";
	gotoxy(1, 31); cout << "                                       ";
	gotoxy(1, 32); cout << "                                       ";
	gotoxy(1, 33); cout << "                                       ";
	gotoxy(1, 34); cout << "                                       ";
}

void Khung(int width, int height) {
	ShowCur(0);
	SetWindowSize(width, height);
	ShowScrollbar(0);
	DisableResizeWindow();
	DisableCtrButton(0, 1, 1);
	table(width + 1, height);

}

void XuLyMenu() {
#define soluachon 7
	int vt = 1;
	Ve_lai(vt, 240);
	while (1) {
		if (_kbhit() == 1)
		{
			char c = _getch();
			if (c == -32) {
				c = _getch();
				if (c == 72) {// mui ten len
					Ve_lai(vt, 6);
					if (vt == 1) {
						vt = soluachon;
					}
					else vt--;
					Ve_lai(vt, 240);
				}
				else
					if (c == 80) {//mui ten xuong
						Ve_lai(vt, 6);
						if (vt == soluachon) {
							vt = 1;
						}
						else vt++;
						Ve_lai(vt, 240);
					}
			}
			else {
				if (c == 13) {
					XuLyLuaChonMenu(vt);

				}
				else {
					if (c == 27) {
						break;
					}
				}
			}
		}
	}
}


void indanhsachDT();

void inhoadon(hoadon &x,khachhang &y) {
	set_color(9);
	gotoxy(43,5);
	cout <<"MA HOA DON : "<<x.getmaHD();
	set_color(240);
	gotoxy(65, 7); cout << "                                     ";
	gotoxy(65, 8); cout << "          THONG TIN HOA DON          ";
	gotoxy(65, 9); cout << "                                     ";
	set_color(8);
	gotoxy(50, 13); cout << "TEN KHACH HANG    : " << y.gettenKH();
	gotoxy(50, 14); cout << "MA KHACH HANG     : " << y.getmaKH();
	gotoxy(50, 15); cout << "SO DIEN THOAI     : " << y.getSDT();
	gotoxy(50, 16); cout << "NGAY LAP HOA DON  : "; x.inngay(cout); cout << endl;
	gotoxy(50, 17); cout << "SO SAN PHAM       : " << x.getsosanpham();
	int j = 18;
	for (int i = 0; i < x.getsosanpham(); i++) {
		gotoxy(50, j++); cout << "SO SERI DIEN THOAI: "<<x.getDT(i);
	}
	
}

int main() {
		 fstream fileKieuDT;
		fileKieuDT.open("DanhSachKieuDT.txt", ios::in);
		KieuDT t;
		while (fileKieuDT.eof() == NULL) {
			fileKieuDT >> t;
			l_KieuDT.themcuoi(t);
		}
		fileKieuDT.close();
	// doc file dt
		fstream fileDT;
		fileDT.open("DanhSachDT.txt", ios::in);
		DT dt;
		while (fileDT.eof() == NULL) {
			fileDT >> dt;
			l_DT.themcuoi(dt);
		}
		fileDT.close();
		l_DT.lienketKieuDT(l_KieuDT);
	// doc file khach hang
		fstream fileKH;
		fileKH.open("DanhSachKhachHang.txt", ios::in);
		khachhang KHACHHANG;
		while (fileKH.eof() == NULL) {
			fileKH >> KHACHHANG;
			l_KH.themcuoi(KHACHHANG);
		}
		fileKH.close();
	//doc file hoa don
		fstream fileHD;
		fileHD.open("DanhSachHoaDon.txt", ios::in);
		hoadon hd;
		while (fileHD.eof() == NULL) {
			fileHD >> hd;
			l_HD.themcuoi(hd);
		}
		
		fileHD.close();
		Khung(119, 35);
		XuLyMenu();
		XoaManHinh();
		fileDT.open("DanhSachDT.txt", ios::out);
		NODE<DT>* p = l_DT.getPhead();
		for (p; p != NULL; p = p->pnext) {
			fileDT << p->data.getseri() << endl;
			fileDT << p->data.getKieu() << endl;
			fileDT << p->data.getDaBan();
			if (p != l_DT.getPtail()) {
				fileDT << endl;
			}
		}
		fileDT.close();
	return 0;
}



//---------------- kieu DT------------------

NODE<KieuDT>* listKieuDT::kiemtra(string s) {
	NODE<KieuDT>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getMaKieu() == s) {
			return p;
		}
	}
	return NULL;
}

void listKieuDT::setDT(DT& x)
{
	if (listKieuDT::kiemtra(x.getKieu()) != NULL) {
		x.setPnext(listKieuDT::kiemtra(x.getKieu()));
	}
}

void listKieuDT::XuatKieuDTtheohang(string const& s,int x) {
	int y = x;
	NODE<KieuDT>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if ( p->data.getNhaSanXuat() == s) {
			gotoxy(50, y);
			y++;
			if (y - x > 20) {
				while (1) {
					set_color(240);
					gotoxy(90, 30);			cout << "                         ";
					gotoxy(90, 31);			cout << "   ENTER DE SANG TRANG   ";
					gotoxy(90, 32);			cout << "                         ";
					set_color(78);
					if (_kbhit() == 0) {
						char c = _getch();
						if (c == 13) {
							y = x + 1;
							set_color(1);
							for (int i = x; i <= 34; i++) {
								gotoxy(41, i);
								for (int j = 1; j <= 78; j++) cout << " ";
							}
							gotoxy(50, x);
							set_color(78);
							break;
						}
					}
				}
			}
			cout << p->data;
		}
	}
}


//---------------------list DT-----------------------

void listDT::lienketKieuDT(listKieuDT& l) {
	NODE<DT>* p = getPhead();
	while (p != NULL) {
		if (l.kiemtra(p->data.getKieu()) != 0) {
			p->data.setPnext(l.kiemtra(p->data.getKieu()));
			p = p->pnext;
		}
		else {
			NODE<DT>* temp = p;
			if (temp == getPhead()) {
				setPhead(p->pnext);
				p = p->pnext;
				delete(temp);
			}
			else {
				if (temp == getPtail()) {
					p->prev->pnext = NULL;
					p = p->prev;
					delete (temp);
				}
				else {
					p->pnext->prev = p->prev;
					p->prev->pnext = p->pnext;
					p = p->pnext;
					delete (temp);
				}
			}
		}
	}
}

void listDT::xuatKieu(listKieuDT& l) {
	NODE<DT>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		p->data.getKieuDT();
	}
}

void listDT::xuatDTchuaban(int x) {
	
	set_color(240);			
	gotoxy(50, x);			cout << setw(29)<<right<<"|"<<setw(31)<<right<<"";
	gotoxy(50, x+1);		cout << setw(29)<<right<<"SO SERI          |"<< setw(31) <<left << "          KIEU DT";
	gotoxy(50, x+2);		cout << setw(29)<<right<< "|" << setw(31)<<right<<"";
	x = x + 3;
	int y = x;
	set_color(78);
	NODE<DT>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getDaBan() == false) {
			gotoxy(50, y);
			y += 1;
			if (y - x > 20) {
				while (1) {
					set_color(240);
					gotoxy(90, 30);			cout << "                         ";
					gotoxy(90, 31);			cout << "   ENTER DE SANG TRANG   ";
					gotoxy(90, 32);			cout << "                         ";
					set_color(78);
					if (_kbhit() == 0) {
						char c = _getch();
						if (c == 13) {
							y = x + 1;
							set_color(1);
							for (int i = x; i <= 34; i++) {
								gotoxy(41, i);
								for (int j = 1; j <= 78; j++) cout << " ";
							}
							gotoxy(50, x);
							set_color(78);
							break;
						}
					}
				}
			}
			cout << p->data;
		}
	}
}

NODE<DT> *listDT::timkiemtheoSERI(string s)
{
	NODE<DT>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getseri() == s) {
			return p;
		}
	}
	return NULL;
}



//--------------------hoa don -----------------

void listHD::tim_theoMaKH(khachhang& x) {
	NODE<hoadon>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getMaKH() == x.getmaKH()) {
			inhoadon(p->data, x);
			while (1) {
				set_color(240);
				gotoxy(90, 30);			cout << "                         ";
				gotoxy(90, 31);			cout << "   ENTER DE SANG TRANG   ";
				gotoxy(90, 32);			cout << "                         ";
				set_color(78);
				if (_kbhit() == 1) {
					char c = _getch();
					if (c == 13) {
						set_color(0);
						for (int i = 5; i <= 29; i++) {
							gotoxy(41, i);
							for (int j = 1; j <= 78; j++) cout << " ";
						}
						break;
					}
				}
			}
		}
	}
}

void listHD::xuat_HD_theongay(date& s,int x)
{
	int y = x;
	set_color(78);
	NODE<hoadon>* p = getPhead();
	for (p; p != NULL; p = p->pnext) {
		if (p->data.getNgayLap() == s) {
			gotoxy(50, y);
			y++;
			if (y - x > 20) {
				while (1) {
					set_color(240);
					gotoxy(90, 30);			cout << "                         ";
					gotoxy(90, 31);			cout << "   ENTER DE SANG TRANG   ";
					gotoxy(90, 32);			cout << "                         ";
					set_color(78);
					if (_kbhit() == 0) {
						char c = _getch();
						if (c == 13) {
							y = x + 1;
							set_color(1);
							for (int i = x; i <= 34; i++) {
								gotoxy(41, i);
								for (int j = 1; j <= 78; j++) cout << " ";
							}
							gotoxy(50, x);
							set_color(78);
							break;
						}
					}
				}
			}
			cout << p->data;
		}
	}
}

//----------------------------khach hang-------

//bool listKH::timKHBangMaKH(string s,khachhang &x)
//{
//	NODE<khachhang>* p = getPhead();
//	for (p; p != NULL; p = p->pnext) {
//		if (p->data.getmaKH() == s) {
//			x= p->data;
//			break;
//		}
//	}
//	return 0;
//}

void indanhsachDT() {
	
}



void XuLyLuaChonMenu(int x) {
	switch (x) {
	case 1: {
		XoaManHinh();
		
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "THEM KIEU DIEN THOAI");
		center(41, 3, 77, colortitle);
		set_color(8);	gotoxy(50, 6); cout << "Ma Kieu        :";      MiniTable(70, 5, 15, 35);
		set_color(8);	gotoxy(50, 9); cout << "Nha San Xuat   :";      MiniTable(70, 8, 15, 35);
		set_color(8);	gotoxy(50, 12); cout << "Gia Ban        :";      MiniTable(70, 11, 15, 35);
		set_color(8);	gotoxy(50, 15); cout << "Thoi Gian BH   :";      MiniTable(70, 14, 15, 35);
		ShowCur(1);
		KieuDT y;
		y.nhapTableKieuDT();
		l_KieuDT.themcuoi(y);
		fstream fileKieuDT;
		fileKieuDT.open("DanhSachKieuDT.txt", ios::app);
		y.nhapfileKieuDT(fileKieuDT);
		fileKieuDT.close();
		ShowCur(0);
		ThemThanhCong();
		break;
	}
	case 2: {
		XoaManHinh();
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "THEM DIEN THOAI");
		center(41, 3, 77, colortitle);
		set_color(8);	gotoxy(50, 6); cout << "So Seri        :";      MiniTable(70, 5, 15, 35);
		set_color(8);	gotoxy(50, 9); cout << "Kieu Dien Thoai:";      MiniTable(70, 8, 15, 35);
		DT y;
		ShowCur(1);
		y.nhapTable();
		ShowCur(0);
		if (l_KieuDT.kiemtra(y.getKieu()) != NULL) {
			l_DT.themcuoi(y);
			ThemThanhCong();
			fstream fileDT;
			fileDT.open("DanhSachDT.txt", ios::app);
			y.themvaofile(fileDT);
			fileDT.close();
		}
		else {
			ThemThatBai();
		}
		break;
	}
	case 3: {
		XoaManHinh();
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "LAP HOA DON");
		center(41, 3, 77, colortitle);
		set_color(8);	center(41, 5, 77, 8, "NHAP THONG TIN KHACH HANG");
		set_color(8);	gotoxy(50, 7); cout << "HO VA TEN      :";      MiniTable(70, 6, 15, 35);
		set_color(8);	gotoxy(50, 10); cout << "SO DIEN THOAI  :";      MiniTable(70, 9, 15, 35);
		set_color(8);	gotoxy(50, 13); cout << "NGAY LAP HD    :";      MiniTable(70, 12, 15, 35);
		set_color(8);	gotoxy(50, 16); cout << "SO DT MUA      :";      MiniTable(70, 15, 15, 35);
		ShowCur(1);
		khachhang y;
		hoadon z;
		bool kt=0;
		y.nhapTableKhachHang();
		if (l_KH.KiemTraKH(y) != NULL) {
			y = l_KH.KiemTraKH(y)->data;
			kt = 1;	
		}
		z.nhaptablehd();
		set_color(240);
		gotoxy(90, 29);			cout << "                         ";
		gotoxy(90, 30);			cout << "   HOA DON DA DUOC IN    ";
		gotoxy(90, 31);			cout << "                         ";
		fstream fileInHD;
		fileInHD.open("HoaDon.txt", ios::out);
		fileInHD << endl;
		fileInHD <<z.getmaHD()<<endl<<endl;
		fileInHD << "                 HOA DON MUA BAN DIEN THOAI"<<endl<<endl;
		fileInHD << "TEN KHACH HANG : " << y.gettenKH()<<endl;
		fileInHD << "MA KHACH HANG  : " << y.getmaKH() << endl;
		fileInHD << "SO DIEN THOAI  : " << y.getSDT() << endl;
		fileInHD << "Ngay lap       : "; z.inngay(fileInHD); fileInHD << endl;
		fileInHD << "SO SAN PHAM    : " << z.getsosanpham() << endl<<endl;
		int tong=0;
		for (int i = 0; i < z.getsosanpham(); i++) {
			fileInHD << "SO SERI " << i + 1 << "      : " << z.getDT(i) << endl;
			NODE<DT> *p=l_DT.timkiemtheoSERI(z.getDT(i));
			if (p == NULL) {
				fileInHD << "KO CO KIEU DT NAY" << endl;
			}
			else if (p->data.getDaBan()!=0) {
				fileInHD << "DIEN THOAI NAY DA DUOC BAN"<<endl;
			}
			else if (p!=NULL)
			{
				//theo vao file hoa don
				fstream fileHD;
				fileHD.open("DanhSachHoaDon.txt", ios::app);
				l_HD.themcuoi(z);
				z.nhapvaofile(fileHD, y.getmaKH());
				fileHD.close();
				//in lai vao file l_DT
				p->data.setDaBan();
				fileInHD << endl;
				fileInHD << "          MA KIEU DT    : " << p->data.getKieu()<<endl;
				fileInHD << "          NHA SAN XUAT  : " << p->data.getPnext()->data.getNhaSanXuat()<<endl;
				fileInHD << "          GIA BAN       : " << p->data.getPnext()->data.getGiaBan() << endl;
				fileInHD << "          TG BAO HANH   : " << p->data.getPnext()->data.getTGBaoHanh() << endl;
				tong += p->data.getPnext()->data.getGiaBan();
				fileInHD << endl;
			}
		}
		fileInHD << endl << endl;
		fileInHD << "TONG TIEN THANH TOAN : " << tong;
		fileInHD.close();
		if (tong != 0) {
			if (kt == 0) {
				fstream fileKH;
				fileKH.open("DanhSachKhachHang.txt", ios::app);
				y.nhapvaofile(fileKH);
				l_KH.themcuoi(y);
				fileKH.close();
			}
			fstream fileDT;
			fileDT.open("DanhSachDT.txt", ios::out);
			NODE<DT>* p = l_DT.getPhead();
			for (p; p != NULL; p = p->pnext) {
				fileDT << p->data.getseri() << endl;
				fileDT << p->data.getKieu() << endl;
				fileDT << p->data.getDaBan();
				if (p != l_DT.getPtail()) {
					fileDT << endl;
				}
			}
			fileDT.close();
		}
		ShowCur(0);
		break;
	}
	case 4: {
		XoaManHinh();
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "THONG TIN CAC HOA DON TRONG 1 NGAY BAT KI");
		center(41, 3, 77, colortitle);
		set_color(8);	gotoxy(50, 6); cout << "NHAP NGAY MUON TIM :";      MiniTable(70, 5, 15, 35);
		date y;
		gotoxy(72, 6);
		ShowCur(1);
		cin >> y;
		ShowCur(0);
		set_color(200);
		gotoxy(50, 5); cout << "               |                |                  |      ";
		gotoxy(50, 6); cout << "   MA HOA DON  | MA KHACH HANG  | NGAY LAP HOA DON |  SSP ";
		gotoxy(50, 7); cout << "               |                |                  |      ";
		l_HD.xuat_HD_theongay(y, 8);
		break;													
	}
	case 5: {
		XoaManHinh();
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "TIM HOA DON BANG MA KHACH HANG");
		center(41, 3, 77, colortitle);
		set_color(8);	gotoxy(50, 6); cout << "NHAP MA KHACH HANG :";      MiniTable(70, 5, 15, 35);
		string y;
		gotoxy(72, 6);
		ShowCur(1);
		cin >> y;
		ShowCur(0);
		NODE<khachhang>* p = l_KH.timKHBangMaKH(y);
		gotoxy(50, 9);
		set_color(1);
		gotoxy(50, 5); cout << "                                                          ";
		gotoxy(50, 6); cout << "                                                          ";
		gotoxy(50, 7); cout << "                                                          ";
		l_HD.tim_theoMaKH(p->data);
		break;
	}
	case 6: {
		XoaManHinh();
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "DANH SACH DIEN THOAI CHUA BAN");
		center(41, 3, 77, colortitle);
		l_DT.xuatDTchuaban(5);
		break;
	}
	case 7: {
		XoaManHinh();
		center(41, 1, 77, colortitle);
		center(41, 2, 77, colortitle, "TIM DIEN THOAI THEO HANG");
		center(41, 3, 77, colortitle);
		set_color(8);	gotoxy(50, 6); cout << "NHAP HANG        :";      MiniTable(70, 5, 15, 35);
		string hang;
		ShowCur(1);
		gotoxy(73, 6);
		cin >> hang;
		ShowCur(0);
		set_color(200);
		gotoxy(50, 5); cout << "                  |                   |              |      ";
		gotoxy(50, 6); cout << "      MA KIEU     |      GIA BAN      |     NSX      |  BH  ";
		gotoxy(50, 7); cout << "                  |                   |              |      ";
		set_color(70);
		l_KieuDT.XuatKieuDTtheohang(hang, 8);
		break;
	}
	}
}

