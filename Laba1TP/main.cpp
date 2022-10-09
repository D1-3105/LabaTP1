#include <iostream>
#include <string.h>
#include "xmlparser.h"
#include "ShipTypes.h"
#include <map>
#include <fstream>

int main() {
	std::string path = "t.txt";

	tortuga::UsualShip *ship= new Ship();
	ship->setCrewCount(25);
	ship->setMeterLength(250);
	ship->setOutputFilePath(path);
	ship->writeTXTInfo();
	tortuga::UsualShip ship1;
	ship1.setInputFilePath(path);
	ship1.readTXTInfo();
}