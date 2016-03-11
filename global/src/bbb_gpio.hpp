/*
 * bbb_io.hpp
 *
 *  Created on: 16/11/2014
 *      Author: benjaminkrebs
 */

#ifndef BBB_GPIO_HPP_
#define BBB_GPIO_HPP_

#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

class BbbGpio
{
public:
	typedef enum
	{
		BBB_GPIO_15 = 15,
		BBB_GPIO_114 = 114,
		BBB_GPIO_113 = 113,
		BBB_GPIO_2 = 2,
		BBB_GPIO_60 = 60
	}gpio_port_t;

	typedef enum
	{
		BBB_GPIO_DIRECTION_IN,
		BBB_GPIO_DIRECTION_OUT
	}gpio_direction_t;

	BbbGpio(gpio_port_t port, bool activeLow,gpio_direction_t direction);
	~BbbGpio();

	void setValue(bool value);
	bool getValue();


private:
	bool init();
	void setDirection(bool outEnable);
	void setActiveLow(bool enable);
	std::string mPath;

	int mDirFile;
	int mValFile;
	int mActiveLowFile;
};



#endif /* BBB_GPIO_HPP_ */
