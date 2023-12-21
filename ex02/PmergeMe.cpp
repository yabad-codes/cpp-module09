/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:47:02 by yabad             #+#    #+#             */
/*   Updated: 2023/12/21 14:32:41 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {(void)other;}

PmergeMe::~PmergeMe() {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other) {
	(void)other;
	return (*this);
}

bool	PmergeMe::numbers_valid(char **av) {
	int i = 1;
	while (av[i]) {
		if (!positive_integer(std::string(av[i])))
			return false;
		i++;
	}
	return true;
}

bool	PmergeMe::positive_integer(std::string str) {
	if (!only_digits(str) || exceeds_max(str.c_str(), str.length()))
		return false;
	return true;
}

bool	PmergeMe::exceeds_max(const char* str, size_t len) {
	if (str[0] == '+') {
		len--;
		str++;
	}
	if (len > MAX_LENGTH)
		return true;
	else if (len < MAX_LENGTH)
		return false;
	else {
		int i = 0;
		while (str[i]) {
			if (str[i] == MAX_INTEGER[i]) {
				i++;
				continue;
			}
			return (str[i] > MAX_INTEGER[i]);
		}
	}
	return false;
}

bool	PmergeMe::only_digits(std::string str) {
	int i = 0;
	if (str[i] == '+')
		i++;
	while (str[i]) {
		if (!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

void PmergeMe::get_values(char **av, int_vect& vect_nums, int_deque& deque_nums) {
	int i = 1;
	while (av[i]) {
		int num = atoi(av[i]);
		vect_nums.push_back(num);
		deque_nums.push_back(num);
		i++;
	}
}

int	PmergeMe::safe_exit(int exit_status) {
	std::cout << "Error" << std::endl;
	exit(exit_status);
}

void PmergeMe::print_vect_of_vect(std::vector<int_vect> v) {
	std::vector<int_vect>::iterator it;
	int_vect::iterator v_it;
	std::cout << "[ ";
	for (it = v.begin(); it != v.end(); it++) {
		std::cout << "{ ";
		print_vect(CYAN, "", *it);
		std::cout << " }";
		if (it != v.end() - 1)
			std::cout << ", ";
	}
}

void PmergeMe::print_vect(const char* color, const char* status, int_vect &vect) {
	int_vect::iterator it;

	std::cout << color << status;
	for (it = vect.begin(); it != vect.end(); it++) {
		std::cout << *it;
		if (it != vect.end() - 1)
			std::cout << " ";
	}
	std::cout << RESET << std::endl;
}

void PmergeMe::print_vect_of_pairs(vect_pair vect) {
	vect_pair::iterator it;
	std::cout << "{ ";
	for (it = vect.begin(); it != vect.end(); it++) {
		std::cout << "(";
		PmergeMe::print_vect(GREEN, "",(*it).first);
		std::cout << " ,";
		PmergeMe::print_vect(RED, "", (*it).second);
		std::cout << ")";
		if (it != vect.end() - 1)
			std::cout << " ";
	}
	std::cout << RESET << " }" << std::endl;
}

void PmergeMe::print_deque(const char* color, const char* status, int_deque& deq) {
	int_deque::iterator it;

	std::cout << color << status;
	for (it = deq.begin(); it != deq.end(); it++) {
		std::cout << *it;
		if (it != deq.end() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::print_time(clock_t start, clock_t end, size_t container_size, const char* type) {
	double time_taken = (double(end - start) * 1000) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << RED << container_size << RESET << " elements with " << RED << type << RESET << " : ";
	std::cout << GREEN << time_taken << RESET << " us" << std::endl;
}

// Ford-Johnson Algorithm for Vectors

void PmergeMe::create_pairs_for_vect(int_vect& numbers, vect_pair& v, size_t len, size_t pairLen) {
	size_t index = 0;
	size_t pairsLeftToCreate = (len / pairLen) % 2 ? len / pairLen - 1 : len / pairLen;

	while (pairsLeftToCreate) {
		int_vect v1, v2;
		while (v1.size() != pairLen)
			v1.push_back(numbers[index++]);
		while (v2.size() != pairLen)
			v2.push_back(numbers[index++]);
		v.push_back(make_pair(v1, v2));
		pairsLeftToCreate -= 2;
	}
}

void PmergeMe::merge_and_update_vect(int_vect& numbers, vect_pair& v) {
	vect_pair::iterator it;
	int_vect::iterator v_it;
	size_t index = 0;

	for (it = v.begin(); it != v.end(); it++) {
		if (it->first.back() > it->second.back()) {
			for (v_it = it->second.begin(); v_it != it->second.end(); v_it++)
				numbers[index++] = *v_it;
			for (v_it = it->first.begin(); v_it != it->first.end(); v_it++)
				numbers[index++] = *v_it;
		}
		else
			index += (it->first.size() * 2);
	}
}

size_t binary_search_insert_vect(const int_vect& numbers, int value, size_t start, size_t end) {
    int_vect::const_iterator lower = std::lower_bound(numbers.begin() + start, numbers.begin() + end, value);
    return static_cast<size_t>(lower - numbers.begin());
}

void PmergeMe::insertion_vect(int_vect& numbers, size_t len, size_t pairLen) {
	for (size_t i = pairLen; i < len; i++) {
		int current = numbers[i];
		size_t j = i - 1;
		size_t insertionPoint = binary_search_insert_vect(numbers, current, 0, i);
		
		while (j >= insertionPoint && j < i) {
			numbers[j + 1] = numbers[j];
			if (j == 0) {
				break;
			}
			j--;
		}
		numbers[insertionPoint] = current;
	}
}

void PmergeMe::merge_insertion_vect(int_vect& numbers, size_t len, size_t pairLen) {
	vect_pair v;
	size_t newSize = (len / pairLen) % 2 ? len - pairLen : len;

	if (pairLen == len)
		return ;
	create_pairs_for_vect(numbers, v, len, pairLen);
	merge_and_update_vect(numbers, v);
	merge_insertion_vect(numbers, newSize, pairLen * 2);
	insertion_vect(numbers, len, pairLen);
}

void PmergeMe::start_sorting_vect(int_vect& numbers) {
	merge_insertion_vect(numbers, numbers.size(), 1);
}

// Ford-Johnson Algorithm for Deques

size_t binary_search_insert_deque(const int_deque& numbers, int value, size_t start, size_t end) {
    int_deque::const_iterator lower = std::lower_bound(numbers.begin() + start, numbers.begin() + end, value);
    return static_cast<size_t>(lower - numbers.begin());
}

void PmergeMe::insertion_deque(int_deque& numbers, size_t len, size_t pairLen) {
    for (size_t i = pairLen; i < len; i++) {
        int current = numbers[i];
        size_t j = i - 1;

        size_t insertionPoint = binary_search_insert_deque(numbers, current, 0, i);

        while (j >= insertionPoint && j < i) {
            numbers[j + 1] = numbers[j];
            if (j == 0) {
                break;
            }
            j--;
        }

        numbers[insertionPoint] = current;
    }
}

void PmergeMe::merge_and_update_deque(int_deque& numbers, deque_pair& v) {
	deque_pair::iterator it;
	int_deque::iterator v_it;
	size_t index = 0;

	for (it = v.begin(); it != v.end(); it++) {
		if (it->first.back() > it->second.back()) {
			for (v_it = it->second.begin(); v_it != it->second.end(); v_it++)
				numbers[index++] = *v_it;
			for (v_it = it->first.begin(); v_it != it->first.end(); v_it++)
				numbers[index++] = *v_it;
		}
		else
			index += (it->first.size() * 2);
	}
}

void PmergeMe::create_pairs_for_deque(int_deque& numbers, deque_pair& v, size_t len, size_t pairLen) {
	size_t index = 0;
	size_t pairsLeftToCreate = (len / pairLen) % 2 ? len / pairLen - 1 : len / pairLen;

	while (pairsLeftToCreate) {
		int_deque v1, v2;
		while (v1.size() != pairLen)
			v1.push_back(numbers[index++]);
		while (v2.size() != pairLen)
			v2.push_back(numbers[index++]);
		v.push_back(make_pair(v1, v2));
		pairsLeftToCreate -= 2;
	}
}

void PmergeMe::merge_insertion_deque(int_deque& numbers, size_t len, size_t pairLen) {
	deque_pair v;
	size_t newSize = (len / pairLen) % 2 ? len - pairLen : len;

	if (pairLen == len)
		return ;
	create_pairs_for_deque(numbers, v, len, pairLen);
	merge_and_update_deque(numbers, v);
	merge_insertion_deque(numbers, newSize, pairLen * 2);
	insertion_deque(numbers, len, pairLen);
}

void PmergeMe::start_sorting_deque(int_deque& numbers) {
	merge_insertion_deque(numbers, numbers.size(), 1);
}