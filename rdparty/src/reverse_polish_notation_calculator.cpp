/*
 * reverse_polish_notation_calculator.cpp
 *
 *  Created on: 13/09/2014
 *      Author: benjaminkrebs
 */

#include "../inc/shunting_yard.hpp"
#include <vector>
#include <tgmath.h>
#include "../inc/reverse_polish_notation_calculator.hpp"

RpnCalculator::RpnCalculator()
{

}

RpnCalculator::RpnCalculator(bool isStateEquation)
{

}

RpnCalculator::~RpnCalculator()
{
}


bool RpnCalculator::setEquation(std::vector<ShuntingYardToken> rpnExpression)
{
	bool retVal = false;

	mpExpression = std::vector<ShuntingYardToken>(rpnExpression);
	if(mpExpression.size() != 0)
	{
		retVal = true;
	}
	return retVal;
}

void RpnCalculator::getOperands(double (&operands)[2], std::vector<double> &stack)
{
	operands[0] = stack.back();
	stack.pop_back();
	operands[1] = stack.back();
	stack.pop_back();
}

void RpnCalculator::singleOperandOperation(double (*mathOperation)(double))
{
	double operand = mStack.back();
	mStack.pop_back();
	mStack.push_back(mathOperation(operand));
}

double RpnCalculator::evaluateExpression()
{
	if(mpExpression.size() == 0)
	{
		std::cout<<"RPN CALC: Expression NOT set!!" <<std::endl;
		return 0;
	}

	double operands[2] = {0,0};
	//rpn evaluator
	for(unsigned int i=0;i<mpExpression.size();i++)
	{
		std::cout << "Stack: ";
		for(int i=0;i<mStack.size();i++)
		{
			std::cout << mStack[i] << " ";
		}
		std::cout << std::endl;

		if(mpExpression[i].isOperator() && i>1)
		{
			operands[0] = 0;
			operands[1] = 0;

			switch (mpExpression[i].getOperator()) {
				case ShuntingYardToken::operators::PLUS:
					getOperands(operands,mStack);
					mStack.push_back(operands[1]+operands[0]);
					break;
				case ShuntingYardToken::operators::MINUS:
					getOperands(operands,mStack);
					mStack.push_back(operands[1]-operands[0]);
					break;
				case ShuntingYardToken::operators::MULTIPLICATION:
					getOperands(operands,mStack);
					mStack.push_back(operands[1]*operands[0]);
					break;
				case ShuntingYardToken::operators::DIVISION:
					getOperands(operands,mStack);
					mStack.push_back(operands[1]/operands[0]);
					break;
				case ShuntingYardToken::operators::POW:
					getOperands(operands,mStack);
					mStack.push_back(std::pow(operands[1],operands[0]));
					break;

					//Single operand operations
				case ShuntingYardToken::operators::SIN:
					singleOperandOperation(&std::sin);
					break;
				case ShuntingYardToken::operators::COS:
					singleOperandOperation(&std::cos);
					break;
				case ShuntingYardToken::operators::TAN:
					singleOperandOperation(&std::tan);
					break;
				case ShuntingYardToken::operators::ASIN:
					singleOperandOperation(&std::asin);
					break;
				case ShuntingYardToken::operators::ACOS:
					singleOperandOperation(&std::acos);
					break;
				case ShuntingYardToken::operators::ATAN:
					singleOperandOperation(&std::atan);
					break;
				case ShuntingYardToken::operators::SQRT:
					singleOperandOperation(&std::sqrt);
					break;
				default:
					std::cout<<"Unknown operator!" << std::endl;
					break;
			}
		}
		else if(mpExpression[i].isOperator() && i<1)
		{
			std::cout<<"ERROR: An operator came before any operands... Weird.."<<std::endl;
		}
		else
		{
			mStack.push_back(mpExpression[i].getNumber());
		}
	}

	if(mStack.size()>1)
	{
		std::cout<<"Something went wrong in the evaluation of the RPN equation, stack was: ";
		for(int i=0;i<mStack.size();i++)
		{
			 std::cout << mStack[i]<<" ";
		}
		std::cout << std::endl;
	}

	if(mStack.size()!=0)
	{
		return mStack.back();
	}
	else
	{
		return -1234567890;
	}

}

double RpnCalculator::evaluateExpression(std::vector<double> &vecX, std::vector<double> &vecU)
{

	return 0;
}


