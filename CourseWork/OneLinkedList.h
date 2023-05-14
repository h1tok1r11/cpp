//#include "Node.h"
//#pragma once
//
//template <typename T>
//class OneLinkedList
//{
//public:
//	Node<T>* phead, *ptail;
//public:
//	OneLinkedList(): phead(nullptr), ptail(nullptr) {};
//	~OneLinkedList() {
//		while (phead != nullptr)
//			popFront();
//	};
//
//	void popFront() {
//		if (phead == nullptr)
//			return;
//		if (phead == ptail) {
//			delete ptail;
//			phead = ptail = nullptr;
//			return;
//		}
//		Node<T>* pcur = phead;
//		phead = pcur->pnext;
//		delete pcur;
//	}
//
//	void pushBack(T data) {
//		 Node<T>* pnew = new Node<T>(data);
//		if (phead == nullptr) {
//			phead = pnew;
//			ptail = phead;
//		}
//		if (ptail != nullptr) {
//			ptail->pnext = pnew;
//			ptail = pnew;
//		}
//	}
//
//	void pushFront(T data) {
//		Node<T>* pnew = new Node<T>(data);
//		pnew->pnext = phead;
//		phead = pnew;
//		if (ptail == nullptr)
//			ptail = pnew;
//	}
//
//	void popBack() {
//		if (ptail == nullptr)
//			return;
//		if (phead = ptail) {
//			delete ptail;
//			phead = ptail = nullptr;
//			return;
//		}
//		Node<T>* pcur = phead;
//		for (; pcur->pnext != ptail; pcur = pcur->pnext);
//		pcur->pnext = nullptr;
//		delete ptail;
//		ptail = pcur;
//
//	}
//
//	Node<T>* getAt(int idx) {
//		if (idx < 0)
//			return nullptr;
//		Node<T>* pcur = phead;
//		int cnt = 0;
//		while (pcur && pcur->pnext && cnt != idx) {
//			pcur = pcur->pnext;
//			cnt++;
//		}
//		return (cnt == idx) ? pcur : nullptr;
//	}
//
//	void insert(int idx, T data) {
//		Node<T>* pleft = getAt(idx);
//		if (pleft == nullptr)
//			return;
//		Node<T>* pright = pleft->pnext;
//		Node<T>* pcur = new Node<T>(data);
//		pcur->pnext = pright;
//		pleft->pnext = pcur;
//		if (pright == nullptr)
//			ptail = pcur;
//	}
//
//	void erase(int idx) {
//		if (idx < 0)
//			return;
//		if (idx == 0) {
//			popFront();
//			return;
//		}
//		Node<T>* pleft = getAt(idx - 1);
//		Node<T>* pcur = pleft->pnext;
//		if (pcur == nullptr)
//			return;
//		Node<T>* pright = pcur->pnext;
//		pleft->pnext = pright;
//		if (pcur == ptail)
//			ptail = pleft;
//		delete pcur;
//	}
//};