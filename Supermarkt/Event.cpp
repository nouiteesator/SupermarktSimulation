#include "Event.h"
#include "Cashbox.h"
#include <cstdlib>
#include <stddef.h>
#include <list>
#include <cstddef>
#include <iostream>
#include "Simulation.h"

using namespace std;

Event::Event(){
}

Event::Event(simpleTime start, int prio, simpleTime end, int status, Customer customer){
	this->startTime = start;
	this->endTime = end;
	this->prio = prio;
	this->status = status;
	this->customer = customer;
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
void Event::execute(list<Event> &eventList, Supermarket *supermarket){
	//TODO implement
	list<Event>& eventReturn = eventList;
	switch(status){
		//CUSTOMER ARRIVES		
		case 1:	{
			//Customer arrives FERTIG
			supermarket->addCustomerArrived(1);
			supermarket->addAllCustomer(this->customer);
			if(supermarket->getAvailableCarts() == 0){
				if(supermarket->getCustWaitForCart().size() > 30){
					if(rand()%100 < 34){
						break;
					}else{	
						supermarket->addCustWaitForCart(customer);
					}
				}else{	
					supermarket->addCustWaitForCart(customer);
				}
			}else{
				supermarket->takeCart();
				eventReturn.push_front(generateNextEvent(3,this->endTime,customer));
			}
			break;
		}
		//CUSTOMER PICKS A CART
		case 2:{
			//Customer gets Cart FERTIG
			endTime = startTime;
			supermarket->takeCart();
			eventReturn.push_front(generateNextEvent(3,endTime));
			break;
		}
		//CUSTOMER PICKS ITEMS
		case 3:{
			//Customer picking Items(Use of Generate Items first)
			//Werte müssen von dem file noch übernommen werden: FAST FERTIG (Infos entziehen
			int a;
			this->endTime = this->startTime;
			int itemChooseTime = Simulation::itemZeit;
			this->endTime.increaseSeconds(this->customer.getItemAmount() * itemChooseTime/*hier*/);			
			eventReturn.push_front(generateNextEvent(4,this->endTime));
			break;
		}
		//CUSTOMER SELECTS CASHBOX
		case 4: {
			//select cashbox
			//NICHT FERTIG DA fester for schleifen wert
			this->endTime = this->startTime;
			vector<Cashbox>* temp = supermarket->getCashBoxes();
			int low = 99;
			int auswahl = 99;
			int cashboxAmount = temp->size();
			for(int i = 0;i < cashboxAmount; i++){
				if((*temp)[i].getCustQueue().size() < low || low == 99){
					low = (*temp)[i].getCustQueue().size();
					auswahl = i;
					this->customer.setCashAuswahl(i);
				}
			}
			if((*temp)[this->customer.getCashAuswahl()].getCustQueue().empty() == true){
				eventReturn.push_front(generateNextEvent(5,this->endTime));	
			}
			Cashbox *cashBox = supermarket->getSpecificCashbox(auswahl);
			Cashbox *cashBox2 = &(*temp)[auswahl];
			cashBox->addCustQueue(this->customer);
			break;
		}
		//CUSTOMER ARRIVES AND CHECKS IF HE CAN IMMEDIATLY PAY
		case 5:  {
			//Customer in Turn for the Cashbox FAST FERTIG (Infos Entziehen)
			int selectedCashboxIndex =this->customer.getCashAuswahl();
			Cashbox *temp = supermarket->getSpecificCashbox(selectedCashboxIndex);
			temp->handleCustomer(); 
			this->endTime = this->startTime;
			int payTimeProduct = Simulation::zeitProProdukt;
			int fixPayTime =Simulation::bezahlen;
			this->endTime.increaseSeconds((this->customer.getItemAmount() * payTimeProduct) + fixPayTime);
			//checking, if the Queue of Customer of the selected Cashbox is filled to generate the next Event for the Customer
			if(supermarket->getSpecificCashbox(selectedCashboxIndex)->getCustQueue().empty() != true){
				//generate Event for Customer that is behind this->Customer in the Cashbox-Queue. 
				eventReturn.push_front(generateNextEvent(5,this->endTime,temp->getCustQueue().front()));
				break;
			}
			eventReturn.push_front(generateNextEvent(6,this->endTime));
			break;
		}
		//CUSTOMER PAYS
		case 6:{
			this->endTime = this->startTime;
			supermarket->addCustomerPaid(1);
			supermarket->returnCart();
			//Checking if the queue for getting a Cart is filled. You can use supermarket->getAvailableCarts() == 0 too
			if(supermarket->getCustWaitForCart().empty() != true){
				//generate Event for the Customer in the front of the Cart Queue, if the queue is filled
				eventReturn.push_front(generateNextEvent(2,this->endTime,supermarket->getCustWaitForCart().front()));
				supermarket->getCustWaitForCart().pop();
			}
			break;
		}
		case 10:{
			//Supermarket opens
			supermarket->setIsOpen(true);
			this->endTime = this->startTime;
			cout << "how to access static fields in event "<<Simulation::kunden<<endl;
			break;
		}
		case 11:{
			//Supermarket closes
			supermarket->setIsOpen(false);
			this->endTime = this->startTime;
			break;
		}
		case 12:{
			//Rushhour
			supermarket->setRushHour(true);
			this->endTime = this->startTime;
			this->endTime.increaseMinutes(120);
			break;
		}
	}
}
simpleTime& Event::getStartTime(){
	return startTime;
}
int Event::getPrio(){
	return prio;
}


std::string Event::toString(){
	std::string retString = startTime.toString()+" prio:"+std::to_string(prio)+" "+endTime.toString()+" status:"+std::to_string(status);
	return  retString;
}

simpleTime& Event::getEndTime(){
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

Event Event::generateNextEvent(int s, simpleTime &start){
	Event event(start,this->getPrio(),start,s,this->customer);
	return event;
}

Event Event::generateNextEvent(int s, simpleTime &start, Customer &c){
	Event newEvent(start,this->getPrio()+rand() %10,start,s,c);
	return newEvent;
}

//Operator

bool Event::operator==(const Event &e)const{
	
	if (startTime == e.startTime && prio == e.prio && endTime == e.endTime, status == e.status){
		return true;
	}
	return false;
}

Customer & Event::getCustomer(){
	return this->customer;
}
