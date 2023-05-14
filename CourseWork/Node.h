#pragma once

template <typename T>
class Node
{
public:
	T data;
	Node* pNext;

	Node(T data = T(), Node* pNext = nullptr) :
		data(data), pNext(pNext) {}
};