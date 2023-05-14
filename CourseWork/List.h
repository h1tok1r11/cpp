#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class List
{
private:
	int Size;
	Node<T>* pHead, *pTail;
public:
	List();
	~List();

	void push_back(T data);
	int getSize() { return Size; }
	T& operator[](const int idx);
	void pop_front();
	void clear();
	void push_front(T data);
	void insert(T data, int idx);
	void removeAt(int idx);
	void pop_back();
	void printItems();
	//Node<T>* getAt(int idx);
};

template <typename T>
inline List<T>::List()
{
	Size = 0;
	pHead = pTail = nullptr;
	//std::cout << "Вызвался конструктор" << std::endl;
}
 
template<typename T>
inline List<T>::~List()
{
	clear();
	//std::cout << "Вызвался деструктор" << std::endl;
}

//template <typename T>
//T* begin() { return &data[0]; }
//template <typename T>
//const T* begin() { return &data[0]; }
//template <typename T>
//T* end() { return &data[length]; }
//template <typename T>
//const T* end() { return &data[length]; }

template<typename T>
void List<T>::push_back(T data)
{
	Node<T>* pNew = new Node<T>(data);
	if (pTail != nullptr)
	{
		pTail->pNext = pNew;
		pTail = pNew;
	}
	else if (pHead == nullptr)
	{
		pHead = pTail = pNew;
	}
	/*else {
		Node<T>* pCur = this->pHead;
		while (pCur->pNext != nullptr)
		{
			pCur = pCur->pNext;
		}
		pCur->pNext = pNew;
	}*/
	Size++;
}

template<typename T>
T& List<T>::operator[](const int idx)
{
	Node<T>* pCur = this->pHead;
	int cnt = 0;
	while (pCur != nullptr)
	{
		if (cnt == idx) return pCur->data;
		pCur = pCur->pNext;
		cnt++;
	}
}

template<typename T>
void List<T>::pop_front()
{
	if (pHead == nullptr) return;
	if (pHead == pTail)
	{
		delete pTail;
		pHead = pTail = nullptr;
		Size--;
		return;
	}
	Node<T>* pTemp = this->pHead;
	pHead = pHead->pNext;
	delete pTemp;
	Size--;
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	pHead = new Node<T>(data, pHead);
	Size++;
	if (pTail == nullptr) pTail = pHead;
}

//template<typename T>
//Node<T>* getAt(int idx) {
//	if (idx < 0) return nullptr;
//	Node<T>* pCur = this->pHead;
//	int cnt = 0;
//	while (pCur && pCur->pNext && cnt != idx) {
//		pCur = pCur->pNext;
//		cnt++;
//	}
//	return (cnt == idx) ? pCur : nullptr;
//}

template<typename T>
void List<T>::insert(T data, int idx)
{
	if (idx == 0) push_front(data);
	else
	{
		Node<T>* pLeft = this->pHead;
		for (int i = 0; i < idx - 1; i++)
		{
			pLeft = pLeft->pNext;
		}
		pLeft->pNext = new Node<T>(data, pLeft->pNext);
		Size++;
		if (pLeft->pNext->pNext == nullptr) pTail = pLeft->pNext;
		/*Node<T>* pLeft = getAt(idx - 1);
		if (pLeft == nullptr) return;
		pLeft->pNext = new Node<T>(data, pLeft->pNext);
		Size++;
		if (pLeft->pNext->pNext == nullptr) pTail = pLeft->pNext;*/
	}
}

template<typename T>
void List<T>::removeAt(int idx)
{
	if (idx < 0) return;
	if (idx == 0)
	{
		pop_front();
		return;
	}
	else
	{
		Node<T>* pLeft = this->pHead;
		for (int i = 0; i < idx - 1; i++)
		{
			pLeft = pLeft->pNext;
		}
		Node<T>* ptoDelete = pLeft->pNext;
		pLeft->pNext = ptoDelete->pNext;
		delete ptoDelete;
		Size--;
		/*Node<T>* pLeft = getAt(idx);
		Node<T>* ptoDelete = pLeft->pNext;
		pLeft->pNext = ptoDelete->pNext;
		delete ptoDelete;
		Size--;*/
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}

template<typename T>
void List<T>::printItems()
{
	Node<T>* pCur = this->pHead;
	int i = 0;
	while (pCur != nullptr) {
		std::cout << i << ". " << pCur->data << std::endl;
		i++;
		pCur = pCur->pNext;
	}
}
