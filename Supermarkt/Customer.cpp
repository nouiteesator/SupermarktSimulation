#include "stdafx.h"
#include "Customer.h"


Customer::Customer()
{
}


Customer::~Customer()
{
}


Customer::Customer(simpleTime arrival){
	arrivalTime = arrival;
}

//TODO get seed
int Customer::generateItemAmount(){
	//int seed =getSeed
	
}


/*
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


*/