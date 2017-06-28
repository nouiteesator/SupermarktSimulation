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

Event::Event(simpleTime start, int prio, simpleTime end, int status, Customer customer, Supermarket &supermarket){
	this->startTime = start;
	this->endTime = end;
	this->prio = prio;
	this->status = status;
	this->customer = customer;
	this->supermarket = supermarket;
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
void Event::execute(list<Event> &eventList){
	//TODO implement
	cout << this->status << endl;
	list<Event>& eventReturn = eventList;
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
			//select cashbox
			//NICHT FERTIG DA fester for schleifen wert
			this->endTime = this->startTime;
			vector<Cashbox>* temp = this->supermarket.getCashBoxes();
			cout<<"case 4 address temp "<< temp <<endl;
			cout<<"case 4 address vector cashboxes;"<<this->supermarket.getCashBoxes()<<endl;
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
			this->supermarket.getSpecificCashbox(auswahl).addCustQueue(this->customer);
//new
			//temp[selection].getCustQueue().push(this->customer);

			cout<<"case 4 supermarket "<<&supermarket<<endl;
			cout<<"case 4 cashbox "<<&supermarket.getSpecificCashbox(0)<<endl;
			cout<< this->supermarket.getSpecificCashbox(auswahl).getCustQueue().size()<<" in case 4 laenge"<<endl;
			cout<<" address of case 4 "<<&this->supermarket.getSpecificCashbox(auswahl).getCustQueue()<<endl;
//old
	//		this->supermarket.getSpecificCashbox(auswahl).getCustQueue().push(this->customer);
			break;
		}
		case 5:  {
			//Customer in Turn for the Cashbox FAST FERTIG (Infos Entziehen)
			cout<<"case 5 ist kacke"<<endl;

			cout<<"case 5 supermarket "<<&supermarket<<endl;
			cout<<"case 5 cashbox "<<&supermarket.getSpecificCashbox(0)<<endl;
			int selectedCashboxIndex =this->customer.getCashAuswahl();
			selectedCashboxIndex = 0;
			//new
			vector<Cashbox>* blub = this->supermarket.getCashBoxes();
			cout<<"case 5 NEW SIZE "<<(*blub)[selectedCashboxIndex].getCustQueue().size()<<endl;
			cout<<"case 5 NEW  address blub!!!! "<<blub<<endl;
			//end
			cout<<this->supermarket.getSpecificCashbox(selectedCashboxIndex).getCustQueue().size()<<"laenge in 5"<<endl;
			cout<<"address of queue "<<&this->supermarket.getSpecificCashbox(selectedCashboxIndex).getCustQueue()<<endl;
			cout<<"case 5 2"<<endl;
			Cashbox temp = this->supermarket.getSpecificCashbox(selectedCashboxIndex);
			cout<<"case 5 3"<<endl;
			temp.handleCustomer();
			cout<<"case 5 4"<<endl;
			this->endTime = this->startTime;
			cout<<"case 5 5"<<endl;
			this->endTime.increaseSeconds((this->customer.getItemAmount() * 3) + 15);
			cout<<"case 5 6"<<endl;
			cout<<this->supermarket.getSpecificCashbox(selectedCashboxIndex).getCustQueue().empty()<<"blub"<<endl;
			if(this->supermarket.getSpecificCashbox(selectedCashboxIndex).getCustQueue().empty() != true){
				cout<<"case 5 in if 7"<<endl;
				//?? wouldn't be this->customer sufficent enough? 
				eventReturn.push_front(generateNextEvent(5,this->endTime,this->supermarket.getSpecificCashbox(selectedCashboxIndex).getCustQueue().front()));
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
	Event event(start,this->getPrio(),start,s,this->customer,this->supermarket);
	return event;
}

Event Event::generateNextEvent(int s, simpleTime &start, Customer &c){
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

Customer & Event::getCustomer(){
	return this->customer;
}

Supermarket Event::getSupermarket(){
	return supermarket;
}
