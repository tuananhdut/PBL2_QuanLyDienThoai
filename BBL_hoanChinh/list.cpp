#include "list.h"
#include "KieuDT.h"
#include <iostream>

using namespace std;

template <typename T>
NODE<T>* khoitaonode(T& value) {
	NODE<T>* p = new NODE<T>;
	p->data = value;
	p->pnext = NULL;
	p->prev = NULL;
	return p;
}

template <typename T>
list<T>::list()
{
	phead = NULL;
	ptail = NULL;
}

template<typename T>
list<T>::list(list<T>& l)
{
	this->phead = l.phead;
	this->ptail = l.ptail;
}

template<typename T>
list<T>::~list()
{
	delete(this->phead);
	delete(this->ptail);
}

template <typename T>
NODE<T>* list<T>::getPhead() {
	return phead;
}

template<typename T>
void list<T>::setPhead(NODE<T> *x)
{
	phead = x;
}

template <typename T>
NODE<T>* list<T>::getPtail() {
	return ptail;
}

template <typename T>
void list<T>::themcuoi(T &value)
{
	NODE<T>* temp = khoitaonode(value);
	if (phead == NULL) {
		phead = temp;
		ptail = temp;
	}
	else {
		ptail->pnext = temp;
		temp->prev = ptail;
		ptail = temp;
	}
}

template <typename T>
void list<T>::themdau(T &value)
{
	NODE<T>* temp = khoitaonode(value);
	if (phead == NULL) {
		phead = temp;
		ptail = temp;
	}
	else {
		temp->pnext = phead;
		phead->prev = temp;
		phead = temp;
	}
}

template <typename T>
void list<T>::xuat()
{
	NODE<T>* p = phead;
	for (p; p != NULL; p = p->pnext) {
		cout << p->data;
	}
}






