/* *************************************************************************
Simulation Model of a Single Server Queue
File: Packets.cpp
By: Trisha Funtanilla
ECS 152A Computer Networks
************************************************************************* */
#include <cstdlib>
#include "Packets.h"

using namespace std;

Packets::Packets() {

}

Packets::~Packets() {
	
}

void Packets::setServiceTime(double sTime) {
	serviceTime = sTime;
}

double Packets::getServiceTime() {
	return serviceTime;
}