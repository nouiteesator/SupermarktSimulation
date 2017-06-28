#pragma once
#include "Customer.h"
#include "simpleTime.h"
#include <queue>
using namespace std;
class Cashbox{
	public:
		Cashbox();
		Cashbox(int);
		~Cashbox();
		void handleCustomer();
		int getCustServed();
		int getCashBoxID();
		int getCashBoxUsed();
		bool getCashUsed();
		queue<Customer>& getCustQueue();
		Customer& getCustQueueFirst();
		void addCustServed();
		void setCashBoxUsed(int);
		void setCashUsed(bool);
		void addCustQueue(Customer);
		void deleteCustQueue();
		simpleTime& getUseTime();
		
	private:
		int custServed;
		queue<Customer> custQueue;
		int cashBoxID;
		int cashBoxUsed;
		bool cashUsed;
		simpleTime useTime;
};
