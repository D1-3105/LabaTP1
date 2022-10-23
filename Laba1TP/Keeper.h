#pragma once
#include "ShipTypes.h"
#include "utils.h"

class Keeper {
protected:
	void SubmarineValidation(int choice, tortuga::Sub& submarine);
	void SailValidation(int choice, tortuga::Sail& sail);
	void BoatValidation(int choice, tortuga::Boat& boat);
	
	void GeneralValidation(int choice, tortuga::UsualShip& object);

	std::string ChooseFormat(std::string fp);
private:

	int menuSailType();
	void validateSailType(int choice, tortuga::Sail& sail);

	tortuga::Sub *submarine;
	tortuga::Boat *boat;
	tortuga::Sail *sail;
public:
	Keeper() :submarine(new tortuga::Sub()), boat(new tortuga::Boat()), sail(new tortuga::Sail()) {};
	void Menu();
	void validate_first_choice(int choice);
	int SubmarineMenu(int start_index);
	int SailMenu(int start_index);
	int BoatMenu(int start_index);
};