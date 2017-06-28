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

Event::Event(simpleTime start, int prio, simpleTime end, int status, Customer customer){
	this->startTime = start;
	this->endTime = end;
	this->prio = prio;
	this->status = status;
	this->customer = customer;
	//this->supermarket = supermarket;
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
	cout << this->status << endl;
	list<Event>& eventReturn = eventList;
	switch(status){
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
		case 2:{
			//Customer gets Cart FERTIG
			endTime = startTime;
			supermarket->takeCart();
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
			//select cashbox
			//NICHT FERTIG DA fester for schleifen wert
			this->endTime = this->startTime;
			vector<Cashbox>* temp = supermarket->getCashBoxes();
			int low = 99;
			int auswahl = 99;
			for(int i = 0;i < 3; i++){
				if((*temp)[i].getCustQueue().size() < low || low == 99){
					low = (*temp)[i].getCustQueue().size();
					auswahl = i;
					this->customer.setCashAuswahl(i);
				}
			}
			int selection = customer.getCashAuswahl();
			if((*temp)[this->customer.getCashAuswahl()].getCustQueue().empty() == true){
				eventReturn.push_front(generateNextEvent(5,this->endTime));	
			}
			Cashbox *cashBox = supermarket->getSpecificCashbox(auswahl);
			cout<< "casd 4 cashbox address "<<cashBox<<endl;
			Cashbox *cashBox2 = &(*temp)[auswahl];
			cout<< "casd 4 cashbox22222 address "<<cashBox2<<endl;
			cashBox->addCustQueue(this->customer);
//new
			//temp[selection].getCustQueue().push(this->customer);

//old
	//		this->supermarket.getSpecificCashbox(auswahl).getCustQueue().push(this->customer);
			break;
		}
		case 5:  {
			//Customer in Turn for the Cashbox FAST FERTIG (Infos Entziehen)
			int selectedCashboxIndex =this->customer.getCashAuswahl();
			//todo delete
			selectedCashboxIndex = 0;
			//new
			vector<Cashbox>* cashboxVector = supermarket->getCashBoxes();
			Cashbox *selectedCashbox =  &(*cashboxVector)[selectedCashboxIndex];

			//end	
			Cashbox *temp = supermarket->getSpecificCashbox(selectedCashboxIndex);
			cout<<"case 5 3"<<endl;
			temp->handleCustomer();
			cout<<"case 5 4"<<endl;
			this->endTime = this->startTime;
			cout<<"case 5 5"<<endl;
			this->endTime.increaseSeconds((this->customer.getItemAmount() * 3) + 15);
			cout<<"case 5 6"<<endl;
			cout<<supermarket->getSpecificCashbox(selectedCashboxIndex)->getCustQueue().empty()<<"blub"<<endl;
			if(supermarket->getSpecificCashbox(selectedCashboxIndex)->getCustQueue().empty() != true){
				cout<<"case 5 in if 7"<<endl;
				//?? wouldn't be this->customer sufficent enough? 
				eventReturn.push_front(generateNextEvent(5,this->endTime,this->customer));
				cout<<"case 5 8 before break"<<endl;
				break;
			}
			cout<<"case 5 shouldn t reach"<<endl;
			eventReturn.push_front(generateNextEvent(6,this->endTime));
			cout<<"case 5 shouldn t reach part 2"<<endl;
			break;
		}
		case 6:{
			//Customer pays and leaves Supermarket
			this->endTime = this->startTime;
			supermarket->addCustomerPaid(1);
			supermarket->returnCart();
			if(supermarket->getCustWaitForCart().empty() != true){
				eventReturn.push_front(generateNextEvent(2,this->endTime,this->customer));
				supermarket->getCustWaitForCart().pop();
			}
			break;
		}
		case 10:{
			//Supermarket opens
			supermarket->setIsOpen(true);
			this->endTime = this->startTime;
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
