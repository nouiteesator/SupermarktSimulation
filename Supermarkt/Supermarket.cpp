#include "stdafx.h"
#include "Supermarket.h"
#include <list>
#include <queue>
#include "Customer.h"
#include "simpleTime.h"
#include "Cashbox.h"
#include <iostream>
//Iteratoren für Lists

std::list<Customer>:: iterator ic;

//constructoren



Supermarket::Supermarket(int c, simpleTime s, simpleTime e, int pAvailableCarts):customerArrived(0),customerPaid(0),
	availableCarts(pAvailableCarts),custWaitForCart(),allCustomer(), isOpen(false),cashBoxes()
{
	this->closeTime = e;
	this->openTime = s;
	for(int i; i < c; i++){
		cashBoxes.push_back(Cashbox(i + 1));
	}
	cout<<"address of vector in Supermarket constructor "<<&cashBoxes<<endl;

}

Supermarket::Supermarket(){
	cout<<"standard constructor of Supermarketis invoked"<<this<<endl;
}


Supermarket::~Supermarket(){
}

//getter

int Supermarket::getCustomerArrived(){
	return this->customerArrived;
}
int Supermarket::getCustomerPaid(){
	return this->customerPaid;
}
int Supermarket::getAvailableCarts(){
	return this->availableCarts;
}
queue<Customer>& Supermarket::getCustWaitForCart(){
	return this->custWaitForCart;
}
list<Customer>& Supermarket::getAllCustomer(){
	return this->allCustomer;
}
vector<Cashbox>* Supermarket::getCashBoxes(){

	cout<<"in get cashBoxes addres " <<&cashBoxes<<endl;
	return &cashBoxes;
}
simpleTime& Supermarket::getOpenTime(){
	return this->openTime;
}
simpleTime& Supermarket::getCloseTime(){
	return this->closeTime; 
}
simpleTime& Supermarket::getActualCloseTime(){
	return this->actualCloseTime;
}
Cashbox& Supermarket::getSpecificCashbox(int i){
	return this->cashBoxes[i];
}
bool Supermarket::getIsOpen(){
	return this->isOpen;
}
bool Supermarket::getRushHour(){
	return this->rushHour;
}

//setter

void Supermarket::addCustomerArrived(int i){
	this->customerArrived += i;
}
void Supermarket::addCustomerPaid(int i){
	this->customerPaid += i;
}
void Supermarket::setAvailableCarts(int i){
	this->availableCarts = i;
}
void Supermarket::addAllCustomer(Customer& i){
	this->allCustomer.push_back(i);
}
void Supermarket::addCustWaitForCart(Customer& i){
	this->custWaitForCart.push(i);
}
void Supermarket::setCashBoxes(int i){
	for(int j; j<i;j++){
		Cashbox temp(j);
		this->cashBoxes.push_back(temp);
	}
}
void Supermarket::setOpenTime(simpleTime i){
	this->openTime = i;
}
void Supermarket::setCloseTime(simpleTime i){
	this->closeTime = i;
}
void Supermarket::setActualCloseTime(simpleTime i){
	this->actualCloseTime = i;
}
void Supermarket::deleteCustWaitForCart(){
	this->custWaitForCart.pop();
}
void Supermarket::setIsOpen(bool i){
	this->isOpen = i;
}
void Supermarket::takeCart(){
	this->availableCarts -= 1;
}
void Supermarket::returnCart(){
	this->availableCarts += 1;
}
void Supermarket::setRushHour(bool i){
	this->rushHour = i;
}



