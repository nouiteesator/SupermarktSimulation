#include "stdafx.h"
#include "Customer.h"
#include "simpleTime.h"
#include <random>
#include <iostream>

//Konstruktoren


Customer::Customer()
{
}


Customer::~Customer()
{
}


Customer::Customer(simpleTime arrival, int amount):waitForCartTime(0),waitForPayTime(0),timeSpent(0,0,0),leaveTime(0,0,0){
	arrivalTime = arrival;
	itemAmount =amount;
	cashAuswahl =0;
}

//Getter

int Customer::getItemAmount(){
	return itemAmount;
}
simpleTime& Customer::getArrivalTime(){
	return arrivalTime;	
}
int Customer::getWaitForCartTime(){
	return waitForCartTime;
}
int Customer::getWaitForPayTime(){
	return waitForPayTime;
}
simpleTime& Customer::getTimeSpent(){
	return timeSpent;
}
int Customer::getCashAuswahl(){
	return this->cashAuswahl;
}

//Setter

void Customer::setItemAmount(int pAmonut){
	itemAmount= pAmonut;

}
void Customer::setWaitForCartTime(int pWaitForCartTime){
	waitForCartTime	= pWaitForCartTime;
}
void Customer::setWaitForPayTime(int pWaitForPayTime){
	waitForPayTime=pWaitForPayTime;
}
void Customer::setTimeSpent(simpleTime pTimeSpent){
		timeSpent = pTimeSpent;
}
void Customer::setArrivalTime(simpleTime pArrivalTime){
	arrivalTime = pArrivalTime;
}
void Customer::setCashAuswahl(int i){
	this->cashAuswahl = i;
}

//Funktionen



