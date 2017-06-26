#pragma once
#include <string>
class simpleTime
{
public:
	simpleTime();
	simpleTime(int, int, int);
	~simpleTime();
	void increaseSeconds(int);
	//Dont believe we need that
	void increaseMinutes(int);
	bool operator ==(simpleTime)const;
	bool operator <(simpleTime)const;
	bool operator >(simpleTime)const;
	std::string toString();
	int getMinutes();
	int getSeconds();
	int getHours();

private: 
	int seconds;
	int minutes;
	int hours;
	void calculateCarry(int);


};


