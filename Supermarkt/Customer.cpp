#include "stdafx.h"
#include "Customer.h"
#include "simpleTime.h"
#include <random>

//Konstruktoren

Customer::Customer()
{
}


Customer::~Customer()
{
}


Customer::Customer(simpleTime arrival){
	arrivalTime = arrival;
	itemAmount = generateItemAmount(10);
}

//Getter

int Customer::getItemAmount(){
	return itemAmount;
}
simpleTime Customer::getArrivalTime(){
	return arrivalTime;	
}
int Customer::getWaitForCartTime(){
	return waitForCartTime;
}
int Customer::getWaitForPayTime(){
	return waitForPayTime;
}
simpleTime Customer::getTimeSpent(){
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

//Hat ein Übergabewert, um diese für Simulationsversuche anzupassen oder um andere Werte zu Testen
int Customer::generateItemAmount(int i){
	//Seed auf static setzen, um einfache erreichbarkeit zu gewährleisten
	std::poisson_distribution<int> distribution(i);
	std::default_random_engine gen(123456);
	return distribution(gen);
}



