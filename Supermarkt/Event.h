#pragma once
#include "simpleTime.h"
#include <string>

//TODO review EXECUTE()
class Event{

public:
	Event(simpleTime, int, simpleTime, int);
	//TODO
	//Event(simpleTime, int, int); //when endtime is omitted endtime = starttime
	void execute(); //needs to be reviewed 
	bool operator>(const Event &e)const;
	bool operator<(const Event &e)const;
	simpleTime getStartTime();
	int getPrio();
	std::string toString();

private:
	simpleTime startTime;
	int prio;// the lower the priorty the higher is the importance
	simpleTime endTime;
	int status;
};