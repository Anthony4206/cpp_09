#pragma once

# include <string>
# include <fstream>
# include <map>

class BitcoinExchange {
	private:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &rhs);
		BitcoinExchange	&operator=(BitcoinExchange const &rhs);

		std::ifstream					_file;
		std::string						_line;
		std::map<std::string, double>	_data;
	public:
		BitcoinExchange(std::string const &csv_file);
		~BitcoinExchange();
};
