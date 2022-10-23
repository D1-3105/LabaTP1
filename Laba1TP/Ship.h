#pragma once
#include <string>
#include <iostream>
#include <fstream>
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
private:
	std::string inp_fp;
	std::string out_fp;
	short crewCount;

	virtual xml::tag makePrimaryTag(std::string input, xml::tag& xml_data, xml::XMLReader& reader);
public:
	Ship() : meterLength(0.0), crewCount(0), input_file_stream(nullptr), output_file_stream(nullptr), inp_fp(""), tag("ship") {
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

	virtual void setInputFilePath(std::string fp) final;
	virtual void setOutputFilePath(std::string fp) final;
	virtual void writeXMLInfo();
	virtual void writeTXTInfo();
	static void checkFileExtension(std::string extension, std::string& fp);
	virtual void readXMLInfo();
	virtual void readTXTInfo();
	virtual void setCrewCount(short& crewCount);
	short getCrewCount();
	virtual void setCrewCount(short crew);
	double getMeterLength();
	virtual void setMeterLength(double ml);
};