/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:04:47 by yabad             #+#    #+#             */
/*   Updated: 2023/12/20 12:43:25 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Error : could not open file." << std::endl;
		exit(EXIT_FAILURE);
	}
	std::ifstream	_file(av[1]);
	try {
		BitcoinExchange::startProcessing(_file);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return (0);
}