#pragma once
#include "Ship.h"
#include "xmlparser.h"
#include <string>

class SailBoat : public Ship {
protected:
	void makeTags(xml::XMLWriter& writer) override;
	void formTXTData() override;
	void makeFieldsFromTXT() override;
	xml::tag extractClassFromFields(std::string& value) override;
private:
	enum class Types {
		Frigate,
		Brig,
		Bark,
		Jol,
		undefined
	};
	Types type;
	bool war_machine;
	double velocity;

public:
	SailBoat() :Ship(), war_machine(false), velocity(0.0), type(SailBoat::Types::undefined) {
		std::cout << "THEN SAILBOAT CREATED BY DEFAULT CONSTRUCTOR" << std::endl;
		tag = "sailboat";
	};
	~SailBoat() {
		std::cout << "FIRSTLY DELETED SAILBOAT THEN ";
	};
	SailBoat(const SailBoat& copy_boat) {
		type = copy_boat.type;
		war_machine = copy_boat.war_machine;
		velocity = copy_boat.velocity;
		tag = copy_boat.tag;
		std::cout << "THEN SAILBOAT WAS FORMED" << std::endl;
	};

	void setType(int type);
	int getType();
	void setVelocity(double vel);
	double getVelocity();
	void setWarmachine(bool wm);
	bool getWarmachine();
};
