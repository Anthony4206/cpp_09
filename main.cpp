#include <iostream>
#include <exception>

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "error: bad argument" << std::endl;
		return (-1);
	}

	BitcoinExchange	exchange("data.csv");

    std::map<std::string, double>::const_iterator it;

    for (it = exchange.getData().begin(); it != exchange.getData().end(); ++it)
	
	return (0);
}
