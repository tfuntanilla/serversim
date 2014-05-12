#include <iostream>
#include "LinkedList.h"

using namespace std;

ListNode::ListNode(Event *e, ListNode *n, ListNode *p): event(e), next(n), prev(p) {}

ListNode::~ListNode() {
	delete event;
}

LinkedList::LinkedList(): head(NULL) {}

LinkedList::~LinkedList() {
	ListNode *ptr;
	for(ptr = head; ptr; ptr = head) {
		head = ptr->next;
		delete ptr;
	}
}

Event* LinkedList::access(int index) {
	
	ListNode *ptr;
	int i = 0;

	for(ptr = head; ptr; ptr = ptr->next) {
		if (i == index) {
			break;
		}
		i++;
	}

	return ptr->event;

}

void LinkedList::insert(Event *event) {

	ListNode *ptr, *previous = NULL;

	for(ptr = head; ptr && (ptr->event->eventTime <= event->eventTime); ptr = ptr->next) {
		previous = ptr;
	}

	if(!previous) {
		head = new ListNode(event, head, NULL);
		head->prev = new ListNode(NULL, NULL, NULL);
	}
	else {
		previous->next = new ListNode(event, ptr, previous);
		previous->next->prev = previous;

	}

}

void LinkedList::print() {
	ListNode *ptr;

	for(ptr = head; ptr; ptr = ptr->next) {
		cout << ptr->event->eventTime << " " << ptr->event->isArrival << endl;
	}

}