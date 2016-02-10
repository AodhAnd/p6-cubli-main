/*
 * adc_dac.cpp
 *
 *  Created on: 31/08/2014
 *      Author: benjaminkrebs
 */




AdcDac::AdcDac(I2C* i2cIf, U8 deviceAddr)
:
mpI2C(i2cIf),
mDeviceAddr(deviceAddr),
mControlByte(0x40)
{
	setDac(0);
}

AdcDac::~AdcDac()
{
	setDac(0);
}

U8 AdcDac::readAdc(unsigned int adcNumber)
{
	mControlByte = 0x40 + adcNumber;
	U8 buf[2] = {mControlByte, 0};
	mpI2C->writeI2C(&buf[0],1,mDeviceAddr);
	mpI2C->readI2C(&buf[1],1,mDeviceAddr);
	return buf[1];
}

void AdcDac::setDac(unsigned int val)
{
	U8 buf[2] = {mControlByte,val};
	mpI2C->writeI2C(buf, 2, mDeviceAddr);
}
