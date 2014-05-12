/* *************************************************************************
Simulation Model of a Single Server Queue
File: Event.h
By: Trisha Funtanilla
ECS 152A Computer Networks
************************************************************************* */

#ifndef EventH
#define EventH

class Event {

public:
	double eventTime;		// time when the event occurs
	bool isArrival;			// is the type arrival or not
	Event();
	~Event();
	void setTime(double t);	
};

class ArrivalEvent: public Event {
public:
	ArrivalEvent(double eTime, bool id);
	~ArrivalEvent();
};


class DepEvent: public Event {
public:
	DepEvent(double eTime, bool id);
	~DepEvent();
};

#endif