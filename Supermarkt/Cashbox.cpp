#include "Cashbox.h"
#include "stdafx.h"
#include "Customer.h"
#include <queue>
#include <list>

//Iterator

std::list<int>:: iterator it;

//Konstruktoren

Cashbox::Cashbox(int i):custServed(0),cashBoxUsed(0),cashUsed(false),custQueue(),useTime(simpleTime(0,0,0)){
	this->cashBoxID = i;
}

Cashbox::Cashbox(){
		
}
Cashbox::~Cashbox(){
	
}

//getter

int Cashbox::getCashBoxID(){
	return this->cashBoxID;
}
int Cashbox::getCashBoxUsed(){
	return this->cashBoxUsed;
}
int Cashbox::getCustServed(){
	return this->custServed;
}
bool Cashbox::getCashUsed(){
	return this->cashUsed;
}
queue<Customer>& Cashbox::getCustQueue(){
	return this->custQueue;
}
Customer& Cashbox::getCustQueueFirst(){
	return this->custQueue.front();
}
simpleTime& Cashbox::getUseTime(){
	return this->useTime;
}

//setter

void Cashbox::addCustServed(){
	this->custServed += 1;
}
void Cashbox::setCashBoxUsed(int i){
	this->cashBoxUsed = i;
}
void Cashbox::setCashUsed(bool i){
	this->cashUsed = i;
}
void Cashbox::addCustQueue(Customer i){
	this->custQueue.push(i);
}
void Cashbox::deleteCustQueue(){
	this->custQueue.pop();
}

//Methoden

void Cashbox::handleCustomer(){
	this->custQueue.pop();
	addCustServed();
}
