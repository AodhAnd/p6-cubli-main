/*
 * bbb_adc.hpp
 *
 *  Created on: 17/11/2014
 *      Author: benjaminkrebs
 */

#ifndef BBB_ADC_HPP_
#define BBB_ADC_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

class BbbAdc
{
public:
	typedef enum
	{
		AIN0 = 0,
		AIN1 = 1,
		AIN2 = 2,
		AIN3 = 3,
		AIN4 = 4,
		AIN5 = 5,
		AIN6 = 6,
		AIN7 = 7
	} analog_in_t;

	BbbAdc(analog_in_t analogIn);
	~BbbAdc();

	unsigned int get();
private:
	int mAdc_fd;
	char mPath[200];

};



#endif /* BBB_ADC_HPP_ */
