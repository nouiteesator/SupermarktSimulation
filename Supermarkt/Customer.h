#pragma once
#include "simpleTime.h"
class Customer
{
	//todo generate getter and setter 
public:
	Customer();
	~Customer();
	Customer(simpleTime); //pass the arrial time
	int getItemAmount();
	void setItemAmount(int);
	simpleTime getArrivalTime();
	int getWaitForCartTime();
	void setWaitForCartTime(int);
	int getWaitForPayTime();
	void setWaitForPayTime(int);
	simpleTime getTimeSpent();
	void setTimeSpent(simpleTime);


private:
	int itemAmount;
	simpleTime arrivalTime;
	int waitForCartTime;
	int waitForPayTime;
	int timeSpent;
	simpleTime timeSpent;
	simpleTime leaveTime;
	int generateItemAmount();
	void setArrivalTime(simpleTime);
};

/*
#pragma once
#include "simpleTime.h"
class Customer
{
	//todo generate getter and setter 
public:


	Customer(simpleTime); //pass the arrial time
	int getItemAmount();
	void setItemAmount(int);
	simpleTime getArrivalTime();
	int getWaitForCartTime();
	void setWaitForCartTime(int);
	int getWaitForPayTime();
	void setWaitForPayTime(int);
	simpleTime getTimeSpent();
	void setTimeSpent(simpleTime);


private:
	int itemAmount;
	simpleTime arrivalTime;
	int waitForCartTime;
	int waitForPayTime;
	int timeSpent;
	simpleTime timeSpent;
	simpleTime leaveTime;
	int generateItemAmount();
	void setArrivalTime(simpleTime);
};

*/