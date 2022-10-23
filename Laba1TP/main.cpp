#include <iostream>
#include <string.h>
#include "xmlparser.h"
#include "ShipTypes.h"
#include <map>
#include <fstream>

int main() {
	setlocale(LC_ALL, "Russian");
	std::string path = "t.xml";
	std::string path_txt = "t.txt";

	tortuga::Boat sub;
	//sub.setCrewCount(150);
	//sub.setMeterLength(250);
	////sub.setType(0);
	//sub.setVelocity(33);
	//sub.setPurpose("11");
	//std::string chars[] = {"Fast and Nice", "Big and Cocky"};
	//sub.setCharacteristics(chars, 2);
	//std::string mats[] = { "Shit", "Cum" };
	//sub.setMaterials(mats,2);
	//sub.setOutputFilePath(path);
	//sub.writeXMLInfo();
	//sub.setOutputFilePath(path_txt);
	//sub.writeTXTInfo();
	sub.setInputFilePath(path_txt);
	sub.readTXTInfo();
	sub.setInputFilePath(path);
	sub.readXMLInfo();
}