#pragma once
#include <string>
#include <iostream>

std::string rtrim(std::string instr, char symb = ' ');
std::string ltrim(std::string instr, char symb = ' ');
std::string trim(std::string instr, char symb = ' ');
template <class T>
void print(T info, bool nl = true) {
	std::cout << info;
	if (nl) {
		std::cout << std::endl;
	}
}