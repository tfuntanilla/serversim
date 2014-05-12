/* *************************************************************************
Simulation Model of a Single Server Queue
File: LinkedList.h
By: Trisha Funtanilla
ECS 152A Computer Networks
************************************************************************* */

#ifndef LinkedListH
#define LinkedListH
#include "Event.h"

class LinkedList;

class ListNode {

	Event *event;
	ListNode *next;
	ListNode *prev;
	ListNode(Event *e, ListNode *n, ListNode *p);
	~ListNode();
	friend class LinkedList;
};

class LinkedList {

	ListNode *head;

public:
	LinkedList();
	~LinkedList();
	Event* access(int index);
	void insert(Event *e);
	void print();
};

#endif