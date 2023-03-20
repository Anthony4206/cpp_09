#pragma once

# include <string>
# include <fstream>
# include <map>

class BitcoinExchange {
	private:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &rhs);
		BitcoinExchange	&operator=(BitcoinExchange const &rhs);

		std::map<std::string, double>	_data;
	public:
		BitcoinExchange(std::string const &csv_file);
		~BitcoinExchange();

		void								errorLine(std::string arg, std::string line);
		std::string							trim(std::string line);
		std::string							decrementDate(std::string date);
		bool								isValidDate(std::string line);
		bool								isValidValue(std::string line);
		void								outputGenerator(std::string line);
};
