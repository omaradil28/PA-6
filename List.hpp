#include"ListNode.hpp"

template <class T>
class List {
public:
	List();
	~List();

	Node<T>* getHead();
	void setHead(Node<T>*);

	void insertAtFront(T&);
	bool isEmpty();

	void destroyList(Node<T>*);

private:
	Node<T>* pHead;
};

template <class T>
List<T>::List() {
	pHead = nullptr;
}

template <class T>
List<T>::~List() {}

template <class T>
Node<T>* List<T>::getHead() {
	return pHead;
}

template <class T>
void List<T>::setHead(Node<T>* newHead) {
	pHead = newHead;
}

//Inserts node at front of linked list
template <class T>
void List<T>::insertAtFront(T& newData) {
	Node<T>* temp = new Node<T>(newData);
	if (this->pHead == nullptr) {
		pHead = temp;
	}
	else {
		temp->setNext(pHead);
		pHead = temp;
	}
}

//Check is list is empty
template <class T>
bool List<T>::isEmpty() {
	return pHead == nullptr;
}

//Destorys the list
template <class T>
void List<T>::destroyList(Node<T>* node) {
	Node<T>* pCur = node;
	Node<T>* pNext;

	while (pCur != nullptr) {
		pNext = pCur->getNext();
		delete pCur;
		pCur = pNext;
	}
	setHead(nullptr);

}
