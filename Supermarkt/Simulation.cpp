// SImulation.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "simpleTime.h"
#include <vector>
#include <queue>
#include "Event.h"
#include <stdlib.h>
#include "Eventhandler.h"
#include "Simulation.h"

using namespace std;

string Simulation::file = "Inputfile.txt";
vector<int> Simulation::inputParams;
int Simulation::kassen;
int Simulation::wagen;
int Simulation::dauer;
int Simulation::itemWert;
int Simulation::itemZeit;
int Simulation::kunden;
int Simulation::zeitProProdukt;
int Simulation::bezahlen;
int Simulation::simulationen;
int Simulation::seed1;
int Simulation::seed2;


Simulation::Simulation(){
	fetchInput(Simulation::file,&Simulation::inputParams);
	Simulation(true);
}
Simulation::Simulation(bool i):supermarket(Simulation::inputParams[0],simpleTime(0,0,0),simpleTime(0+Simulation::inputParams[2],0,0),Simulation::inputParams[1]),
	realTime(0,0,0),eventQueue(),distribution(inputParams[5]),itemPoisson(inputParams[4])
{
	Simulation::kassen = inputParams[0];
	Simulation::wagen = inputParams[1];
	Simulation::dauer = inputParams[2];
	//Simulation::rushhour = inputParams[3];
	Simulation::itemWert = inputParams[4];
	cout<< "item mittelwert "<< itemWert <<endl;
	Simulation::kunden = inputParams[5];
	Simulation::itemZeit = inputParams[6];
	Simulation::zeitProProdukt = inputParams[7];
	Simulation::bezahlen = inputParams[8];
	Simulation::simulationen = inputParams[9];
	Simulation::seed1 = inputParams[10];
	Simulation::seed2 = inputParams[11];
	gen.seed(seed1);
	genForItems.seed(seed2);

	this->preperation();
	this->runQueue();
}

Simulation::~Simulation()
{
}

int Simulation::getSeed(){
	return seed;
}


int Simulation::customerStream(){
	int amountOfCustomer = distribution(gen);
	return amountOfCustomer;

}

void Simulation::generateCustomer(int a, simpleTime start){ //ja ich wei�, kann man sch�ner machen
	int arrivalrate = 60 / a;
	simpleTime temp2 = start;
	int temp = 0;
	for(int i = 0; i < a;i++){
		temp += arrivalrate;
		temp2.increaseSeconds(temp);
		int itemAmount = generateItemAmount();
		//nobody goes into a store and buys nothing
		//but waits at the cashbox for at least 10 secs
		if( itemAmount <1){
			itemAmount =1;
		}
		Customer newCustomer(temp2, itemAmount);
		int j = rand() %100 + 1;
		Event e = generateEvent(temp2,j,temp2,1,newCustomer);
		eventQueue.addEventQueue(e);
	}
}

int Simulation::generateItemAmount(){
	return itemPoisson(genForItems);
}
void Simulation::setAmount(int i){
	this->amount = i;
}

Event Simulation::generateEvent(simpleTime s, int p, simpleTime& e, int st, Customer &c){
	Event retE(s,p,e,st,c);
	return retE;
}

Supermarket& Simulation::getSupermarket(){
	return this->supermarket;
}
void Simulation::preperation(){
	//start event
	Event e(simpleTime(0,0,0),1,simpleTime(0,0,0),10,Customer());
	eventQueue.addEventQueue(e);
	//close Event 
	eventQueue.addEventQueue(Event(simpleTime(0+Simulation::dauer,0,0),1,simpleTime(0+Simulation::dauer,0,0),11,Customer()));
	//double amount of customer event
	eventQueue.addEventQueue(Event(simpleTime(0+Simulation::dauer-2,0,0),1,simpleTime(0+Simulation::dauer-2,0,0),12,Customer()));
	//theese loops are used to generate all customers 
	simpleTime temp2(0+Simulation::dauer-2,0,0);
	while(realTime < temp2){
		generateCustomer(customerStream(),realTime);
		realTime.increaseMinutes(1);
	}
	while(realTime < simpleTime(Simulation::dauer,0,0)){
		generateCustomer(customerStream()*2,realTime);
		realTime.increaseMinutes(1);
	}
	realTime = simpleTime(0,0,0);
}
simpleTime Simulation::getRealTime(){
	return this->realTime;
}

//read the input file and fetch all arguments into the params array
void Simulation::fetchInput(string pFilePath,vector<int>* pInputParams){
	ifstream fileToRead(pFilePath);
	//is only used to extract the comments
	string tmp;
	int value;
	if (!fileToRead.is_open())
	{
		cout << "failed to open file" << endl;
		exit(EXIT_FAILURE);
	}
	while (fileToRead >> tmp >> value){
		cout<<tmp<<endl;
		cout<<value<<endl;
		pInputParams->push_back(value);
	}
	
}
//run as long as the queue is filled
//TODO set the real time
void Simulation::runQueue(){
	cout << eventQueue.getEventQueue().size() << endl;
	while(eventQueue.getEventQueue().empty() != true){
		Event e = eventQueue.getEventQueue().top();
		realTime = e.getEndTime();
		eventQueue.executeEvent(&supermarket);
	}
	cout<<"test how to acces static fields " <<kunden<<endl;
	cout<<"finish"<<endl;
	cout<< "last event at "<< realTime.toString()<<endl;
	cout<<"customer arrived "<<supermarket.getCustomerArrived()<<endl;
	cout<<"customer payed "<<supermarket.getCustomerPaid()<<endl;
	cout<<"customer left "<<supermarket.getCustomerArrived() - supermarket.getCustomerPaid()<<endl;
	for(int i; i < supermarket.getCashBoxes()->size(); i++){
		cout << "Kasse: " << i+1 << " Aktive Zeit: " << supermarket.getSpecificCashbox(i)->getUseTime().toString() << endl;
	}
	cout << supermarket.getAvailableCarts() << endl;
}
