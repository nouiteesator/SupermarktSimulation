// SImulation.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
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
	realTime(0,0,0),distribution(10),eventQueue()
{
	Simulation::kassen = inputParams[0];
	Simulation::wagen = inputParams[1];
	Simulation::dauer = inputParams[2];
	//Simulation::rushhour = inputParams[3];
	Simulation::itemWert = inputParams[4];
	Simulation::kunden = inputParams[5];
	Simulation::itemZeit = inputParams[6];
	Simulation::zeitProProdukt = inputParams[7];
	Simulation::bezahlen = inputParams[8];
	Simulation::simulationen = inputParams[9];
	Simulation::seed1 = inputParams[10];
	Simulation::seed2 = inputParams[11];
	gen.seed(seed1);
	
	this->preperation();
	this->runQueue();
}

Simulation::~Simulation()
{
}

int Simulation::getSeed(){
	return seed;
}


int Simulation::customerStream(int i){
	cout << "customer stream was invoked " << endl;
	int amountOfCustomer = distribution(gen);
	cout << "amount of generated customer " << amountOfCustomer << endl;
	return amountOfCustomer;

}

void Simulation::generateCustomer(int a, simpleTime start){ //ja ich weiß, kann man schöner machen
	int arrivalrate = 60 / a;
	simpleTime temp2 = start;
	int temp = 0;
	for(int i = 0; i < a;i++){
		temp += arrivalrate;
		temp2.increaseSeconds(temp);
		Customer newCustomer(temp2);
		int j = rand() %100 + 1;
		Event e = generateEvent(temp2,j,temp2,1,newCustomer);
		eventQueue.addEventQueue(e);
	}
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
	cout<<"calling preperation "<<endl;
	Event e(simpleTime(0,0,0),1,simpleTime(0,0,0),10,Customer());
	eventQueue.addEventQueue(e);
	eventQueue.addEventQueue(Event(simpleTime(0+Simulation::dauer,0,0),1,simpleTime(0+Simulation::dauer,0,0),11,Customer()));
	eventQueue.addEventQueue(Event(simpleTime(0+Simulation::dauer-2,0,0),1,simpleTime(0+Simulation::dauer-2,0,0),12,Customer()));
	//it was never requestet whether there 
	//is a rushhour or not
	//theese loops are used to generate all customers 
	// not so clever because it jams our queue

	//simpleTime temp2(0+Simulation::dauer-2,0,0);
	//debug
	simpleTime temp2(0,1,0);
	while(realTime < temp2){
		generateCustomer(customerStream(Simulation::kunden),realTime);
		realTime.increaseMinutes(1);
	}
	/*
	while(realTime < simpleTime(Simulation::dauer,0,0)){
		generateCustomer(customerStream(Simulation::kunden*2),realTime);
		realTime.increaseMinutes(1);
	}
	*/
	realTime = simpleTime(0,0,0);
}
simpleTime Simulation::getRealTime(){
	return this->realTime;
}
void Simulation::setRealTime(simpleTime i){
	this->realTime = i;
}
Eventhandler& Simulation::getEventhandler(){
	return this->eventQueue;
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
	Event e = eventQueue.getEventQueue().top();
	cout << e.toString() << endl;
	while(eventQueue.getEventQueue().empty() != true){
		cout << eventQueue.getEventQueue().size() << endl;
		eventQueue.executeEvent(&supermarket);
	}
	cout<<"finish"<<endl;
	cout<<"customer arrived "<<supermarket.getCustomerArrived()<<endl;
}
