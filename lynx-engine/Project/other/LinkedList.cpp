#include "LinkedList.h"

LinkedList::LinkedList() {
	length = 0;
}

LinkedList::~LinkedList() {}

void LinkedList::add(int _id, double _balance) {
	newHead = new Node;
	newHead->id = _id;
	newHead->balance = _balance;
	newHead->next = head;
	head = newHead;
	length++;
}

void LinkedList::outputList() {
	Node* ptr = head;
	while (ptr != NULL) {
		printl("id: " + toString(ptr->id) + "   balance: " + toString(ptr->balance));
		ptr = ptr->next;
	}
}