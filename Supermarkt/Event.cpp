#include "Event.h"
#include "Cashbox.h"
#include <iostream>
#include <cstdlib>
#include <stddef.h>
#include <list>
#include <cstddef>

using namespace std;

Event::Event(){
}

Event::Event(simpleTime start, int prio, simpleTime end, int status, Customer customer, Supermarket supermarket){
	this->startTime = start;
	this->endTime = end;
	this->prio = prio;
	this->status = status;
	this->customer = customer;
	this->supermarket = supermarket;
}
Event::~Event(){
}
/* does not work yet
Event::Event(simpleTime start, int priority,int stat){
	std::cout<<start.toString()<<std::endl;
	simpleTime end(start.getHours(), start.getMinutes(), start.getSeconds());
	Event(start, priority, end, stat);
}*/

//TODO
list<Event> Event::execute(){
	//TODO implement
	cout << this->status << endl;
	list<Event> eventReturn;
	switch(status){
		case 1:	{
		
			//Customer arrives FERTIG
			this->supermarket.addCustomerArrived(1);
			this->supermarket.addAllCustomer(this->customer);
			if(this->supermarket.getAvailableCarts() == 0){
				if(this->supermarket.getCustWaitForCart().size() > 30){
					if(rand()%100 < 34){
						break;
					}else{	
						supermarket.addCustWaitForCart(customer);
					}
				}else{	
					supermarket.addCustWaitForCart(customer);
				}
			}else{
				supermarket.takeCart();
				eventReturn.push_front(generateNextEvent(3,this->endTime,customer));
			}
			break;
		}
		case 2:{
			//Customer gets Cart FERTIG
			endTime = startTime;
			supermarket.takeCart();
			eventReturn.push_front(generateNextEvent(3,endTime));
			break;
		}
		case 3:{
			//Customer picking Items(Use of Generate Items first)
			//Werte müssen von dem file noch übernommen werden: FAST FERTIG (Infos entziehen
			int a;
			a = this->customer.generateItemAmount(10/*hier*/);
			this->customer.setItemAmount(a);
			this->endTime = this->startTime;
			this->endTime.increaseSeconds(this->customer.getItemAmount() * 10/*hier*/);			
			eventReturn.push_front(generateNextEvent(4,this->endTime));
			break;
		}
		case 4: {
			//Customer choosing Cashbox FERTIG
			this->endTime = this->startTime;
			vector<Cashbox> temp = this->supermarket.getCashBoxes();
			int low = 99;
			int auswahl = 99;
			for(int i = 0;i < 3; i++){
				if(temp[i].getCustQueue().size() < low || low == 99){
					low = temp[i].getCustQueue().size();
					auswahl = i;
					this->customer.setCashAuswahl(i);
				}
			}
			if(temp[this->customer.getCashAuswahl()].getCustQueue().empty() == true){
				eventReturn.push_front(generateNextEvent(5,this->endTime));	
			}
			this->supermarket.getSpecificCashbox(auswahl).addCustQueue(this->customer);
			break;
		}
		case 5:  {
			//Customer in Turn for the Cashbox FAST FERTIG (Infos Entziehen)
			Cashbox temp = this->supermarket.getSpecificCashbox(this->customer.getCashAuswahl());
			temp.handleCustomer();
			this->endTime = this->startTime;
			this->endTime.increaseSeconds((this->customer.getItemAmount() * 3) + 15);
			if(this->supermarket.getSpecificCashbox(this->customer.getCashAuswahl()).getCustQueue().empty() != true){
				eventReturn.push_front(generateNextEvent(5,this->endTime,this->supermarket.getSpecificCashbox(this->customer.getCashAuswahl()).getCustQueue().front()));
			}
			eventReturn.push_front(generateNextEvent(6,this->endTime));
			break;
		}
		case 6:{
			//Customer pays and leaves Supermarket
			this->endTime = this->startTime;
			this->supermarket.addCustomerPaid(1);
			this->supermarket.returnCart();
			if(this->supermarket.getCustWaitForCart().empty() != true){
				eventReturn.push_front(generateNextEvent(2,this->endTime,this->supermarket.getCustWaitForCart().front()));
				this->supermarket.getCustWaitForCart().pop();
			}
			break;
		}
		case 10:{
			//Supermarket opens
			this->supermarket.setIsOpen(true);
			this->endTime = this->startTime;
			break;
		}
		case 11:{
			//Supermarket closes
			this->supermarket.setIsOpen(false);
			this->endTime = this->startTime;
			break;
		}
		case 12:{
			//Rushhour
			this->supermarket.setRushHour(true);
			this->endTime = this->startTime;
			this->endTime.increaseMinutes(120);
			break;
		}
	}
	return eventReturn;
}
simpleTime Event::getStartTime(){
	return startTime;
}
int Event::getPrio(){
	return prio;
}


std::string Event::toString(){
	std::string retString = startTime.toString()+" prio:"+std::to_string(prio)+" "+endTime.toString()+" status:"+std::to_string(status);
	return  retString;
}

simpleTime Event::getEndTime(){
	return this->endTime;
}

//is used to insert the events at the right spot
//comparison between start time and if needed priority 
//if events are equal returns true
bool Event::operator>(const Event &e)const{
	if(startTime > e.startTime){
		return true;
	}
	if(startTime < e.startTime){
		return false;
	}
	//start time must be the same
	//check now by prio
	if(prio < e.prio){
		return false;
	}
	//prio is higher -> less important || prio's are equal
	return true;
}

bool Event::operator<(const Event &e)const{
	if(startTime > e.startTime){
		return false;
	}
	if(startTime < e.startTime){
		return true;
	}
	//start time must be the same
	//check now by prio
	if(prio < e.prio){
		return true;
	}
	//prio is higher -> less important || prio's are equal
	return false;
}

Event Event::generateNextEvent(int s, simpleTime start){
	Event event(start,this->getPrio(),start,s,this->customer,this->supermarket);
	return event;
}

Event Event::generateNextEvent(int s, simpleTime start, Customer c){
	Event newEvent(start,this->getPrio()+rand() %10,start,s,c,this->supermarket);
	return newEvent;
}

//Operator

bool Event::operator==(const Event &e)const{
	
	if (startTime == e.startTime && prio == e.prio && endTime == e.endTime, status == e.status){
		return true;
	}
	return false;
}
