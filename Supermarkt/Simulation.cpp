// SImulation.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "simpleTime.h"
#include <vector>
#include <random>
#include <queue>
#include "Event.h" 
using namespace std;

void fetchInput(string, vector<int>*);
void testTime();
//TODO implement as Singleton
//TODO add getter/setter and stuff
class Simulation
{
public:
	Simulation();
	~Simulation();
	int getSeed();
	int customerStream();

private:
	simpleTime realTime; //the simulation time which is
						//set by events
	int doubleAmountOfCustomers; //0 -> nope 1 yes
	int itemSpawnMean;  
	int customerSpawnMean;
	int timeForSelectingOneItem;
	int cashboxServiceTimePerItem;
	int paymentTime;
	int simAmounts;
	int seed;

};
//TODO implement new Constructor 
Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

int Simulation::getSeed(){
	return seed;
}



//TODO implement

int Simulation::customerStream(){
cout << "customer stream was invoked " << endl;
//unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

std::poisson_distribution<int> distribution(10);
std::default_random_engine gen(getSeed());



int amountOfCustomer = distribution(gen);
cout << "amount of generated customer " << amountOfCustomer << endl;
//the times and intervalls when a new customer arrives
vector<int> arrivalDistribution(amountOfCustomer);

int arrivalRate = 60 / amountOfCustomer;
int tmp = arrivalRate;



for (int i = 0; i < amountOfCustomer; i++)
{
	arrivalDistribution[i] = tmp;
	tmp += arrivalRate;
}
	//only for debugging
	int counter = 0;

for  (int var : arrivalDistribution)
{

cout << "arrvial of " << counter << " value  " << var << endl;
counter++;
}
return amountOfCustomer;

}


/*======================================================================
==============================MAIN======================================
======================================================================*/

int main(int argc, char** argv)
{

	//get the file as parameter so a different file can be used
	string file = "Inputfile.txt";
	std::vector<int> inputParams; 
	fetchInput(file,&inputParams);
	
	
	//debug test whether this does work
	Simulation s;
	
	
	
	priority_queue<Event, vector<Event>,greater<Event>> pq;
	pq.emplace(simpleTime(8,0,0),2,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(8,0,0),1,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(8,0,0),3,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(7,0,0),2,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(7,0,0),7,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(8,0,1),1,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(8,1,0),1,simpleTime(9,0,0),3);
	pq.emplace(simpleTime(9,0,0),1,simpleTime(9,0,0),3);

	Event tmp =pq.top();
	cout<< tmp.getStartTime().toString()<<endl;

	while(!pq.empty()){
		Event e = pq.top();
		cout<<"start zeit "<<e.getStartTime().toString()<<" prio:"<<e.getPrio()<<endl;
		pq.pop();
	}


	
	    
	//test priority queue with simpletime WORKS!!!!!!!!!!!!!!!!!!!!!
	/*	priority_queue<simpleTime,vector<simpleTime>, greater<simpleTime> > pq;
	pq.emplace(simpleTime(8,0,0));
	pq.emplace(simpleTime(9,0,0));
	pq.emplace(simpleTime(10,0,0));
	pq.emplace(simpleTime(7,0,0));
	pq.emplace(simpleTime(8,0,0));
	pq.emplace(simpleTime(6,0,0));
	while(!pq.empty()){
		simpleTime st = pq.top();
		cout<<"start zeit "<<st.toString()<<endl;
		pq.pop();
	}
	//END TEST of priority queue
	*/

	
	
}


//read the input file and fetch all arguments into the params array
void fetchInput(string pFilePath,vector<int>* pInputParams){
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
//================================================================================================================
//===========================================only for test purposes===============================================
//================================================================================================================
void testTime(){
	simpleTime stContainer[] = { simpleTime(2, 58, 1), simpleTime(2, 58, 1), simpleTime(2, 58, 0), simpleTime(2, 57, 1), simpleTime(1, 58, 1), simpleTime(2, 58, 2), simpleTime(2, 59, 1), simpleTime(3, 58, 1) };
	simpleTime st(2, 58, 1);
	simpleTime same(2, 58, 1);
	simpleTime lessSecond(2, 58, 0);
	simpleTime lessMinute(2, 57, 1);
	simpleTime lessHour(1, 58, 1);
	simpleTime greaterS(2, 58, 2);
	simpleTime greaterM(2, 59, 1);
	simpleTime greaterH(3, 58, 1);

	int counter = 0;
	for (simpleTime var : stContainer)
	{
		cout << "counter: " << counter << " same: " << (st == var) << " less: " << (st < var) << " greater " << (st>var) << endl;
		counter++;
	}
	st.increaseSeconds(5);
	cout << "added five seconds expect 2, 58,6: " << st.toString() << endl;
	st.increaseSeconds(55);
	cout << "added five seconds expect 2, 59,1: " << st.toString() << endl;
	st.increaseSeconds(70);
	cout << "added five seconds expect 3, 0,11: " << st.toString() << endl;

}