/*
 * adc_dac.hpp
 *
 *  Created on: 25/08/2014
 *      Author: benjaminkrebs
 *
 *  Notes:
 *  	Made especially to interface with the PCF8591
 */

#ifndef ADC_DAC_HPP_
#define ADC_DAC_HPP_

#include "types.hpp"
#include "i2c.hpp"

class AdcDac {
public:
	AdcDac(I2C* i2cIf, U8 deviceAddr);
	~AdcDac();
	U8 readAdc(unsigned int adcNumber);
	void setDac(unsigned int val);

private:
	I2C* mpI2C;
	U8 mDeviceAddr;
	U8 mControlByte;
};



#endif /* ADC_DAC_HPP_ */
