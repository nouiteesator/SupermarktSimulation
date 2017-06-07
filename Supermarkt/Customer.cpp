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
	itemAmount = generateItemAmount();
}

//TODO get seed
int Customer::generateItemAmount(){
	//int seed =getSeed
	//poisson distribution 	
	//TODO implement poisson
}

int Customer::getItemAmount(){
	return itemAmount;
}

void Customer::setItemAmount(int pAmonut){
	itemAmount= pAmonut;

}

simpleTime Customer::getArrivalTime(){
	return arrivalTime;	
}
int Customer::getWaitForCartTime(){
	return waitForCartTime;
}
void Customer::setWaitForCartTime(int pWaitForCartTime){
	waitForCartTime	= pWaitForCartTime;
}

int Customer::getWaitForPayTime(){
	return waitForPayTime;
}
void Customer::setWaitForPayTime(int pWaitForPayTime){
	waitForPayTime=pWaitForPayTime;
}
simpleTime Customer::getTimeSpent(){
	return timeSpent;
}
void setTimeSpent(simpleTime pTimeSpent){
		timeSpent = pTimeSpent;
}
void setArrivalTime(simpleTime pArrivalTime){
	arrivalTime = pArrivalTime;
}
