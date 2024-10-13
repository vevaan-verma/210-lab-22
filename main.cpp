// COMSC-210 | Lab 22 | Vevaan Verma
using namespace std;
#include <iostream>

/* CONSTANTS */
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {

private:
	struct Node {

		int data;
		Node* prev;
		Node* next;

		Node(int val, Node* p = nullptr, Node* n = nullptr) {

			data = val;
			prev = p;
			next = n;

		}
	};
	Node* head;
	Node* tail;

public:
	// constructor
	DoublyLinkedList() { head = nullptr; tail = nullptr; }

	void push_back(int value) {

		Node* newNode = new Node(value);

		if (!tail) { // if there's no tail, the list is empty

			head = tail = newNode;

		} else {

			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;

		}
	}

	void push_front(int value) {

		Node* newNode = new Node(value);

		if (!head) { // if there's no head, the list is empty

			head = tail = newNode;

		} else {

			newNode->next = head;
			head->prev = newNode;
			head = newNode;

		}
	}

	void insert_after(int value, int position) {

		if (position < 0) {

			cout << "Position must be >= 0." << endl;
			return;

		}

		Node* newNode = new Node(value);

		if (!head) {

			head = tail = newNode;
			return;

		}

		Node* temp = head;

		for (int i = 0; i < position && temp; ++i)
			temp = temp->next;

		if (!temp) {

			cout << "Position exceeds list size. Node not inserted.\n";
			delete newNode;
			return;

		}

		newNode->next = temp->next;
		newNode->prev = temp;

		if (temp->next)
			temp->next->prev = newNode;
		else
			tail = newNode; // Inserting at the end

		temp->next = newNode;

	}

	void delete_node(int value) {

		if (!head) return; // Empty list
		Node* temp = head;

		while (temp && temp->data != value)
			temp = temp->next;

		if (!temp) return; // Value not found

		if (temp->prev)
			temp->prev->next = temp->next;
		else
			head = temp->next; // Deleting the head

		if (temp->next)
			temp->next->prev = temp->prev;
		else
			tail = temp->prev; // Deleting the tail

		delete temp;

	}

	// delete_pos() removes a node at a specific position in the list
	// arguments: int - the position of the node to delete
	// returns: void
	void delete_pos(int position) {

		if (position < 0) {

			cout << "Position must be >= 0." << endl;
			return;

		}

		if (!head) return; // empty list

		Node* temp = head; // start at the head

		for (int i = 0; i < position && temp; i++) // move to the position to delete
			temp = temp->next;

		if (!temp) {

			cout << "Position exceeds list size." << endl;
			return;

		}

		if (temp->prev)
			temp->prev->next = temp->next; // set the previous node's next to the node after the one being deleted
		else
			head = temp->next; // deleting the head, so move head to next node

		if (temp->next)
			temp->next->prev = temp->prev; // set the next node's previous to the node before the one being deleted
		else
			tail = temp->prev; // deleting the tail, so move tail to previous node

		delete temp; // delete the node

	}

	void print() {

		Node* current = head;
		if (!current) return;

		while (current) {

			cout << current->data << " ";
			current = current->next;

		}

		cout << endl;

	}

	void print_reverse() {

		Node* current = tail;
		if (!current) return;

		while (current) {

			cout << current->data << " ";
			current = current->prev;

		}

		cout << endl;

	}

	~DoublyLinkedList() {

		while (head) {

			Node* temp = head;
			head = head->next;
			delete temp;

		}
	}
};


// main() is the entry point and driver of the program
// arguments: none
// returns: int - the exit code of the program
int main() {

	DoublyLinkedList list;
	int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;

	for (int i = 0; i < size; ++i)
		list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

	cout << "List forward: ";
	list.print();
	cout << "List backward: ";
	list.print_reverse();
	cout << "Deleting list, then trying to print.\n";
	list.~DoublyLinkedList();
	cout << "List forward: ";
	list.print();

	return 0;

}