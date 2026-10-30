#include "BitcoinExchange.hpp"

static std::string trim(const std::string &str);
static bool isLeapYear(int year);
static bool isValidDate(const std::string &date);
static bool parseNumber(const std::string &str, double &value);

BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: _rates(other._rates)
{
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

// Load database 
void BitcoinExchange::loadDatabase(const std::string &filename)
{
	(void)filename;
}

double BitcoinExchange::findRate(const std::string &date) const
{
	(void)date;
	return 1.0;

}


static std::string trim(const std::string &str)
{
	const std::string whitespace = " \t\r\n";

	std::string::size_type start =
		str.find_first_not_of(whitespace);
	if (start == std::string::npos)
		return "";
	
	std::string::size_type end =
		str.find_last_not_of(whitespace);
	
	return str.substr(start, end - start + 1);
}

static bool isLeapYear(int year)
{
	return (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0));
}

static bool isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	for (std::size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year;
	int month;
	int day;

	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12)
		return false;
	
	const int dayInMonth[12] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	int maxDay = dayInMonth[month - 1];

	if (month == 2 && isLeapYear(year))
		maxDay = 29;
	
	return(day >= 1 && day <= maxDay);

}

// 
static bool parseNumber(const std::string &str, double &value)
{
	std::stringstream ss(str);
	ss >> value;
	if (ss.fail())
		return false;
	ss >> std::ws;

	return ss.eof();
}


void BitcoinExchange::processInputFile(const std::string &filename) const
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("could not open file");
	/* ファイルエラーの種類 */
	// could not open file

	// empty input
	std::string line;
	if (!std::getline(file, line))
		throw std::runtime_error("empty input file");

	if (trim(line) != "date | value")
		throw std::runtime_error("invalid input header");
	// invalid input header とか？

	while (std::getline(file, line))
	{
		std::string::size_type pos = line.find('|');

		if (pos == std::string::npos || line.find('|', pos + 1) != std::string::npos)
		{
			std::cerr << "Error: bad input => "
					  << line << std::endl;
			continue;
		}
		std::string date = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 1));

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => "
					  << line << std::endl;
			continue;
		}

		double value;

		if (!parseNumber(valueStr, value))
		{
			std::cerr << "Error: bad input => "
					  << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number."
					  << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cerr << "Error: too large a number."
					  << std::endl;
			continue;
		}

		try
		{
			double rate = findRate(date);

			std::cout << date << " => "
					  << value << " = "
					  << value * rate << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what()
					  << std::endl;
		}
		


	}

	if (file.bad())
		throw std::runtime_error("input file read error");


	// bad input
	// ...

}

