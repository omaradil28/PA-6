#include"Data.hpp"

template <class T>
class Node {
public:
	Node(T&);
	~Node();

	Node<T>* getNext();
	void setNext(Node<T>*);

	T* getData();
	void setData(T);

private:
	Node<T>* pNext;
	T data;
};


template <class T>
Node<T>::Node(T& newData) {
	this->pNext = nullptr;
	this->data = newData;
}

template <class T>
Node<T>::~Node() {}

template <class T>
Node<T>* Node<T>::getNext() {
	return this->pNext;
}

template <class T>
void Node<T>::setNext(Node<T>* node) {
	pNext = node;
}

template <class T>
T* Node<T>::getData() {
	return &data;
}

template <class T>
void Node<T>::setData(T newData) {
	data = newData;
}
