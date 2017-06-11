#include "Event.h"
#include <iostream>

Event::Event(simpleTime start, int priority, simpleTime end, int stat):startTime(start), prio(priority), endTime(end),
status(stat){}
/* does not work yet
Event::Event(simpleTime start, int priority,int stat){
	std::cout<<start.toString()<<std::endl;
	simpleTime end(start.getHours(), start.getMinutes(), start.getSeconds());
	Event(start, priority, end, stat);
}*/

//TODO
void Event::execute(){
	//TODO implement
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
