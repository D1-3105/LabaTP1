#include "Keeper.h"



void Keeper::GeneralValidation(int choice, tortuga::UsualShip& object)
{
	auto fileEntering = [](bool erase) {
		if (erase)
			system("cls");
		std::string path;
		print("Enter file path: ", false);
		std::cin.ignore();
		std::getline(std::cin,path);
		return path;
	};
	switch (choice)
	{
	case 1: {
		object.setInputFilePath(fileEntering(true));
		break;
	}
	case 2: {
		object.setOutputFilePath(fileEntering(true));
		break;
	}
	case 3: {
		if (not object.isWritable()) {
			print("Object is not writable. Complete required fields!");
			system("pause");
			return;
		}
		std::string ext = ChooseFormat(object.getOutputFilePath());
		if (ext == "xml") {
			object.writeXMLInfo();
		}
		else if (ext == "txt") {
			object.writeTXTInfo();
		}
		else {
			throw "Invalid file extension!";
		}
		print("Completed.");
		break;
	}
	case 4: {
		std::string ext = ChooseFormat(object.getInputFilePath());
		if (ext == "xml") {
			object.readXMLInfo();
		}
		else if (ext == "txt") {
			object.readTXTInfo();
		}
		else {
			print("Invalid file extension!");
			break;
		}
		break;
	}
	case 5: {
		int len;
		system("cls");
		print("Enter length: ");
		std::cin >> len;
		object.setMeterLength(len);
		break;
	}
	case 6: {
		int crew;
		system("cls");
		print("Enter crew count: ");
		std::cin >> crew;
		object.setCrewCount(crew);
		break;
	}
	default:
		throw "Invalid choice!";
	}
}

std::string Keeper::ChooseFormat(std::string fp)
{
	if (Ship::checkFileExtension("xml", fp, false)) {
		return "xml";
	}
	if (Ship::checkFileExtension("txt", fp, false)) {
		return "txt";
	}
}

int Keeper::menuSailType()
{
	system("cls");
	print("1. Frigate");
	print("2. Brig");
	print("3. Bark");
	print("4. Jol");
	print("-1. Undefined");
	int choice;
	std::cin >> choice;
	return choice;
}

void Keeper::validateSailType(int choice, tortuga::Sail& sail)
{
	sail.setType(choice);
}

void Keeper::Menu()
{
	system("cls");
	print("Available types:");
	print("1. Submarine");
	print("2. Sail");
	print("3. Speed Boat");
	print("Enter the number of interested type:");
	int choice;
	std::cin >> choice;
	try {
		validate_first_choice(choice);
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << std::endl;
		system("pause");
	}
}

void Keeper::validate_first_choice(int choice)
{
	system("cls");
	print("1. Set input file");
	print("2. Set output file");
	print("3. Write file");
	print("4. Read file");
	print("5. Set length");
	print("6. Set crew");
	int start_index = 7;
	switch (choice)
	{
	case 1: {
		int res = SubmarineMenu(start_index);
		if (res < start_index) {
			GeneralValidation(res, *submarine);
		}
		else {
			SubmarineValidation(res - start_index + 1, *submarine);
		}
		break;
	}
	case 2: {
		int res = SailMenu(start_index);
		if (res < start_index) {
			GeneralValidation(res, *sail);
		}
		else {
			SailValidation(res - start_index + 1, *sail);
		}
		break;

	}
	case 3: {
		int res = BoatMenu(start_index);
		if (res < start_index) {
			GeneralValidation(res, *boat);
		}
		else {
			BoatValidation(res - start_index + 1, *boat);
		}
		break;
	}
	default: {
		throw std::invalid_argument("Invalid choice");
	}
	}
}

int Keeper::SubmarineMenu(int start_index)
{
	int end_index = start_index;
	print(std::to_string(end_index++) + ". Set underwater time");
	print(std::to_string(end_index++) + ". Set max velocity");
	print(std::to_string(end_index++) + ". Set weapons");
	print(std::to_string(end_index++) + ". Set width");
	print(std::to_string(end_index++) + ". Delete");
	print(std::to_string(end_index++) + ". Show data");
	int choice;
	std::cin >> choice;
	return choice;
}

void Keeper::SubmarineValidation(int choice, tortuga::Sub& submarine)
{
	system("cls");
	switch (choice) {
	case 1: {
		long long uwt;
		print("Enter underwater time: ", false);
		std::cin >> uwt;
		submarine.setUnderwaterTime(uwt);
		break;
	}
	case 2: {
		double max_v;
		print("Enter max velocity:", false);
		std::cin >> max_v;
		submarine.setMaxVelocity(max_v);
		break;
	}
	case 3: {
		print("How much weapons submarine has?", false);
		size_t count;
		std::cin >> count;
		std::string* weapons = new std::string[count];
		for (size_t i = 0; i < count; i++) {
			print("Enter the weapon:");
			std::cin >> weapons[i];
		}
		submarine.setWeapons(weapons, count);
		break;
	}
	case 4: {
		double w;
		print("Enter width: ", false);
		std::cin >> w;
		submarine.setWidth(w);
		break;
	}
	case 5:
		delete this->submarine;
		this->submarine = new tortuga::Sub();
		system("pause");
		break;
	case 6:
		print("Submarine data:");
		print("\tCrew: " + std::to_string(submarine.getCrewCount()));
		print("\tLength: " + std::to_string(submarine.getMeterLength()));
		print("\tWidth: " + std::to_string(submarine.getWidth()));
		print("\tUnderwater time: " + std::to_string(submarine.getUnderwaterTime()));
		print("\tMax velocity: " + std::to_string(submarine.getMaxVelocity()));
		print("\tWeapons: " + submarine.StringifyWeapons());
		system("pause");
		break;
	default:
		throw std::exception("Incorrect mode!");
	}

}


int Keeper::SailMenu(int start_index)
{
	print(std::to_string(start_index++) + ". Set type");
	print(std::to_string(start_index++) + ". Set velocity");
	print(std::to_string(start_index++) + ". War/Civil");
	print(std::to_string(start_index++) + ". Delete");
	int choice;
	std::cin >> choice;
	return choice;
}

void Keeper::SailValidation(int choice, tortuga::Sail& sail)
{
	switch (choice) {
	case 1: {
		int res = menuSailType();
		validateSailType(res, sail);
	}
	case 2: {
		int v;
		print("Enter the velocity: ", false);
		std::cin >> v;
		sail.setVelocity(v);
	}
	case 3: {
		print("1 = War, 0 = Civil");
		int war;
		std::cin >> war;
		sail.setWarmachine(war);
	}
	case 4: {
		delete this->sail;
		this->sail = new tortuga::Sail();
		system("pause");
		break;
	}
	default:
		throw std::exception("Incorrect mode!");
	}
}

int Keeper::BoatMenu(int start_index)
{
	print(std::to_string(start_index++) + ". Set purpose");
	print(std::to_string(start_index++) + ". Set materials");
	print(std::to_string(start_index++) + ". Set charachteristics");
	print(std::to_string(start_index++) + ". Set velocity");
	print(std::to_string(start_index++) + ". Delete");
	print(std::to_string(start_index++) + ". Show data");
	int choice;
	std::cin >> choice;
	return choice;
}

void Keeper::BoatValidation(int choice, tortuga::Boat& boat)
{
	system("cls");
	switch (choice) {
	case 1: {
		print("Enter the purpose:");
		std::string purpose;
		std::getline(std::cin, purpose);
		boat.setPurpose(purpose);
		break;
	}
	case 2: {
		print("How much materials is the boat made of?", false);
		size_t count;
		std::cin >> count;
		std::string* materials = new std::string[count];
		for (size_t i = 0; i < count; i++) {
			print("Enter the material:");
			std::cin >> materials [i] ;
		}
		boat.setMaterials(materials, count);
		break;
	}
	case 3: {
		print("How much charachteristics has the boat?", false);
		size_t count;
		std::cin >> count;
		std::string* chars = new std::string[count];
		for (size_t i = 0; i < count; i++) {
			print("Enter the material:");
			std::cin >> chars[i];
		}
		boat.setCharacteristics(chars, count);
		break;
	}
	case 4: {
		int v;
		print("Enter the velocity: ", false);
		std::cin >> v;
		boat.setVelocity(v);
	}
	case 5: {
		delete this->boat;
		this->boat = new tortuga::Boat();
		system("pause");
		break;
	}
	case 6: {
		break;
	}
	default:
		throw std::exception("Invalid choice!");
	}
}

