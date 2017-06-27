#pragma once
#include "simpleTime.h"
#include <string>
#include "Customer.h"
#include "Supermarket.h"
#include <list>

//TODO review EXECUTE()
class Event{

public:
	Event(simpleTime, int, simpleTime, int, Customer, Supermarket&);
	Event();
	~Event();
	void execute(list<Event>&); //needs to be reviewed 
	bool operator>(const Event &e)const;
	bool operator<(const Event &e)const;
	simpleTime& getStartTime();
	simpleTime& getEndTime();
	int getPrio();
	std::string toString();
	Customer& getCustomer();
	Supermarket& getSupermarket();
	Event generateNextEvent(int,simpleTime&);
	Event generateNextEvent(int,simpleTime&,Customer&);
	bool operator==(const Event &e)const;

private:
	simpleTime startTime;
	int prio;// the lower the priorty the higher is the importance
	simpleTime endTime;
	int status;
	Customer customer;
	Supermarket supermarket;
};
