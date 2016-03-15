/*
 * converter.hpp
 *
 *  Created on: 31/08/2014
 *      Author: benjaminkrebs
 */

#ifndef CONVERTER_HPP_
#define CONVERTER_HPP_

#include "types.hpp"
#include <stdio.h>

class Converter
{
public:
	static signed int twosComplementToSignedInt(U8 msb, U8 lsb)
	{
		signed int val = 0;



		if(msb>>7 == 0x1) //Negative number
		{
			val = - (((~(msb) << 8 | (~(lsb) & 0xFF)) & 0x7FFF)+1);
		}
		else //Positive number
		{
			val = ((msb) << 8 | ((lsb) & 0xFF)) & 0x7FFF;
		}

		printf("val is: %#04x , %d , msb>>7: %#2x \n",val,val, msb>>7);

		return val;
	}
};



#endif /* CONVERTER_HPP_ */
