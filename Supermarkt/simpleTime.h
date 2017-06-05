#pragma once
#include <string>
class simpleTime
{
public:
	simpleTime();
	simpleTime(int, int, int);
	~simpleTime();
	void increaseSeconds(int s);
	//Dont believe we need that
	void increaseMinutes(int);
	bool operator ==(simpleTime);
	bool operator <(simpleTime);
	bool operator >(simpleTime);
	std::string toString();

private: 
	int seconds;
	int minutes;
	int hours;
	void calculateCarry(int secs);


};


