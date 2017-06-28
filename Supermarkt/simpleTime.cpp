#include "stdafx.h"
#include "simpleTime.h"


simpleTime::simpleTime()
{
}


simpleTime::~simpleTime()
{
}

//TODO implement safety controls for idiots who try to invoke 
//simpleTime with valus greater 23,59,59
//atm no restriction 
simpleTime::simpleTime(int h, int m, int s){
	hours = h;
	minutes = m;
	seconds = s;
}

int simpleTime::getSeconds(){
	return seconds;
}

int simpleTime::getMinutes(){
	return minutes;
}

int simpleTime::getHours(){
	return hours;
}

void simpleTime::increaseSeconds(int s){
	calculateCarry(s);
}
void simpleTime::increaseMinutes(int m){
	calculateCarry(m * 60);
	
}

void simpleTime::calculateCarry(int s){
	
	seconds += s;
	int minutesCarry = 0;
	int hourCarry = 0;
	if (seconds >= 60){
		minutesCarry = seconds/ 60;
		seconds = seconds% 60;
		minutes += minutesCarry;
	}

	if (minutes >= 60){
		hourCarry = minutes / 60;
		minutes = minutes % 60;
		hours += hourCarry;
	}	

}
bool simpleTime::operator==(simpleTime st)const{
	if (hours == st.hours && minutes == st.minutes && seconds == st.seconds){
		return true;
	}
	return false;
}

bool simpleTime::operator<(simpleTime st)const{

	if (hours < st.hours){
		return true;
	}
	else if (hours >st.hours)
	{
		return false;
	}
	//at this point hours must be the same
	if (minutes < st.minutes){
		return true;
	}
	else if (minutes > st.minutes)
	{
		return false;
	}
	//at this point minutes and hours must be equals
	if (seconds < st.seconds){
		return true;
	}
	//this.seconds are greater or equals
	return false;
}

bool simpleTime::operator>(simpleTime st)const{
	
	if (*this == st){
		return false;
	}
	if (*this < st){
		return false;
	}
	return true;
}

simpleTime simpleTime::operator-(simpleTime st)const{
	
	int tempS = seconds - st.getSeconds();
	int tempM = minutes - st.getMinutes();
	int tempH = hours - st.getHours();
	if(tempS < 0){
		tempM -= 1;
		tempS += 60;
	}
	if(tempM < 0){
		tempH -= 1;
		tempM += 60;
	}
	simpleTime temp(tempH,tempM,tempS);
	return temp;
}

std::string simpleTime::toString(){
	std::string retString= std::to_string(hours) + "h " + std::to_string(minutes) + "minuten " + std::to_string(seconds) + "sekunden";
	return retString;
}
