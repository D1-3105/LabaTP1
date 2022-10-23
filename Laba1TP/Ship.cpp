#include "Ship.h"

void Ship::setInputFilePath(std::string fp)
{
	this->inp_fp = fp;
	this->input_file_stream = xml::streamInit<std::ifstream>(fp);
}

void Ship::checkFileExtension(std::string extension, std::string& fp)
{
	std::regex fileRegex("\\w+[\\\.](\\w+)");
	std::smatch result;
	std::regex_search(fp, result, fileRegex);
	std::cout << result.str() << std::endl;
	if (extension != result[1])
		throw std::invalid_argument("INVALID EXTENSION");
}

void Ship::readXMLInfo()
{
	this->checkFileExtension("xml", this->inp_fp);
	xml::XMLReader reader(*this->input_file_stream);
	std::string input;
	if (!this->input_file_stream->is_open())
		throw std::exception("FILE IS INVALID");
	std::string curline;
	while (!this->input_file_stream->eof()) {
		std::getline(*input_file_stream, curline);
		input += curline+"\n";
	}
	xml::tag xml_data = reader.readCurrentTag(input);
	try {
		xml::tag key_tag = makePrimaryTag(input, xml_data, reader);
		this->extractClassFromFields(key_tag[this->tag]["value"]);
	}
	catch (std::exception e) {
		std::cout << e.what() <<std::endl;
		throw e;
	}
}

void Ship::readTXTInfo()
{
	this->checkFileExtension("txt", this->inp_fp);
	if ((*input_file_stream).is_open()) {
		this->makeFieldsFromTXT();
		this->input_file_stream->close();
	}
}

xml::tag Ship::extractClassFromFields(std::string& value)
{
	xml::tag map_values= xml::XMLReader::extractFinalValues(value);
	this->crewCount = std::stoi(map_values["crew"]["value"]);
	map_values.erase("crew");
	this->meterLength = std::stof(map_values["length"]["value"]);
	map_values.erase("length");
	return map_values;
}

void Ship::makeFieldsFromTXT()
{
	*input_file_stream >> meterLength;
	*input_file_stream >> crewCount;
}

void Ship::setOutputFilePath(std::string fp) {
	this->out_fp = fp;
	output_file_stream = xml::streamInit<std::ofstream>(fp);
}


xml::tag Ship::makePrimaryTag(std::string input, xml::tag& const xml_data, xml::XMLReader& reader)
{
	if (xml_data.count("source") != 1
		or xml::XMLReader::convertAttributes(xml_data["source"]["attributes"])["lang"] != "xml")
		throw std::exception("NO XML TAG PRESENT IN FILE");
	xml::tag prim_tag = reader.readCurrentTag(xml_data["source"]["value"]);
	if (prim_tag.count(this->tag) == 1)
		return prim_tag;
	else {
		std::stringstream exception_builder;
		exception_builder << "NO " << this->tag << " PRESENT IN FILE";
		throw std::exception(exception_builder.str().c_str());
	}
}

void Ship::setCrewCount(short& crewCount)
{
	this->crewCount = crewCount;
}

void Ship::writeXMLInfo()
{
	this->checkFileExtension("xml", this->out_fp);
	xml::XMLWriter writer(*this->output_file_stream);
	this->makeTags(writer);
	if (this->output_file_stream->is_open()) {
		writer.make_output();
		this->output_file_stream->close();
	}
	
}

short Ship::getCrewCount()
{
	return crewCount;
}

void Ship::writeTXTInfo() {
	this->checkFileExtension("txt", this->out_fp);
	if (this->output_file_stream->is_open()) {
		formTXTData();
		this->output_file_stream->close();
	}

}

void Ship::setCrewCount(short crew)
{
	crewCount = crew;
}

double Ship::getMeterLength()
{
	return meterLength;
}

void Ship::setMeterLength(double ml)
{
	meterLength = ml;
}

void Ship::formTXTData()
{
	*output_file_stream << this->meterLength << " " << crewCount << " ";
}

void Ship::makeTags(xml::XMLWriter& writer)
{
	writer.makeInitializeOutput();
	writer.makeNewTag(tag, "", false);
	writer.makeNewTag("length", this->meterLength, false, xml::attributes(), true);
	writer.makeNewTag("crew", this->crewCount, false, xml::attributes(), true);
}
