#include "xmlparser.h"

xml::XMLWriter::XMLWriter(std::string& outputFilePath)
{
	os= xml::streamInit<std::ofstream>(outputFilePath);
	this->pos = 0;
}

void xml::XMLWriter::make_output()
{
	*os << ss.str().c_str();
}

std::string xml::XMLWriter::formEndTag(std::string& tagName)
{
	std::stringstream tagend_string_stream;
	tagend_string_stream << "</" << tagName << ">";
	return tagend_string_stream.str();
}

std::string xml::XMLWriter::makeAttrsString(std::map<std::string, std::string>& attributes)
{
	std::stringstream attrs_string_stream;
	for (auto const& [key, val] : attributes)
	{
		attrs_string_stream << key << "=" << "\"" << val << "\"" << " ";
	}
	return trim(attrs_string_stream.str());
}

void xml::XMLWriter::makeInitializeOutput()
{
	if (os->is_open()) {
		std::map<std::string, std::string> attributes;
		attributes["lang"] = "xml";
		makeNewTag("source", "", false, attributes);
	}
}

xml::XMLReader::XMLReader(std::string& inputFilePath)
{
	this->is = xml::streamInit<std::ifstream>(inputFilePath);
	this->pos = 0;
}

std::map<std::string, std::string> xml::XMLReader::convertStringParameters(std::string attrs, std::string value, bool requiresCheck)
{
	 std::map<std::string, std::string> mapped;
	 mapped["attributes"] = attrs;
	 mapped["value"] = value;
	 std::regex base_tag_regex("<(\\w+)([^>]*)*\\s*>(.*)<\/\\w+>");
	 std::regex advanced_tag_regex("<\\w+(\\s+\\w+=\".+\"\\s*)*/>");
	 auto re_check = [&value](std::regex& re) ->bool { return std::regex_search(value, re); }; // for better reading
	 if (requiresCheck and
		 (re_check(advanced_tag_regex) or re_check(base_tag_regex)))
	 {
		 mapped["recurrent"] = "1";
	 }
	 else {
		 mapped["recurrent"] = "0";
	 }
	 return mapped;
}

std::map<
	std::string, std::string
> xml::XMLReader::convertAttributes(std::string& attrs) {
	std::regex attr_regex("(\\w+)=\"(.*?)\"");
	std::smatch sm_attrs;

	// 0 - full attrs string
	// 1 - attr name
	// 2 - attr val

	std::regex_search(attrs, sm_attrs, attr_regex);
	std::map<
		std::string, std::string
	> ret;
	for (std::sregex_iterator i = std::sregex_iterator(attrs.begin(), attrs.end(), attr_regex);i != std::sregex_iterator();++i){
		sm_attrs = *i;
		ret[sm_attrs[1].str()] = sm_attrs[2].str();
	}
	return ret;
}

xml::tag xml::XMLReader::readCurrentTag(std::string level)
{
	std::stringstream tmp_string;
	std::regex_replace(std::ostream_iterator<char>(tmp_string), level.begin(), level.end(), std::regex("[\t\n]"), "");
	level = tmp_string.str();
	std::regex base_tag_regex("<(\\w+)(\\s+\\w+=\".+\")*>(.*)<\/\\w+>"); 

	// <ship crew="22" len="230.00"><ship>123</ship></ship>
	// entire input matched = 0 group
	// tag name = 1 group
	// attributes = 2 group  :    crew="22" len="230.00"
	// value = 3 group		:	<ship>123</ship>

	std::regex advanced_tag_regex("<(\\w+)(\\s+\\w+=\".+\")*\\s*/>");

	// <ship crew="22" len="230.00"/>
	// entire input matched = 0 group
	// tag name = 1 group
	// attributes = 2 group  :    crew="22" len="230.00"
	std::regex multiple_tag_regex("<\\w+(?:\\s+\\w+=\".*\")*\\s*>(?:.*)<\/\\w+>|<\\w+(?:\\s+\\w+=\".*\")*\/>"); // base_tag_regex+advanced_tag_regex
	//
	xml::tag level_deserialized;
	//
	std::smatch sm_tags;
	try {
		for (std::sregex_iterator i = std::sregex_iterator(level.begin(), level.end(), multiple_tag_regex);
			i != std::sregex_iterator();
			++i) { // iter through multiple regex conciedences
			sm_tags = *i;
			std::string cur_tag = sm_tags.str();
			auto tmp = this->readBranchTag(cur_tag, base_tag_regex, advanced_tag_regex);
			level_deserialized.insert(tmp.begin(), tmp.end());
		}
	}
	catch(std::exception e) {
		std::cout << e.what() <<std::endl;
		throw e;
	}
	
	return level_deserialized;
}

xml::tag xml::XMLReader::extractFinalValues(std::string& boxed_value)
{
	std::regex value_regex("<(\\w+)(\\s+\\w+=\".*\")*>([^<]*)<\/\\w+>");

	// 0 - full match
	// 1 - tag name
	// 2 - attributes
	// 3 - value

	xml::tag values_map;

	std::smatch values;
	for (std::sregex_iterator i = std::sregex_iterator(boxed_value.begin(), boxed_value.end(), value_regex);i != std::sregex_iterator();++i) {
		values = *i;
		values_map[values[1]]["attributes"] = values[2].str();
		values_map[values[1]]["value"] = values[3].str();
	}
	return values_map;
}


xml::tag xml::XMLReader::readBranchTag(std::string& data, std::regex& base_tag_regex, std::regex& advanced_tag_regex) {
	std::smatch smatch_base;
	std::smatch smatch_advanced;
	auto end_cur_level_tag = 0;
	bool base_bool = std::regex_search(data, smatch_base, base_tag_regex);
	bool adv_bool = std::regex_search(data, smatch_advanced, advanced_tag_regex);
	std::map<
		std::string,
		std::map<
		std::string, std::string // watch return type of func
		>
	> dicted_data;

	auto convert_smatch = [](std::smatch& sm)-> std::string* {
		std::string* mas = new std::string[2];
		mas[0] = ltrim(sm[2].str()); // attrs
		mas[1] = sm[3].str(); // val
		return mas;
	};
	std::string* params;
	std::string header;
	if (base_bool) {
		params = convert_smatch(smatch_base);
		header = smatch_base[1].str();
	}
	else {
		params = convert_smatch(smatch_advanced);
		header = smatch_advanced[1].str();
	}
	dicted_data[header] = this->convertStringParameters(params[0], params[1]);
	return dicted_data;
}