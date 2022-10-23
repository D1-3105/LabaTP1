#include "SpeedBoat.h"

void SpeedBoat::makeFieldsFromTXT()
{
	Ship::makeFieldsFromTXT();
	std::getline(*input_file_stream,purpose);
	*input_file_stream >> materials_count;
	materials = new std::string[materials_count];
	for (int i = 0; i < materials_count; i++) {
		std::getline((*input_file_stream), materials[i]);
	}
	*input_file_stream >> chars_count;
	for (int i = 0; i < chars_count; i++) {
		std::getline((*input_file_stream), characteristics[i]);
	}
	*input_file_stream >> velocity;
}

void SpeedBoat::formTXTData()
{
	Ship::formTXTData();
	*output_file_stream << purpose << "\n" << materials_count << "\n";
	for (int i = 0; i < materials_count; i++) {
		*output_file_stream << materials[i] << "\n";
	}
	*output_file_stream << chars_count << "\n";
	for (int i = 0; i < chars_count; i++) {
		*output_file_stream << characteristics[i] << "\n";
	}
	*output_file_stream << velocity;
}

void SpeedBoat::makeTags(xml::XMLWriter& writer)
{
	Ship::makeTags(writer);
	writer.makeNewTag("purpose", purpose, false, xml::attributes(), true);
	writer.makeNewTag("materials_count", materials_count, false, xml::attributes(), true);
	for (int i = 0; i < materials_count; i++)
		writer.makeNewTag("material" + std::to_string(i), materials[i], false, xml::attributes(), true);
	writer.makeNewTag("chars_count", chars_count, false, xml::attributes(), true);
	for (int i = 0; i < chars_count; i++) {
		writer.makeNewTag("char" + std::to_string(i), characteristics[i], false, xml::attributes(), true);
	}
	writer.makeNewTag("velocity", velocity, false, xml::attributes(), true);
}

xml::tag SpeedBoat::extractClassFromFields(std::string& value)
{
	xml::tag values_map = Ship::extractClassFromFields(value);
	purpose = values_map["purpose"]["value"];
	values_map.erase("purpose");
	materials_count = std::stoi(values_map["materials_count"]["value"]);
	values_map.erase("materials_count");
	materials = Ship::readXMLarray<std::string>("material", values_map, materials_count);
	chars_count = std::stoi(values_map["chars_count"]["value"]);
	values_map.erase("chars_count");
	characteristics = Ship::readXMLarray<std::string>("char", values_map, chars_count);
	velocity = std::stod(values_map["velocity"]["value"]);
	return values_map;
}

void SpeedBoat::setMaterials(std::string* mat, size_t len)
{
	materials_count = len;
	materials = new std::string[len];
	for (size_t i = 0; i < len; i++) {
		materials[i] = mat[i];
	}
}

std::tuple<std::string*, size_t> SpeedBoat::getMaterials()
{
	return std::tuple<std::string*, size_t>(materials, materials_count);
}

void SpeedBoat::setCharacteristics(std::string* chars, size_t len)
{
	chars_count = len;
	characteristics = new std::string[len];
	for (size_t i = 0; i < len; i++) {
		characteristics[i] = chars[i];
	}
}

std::tuple<std::string*, size_t> SpeedBoat::getCharacteristics()
{
	return std::tuple<std::string*, size_t>(characteristics, chars_count);
}

void SpeedBoat::setVelocity(double vel)
{
	velocity = vel;
}

double SpeedBoat::getVelocity()
{
	return velocity;
}

void SpeedBoat::setPurpose(std::string p)
{
	purpose = p;
}

std::string SpeedBoat::StringifyMaterials()
{
	return Ship::Stringify(materials, materials_count);
}

std::string SpeedBoat::getPurpose()
{
	return purpose;
}

std::string SpeedBoat::StringifyCharacteristics()
{
	return Ship::Stringify(characteristics, chars_count);
}
