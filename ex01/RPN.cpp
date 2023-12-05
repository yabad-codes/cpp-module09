/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:19:01 by yabad             #+#    #+#             */
/*   Updated: 2023/12/05 16:33:34 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN& other) {(void)other;}
RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other) {
	(void)other;
	return *this;
}

bool	RPN::isop(char op) {
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

void	RPN::print_error() {
	std::cout << "Error" << std::endl;
	exit(EXIT_FAILURE);
}

void	RPN::perform_operation(std::stack<int> &_stack, char op) {
	int	n2 = _stack.top();
	_stack.pop();
	int	n1 = _stack.top();
	_stack.pop();
	
	if (op == '+')
		_stack.push(n1 + n2);
	else if (op == '-')
		_stack.push(n1 - n2);
	else if (op == '*')
		_stack.push(n1 * n2);
	else
		_stack.push(n1 / n2);
}

void	RPN::calculate(std::string expr) {
	std::stack<int>	_stack;
	for (size_t i = 0; i < expr.length(); i++) {
		if (expr[i] == ' ')
			continue;
		else if (isdigit(expr[i]))
			_stack.push(static_cast<int>(expr[i] - 48));
		else if (RPN::isop(expr[i])) {
			if (_stack.size() >= 2)
				RPN::perform_operation(_stack, expr[i]);
			else
				RPN::print_error();
		}
		else
			print_error();
	}
	if (_stack.size() == 1)
		std::cout << _stack.top() << std::endl;
	else
		print_error();
}
