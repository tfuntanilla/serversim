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