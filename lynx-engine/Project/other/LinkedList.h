#pragma once
#include "StringUtils.h"
using namespace StringUtils;

struct Node {
	int id;
	double balance;	
	Node* next; 
};

class LinkedList {
private:
	Node* head; // current node in first position
	Node* newHead; // new node being added to first position
public:
	int length;
	LinkedList();
	~LinkedList();
	void add(int _id, double _balance);
	void outputList();
};

