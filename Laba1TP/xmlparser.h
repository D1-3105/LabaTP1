#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>
#include "utils.h"


namespace xml {
	using tag = std::map<
		std::string, 
		std::map<std::string, std::string>
	>;
	using attributes = std::map<
		std::string, std::string
	>;
	template<class T> inline std::string convertToString(T& toString);
	template<class T> inline std::stringstream insertStream(std::stringstream& ss, T obj, int pos);
	class XMLWriter {
	private:
		std::ofstream* os;
		std::stringstream ss;
		int pos;
	public:
		std::string getOutput() {
			return this->ss.str();
		}
		XMLWriter(std::ofstream& os_) : os{ &os_ }, pos(0) {};
		XMLWriter(std::string& outputFilePath);

		template<class T>
		std::string makeNewTag(std::string tagName, T& value, bool shortened, 
			std::map<std::string, std::string> attributes = xml::attributes(), bool breakscope = false) {
			//
			std::stringstream tag_string_stream; // <source lang="eng"></source>
			tag_string_stream << "<"<< tagName.c_str();
			
			std::string attrs_string = this->makeAttrsString(attributes); // lang:eng -> lang="eng"
			if (attrs_string != "") {
				tag_string_stream << " ";
			}
			tag_string_stream << attrs_string.c_str(); // delete trailing space
			int tmp_pos = 0;
			if (!shortened) {
				tag_string_stream << ">" << value;
				if (!breakscope) {
					tmp_pos += tag_string_stream.str().length(); // // <source lang="eng">[*we're here!*]</source> 
				}
				tag_string_stream << formEndTag(tagName);
				if (breakscope) {

					tmp_pos += tag_string_stream.str().length(); // <source lang="eng"></source>[*we're here*]
				}
				
			}
			else {
				tag_string_stream << "/>";
				tmp_pos += tag_string_stream.str().length();
			}
			std::stringstream tmp_ss;
			tmp_ss << tag_string_stream.str();
			//std::cout << ss.str() << " - " << pos << ss.str()[pos] << std::endl;
			ss = xml::insertStream(ss, tmp_ss.str(), pos);
			pos += tmp_pos;
			
			return tag_string_stream.str();
		}

		void make_output();
		std::string formEndTag(std::string& tagName); // </source>, </ship>

		std::string makeAttrsString(std::map<std::string, std::string>& attributes);

		void makeInitializeOutput();
	};


	class XMLReader {
	private:
		std::ifstream* is;
		int pos;
	public:
		static xml::tag extractFinalValues(std::string& boxed_value);
		XMLReader(std::ifstream& is_) : is{ &is_ }, pos(0) {};
		XMLReader(std::string& inputFilePath);
		std::string readInitializeInput();
		std::map<std::string, std::string> // value:"", attributes:"", "recurent":""
			convertStringParameters(std::string attrs, std::string value, bool requiresCheck = true);
		static std::map<
			std::string, std::string
		> convertAttributes(std::string& attrs);
		xml::tag readCurrentTag(std::string data);
		std::map<
			std::string,
			std::map<
				std::string, std::string // "value":"<ship>123</ship>", "attributes":"crew="22" len="230.00"", "recurent":"1/0" (including new tag??)
			>
		> readBranchTag(std::string& data, std::regex& base_tag_regex, std::regex& advanced_tag_regex);
	};


	template<class STREAMTYPE>
	STREAMTYPE* streamInit(std::string& fp) {
		if (fp != "") {
			STREAMTYPE* stream = new STREAMTYPE(fp.c_str());
			return stream;
		}
		else {
			throw std::invalid_argument("INVALID FILEPATH");
		}
	}
	template<class T>
	inline std::string convertToString(T& toString) {
		std::stringstream string_converter;
		string_converter << toString;
		return string_converter.str();
	}
	template<class T> 
	inline std::stringstream insertStream(std::stringstream& ss, T obj, int pos) {
		
		std::string previous = ss.str();
		std::stringstream new_ss;
		for (int i = 0; i < pos; i++) {
			new_ss << previous[i];
		}
		new_ss << obj;
		for (int i = pos; i < previous.length(); i++) {
			new_ss << previous[i];
		}
		
		return new_ss;
	}
}

