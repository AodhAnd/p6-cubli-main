/*
 * beaglebone_black.hpp
 *
 *  Created on: 25/10/2014
 *      Author: benjaminkrebs
 */

#ifndef BEAGLEBONE_BLACK_HPP_
#define BEAGLEBONE_BLACK_HPP_

#include <stdio.h>
#include <fcntl.h>

//GPIO
#define GPIO60	"/sys/class/gpio/gpio60/value"
#define GPIO30	"/sys/class/gpio/gpio30/value"

//PWM
#define EHRPWM0A




bool readGpio(const char* gpioAddr)
{
	char val;

	int fd = open(gpioAddr,O_RDONLY);

	if(fd == -1)
	{
		perror("GPIO does not exist!");
	}

	read(fd,&val,1);

	close(fd);

	if (val == '1')
		return true;
	else
		return false;
}


#endif /* BEAGLEBONE_BLACK_HPP_ */
