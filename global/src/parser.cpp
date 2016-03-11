/*
 * parser.cpp
 *
 *  Created on: 08/09/2014
 *      Author: benjaminkrebs
 */

static const char operatorArray[] = {'+','-','*','/','^','x','y'};


bool Parser::isOperator(char c, operators &op)
{
	for(int i=0;i<sizeof(operatorArray);i++){

	}
}

Parser::operators Parser::isTrigonometry(const char* pC)
{
	operators retOp = operators::OPERATOR_INVALID;

	if(strcmp(pC,"sin") == 0)
	{
		retOp = operators::OPERATOR_SIN;
	}
	else if(strcmp(pC,"tan") == 0)
	{
		retOp = operators::OPERATOR_TAN;
	}
	else if(strcmp(pC,"cos") == 0)
	{
		retOp = operators::OPERATOR_COS;
	}
	else if(strcmp(pC,"atan") == 0)
	{
		retOp = operators::OPERATOR_ATAN;
	}
	else if(strcmp(pC,"acos") == 0)
	{
		retOp = operators::OPERATOR_ACOS;
	}
	else if(strcmp(pC,"asin") == 0)
	{
		retOp = operators::OPERATOR_ASIN;
	}

	return retOp;
}

void Parser::parseExpression(char expression[],unsigned int exprLength)
{
	operators currentOp = operators::OPERATOR_INVALID;

	for(int i=0;i<exprLength;i++)
	{
		if(i<exprLength-4)
		{
			currentOp = isTrigonometry(&expression[i]);
			if(currentOp != operators::OPERATOR_INVALID)
			{
				std::cout<<"trigonometric function found!"<<std::endl;
			}
		}



	}
}
