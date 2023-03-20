#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string const &csv_file) {
	std::ifstream	data_file(csv_file);

	if (!data_file.is_open()) {
		try {
			throw std::runtime_error("error: the file is invalid");
		} catch (std::exception const &e) {
			std::cout << e.what() << std::endl;
			return ;
		}
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

void	BitcoinExchange::errorLine(std::string arg, std::string line) {
	try {
		if (!line.empty())
			throw std::invalid_argument(arg + line);
		else
			throw std::invalid_argument(arg);
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

std::string	BitcoinExchange::decrementDate(std::string date) {
	int	year = std::stoi(date.substr(0, 4));
	int	month = std::stoi(date.substr(5, 2));
	int	day = std::stoi(date.substr(8, 2));

	if (month == 1 && day == 1) {
		year--;
		month = 12;
		day = 31;
	} else if (day == 1) {
		month--;
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			day = 30;
		} else if (month == 2) {
			day = 28;
		} else {
			day = 31;
		}
	} else {
		day--;
	}
	date.replace(0, 4, std::to_string(year));
	if (month < 10) {
		date.replace(5, 1, "0");
		date.replace(6, 1, std::to_string(month));
	} else {
		date.replace(5, 2, std::to_string(month));
	}
	if (day < 10) {
		date.replace(8, 1, "0");
		date.replace(9, 1, std::to_string(day));
	} else {
		date.replace(8, 2, std::to_string(day));
	}
	return (date);
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
	if (year < 2009 || (year == 2009 && month == 1 && day == 1)) {
		errorLine("Error: the date is too old => ", line);
		return (false);
	}
	if (year > 2023 || (year == 2023 && month > 3)) {
		errorLine("Error: cannot use a future date => ", line);
		return (false);
	}
	return (true);
}

bool	BitcoinExchange::isValidValue(std::string line) {
	bool	is_float = false;

	for (size_t i(0); i < line.size(); ++i) {
		if (line[i] == '-' && i == 0) {
			continue ;
		} else if (std::isdigit(line[i])) {
			continue ;
		} else if ((i != 0 || i != line.size() - 1) && !is_float && line[i] == '.'
			&& std::isdigit(line[i - 1]) && std::isdigit(line[i + 1])) {
			is_float = true;
			continue ;
		} else {
			errorLine("Error: wrong value => ", line);
			return (false);
		}
	}

	double	value = std::stod(line);

	if (value < 0) {
		errorLine("Error: not a positive number.", "");
		return (false);
	} else if (value > 1000) {
		errorLine("Error: too large a number.", "");
		return (false);	
	}
	return (true);
}

void	BitcoinExchange::outputGenerator(std::string line) {
	size_t	pos = line.find("|");

	if (pos == std::string::npos) {
		errorLine("Error: bad input => ", line);
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
	std::cout << date << " => " << value << " = ";

	std::map<std::string, double>::iterator	it;

	while (1) {
		it = _data.find(date);
		if (it != _data.end()) {
			break;
		}
		date = decrementDate(date);
	} 
	std::cout << (it->second * std::stod(value))  << std::endl;
}
