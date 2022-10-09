#include "utils.h"

std::string rtrim(std::string instr, char symb)
{
	instr.erase(instr.find_last_not_of(symb) + 1);
	return instr;
}

std::string ltrim(std::string instr, char symb)
{
	instr.erase(0, instr.find_first_not_of(symb));
	return instr;
}

std::string trim(std::string instr, char symb)
{
	return rtrim(ltrim(instr, symb), symb);
}
