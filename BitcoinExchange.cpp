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
	std::string		line;
	while (std::getline(data_file, line)) {
		std::istringstream	iss(line);
		std::string			data_str;
		double				value;

		if (std::getline(iss, data_str, ',') && iss >> value) {
			_data.insert(std::pair<std::string, double>(data_str, value));
		}
	}
}

BitcoinExchange::~BitcoinExchange() {
	return ;
}

std::map<std::string, double> const &BitcoinExchange::getData() const {
	return (_data);
}

void	BitcoinExchange::errorLine(std::string arg, std::string line) {
	try {
		throw std::invalid_argument(arg + line);
	} catch (std::exception	const &e) {
		std::cout << e.what() << std::endl;
		return ;
	}
}

std::string	BitcoinExchange::trim(std::string line) {
	size_t	begin = line.find_first_not_of(" ");
	size_t	end = line.find_last_not_of(" ");

	if (begin != std::string::npos)
		line = line.substr(begin);
	if (end != std::string::npos)
		line = line.substr(0, end + 1);
	return (line);
}

bool	BitcoinExchange::isValidDate(std::string line) {
	if (line.size() != 10) {
		errorLine("Error: wrong date format => ", line);
		return (false);
	}
	for (int i(0); i < 10; ++i) {
		if (i == 4 || i == 7) {
			if (line[i] != '-') {
				errorLine("Error: wrong date format => ", line);
				return (false);			
			}
		}
		else {
			if (!std::isdigit(line[i])) {
				errorLine("Error: wrong date format => ", line);
				return (false);
			}
		}
	}

	int	year = std::stoi(line.substr(0, 4));
	int	month = std::stoi(line.substr(5, 2));
	int	day = std::stoi(line.substr(8, 2));

	if (year) {
		errorLine("Error: wrong date format => ", line);
		return (false);
	}
	if (month < 1 || month > 12 || day < 1 || day > 31) {
		errorLine("Error: wrong date format => ", line);
		return (false);
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		errorLine("Error: wrong date format => ", line);
		return (false);
	}
	if (month == 2) {
		if (day > 28) {
			errorLine("Error: wrong date format => ", line);
			return (false);
		}
	}
	return (true);
}

bool	BitcoinExchange::isValidValue(std::string line) {
	bool	is_float = false;

	for (size_t i(0); i < line.size(); ++i) {
		if (line[i] == '-' && i == 0) {
			continue ;
		} else if (std::isdigit(line[i])) {
			continue;
		} else if ((i != 0 || i != line.size() - 1) && !is_float && line[i] == '.'
			&& std::isdigit(line[i - 1]) && std::isdigit(line[i + 1])) {
			is_float = true;
			continue ;
		} else {
			errorLine("Error: wrong value => ", line);
			return (false);
		}
	}
	return (true);
}
void	BitcoinExchange::outputGenerator(std::string line) {
	size_t	pos = line.find("|");

	if (pos == std::string::npos) {
		errorLine("Error: bad input", line);
		return ;
	}

	std::string	date = trim(line.substr(0, pos));
	std::string	value = trim(line.substr(pos + 1));

	if (isValidDate(date) == false) {
		return ;
	}
	if (isValidValue(value) == false) {
		return ;
	}
	std::cout << date << " : " << value << std::endl;
}

/*std::map<std::string, double>::const_iterator BitcoinExchange::findData(std::string const &date) const {
	std::map<std::string, double>::const_iterator	it;

	it = _data.find(date);
	if (it != _data.end()) {
		return (it);
	}
}*/
