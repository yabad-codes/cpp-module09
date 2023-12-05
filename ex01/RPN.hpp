/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:03:03 by yabad             #+#    #+#             */
/*   Updated: 2023/12/05 16:34:44 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN {
	private:
		RPN();
		RPN(const RPN&);
		~RPN();

		RPN& operator=(const RPN&);

		static bool	isop(char op);
		static void	print_error();
		static void	perform_operation(std::stack<int>&, char op);
	public:
		static void	calculate(std::string);
};

#endif