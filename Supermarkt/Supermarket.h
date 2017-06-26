#pragma once
#include <queue>
#include <list>
#include <vector>
#include "Customer.h"
#include "simpleTime.h"
#include "Cashbox.h"

class Supermarket
{
public:
	Supermarket(int, simpleTime, simpleTime);
	Supermarket();
	~Supermarket();
	int getCustomerArrived();
	int getCustomerPaid();
	int getAvailableCarts();
	queue<Customer> getCustWaitForCart();
	vector<Cashbox> getCashBoxes();
	simpleTime getOpenTime();
	simpleTime getCloseTime();
	simpleTime getActualCloseTime();
	list<Customer> getAllCustomer();
	void addCustomerArrived(int);
	void addCustomerPaid(int);
	void setAvailableCarts(int);
	void addCustWaitForCart(Customer);
	void setCashBoxes(int);
	void setOpenTime(simpleTime);
	void setCloseTime(simpleTime);
	void setActualCloseTime(simpleTime);
	void addAllCustomer(Customer);
	void deleteCustWaitForCart();
	Cashbox getSpecificCashbox(int);
	bool getIsOpen();
	void setIsOpen(bool);
	void takeCart();
	void returnCart();
	bool getRushHour();
	void setRushHour(bool);
	


private:
	int customerArrived;
	int customerPaid;
	int availableCarts;
	queue<Customer> custWaitForCart;
	vector<Cashbox> cashBoxes;
	simpleTime openTime;
	simpleTime closeTime;
	simpleTime actualCloseTime;
	list<Customer> allCustomer;
	bool isOpen;
	bool rushHour;
};

