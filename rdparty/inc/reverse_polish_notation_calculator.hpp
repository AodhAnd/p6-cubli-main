/*
 * reverse_polish_notation_calculator.hpp
 *
 *  Created on: 13/09/2014
 *      Author: benjaminkrebs
 */

#ifndef REVERSE_POLISH_NOTATION_CALCULATOR_HPP_
#define REVERSE_POLISH_NOTATION_CALCULATOR_HPP_

#include "shunting_yard.hpp"
#include <vector>
#include <iostream>

class RpnCalculator
{
public:
	RpnCalculator();
	~RpnCalculator();
	RpnCalculator(bool isStateEquation);
	bool setEquation(std::vector<ShuntingYardToken> rpnExpression);
	double evaluateExpression();
	double evaluateExpression(std::vector<double> &vecX, std::vector<double> &vecU);
private:
	std::vector<ShuntingYardToken> mpExpression;
	std::vector<double> mStack;
	void getOperands(double (&operands)[2], std::vector<double> &stack);
	void singleOperandOperation(double (*mathOperation)(double));
};



#endif /* REVERSE_POLISH_NOTATION_CALCULATOR_HPP_ */
