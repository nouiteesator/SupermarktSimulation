#include "stdafx.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Event.h"
#include "simpleTime.h"
#include "Eventhandler.h"

//Konstruktoren

Eventhandler::Eventhandler(){
	
}
Eventhandler::~Eventhandler(){
	
}

//getter

priority_queue<Event, vector<Event>,greater<Event>>& Eventhandler::getEventQueue(){
	return eventQueue;
}
Event  Eventhandler::getfirstEvent(){
	return eventQueue.top();
}

//setter

void Eventhandler::addEventQueue(Event i){
	this->eventQueue.push(i);
}
void Eventhandler::deleteEventQueue(){
	eventQueue.pop();
}

//Funktionen

void Eventhandler::executeEvent(Supermarket *s){

	list<Event> temp;
	getfirstEvent().execute(temp,s);
	eventQueue.pop();
	if(temp.empty() == false){
	//why dont you use a while/for loop 
		if(temp.front() == temp.back()){
			eventQueue.push(temp.front());			
		}else{
			eventQueue.push(temp.front());
			eventQueue.push(temp.back());
		}
	}
}
