#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED

#include <exception>
#include <iostream>
#include <cstring>
#include "colorclass.h"

template<class T> class Collection {
public:
	class Exception : public std::exception {
	protected:
		std::string msg;

	public:
		explicit Exception(const char* message) : msg(message) { }

		explicit Exception(const std::string& message) : msg(message) { }

		virtual ~Exception() throw () { }

		virtual const char* what() const throw () {
			return msg.c_str();
		}
	};

private:
	class Node {
	private:
		T* dataPtr;
		Node* prev;
		Node* next;

	public:
		class Exception : public Collection::Exception { };

		Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) { }

		Node(const T& e, Node* p = nullptr, Node* n = nullptr) : prev(p), next(n) {
			if ((dataPtr = new T(e)) == nullptr) {
				///throw Exception("Not available memory, creating new node");
			}
		}

		~Node() {
			delete dataPtr;
		}

		T* getDataPtr() {
			return dataPtr;
		}

		T& getData() {
			if (dataPtr == nullptr) {
				///throw Exception("Data not available, Node::getData");
			}

			return *dataPtr;
		}

		Node*& getPrev() {
			return prev;
		}

		Node*& getNext() {
			return next;
		}

		void setDataPtr(T* p) {
			dataPtr = p;
		}

		void setData(const T& e) {
			if (dataPtr == nullptr and (dataPtr = new T(e)) == nullptr) {
				throw Exception("Memory not available to store data, Node::setData");
			}
			else {
				*dataPtr = e;
			}
		}

		void setPrev(Node* p) {
			prev = p;
		}

		void setNext(Node* p) {
			next = p;
		}
	};

	Node* header;
	unsigned int itemCounter;
	bool isOrdered;

	bool isValidPos(Node* p) {
		if (p == nullptr) {
			return false;
		}

		Node* aux(header->getNext());
		while (aux != header) {
			if (aux == p) {
				return true;
			}

			aux = aux->getNext();
		}

		return false;
	}

	Node* idxToPos(int idx) {
		if (idx < 0 || idx >= itemCounter) {
			return nullptr;
		}

		Node* aux(header->getNext());
		for (int i = 0; i < idx; i++, aux = aux->getNext());

		return aux;
	}

	void copyCollection(Collection& c) {
		Node* aux(c.header->getNext());
		while (aux != c.header) {
			insertData(aux->getData());

			aux = aux->getNext();
		}
	}

	void swapData(Node* a, Node* b) {
		T* aux(a->getDataPtr());
		a->setDataPtr(b->getDataPtr());
		b->setDataPtr(aux);
	}

	void qckSort(Node* left, Node* right) {
		if (left == right) {
			return;
		}

		if (left->getNext() == right) {
			if (left->getData()->elemento.getDistanciaHN() > right->getData()->elemento.getDistanciaHN()) {
				swapData(left, right);

			}

			return;
		}

		Node *i(left);
		Node *j(right);

		while (i != j) {
			while (i != j && i->getData()->elemento.getDistanciaHN() <= right->getData()->elemento.getDistanciaHN()) {
				i = i->getNext();
			}

			while (i != j && j->getData()->elemento.getDistanciaHN() > right->getData()->elemento.getDistanciaHN()) {
				j = j->getPrev();
			}

			if (i != j) {
				swapData(i, j);
			}
		}

		if (i != right) {
			swapData(i, right);
		}

		if (i != left) {
			qckSort(left, i->getPrev());
		}

		if (i != right) {
			qckSort(i->getNext(), right);
		}
	}

public:
	typedef Node* Position;

	Collection() : header(nullptr), itemCounter(), isOrdered(true) {
		if ((header = new Node) == nullptr) {
			throw Exception("Memory not available, creating collection");
		}

		header->setPrev(header);
		header->setNext(header);
	}

	Collection(Collection& c) : Collection() {
		copyCollection(c);
	}

	~Collection() {
		deleteAll();
	}

	bool isEmpty() {
		return header->getNext() == header;
	}

	Node* insertData(Node* p, const T& e) {
		if (p != nullptr && !isValidPos(p)) {
			throw Exception("Invalid position, insert");
		}

		if (p == nullptr) {
			p = header;
		}

		Node* aux;
		if ((aux = new Node(e, p, p->getNext())) == nullptr) {
			throw Exception("Memory not available, inserting");
		}

		aux->setNext(header);
		aux->setPrev(header->getPrev());

		p->getPrev()->setNext(aux);
		p->setPrev(aux);

		itemCounter++;
		isOrdered = false;

		return aux;
	}

	Node* insertData(const T& e) {
		Node* aux;
		if ((aux = new Node(e, header->getPrev(), header)) == nullptr) {
			throw Exception("Memory not available, inserting");
		}


		aux->setNext(header);
		aux->setPrev(header->getPrev());

		header->getPrev()->setNext(aux);
		header->setPrev(aux);

		itemCounter++;
		isOrdered = false;


		return aux;
	}

	Node* insertOrderedData(const T& e) {
		if (!isOrdered) {
			sortData();
		}

		Node* p(header);
		Node* aux(header->getNext());

		while (aux != header && e->elemento.getDistanciaGN() > aux->getData()->elemento.getDistanciaGN()) {
			p = aux;
			aux = aux->getNext();
		}

		try {
			if ((aux = new Node(e, p, p->getNext())) == nullptr) {
				throw Exception("Memory not available, inserting");
			}
		}
		catch (typename Node::Exception ex) {
			throw Exception(ex.what());
		}

		p->getNext()->setPrev(aux);
		p->setNext(aux);

		itemCounter++;

		return aux;
	}

	int getItemCounter() {
		return itemCounter;
	}

	Node* push(const T& e) {
		Node *aux;
		try {
			if ((aux = new Node(e, header, header->getNext())) == nullptr) {
				throw Exception("Memory not available, inserting");
			}
		}
		catch (typename Node::Exception ex) {
			throw Exception(ex.what());
		}

		aux->setNext(header);
		aux->setPrev(header->getPrev());

		header->getPrev()->setNext(aux);
		header->setPrev(aux);

		itemCounter++;
		isOrdered = false;

		return aux;
	}

	Node* enqueue(const T& e) {
		return insertData(e);
	}

	Node* enqueuePriorized(const T& e) {
		if (!isOrdered) {
			sortData();
		}

		return insertOrderedData(e);
	}

	void deleteData(const T& e) {
		Node* p(findData(e));

		deleteData(p);
	}

	void deleteData(Node* p) {
		if (!isValidPos(p)) {
			throw Exception("Invalid position, deleteData");
		}

		p->getPrev()->setNext(p->getNext());
		p->getNext()->setPrev(p->getPrev());

		itemCounter--;

		delete p;
	}

	void deleteAll() {
		Node* aux;
		while (header->getNext() != header) {
			aux = header->getNext();
			header->setNext(header->getNext()->getNext());

			delete aux;
		}

		header->setPrev(header);
		itemCounter = 0;
	}

	T pop() {
		if (isEmpty()) {
			throw Exception("Insufficient data, pop");
		}

		T r(header->getPrev()->getData());
		//T r(retrieveData(getLast()));

		Node* aux(header->getPrev());

		aux->getPrev()->setNext(aux->getNext());
		aux->getNext()->setPrev(aux->getPrev());

		delete aux;

		//this->deleteData(this->getLast());
		itemCounter--;
		return r;
	}

	T dequeue() {
		if (isEmpty()) {
			throw Exception("Insufficient data, dequeue");
		}

		T r = header->getNext()->getData();

		Node* aux(header->getNext());

		aux->getPrev()->setNext(aux->getNext());
		aux->getNext()->setPrev(aux->getPrev());

		delete aux;
		itemCounter--;

		return r;
	}

	Node* getFirst() {
		if (isEmpty()) {
			return nullptr;
		}

		return header->getNext();
	}

	Node* getLast() {
		if (isEmpty()) {
			return nullptr;
		}

		return header->getPrev();
	}

	Node* getPrev(Node* p) {
		if (isEmpty() or p == header->getNext() or !isValidPos(p)) {
			return nullptr;
		}

		return p->getPrev();
	}

	Node* getNext(Node* p) {
		if (isEmpty() or p == header->getPrev() or !isValidPos(p)) {
			return nullptr;
		}

		return p->getPrev();
	}

	Node* findData(const T& e) {
		if (isEmpty()) {
			return nullptr;
		}
		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData() == e) {
				return aux;
			}
			aux = aux->getNext();
		}
		return nullptr;
	}

	Node* findId(int& toFind) {
		if (isEmpty()) {
			return nullptr;
		}
		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData().getId() == toFind) {
				return aux;
			}
			aux = aux->getNext();
		}
		return nullptr;
	}

	bool findId(const int& toFind) {
		if (isEmpty()) {
			return false;
		}
		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData().getId() == toFind) {
				return true;
			}
			aux = aux->getNext();
		}
		return false;
	}

	T findMenorCostoHN() {
		if (isEmpty()) {
			return nullptr;
		}
		int menorCosto;
		menorCosto = 999;
		T auxMenor;

		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData()->elemento.getDistanciaHN() < menorCosto) {
				menorCosto = aux->getData()->elemento.getDistanciaHN();
				auxMenor = aux->getData();
			}
			aux = aux->getNext();
		}
		return auxMenor;
	}

	T findMenorCostoGN() {
		if (isEmpty()) {
			return nullptr;
		}
		int menorCosto;
		menorCosto = 999;
		T auxMenor;

		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData()->elemento.getDistanciaGN() < menorCosto) {
				menorCosto = aux->getData()->elemento.getDistanciaGN();
				auxMenor = aux->getData();
			}
			aux = aux->getNext();
		}
		return auxMenor;
	}

	T findMenorCostoAEst() {
		if (isEmpty()) {
			return nullptr;
		}
		int menorCosto;
		menorCosto = 9999999;
		T auxMenor;

		Node* aux(header->getNext());
		while (aux != header) {
			float suma = aux->getData()->elemento.getDistanciaGN() + aux->getData()->elemento.getDistanciaHN();

			if (suma < menorCosto) {
				menorCosto = suma;
				auxMenor = aux->getData();
			}
			aux = aux->getNext();
		}
		return auxMenor;
	}

	float valueGround(const int& toFind) {
		if (isEmpty()) {
			return false;
		}
		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData().getId() == toFind) {
				return aux->getData().getValue();
			}
			aux = aux->getNext();
		}
	}

	Node* findPositionXY(T& e) {
		if (isEmpty()) {
			return nullptr;
		}
		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData().getPositionX() == e.getPositionX() && aux->getData().getPositionY() == e.getPositionY()) {
				return aux;
			}
			aux = aux->getNext();
		}
		return nullptr;
	}

	bool findasdfY(int x, int y) {
		if (isEmpty()) {
			return false;
		}
		Node* aux(header->getNext());
		while (aux != header) {
			if (aux->getData().getPositionX() == x && aux->getData().getPositionY() == y) {
				return true;
			}
			aux = aux->getNext();
		}
		return false;
	}

	T& getData(Node* aux) {
		if (aux != nullptr) {
			return aux->getData();
		}
	}

	T& retrieveData(Node* p) {
		if (!isValidPos(p)) {
			throw Exception("Invalid position, retrieve");
		}

		return p->getData();
	}

	T& getTop() {
		if (isEmpty()) {
			throw Exception("Insufficient data, getTop");
		}

		return header->getPrev()->getData();
	}

	T getFront() {
		if (isEmpty()) {
			throw Exception("Insufficient data, getFront");
		}
		return header->getNext()->getData();
	}

	void sortData() {
		qckSort(header->getNext(), header->getPrev());

		isOrdered = true;
	}

	Node* getPointerDataByPosition(int idx) {
		return idxToPos(idx);
	}

	T& getDataByPosition(int idx) {
		return retrieveData(idxToPos(idx));
	}

	T& operator [] (const int idx) {
		return retrieveData(idxToPos(idx));
	}

	Collection& operator + (const Collection& c) {
		copyCollection(c);

		return *this;
	}

	Collection& operator = (const Collection& c) {
		deleteAll();
		copyCollection(c);

		return *this;
	}

};

#endif // COLLECTION_H_INCLUDED

