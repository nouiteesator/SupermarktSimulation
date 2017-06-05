#pragma once
#include "simpleTime.h"
class Customer
{
public:
	Customer();
	~Customer();
	Customer(simpleTime); //pass the arrial time
private:
	int itemAmount;
	simpleTime arrivalTime;
	int waitForCartTime;
	int waitForPayTime;
	int timeSpent;
	simpleTime timeSpent;
	simpleTime leaveTime;
	int generateItemAmount();
};

