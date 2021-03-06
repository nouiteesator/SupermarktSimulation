#include "Supermarket.h"
#include "simpleTime.h"
#include "Eventhandler.h"
#include "Event.h"
#include <string>
#include <vector>
#include <random>
//ulimit -c unlimited 
class Simulation
{
	
	
public:
	static std::string file;
	static std::vector<int> inputParams;
	static int kassen;
	static int wagen;
	static int dauer;
	static int rushhour;
	static int itemWert;
	static int itemZeit;
	static int kunden;
	static int zeitProProdukt;
	static int bezahlen;
	static int simulationen;
	static int seed1;
	static int seed2;

	Simulation();
	Simulation(bool);
	~Simulation();
	int getSeed();
	int customerStream();
	Supermarket& getSupermarket();
	void preperation();
	simpleTime getRealTime();
	void fetchInput(string, vector<int>*);
	void testTime();
	void generateCustomer(int, simpleTime);
	Event generateEvent(simpleTime, int, simpleTime&, int, Customer&);
	void setAmount(int);
	void runQueue();
	int generateItemAmount();
	void generateReport();

private:
	simpleTime realTime; //the simulation time which is set by events
	int doubleAmountOfCustomers; //0 -> nope 1 yes
	int itemSpawnMean;  
	int customerSpawnMean;
	int timeForSelectingOneItem;
	int cashboxServiceTimePerItem;
	int paymentTime;
	int simAmounts;
	int seed;
	int amount;
	Supermarket supermarket;
	Eventhandler eventQueue;
	simpleTime real;
	std::poisson_distribution<int> distribution;
	std::poisson_distribution<int> itemPoisson;
	default_random_engine gen;
	default_random_engine genForItems;

};
