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

	void delete_val(int value) {

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

	// pop_front() removes the first node from the list
	// arguments: none
	// returns: void
	void pop_front() {

		// this can also be done through delete_pos(0), but this method is implemented for class completeness

		if (!head) return; // empty list

		Node* temp = head; // save the head node for deletion
		head = head->next; // move head to the next node

		if (head) // if the new head exists (original list had more than one node)
			head->prev = nullptr; // set the new head's previous to nullptr
		else // if the list only had one node
			tail = nullptr; // list is now empty

		delete temp; // delete the old head node

	}

	// pop_back() removes the last node from the list
	// arguments: none
	// returns: void
	void pop_back() {

		if (!tail) return; // empty list

		Node* temp = tail; // save the tail node for deletion
		tail = tail->prev; // move tail to the previous node

		if (tail) // if the new tail exists (original list had more than one node)
			tail->next = nullptr; // set the new tail's next to nullptr
		else // if the list only had one node
			head = nullptr; // list is now empty

		delete temp; // delete the old tail node

	}

	void print() {

		Node* current = head;
		if (!current) return;

		while (current) {

			cout << current->data << endl;
			current = current->next;

		}

		cout << endl;

	}

	void print_reverse() {

		Node* current = tail;
		if (!current) return;

		while (current) {

			cout << current->data << endl;
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

	cout << "List:" << endl;
	list.print();

	cout << "Removing the third node..." << endl;
	list.delete_pos(2);
	cout << "New List:" << endl;
	list.print();

	cout << "Removing the first node..." << endl;
	list.pop_front();
	cout << "New List:" << endl;
	list.print();

	cout << "Removing the last node..." << endl;
	list.pop_back();
	cout << "New List:" << endl;
	list.print();

	cout << "Deleting the value 99..." << endl;
	list.delete_val(99);
	cout << "New List:" << endl;
	list.print();

	return 0;

}