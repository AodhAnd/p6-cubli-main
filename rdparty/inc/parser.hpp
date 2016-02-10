/*
 * parser.hpp
 *
 *  Created on: 08/09/2014
 *      Author: benjaminkrebs
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cmath>

class Parser {
public:
	void parseExpression(char expression[],unsigned int exprLength);


private:
	enum operators{
		OPERATOR_SIN,
		OPERATOR_COS,
		OPERATOR_TAN,
		OPERATOR_ASIN,
		OPERATOR_ACOS,
		OPERATOR_ATAN,
		OPERATOR_PLUS,
		OPERATOR_MINUS,
		OPERATOR_MULTIPY,
		OPERATOR_DIVIDE,
		OPERATOR_EXP,
		OPERATOR_INVALID
	};
	bool isOperator(char c, operators &op);
	operators isTrigonometry(const char* pC);

	std::vector<int> operatorIndex;
	std::vector<double> exprVec;
};



#endif /* PARSER_HPP_ */
