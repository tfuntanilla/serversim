/* *************************************************************************
Simulation Model of a Single Server Queue
File: Packets.h
By: Trisha Funtanilla
ECS 152A Computer Networks
************************************************************************* */
#ifndef PacketsH
#define PacketsH

class Packets {

protected:
	double serviceTime;

public:
	Packets();
	~Packets();
	void setServiceTime(double stime);
	double getServiceTime();
};

#endif