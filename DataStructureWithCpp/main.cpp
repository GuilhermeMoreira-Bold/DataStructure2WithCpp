#include <iostream>
#include <fstream>
#include<string>
#include <regex>

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
class FileReader {
public:

	static int index() {
		ifstream readFile("C:/Users/gulhe/Source/Repos/GuilhermeMoreira-Bold/DataStructure2WithCpp/data/filesIndex.txt");
		string line;
		if (readFile.is_open()) {
			if (getline(readFile, line)) {
				int index = stoi(line);
				cout << index << endl;
				readFile.close();
				return index;
			}
		}
		else {
			cout << "Index wrong";
			return -1;
		}
	}
	static LinkedList<long> read(string& filePath){
		LinkedList<long> list;
		ifstream readFile(filePath);
		
		string line;
		
		if (readFile.is_open()) {
			regex integerPattern(R"(-?\b\d+\b)");
			smatch match;
			try {
				while (getline(readFile, line)) {
					sregex_iterator it(line.begin(), line.end(), integerPattern);
					sregex_iterator end;
					while (it != end) {
						match = *it;
						if (match.size() > 0) {
							list.add(std::stol(match[0]));
						}
						++it;
					}
				}
			}
			catch (const invalid_argument& e) {
				cerr << "Error: Invalid argument's" << e.what() << endl;
			}
			readFile.close();
			return list;
		}
		else {
			cout << "Is not possible open the file";
		}
	}
		
};	
class FileWrite {
public:
	static void write(string& fileName,LinkedList<long>& list){
		string filePath = "C:/Users/gulhe/Source/Repos/GuilhermeMoreira-Bold/DataStructure2WithCpp/results/"+ fileName + to_string(FileReader::index() + 1) + ".txt";
		cout << to_string(FileReader::index() + 1);
		ofstream myFile(filePath);
		if(myFile.is_open()) {
			try {
				myFile << "[";
				for (int i = 0; i < list.size(); i++) {
					if (i != 0) {
						myFile << ", ";
					}
					myFile << list.get(i);
				}
				myFile << "]";
			}catch (const invalid_argument& e) {
				cerr << "Error: Invalid argument's in write files" << e.what() << endl;
			}
			myFile.close();
		}
		writeNewIndex();
	}
	static void writeNewIndex() {
		string filePath = "C:/Users/gulhe/Source/Repos/GuilhermeMoreira-Bold/DataStructure2WithCpp/data/filesIndex.txt";
		ofstream file(filePath);
		int index = (FileReader::index() + 1);
		string newIndex;
		file << to_string(index);
		file.close();
	}
};

int main() {
	string path = "C:/Users/gulhe/Source/Repos/GuilhermeMoreira-Bold/DataStructure2WithCpp/data/casos/aleatorio/dados5.txt";
	LinkedList<long> list = FileReader::read(path);
	for (int i = 0; i < list.size(); i++) {
		cout << "Number:" << list.get(i) << "\n" << endl;
	}
	string name = "test";
	FileWrite::write(name,list);
	
	return 0;
}