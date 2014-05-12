#include <cstdlib>
#include "Event.h"

using namespace std;

Event::Event() {
	eventTime = 0;
}

Event::~Event() {

}

void Event::setTime(double t) {
	eventTime = t;
}

ArrivalEvent::ArrivalEvent(double eTime, bool id) {
	eventTime = eTime;
	isArrival = id;
}


ArrivalEvent::~ArrivalEvent() {

}

DepEvent::DepEvent(double eTime, bool id) {
	eventTime = eTime;
	isArrival = false;
}

DepEvent::~DepEvent() {
	
}
