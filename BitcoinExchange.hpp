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

		std::map<std::string, double> const &getData() const;

		void								errorLine(std::string arg, std::string line);
		bool								isValidDate(std::string line);
		bool								isValidValue(std::string line);
		std::string							trim(std::string line);
		void								outputGenerator(std::string line);

//		std::map<std::string, double>::const_iterator	findData(std::string const &date) const;
};
