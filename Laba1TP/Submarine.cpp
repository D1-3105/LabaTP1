#include "Submarine.h"

void Submarine::makeTags(xml::XMLWriter& writer)
{
	Ship::makeTags(writer);
	writer.makeNewTag("width", width, false, xml::attributes(), true);
	writer.makeNewTag("underwater_time", underwater_time, false, xml::attributes(), true);
	writer.makeNewTag("max_velocity", max_velocity, false, xml::attributes(), true);
	writer.makeNewTag("weapons_count", weapons_count, false, xml::attributes(), true);
	for (int i = 0; i < weapons_count; i++) {
		writer.makeNewTag("weapon"+std::to_string(i), weapons[i], false, xml::attributes(), true);
	}
}

void Submarine::formTXTData()
{
	Ship::formTXTData();
	*output_file_stream << width << " " << underwater_time << " " << max_velocity << " " << weapons_count << "\n";
	for (int i = 0; i < weapons_count; i++)
		*output_file_stream << weapons[i] << "\n";
}

void Submarine::makeFieldsFromTXT()
{
	Ship::makeFieldsFromTXT();
	*input_file_stream >> width;
	*input_file_stream >> underwater_time;
	*input_file_stream >> max_velocity;
	*input_file_stream >> weapons_count;
	weapons = new std::string[weapons_count];
	for (size_t i = 0; i < weapons_count; i++) {
		std::getline(*input_file_stream, weapons[i]);
	}
}

xml::tag Submarine::extractClassFromFields(std::string& value)
{
	xml::tag values_map = Ship::extractClassFromFields(value);
	width = std::stof(values_map["width"]["value"]);
	values_map.erase("width");
	underwater_time = std::stoll(values_map["underwater_time"]["value"]);
	values_map.erase("underwater_time");
	max_velocity = std::stof(values_map["max_velocity"]["value"]);
	values_map.erase("max_velocity");
	weapons_count = std::stoi(values_map["weapons_count"]["value"]);
	values_map.erase("weapons_count");
	weapons = Ship::readXMLarray<std::string>("weapon", values_map, weapons_count);
	return values_map;
}

void Submarine::setUnderwaterTime(long long under)
{
	underwater_time = under;
}

long long Submarine::getUnderwaterTime()
{

	return underwater_time;
}

double Submarine::getMaxVelocity()
{
	return max_velocity;
}

void Submarine::setMaxVelocity(double mv)
{
	max_velocity = mv;
}

void Submarine::setWeapons(std::string* weapons_inp, size_t weapons_len)
{
	weapons_count = weapons_len;
	weapons = new std::string[weapons_len];
	for (size_t i = 0; i < weapons_count; i++) {
		weapons[i] = weapons_inp[i];
	}
}

std::tuple<std::string*, size_t> Submarine::getWeapons()
{

	return std::tuple<std::string*, size_t>(weapons, weapons_count);
}

std::string Submarine::StringifyWeapons()
{
	return Ship::Stringify(weapons, weapons_count);
}

