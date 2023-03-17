#include <iostream>
#include <exception>

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "error: bad argument" << std::endl;
		return (-1);
	}

	BitcoinExchange	exchange("data.csv");

	
	return (0);
}