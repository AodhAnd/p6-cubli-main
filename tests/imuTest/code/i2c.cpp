/*
 * i2c.cpp
 *
 *  Created on: 29/08/2014
 *      Author: benjaminkrebs
 */

#include <fcntl.h>
#include "./inc/types.hpp"
#include <linux/i2c-dev.h>
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

//this
#include "inc/i2c.hpp"

I2C::I2C(const char* devicePath)
{
	i2c_fd = open(devicePath, O_RDWR);
	if(i2c_fd<0)
	{
		perror("Unable to open i2c interface");
	}
	else
	{
		std::cout<<"i2c initialized.."<<std::endl;
	}

}

I2C::~I2C()
{
	if(close(i2c_fd)<0)
	{
		perror("Unable to close i2c");
	}
	else
	{
		std::cout<<"i2c closed up.."<<std::endl;
	}
}

int I2C::writeI2C(U8* buffer,unsigned int numBytes,U8 i2cAddress)
{
	ioctl(i2c_fd, I2C_SLAVE, i2cAddress);
	int bytesWritten = write(i2c_fd, buffer, numBytes);
	if(bytesWritten<0)
	{
		perror("Unable to write to i2c");
	}

	return bytesWritten;
}

int I2C::readI2C(U8* buffer,unsigned int numBytes,U8 i2cAddress)
{
	int ioctl_status;
	ioctl_status = ioctl(i2c_fd, I2C_SLAVE, i2cAddress);
	if (ioctl_status < 0)
	{
		perror("Error manipulating the I2C file descriptor");
	}
	int bytesRead = read(i2c_fd,buffer,numBytes);
	if(bytesRead<0)
	{
		perror("Unable to read from i2c");
	}

	return bytesRead;
}
