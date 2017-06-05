// Supermarkt.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "simpleTime.h"
using namespace std;
int* fetchInput(string);
void testTime();
//TODO implement as Singleton
//TODO add getter/setter and stuff
class Simulation
{
public:
	Simulation();
	~Simulation();

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


//TODO implement
/*
int customerStream(){
cout << "customer stream was invoked " << endl;
unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
std::poisson_distribution<int> distribution(10);
std::default_random_engine gen(seed1);



int amountOfCustomer = distribution(gen);
cout << "amount of generated customer " << amountOfCustomer << endl;
vector<int> arrivalDistribution(amountOfCustomer);

int arrivalRate = 60 / amountOfCustomer;
int tmp = arrivalRate;

for (int i = 0; i < amountOfCustomer; i++)
{
arrivalDistribution[i] = tmp;
tmp += arrivalRate;
}
int counter = 0;

for each (int var in arrivalDistribution)
{

cout << "arrvial of " << counter << " value  " << var << endl;
counter++;
}
return amountOfCustomer;

}


*/

/*
==============================MAIN======================================
*/

int _tmain(int argc, _TCHAR* argv[])
{

	//get the file as parameter so a different file can be used
	string file = "Inputfile.txt";
	int *inputParams = fetchInput(file);
	cout << inputParams[0] << endl;
	
	
}


//read the input file and fetch all arguments into the params array
int* fetchInput(string filePath){

	ifstream fileToRead(filePath);
	//is only used to extract the comments
	string tmp;
	int value;
	//TODO maybe use a vector instead
	// so the size can be 
	//changed via variable
	int params[11];
	int counter = 0;
	if (!fileToRead.is_open())
	{
		cout << "failed to open file" << endl;
		exit(EXIT_FAILURE);
	}
	while (fileToRead >> tmp >> value){
		params[counter] = value;
		counter++;
	}
	cout << params[0] << endl;
	return params;
	
}
//only for test purposes
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
	for each (simpleTime var in stContainer)
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