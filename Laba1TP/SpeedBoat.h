#pragma once
#include "Ship.h"
#include "xmlparser.h"
#include <string>

class SpeedBoat :public Ship {
protected:
	virtual void makeFieldsFromTXT();
	virtual void formTXTData();
	virtual void makeTags(xml::XMLWriter& writer);
	virtual xml::tag extractClassFromFields(std::string& value);
private:
	std::string purpose;
	size_t materials_count;
	std::string* materials;
	size_t chars_count;
	std::string* characteristics;
	double velocity;
public:
	SpeedBoat() : purpose(""), materials_count(0), materials(nullptr), chars_count(0), characteristics(nullptr), velocity(0), Ship() {
		std::cout << "THEN SPEEDBOAT CREATED BY DEFAULT CONSTRUCTOR" << std::endl;
		tag = "sailboat";
	};
	~SpeedBoat() {
		delete[] materials;
		delete[] characteristics;
		std::cout << "FIRSTLY DELETED SPEEDBOAT THEN ";
	};
	SpeedBoat(const SpeedBoat& copy) {
		purpose = copy.purpose;
		setMaterials(copy.materials, copy.materials_count);
		setCharacteristics(copy.characteristics, copy.chars_count);
		velocity = copy.velocity;
		std::cout << "THEN SAILBOAT WAS FORMED" << std::endl;
		tag = "sailboat";
	};

	void setMaterials(std::string* mat, size_t len);
	std::tuple<std::string*, size_t> getMaterials();
	void setCharacteristics(std::string* chars, size_t len);
	std::tuple<std::string*, size_t> getCharacteristics();
	void setVelocity(double vel);
	double getVelocity();
	void setPurpose(std::string p);
	std::string getPurpose();

	std::string StringifyMaterials();
	std::string StringifyCharacteristics();
};
