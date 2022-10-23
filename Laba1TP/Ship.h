#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "xmlparser.h"


class Ship {
protected:
	double meterLength;
	std::string tag;
	std::ifstream* input_file_stream;
	std::ofstream* output_file_stream;

	virtual void makeFieldsFromTXT();
	virtual void formTXTData();
	virtual void makeTags(xml::XMLWriter& writer);
	virtual xml::tag extractClassFromFields(std::string& value);
	template <class T>
	std::string Stringify(const T* array_param, size_t len);

	template<class T>
	T* readXMLarray(std::string tag_prefix, xml::tag& values_map, size_t length);
private:
	std::string inp_fp;
	std::string out_fp;
	short crewCount;
	virtual xml::tag makePrimaryTag(std::string input, xml::tag& xml_data, xml::XMLReader& reader);
public:

	Ship() : meterLength(0), crewCount(0), input_file_stream(nullptr), output_file_stream(nullptr), inp_fp(""), tag("ship") {
		std::cout << "SHIP INITIALIZED BY DEFAULT CONSTRUCTOR" << std::endl;
	};
	~Ship() {
		std::cout << "SHIP DELETED BY DEFAULT CONSTRUCTOR" << std::endl;
		if (input_file_stream != nullptr and input_file_stream->is_open()) {
			input_file_stream->close();
		}
		if (output_file_stream != nullptr and output_file_stream->is_open()) {
			output_file_stream->close();
		}
		meterLength = 0;
		crewCount = 0;
		
	};
	Ship(const Ship& copyMe): tag("ship") {
		std::cout << "SHIP WAS COPIED" << std::endl;
		input_file_stream = copyMe.input_file_stream;
		output_file_stream = copyMe.output_file_stream;
		inp_fp = copyMe.inp_fp;
		crewCount = copyMe.crewCount;
		meterLength = copyMe.meterLength;
		tag = copyMe.tag;
	}

	static bool checkFileExtension(std::string extension, std::string& fp, bool raise_exceptions = true);
	virtual bool isWritable();

	virtual void setInputFilePath(std::string fp) final;
	std::string getInputFilePath();
	virtual void setOutputFilePath(std::string fp) final;
	std::string getOutputFilePath();
	virtual void writeXMLInfo();
	virtual void writeTXTInfo();
	virtual void readXMLInfo();
	virtual void readTXTInfo();
	virtual void setCrewCount(short& crewCount);
	virtual short getCrewCount();
	virtual void setCrewCount(short crew);
	double getMeterLength();
	virtual void setMeterLength(double ml);
};



template<class T>
T* Ship::readXMLarray(std::string tag_prefix, xml::tag& values_map, size_t length)
{
	T* on_ret = new T[length];
	std::smatch res;
	for (int i = 0; i < length; i++) {
		on_ret[i] = values_map[tag_prefix + std::to_string(i)]["value"];
	}
	return on_ret;
};

template <class T>
std::string Ship::Stringify(const T* array_param, size_t len)
{
	std::stringstream param_stringstream;
	for (size_t i = 0; i < len; i++) {
		param_stringstream << array_param[i] << ";";
	}
	return param_stringstream.str();
}