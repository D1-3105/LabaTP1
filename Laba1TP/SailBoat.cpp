#include "SailBoat.h"
void SailBoat::setType(int t)
{
	switch (t) {
	case 0:
		this->type = SailBoat::Types::Frigate;
		break;
	case 1:
		this->type = SailBoat::Types::Brig;
		break;
	case 2:
		this->type = SailBoat::Types::Bark;
		break;
	case 3:
		this->type = SailBoat::Types::Jol;
		break;
	default:
		this->type = SailBoat::Types::undefined;
		break;
	}
}

int SailBoat::getType()
{
	switch (type){
	case SailBoat::Types::Frigate:
		return 0;
	case SailBoat::Types::Brig:
		return 1;
	case SailBoat::Types::Bark:
		return 2;
	case SailBoat::Types::Jol:
		return 3;
	case SailBoat::Types::undefined:
		return -1;
	}
}

double SailBoat::getVelocity()
{
	return velocity;
}

void SailBoat::setWarmachine(bool wm)
{
	war_machine = wm;
}

bool SailBoat::isWritable()
{
	if(velocity == -1 or not Ship::isWritable())
		return false;
	return true;
}

bool SailBoat::getWarmachine()
{
	return war_machine;
}

void SailBoat::setVelocity(double vel)
{
	velocity = vel;
}

void SailBoat::makeTags(xml::XMLWriter& writer)
{
	Ship::makeTags(writer);
	int inner_type = getType();
	writer.makeNewTag("type", inner_type, false, xml::attributes(), true);
	writer.makeNewTag("war_machine", war_machine, false, xml::attributes(), true);
	writer.makeNewTag("velocity", velocity, false, xml::attributes(), true);
}

void SailBoat::formTXTData()
{
	Ship::formTXTData();
	*output_file_stream << getType() << " " << war_machine << " " << velocity << " ";
}

void SailBoat::makeFieldsFromTXT()
{
	Ship::makeFieldsFromTXT();
	int inner_type;
	*input_file_stream >> inner_type;
	setType(inner_type);
	*input_file_stream >> war_machine;
	*input_file_stream >> velocity;
}

xml::tag SailBoat::extractClassFromFields(std::string& value)
{
	xml::tag values_map = Ship::extractClassFromFields(value);
	int inner_type = std::stoi(values_map["type"]["value"]);
	setType(inner_type);
	values_map.erase("type");
	war_machine = std::stoi(values_map["war_machine"]["value"]);
	values_map.erase("war_machine");
	velocity = std::stod(values_map["velocity"]["value"]);
	values_map.erase("velocity");
	return values_map;
}
