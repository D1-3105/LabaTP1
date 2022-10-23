#include <iostream>
#include <string.h>
#include "xmlparser.h"
#include "ShipTypes.h"
#include <map>
#include <fstream>

int main() {
	std::string path = "t.xml";
	std::string path_txt = "t.txt";

	tortuga::SailBoat sub;
	/*sub.setCrewCount(150);
	sub.setOutputFilePath(path);
	sub.setMeterLength(250);
	sub.setType(0);
	sub.setVelocity(33);
	sub.writeXMLInfo();
	sub.setOutputFilePath(path_txt);
	sub.writeTXTInfo();*/
	sub.setInputFilePath(path_txt);
	sub.readTXTInfo();
}