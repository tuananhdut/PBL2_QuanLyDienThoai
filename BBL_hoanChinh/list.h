#pragma once
#include "KieuDT.h"


using namespace std;
template <typename T>
struct NODE {
	T data;
	struct NODE* pnext;
	struct NODE* prev;
};


template <typename T>
class list {
	NODE<T>* phead;
	NODE<T>* ptail;
public:
	list();
	list(list<T>& l);
	~list();
	NODE<T>* getPhead();
	void setPhead(NODE<T> *x);
	NODE<T>* getPtail();
	void themcuoi(T &value);
	void themdau(T &value);
	void xuat();
};




