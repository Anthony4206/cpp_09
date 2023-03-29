#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "error: bad argument" << std::endl;
		return (-1);
	}

	BitcoinExchange	exchange("data.csv");

	std::ifstream	input_file(argv[1]);

	if (!input_file.is_open()) {
		try {
			throw std::runtime_error("error: the input file is invalid");
		} catch (std::exception const &e) {
			std::cout << e.what() << std::endl;
			return (-1);
		}
	}

	std::string		date;
	bool			first_line = true;
	while (std::getline(input_file, date)) {
		if (date == "date | value" && first_line) {
			first_line = false;
			continue ;
		} else if (first_line) {
			first_line = false;
		}
		exchange.outputGenerator(date);
	}
	return (0);
}
