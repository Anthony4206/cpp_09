#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string const &csv_file) {
	std::ifstream	data_file(csv_file);

	if (!data_file.is_open()) {
		throw std::runtime_error("error: the file is invalid");
	}

	std::string	line;
	while (std::getline(data_file, line)) {
		std::istringstream	iss(line);
		std::string			data_str;
		double				value;

		if (std::getline(iss, data_str, '|') && iss >> value) {
			_data.insert({data_str, value});
		}

	}
}

BitcoinExchange::~BitcoinExchange() {
	return ;
}