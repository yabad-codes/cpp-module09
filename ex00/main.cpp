/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:04:47 by yabad             #+#    #+#             */
/*   Updated: 2023/12/04 17:51:31 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Error : could not open file." << std::endl;
		return (-1);
	}
	std::ifstream	_file(av[1]);
	BitcoinExchange::startProcessing(_file);
	return (0);
}