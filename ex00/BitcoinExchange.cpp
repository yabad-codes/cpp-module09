/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:04:26 by yabad             #+#    #+#             */
/*   Updated: 2023/12/20 12:44:19 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {(void)other;}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other) {
	(void)other;
	return (*this);
}

bool	BitcoinExchange::split_line(std::string line, std::string del, std::string& date, std::string& value) {
	size_t	delPos = line.find(del);
	if (delPos != std::string::npos) {
		date = line.substr(0, delPos);
		value = line.substr(delPos + del.length());
		return (true);
	}
	return (false);
}

bool	BitcoinExchange::in_date_format(std::string date) {
	for (size_t i = 0; i < date.length(); i++) {
		if ((i == 4 || i == 7) && date[i] != '-')
			return false;
		if (i != 4 && i != 7 && !isdigit(date[i]))
			return false;
	}
	return true;
}

bool	BitcoinExchange::in_history_range(std::string date, t_date& s_date) {
	s_date.year = atoi(date.substr(0, 4).c_str());
	s_date.month = atoi(date.substr(5, 7).c_str());
	s_date.day = atoi(date.substr(8, 10).c_str());
	if (s_date.year < 2009 || s_date.year > 2023 ||\
		s_date.month < 1 || s_date.month > 12 ||\
		s_date.day < 1 || s_date.day > 31)
			return false;
	if (s_date.year == 2009 && s_date.month == 1 && s_date.day < 3)
		return false;
	return true;
}

bool	BitcoinExchange::date_is_valid(std::string date, t_date& s_date) {
	if (!in_date_format(date))
		return false;
	if (!in_history_range(date, s_date))
		return false;
	return true;	
}

double	BitcoinExchange::value_is_valid(std::string value) {
	char	*endPtr;
	double	number = std::strtod(value.c_str(), &endPtr);
	if (number >= static_cast<double>(0) && number <= static_cast<double>(1000) && *endPtr == '\0')
		return number;
	return -1;
}

double	strtodouble(std::string value) {
	char	*endPtr;
	double	number = std::strtod(value.c_str(), &endPtr);
	return number;
}

std::map<std::string, double>	BitcoinExchange::getData(const std::string dataPath) {
	std::map<std::string, double>	dataMap;
	std::ifstream	_file(dataPath);
	
	if (!_file.is_open()) {
		throw std::exception();
	}
	std::string	line;
	std::getline(_file, line);
	while (std::getline(_file, line)) {
		std::string date, value;
		BitcoinExchange::split_line(line, ",", date, value);
		dataMap[date] = strtodouble(value);
	}
	_file.close();
	return dataMap;
}

void	BitcoinExchange::performCalculations(std::string date, double number, std::map<std::string, double> dataMap) {
	std::map<std::string, double>::iterator it = dataMap.upper_bound(date);
	it--;
	std::cout << date << " => " << number << " = " << number * it->second << std::endl;
}

void	BitcoinExchange::startProcessing(std::ifstream& _file) {
	if (_file.is_open()) {
		std::map<std::string, double> dataMap;
		std::string	line;
		try {
			dataMap = getData(std::string("./data.csv"));
		} catch (...) {
			throw std::runtime_error("Can't read data from database");
		}
		std::getline(_file, line);
		if (line != std::string("date | value"))
			throw std::runtime_error("File format not valid");
		while (std::getline(_file, line)) {
			std::string	date;
			std::string value;
			if (!BitcoinExchange::split_line(line, " | ", date, value)) {
				std::cout << "Error : line isn't complete." << std::endl;
				continue;
			}
			t_date	s_date;
			if (BitcoinExchange::date_is_valid(date, s_date)) {
				double number = BitcoinExchange::value_is_valid(value);
				if (number == -1) {
					std::cout << "Error : value is not valid." << std::endl;
					continue;
				}
				performCalculations(date, number, dataMap);
			} else {
				std::cout << "Error : date is not valid." << std::endl;
				continue;
			}
		}
		_file.close();
		return ;
	}
	throw std::runtime_error("Can't open file.");
}