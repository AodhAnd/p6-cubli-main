/*
 * shunting_yard.hpp
 *
 *  Created on: 13/09/2014
 *      Author: benjaminkrebs
 */

#ifndef SHUNTING_YARD_HPP_
#define SHUNTING_YARD_HPP_

#include <iostream>
#include <vector>
#include "../inc/types.hpp"

class ShuntingYardToken
{
public:
	enum operators
	{
		PLUS = '+',
		MINUS = '-',
		MULTIPLICATION = '*',
		DIVISION = '/',
		SQRT = 'Q',
		POW = '^',
		SIN = 'S',
		ASIN = 'A',
		COS = 'C',
		ACOS = 'B',
		TAN = 'T',
		ATAN = 'D',
		NOT_APPLICAPLE = 'N',
		LEFT_PAR = '(',
		RIGHT_PAR = ')'
	};



	ShuntingYardToken(double number):mOperator(operators::NOT_APPLICAPLE),mNumber(number),mIsOperator(false),mIsLeftPar(false),mIsRightPar(false)
	{	}

	ShuntingYardToken(operators mathOperator):mOperator(mathOperator),mNumber(0),mIsOperator(true),mIsLeftPar(false),mIsRightPar(false)
	{
		if(mathOperator == LEFT_PAR)
		{
			mIsLeftPar = true;
		}
		else if(mathOperator == RIGHT_PAR)
		{
			mIsRightPar = true;
		}
	}

	/*
	ShuntingYardToken(ShuntingYardToken& token):mOperator(token.mOperator),mNumber(token.mNumber),mIsOperator(token.mIsOperator)
	{	}
*/
	bool isOperator()
	{
		return mIsOperator;
	}

	bool isLeftPar()
	{
		return mIsLeftPar;
	}

	bool isRightPar()
	{
		return mIsRightPar;
	}

	operators getOperator()
	{
		return mOperator;
	}

	double getNumber()
	{
		return mNumber;
	}

	unsigned int getPrecedence()
	{
		unsigned int precedence = 0;

		switch (mOperator) {
		case PLUS:
			precedence=2;
			break;
		case MINUS:
			precedence=2;
			break;
		case MULTIPLICATION:
			precedence=3;
			break;
		case DIVISION:
			precedence=3;
			break;
		case POW:
			precedence=4;
			break;
		case SQRT:
			precedence=5;
			break;
		case SIN:
			precedence=5;
			break;
		case COS:
			precedence=5;
			break;
		case TAN:
			precedence=5;
			break;
		case ASIN:
			precedence=5;
			break;
		case ACOS:
			precedence=5;
			break;
		case ATAN:
			precedence=5;
			break;
		case LEFT_PAR:
			precedence=0;
			break;
		case RIGHT_PAR:
			precedence=0;
			break;
		case NOT_APPLICAPLE:
			precedence = 0;
			break;
		}
		return precedence;
	}

private:
	operators mOperator;
	double mNumber;
	bool mIsOperator;
	bool mIsLeftPar;
	bool mIsRightPar;
};












class ShuntingYardParser
{
public:
	ShuntingYardParser();

	std::vector<ShuntingYardToken> parseExpression(std::string mathString);
private:
	std::vector<ShuntingYardToken> mOutputStack;
	std::vector<ShuntingYardToken> mOperatorStack;

	void showStacks();
	void popWholeOperatorStack();

	enum {
		NUM_ONGOING,
		NUM_NO_NUMBER
	};
	U8 mNumState;

	std::string mCurrentDigits;

};

#endif /* SHUNTING_YARD_HPP_ */
