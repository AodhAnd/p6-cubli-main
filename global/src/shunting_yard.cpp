/*
 * shunting_yard.cpp
 *
 *  Created on: 13/09/2014
 *      Author: benjaminkrebs
 */


#include <string.h>
#include <ctype.h>

#include "../inc/shunting_yard.hpp"

const std::string VALID_NUMBERS("1234567890.");
const std::string VALID_OPERATORS[] = {"sin","asin","cos","acos","tan","atan","sqrt","^","+","-","*","/"};

ShuntingYardParser::ShuntingYardParser():mNumState(NUM_NO_NUMBER)
{

}

void ShuntingYardParser::showStacks()
{
	std::cout << "Output Stack: ";
	for(int j=0;j<mOutputStack.size();j++){
		if(mOutputStack[j].isOperator())
		{
			std::cout << (char)mOutputStack[j].getOperator() << " ";
		}
		else
		{
			std::cout << mOutputStack[j].getNumber() << " ";
		}

	}
	std::cout << "\t Operator Stack: ";
	for(int j=0;j<mOperatorStack.size();j++){std::cout << (char)mOperatorStack[j].getOperator() << " ";}
	std::cout << std::endl;
}

std::vector<ShuntingYardToken> ShuntingYardParser::parseExpression(std::string mathString)
{
	std::cout<<"String to be parsed: "<<mathString<<std::endl;

	ShuntingYardToken* intermediateToken;

	int lastOpSize = 0;
	int lastOuSize = 0;

	for(int i=0;i<mathString.size();i++)
	{
		std::cout << "Parsing char: "<<mathString[i]<<std::endl;

		lastOpSize = mOperatorStack.size();
		lastOuSize = mOutputStack.size();



		// Check if it is a number
		if((mNumState == NUM_ONGOING || isdigit(mathString[i])) && i+1 == mathString.size())
		{
			mCurrentDigits.push_back(mathString[i]);
			mOutputStack.push_back(atof(mCurrentDigits.c_str()));
			mCurrentDigits.clear();
			mNumState = NUM_NO_NUMBER;
		}
		else if(isdigit(mathString[i]))
		{
			mCurrentDigits.push_back(mathString[i]);
			mNumState = NUM_ONGOING;
		}
		else if(mNumState == NUM_ONGOING)
		{
			mOutputStack.push_back(atof(mCurrentDigits.c_str()));
			mCurrentDigits.clear();
			mNumState = NUM_NO_NUMBER;
		}




		// Check if it is an operator
		switch (mathString[i]) {
		case '+':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::PLUS));
			break;
		case '-':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::MINUS));
			break;
		case '*':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::MULTIPLICATION));
			break;
		case '/':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::DIVISION));
			break;
		case '^':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::POW));
			break;
		case '(':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::LEFT_PAR));
			break;
		case ')':
			mOperatorStack.push_back(ShuntingYardToken(ShuntingYardToken::operators::RIGHT_PAR));
			break;
		default:
			break;
		}



		//Handle operator precedence and operator stack
		if(mOperatorStack.size()>lastOpSize && mOperatorStack.size()>1)
		{
			if(mOperatorStack.back().getPrecedence() == mOperatorStack.at(mOperatorStack.size()-2).getPrecedence())
			{
				mOutputStack.push_back(mOperatorStack.at(mOperatorStack.size()-2));
				mOperatorStack.erase(mOperatorStack.end()-2);
			}
			else if(mOperatorStack.back().getPrecedence() < mOperatorStack.at(mOperatorStack.size()-2).getPrecedence())
			{
				intermediateToken = new ShuntingYardToken(mOperatorStack.at(mOperatorStack.size()-1));
				mOperatorStack.pop_back();
				popWholeOperatorStack();
				mOperatorStack.push_back(*intermediateToken);
				delete intermediateToken;
			}
		}



		showStacks();

	}











	popWholeOperatorStack();

	showStacks();



	return mOutputStack;
}

void ShuntingYardParser::popWholeOperatorStack()
{
	//Pop the operator stack onto the output stack
	while(!mOperatorStack.empty())
	{
		mOutputStack.push_back(mOperatorStack.back());
		mOperatorStack.pop_back();
	}
}
