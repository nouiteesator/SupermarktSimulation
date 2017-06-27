#pragma once
#include <queue>
#include <vector>
#include "Event.h"
#include "simpleTime.h"

class Eventhandler{
	public:
		Eventhandler();
		~Eventhandler();
		priority_queue<Event, vector<Event>,greater<Event>> & getEventQueue();
		void addEventQueue(Event);
		void deleteEventQueue();
		Event getfirstEvent();
		void executeEvent();
		
	private:
		priority_queue<Event, vector<Event>,greater<Event>> eventQueue;
};
