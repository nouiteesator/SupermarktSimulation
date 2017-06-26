#include <iostream>
#include "Simulation.h"
#include "stdafx.h"
#include <fstream>
#include <string>
#include <ctime>
#include "simpleTime.h"
#include <vector>
#include <random>
#include <queue>
#include "Event.h"
#include <stdlib.h>
#include "Eventhandler.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	using namespace std;
	Simulation s;
	int i;
	s.getEventhandler().addEventQueue(Event());
	while(s.getEventhandler().getEventQueue().empty() != true){
		s.getEventhandler().executeEvent();
		
		i++;
	}
	//debug test whether this does work
	/*while(s.getEventhandler().getEventQueue().empty() != true){
		simpleTime i = s.getEventhandler().executeEvent();
		s.setRealTime(i);
	}
	s.getSupermarket().setActualCloseTime(realTime);
	*/
	cout << s.getSupermarket().getCustomerArrived() << endl;
	
	return 0;
}

