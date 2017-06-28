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
	realTime(0,0,0),eventQueue(),distribution(inputParams[5]),itemPoisson(inputParams[4])
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
	genForItems.seed(seed2);

	this->preperation();
	this->runQueue();
	generateReport();
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

void Simulation::generateCustomer(int a, simpleTime start){ //ja ich weiß, kann man schöner machen
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
}




//=========================For Report========================
//the file which is used is Results.txt and lays in the same 
//folder as the other documents

/*
	customer
	XXXXwhich information do we want?
	XXXXamount of all customers
	XXXXamount of all customer who left
	XXXXamount of all customer who stayed and paid
	how long did a customer stayed -> average time; ->min time -> max Time


	cashboxes
	how many did each cashbox served as number and %
	how long was average lane length
	time of an empty queue

	supermarket
	XXXXwhen did it actually close

*/
void Simulation::generateReport(){

	int custArrived =supermarket.getCustomerArrived();
	list<Customer>allCustomer =supermarket.getAllCustomer();
	string reportPath ="Results.txt";
	simpleTime max(0,0,1);
	simpleTime min(99,0,1);
	simpleTime avg(0,0,0);
	simpleTime tmpComp(0,0,1);
	//set the report open for output operations and append results if 
	//file allready exists
	ofstream report (reportPath, ios::out | ios::app);
 	if (!report.is_open())
  	{
   		cerr<< "Error could not open the "<<reportPath<<" file "<<endl;
    	report.close();
    	return;
  	}
  	// 335 51 38
  		//get max and min value and average time for customer
  	for(std::list<Customer>::iterator it=allCustomer.begin(); it != allCustomer.end();it++){
  		 simpleTime spent = it->getTimeSpent();
  		 avg = avg+spent ;
  		 cout<< avg.toString()<<endl;
  		 if(spent > max){
  		 	max = spent;
  		 }
  		 if(spent < min && spent > tmpComp){
  		 	min =spent;
  		 }
  	}
  	int avgSec =avg.getSeconds();
  	int avgMinutes = avg.getMinutes();
  	int avgHours =avg.getHours();
  	cout<<"seconds "<<avgSec<<endl;;
  	cout<<"minutes "<<avgMinutes<<endl;;
  	cout<<"hours "<<avgHours<<endl;;
  	int totalSecs = avgSec +avgMinutes*60 +avgHours*60*60;
  	int avgSecs= totalSecs/supermarket.getCustomerPaid();
  	cout<< "cust paid "<<supermarket.getCustomerPaid()<<endl;
  	cout<< "average seconds "<<avgSecs<<endl;
  	simpleTime output(0,0,0);
  	output.increaseSeconds(avgSecs);

  	report<<"================Start of Simulation=========\n";
  	report<<"++++++++++++++++Eingabewerte++++++++++++++++\n";
  	report<<"Anzahl der Kassen "<<kassen<<"\n";
	report<< "Anzahl der Einkaufswagen "<<wagen<<"\n";
	report<<"Oeffnungsdauer "<<dauer<<"\n";
	report<<"Item itemMittelwert "<<itemWert<<"\n";
	report<<"Auwahlzeit fuer ein Produkt "<<itemZeit<<"\n";
	report<<"Kunden Mittelwert "<<kunden<<"\n";
	report<<"Kassenbedienzeit pro Produkt "<<zeitProProdukt<<"\n";
	report<<"Fixe bezahl Zeit "<<bezahlen<<"\n";
	report<<"Seed fuer die Kunden-Erstellung "<<seed1<<"\n";
	report<<"Seed fuer die Itemgenerierung "<<seed2<<"\n";

  	report<<"++++++++++++++++Ausgabewerte++++++++++++++++\n";
  	report<< "supermarket close time  "<< realTime.toString()<<"\n";
	report<<"customer arrived "<<custArrived<<"\n";
	report<<"customer payed "<<supermarket.getCustomerPaid()<<"\n";
	report<<"customer left "<<custArrived - supermarket.getCustomerPaid()<<"\n";
	report<<"customer min time spent "<<min.toString()<<"\n";
	report<<"customer max time spent  "<<max.toString()<<"\n";
	report<<"customer average time spent "<<output.toString()<<"\n";
		for(int i=0; i < supermarket.getCashBoxes()->size(); i++){
	 report<< "Kasse: " << i+1 << " Aktive Zeit: " << supermarket.getSpecificCashbox(i)->getUseTime().toString() << "\n";
	}  	


  		//here comes real data
  	report<<"====================+END OF SIMULATION==================\n";
  	report<<"\n";
  	report<<"\n";
  	report.close();	
}
 
