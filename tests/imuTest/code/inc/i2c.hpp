
/*
 * i2c.hpp
 *
 *  Created on: 25/08/2014
 *      Author: benjaminkrebs
 */

#ifndef I2C_HPP_
#define I2C_HPP_

#include "types.hpp"
#include <linux/i2c-dev.h>

class I2C
{
public:
	I2C(const char* devicePath);
	//I2C(&I2C);
	~I2C();

	int writeI2C(U8* buffer,unsigned int numBytes,U8 i2cAddress);
	int readI2C(U8* buffer,unsigned int numBytes,U8 i2cAddress);


private:
	int i2c_fd;
};

#endif /* I2C_HPP_ */
