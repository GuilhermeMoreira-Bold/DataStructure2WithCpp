#include <iostream>
using namespace std;

template<typename T>

class Node {
public:
	T data;
	Node* next;

	Node(T val) : data(val), next(nullptr){}
};
template<typename T>
class LinkedList {
private:
	Node<T>* head;
	int Size;
public:
	LinkedList() :head(nullptr){}

	void add(T value) {
		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr) {
			head = newNode;
			Size++;
		}
		else {
			Node<T>* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
			Size++;
		}
	}
	T get(int index) {
		Node<T>* node = head;
		int currentPosition = 0;
		while (node != nullptr && currentPosition < index) {
			node = node->next;
			currentPosition++;
		}
		if (node != nullptr) {
			return node->data;
		}
		else {
			throw out_of_range("Index out of bound");
		}
	}
	void set(T value,int index) {
		Node<T>* node = head;
		int currentPosition = 0;
		while(node != nullptr && currentPosition <  index){
			node = node->next;
			currentPosition++;
		}
		if (node != nullptr) {
			node->data = value;
		}
		else {
			throw out_of_range("Index out of range");
		}
	}
	int size() {
		return Size;
	}
	~LinkedList() {
		Node<T>* node = head;
		while (node != nullptr) {
			Node<T>* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}

};

int main() {
	LinkedList<long> longList;
	longList.add(1);
	longList.add(2);
	longList.add(3);

	for (int i = 0; i < longList.size(); i++) {
		cout << "Number: " << longList.get(i);
	}
	

	return 0;
}