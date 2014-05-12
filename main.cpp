#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <cmath>
#include <ctime>
#include <queue>
#include <list>
#include <iomanip>
#include "Event.h"
#include "LinkedList.h"
#include "Packets.h"

using namespace std;

double negExp(double rate);		// generate values for negative exponential distribution
void processArrivalEvent(int &len, double &currentTime, double lamda, double mu, LinkedList &tempList);
void processDepEvent(int index, int &len, double &currentTime, double lambda, double mu, LinkedList &tempList);
void printGEL(ofstream &out);	// prints global events list in a file
void printStats(int len, double totTime);

int totalPackets = 0, droppedPackets = 0, seenPackets = 0, MAXBUFFER;
double busyTime = 0;
double start = 0, stop = 0; // variables to keep track of server utilization time
bool isBusy = false;		// variable to keep track of when the server stops being busy/becomes busy again
queue<Packets*> packetsQ;		// FIFO queue/buffer
list<Event*> globalEventList;	// Global events list
list<double> transTimeList;		// list containing all transmission times of all packets

int main() {
	
	time_t totalTime, endTime;			// keeps track of simulation running time
	int length = 0;						// number of packets in the queue
	double arrivalRate, serviceRate;
	double ttime = 0;					// current time
	ofstream eventsList;
	eventsList.open("eventsList.txt");


	LinkedList tempList;				// temporary list to hold events

	cout << "Arrival rate (lambda): ";	// set arrival rate lambda
	cin >> arrivalRate;
	cout << "Service rate (mu): ";	// set service rate mu
	cin >> serviceRate;
	cout << "MAXBUFFER: ";
	cin >> MAXBUFFER;

	time(&totalTime);		// start server running time
	
	// create first arrival event and insert it to tempList
	ttime = negExp(arrivalRate) + ttime; 
    ArrivalEvent *firstEvent = new ArrivalEvent(ttime, true);
	tempList.insert(firstEvent);


	int arrivalCount = 0, departCount = 0; // used in keeping track of number of arrival and departure events
	for(int i=0; i<100000; i++) {
		Event *event = new Event();
		event = tempList.access(i);			// get event to process
		ttime = event->eventTime;
		if ((event->isArrival) == true) {	// if event is arrival
			arrivalCount++;
			globalEventList.push_back(event);
			processArrivalEvent(length, ttime, arrivalRate, serviceRate, tempList);
		
		}
		else if (departCount < arrivalCount) {	// if event is departure 
			// make sure number of dep events is not greater than that of arrival events
			departCount++;
			globalEventList.push_back(event);
			processDepEvent(i, length, ttime, arrivalRate, serviceRate, tempList);
		}

	}
	
	time(&endTime);
	totalTime = (double)(difftime(endTime, totalTime)) + ttime;		// stop server running time
	if (isBusy == true) {
		//cout << busyTime << endl;
		busyTime = busyTime + (ttime - start);
	}
	//cout << endTime << endl;
	cout << "=================" << endl;
	printStats(length, totalTime);
	printGEL(eventsList);
	eventsList.close();

	return 0;
}

double negExp(double rate) {

	double u;
	u = (double)rand() / (double)RAND_MAX;
    return ((-1.0/rate)*log(1.0-u));
}

void processArrivalEvent(int &len, double &currentTime, double lambda, double mu, LinkedList &tempList) {
	
	// Schedule the next arrival
	double nextTime = currentTime + negExp(lambda);	// next arrival time

	// new packet
	Packets *packet = new Packets();
	totalPackets++;
	packet->setServiceTime(negExp(mu));

	// create new arrival event
	ArrivalEvent *newEvent = new ArrivalEvent(nextTime, true);
	tempList.insert(newEvent);
	
	// Process the arrival event
	if (len == 0) { // if the server is free
		if (isBusy == true) {
			stop = currentTime;
			busyTime = busyTime + (stop - start);
			isBusy = false;
		}
		DepEvent *newDepEvent = new DepEvent(currentTime + packet->getServiceTime(), false);
		tempList.insert(newDepEvent);
		// packet gets pushed into the buffer because it is being processed
		packetsQ.push(packet);
		transTimeList.push_back(packet->getServiceTime());
		len++;

	}
	else { // if the server is busy push packet into queue or drop if queue is full
		
		seenPackets += len;
		if (isBusy == false) {
			start = currentTime;
		}
		isBusy = true;
		if (len < MAXBUFFER) {
			packetsQ.push(packet);
			transTimeList.push_back(packet->getServiceTime());
			len++;
		}
		else {
			droppedPackets++;
		}
		
	}
}

void processDepEvent(int index, int &len, double &currentTime, double lambda, double mu, LinkedList &tempList) {
	
	if (len > 0) {
		Packets *packet = packetsQ.front();
		packetsQ.pop();
		len--;
		
		packet->setServiceTime(negExp(mu));
		DepEvent *newDepEvent = new DepEvent(currentTime + packet->getServiceTime(), false);
		tempList.insert(newDepEvent);
	}
}

void printGEL(ofstream &out){

	out << "Time QueueLength" << endl;

	int q = 0;
	int x = 0;
	Event *event = new Event();
	while (!globalEventList.empty()) {
		event = globalEventList.front();

		if ((event->isArrival) == true) {
			x += q;
			q++;
			out << event->eventTime << setprecision(12) << " " << q << endl;
		}
		else {
			q--;
			out << event->eventTime << setprecision(12) << " " << q << endl;
		}

		globalEventList.pop_front();
	}

	cout << x << endl;
}

void printStats(int len, double totTime){
	/*
	Event *event = new Event();
	while (!globalEventList.empty()) {
		event = globalEventList.front();
		cout << event->eventTime << " " << event->isArrival << endl;
		globalEventList.pop_front();
	}
	
	cout << "=========================" << endl;
	while (!transTimeList.empty()) {
		double t = transTimeList.front();
		cout << t << endl;
		transTimeList.pop_front();
	}
	*/
	cout << seenPackets << endl;
	cout << "Utilization: " << ((double) busyTime / (double) totTime) << endl;
	cout << "Mean Queue Length: " << ((double) seenPackets / (double) totalPackets) << endl;
	cout << "Total packets: " << totalPackets << endl;
	cout << "Packets dropped: " << droppedPackets << endl;
}
