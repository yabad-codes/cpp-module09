/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:47:16 by yabad             #+#    #+#             */
/*   Updated: 2023/12/19 22:42:59 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av) {
	std::vector<int> vect_numbers;
	std::deque<int> deque_numbers;
	clock_t	start, end;
	
	if (ac <= 1 || !PmergeMe::numbers_valid(av))
		PmergeMe::safe_exit(EXIT_FAILURE);
		
	PmergeMe::get_values(av, vect_numbers, deque_numbers);
	
	//using vectors
	PmergeMe::print_vect(PURPLE, "Before : ", vect_numbers);
	start = clock();
	PmergeMe::start_sorting_vect(vect_numbers);
	end = clock();
	PmergeMe::print_vect(CYAN, "After : ", vect_numbers);
	PmergeMe::print_time(start, end, vect_numbers.size(), "std::vector");

	//using deques
	start = clock();
	PmergeMe::start_sorting_deque(deque_numbers);
	end = clock();
	PmergeMe::print_time(start, end, vect_numbers.size(), "std::deque");
	return 0;
}