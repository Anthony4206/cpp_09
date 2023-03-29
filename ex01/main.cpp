#include <iostream>
#include <string>

#include "RPN.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "error: bad argument" << std::endl;
		return (-1);
	}

	RPN			stack;
	std::string	input = argv[1];

	if (input.empty()) {
		std::cerr << "error: argument is empty" << std::endl;
		return (-1);
	}
	for (size_t i(0); i < input.size(); ++i) {
		if (std::isdigit(input[i])) {
			stack.digitProcessing(input.substr(i, 1));
		} else if (input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*') {
			stack.signProcessing(input.substr(i, 1));
		} else if (input[i] == ' ') {
			continue ;
		} else {
			std::cerr << "Error" << std::endl;
			return (-1);
		}
	}
	if (stack.checkStack() == -1) {
		std::cerr << "error: missing sign" << std::endl;
		return (-1);
	}
	std::cout << stack.getResult() << std::endl;
	return (0);
} 