#pragma once
#include "Ship.h"

class Submarine : public Ship {
protected:
	void makeTags(xml::XMLWriter& writer) override;
	void formTXTData() override;
	void makeFieldsFromTXT() override;
	xml::tag extractClassFromFields(std::string& value) override;
private:
	double width;
	long long underwater_time;
	double max_velocity;
	size_t weapons_count;
	std::string* weapons;
public:
	Submarine() : width(0.0), underwater_time(0), max_velocity(0.0), weapons(nullptr), weapons_count(0), Ship() {
		std::cout << "THEN SUBMARINE CREATED BY DEFAULT CONSTRUCTOR" << std::endl;
		tag = "submarine";
	};

	~Submarine() {
		delete[] weapons;
		width = 0;
		underwater_time = 0;
		max_velocity = 0;
		weapons_count = 0;
		std::cout << "FIRSTLY DELETED SUBMARINE THEN ";
	}

	Submarine(const Submarine& sub_copy) {
		width = sub_copy.width;
		underwater_time = sub_copy.underwater_time;
		max_velocity = sub_copy.max_velocity;
		setWeapons(sub_copy.weapons, sub_copy.weapons_count);
		std::cout << "THEN SUBMARINE WAS FORMED"<< std::endl;
		tag = "submarine";
	};

	bool isWritable() override;
	void setWidth(double w);
	double getWidth();
	void setUnderwaterTime(long long under);
	long long getUnderwaterTime();
	double getMaxVelocity();
	void setMaxVelocity(double mv);
	void setWeapons(std::string* weapons, size_t weapons_len);
	std::tuple<std::string*, size_t> getWeapons();
	std::string StringifyWeapons();
};
