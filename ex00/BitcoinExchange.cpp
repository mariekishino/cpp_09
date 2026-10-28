#include "BitcoinExchange.hpp"

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

}

double BitcoinExchange::findRate(const std::string &date) const
{

}


void BitcoinExchange::processInputfile(const std::string &filename) const
{
	/* ファイルエラーの種類 */
	// could not open file
	// empty input
	// invalid input header とか？


	// bad input
	// ...

}

