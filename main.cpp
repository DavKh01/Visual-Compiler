#include <iostream>
#include "compiler.h"
int main() {
	std::string input;
	std::cout << "Enter the input file name (name.txt): ";
	std::cin >> input;
	used_types(input);
	create_table(input);
}