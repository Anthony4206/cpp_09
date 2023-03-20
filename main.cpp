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
			throw std::runtime_error("error: the file is invalid");
		} catch (std::exception const &e) {
			std::cout << e.what() << std::endl;
			return (-1);
		}
	}

	std::string		date;
	while (std::getline(input_file, date)) {
		exchange.outputGenerator(date);
	}
	
	return (0);
}
