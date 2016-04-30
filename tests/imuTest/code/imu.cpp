
/*
 * imu.cpp
 *
 *  Created on: 29/08/2014
 *      Author: benjaminkrebs
 */



#include <iostream>
#include <stdio.h>
#include "./inc/i2c.hpp"

//This
#include "./inc/imu.hpp"

Imu::Imu(U8 i2cAddr,I2C* i2cObj)
:
mpI2C(i2cObj),
mI2cAddr(i2cAddr)
{
  setSleep(false);
  printf("IMU at 0x%2X initialized...\n",mI2cAddr);
}

Imu::~Imu()
{
  setSleep(true);
}

void Imu::setSleep(bool mode)
{
  U8 val = mode?0x40:0x00;
  writeByte(val,MPU6050_PWR_MGMT_1);
}

void Imu::setRegisterValue(U8 value, U8 regAddress)
{
  writeByte(value,regAddress);
}


U8 Imu::getSleepMode()
{
  U8 modeOut;
  readByte(&modeOut,MPU6050_PWR_MGMT_1);
  return modeOut;
}


void Imu::writeByte(U8 val, U8 fromReg)
{
  U8 buffer[] = {fromReg,val}; //First transmit the register address to write to, then the value
  mpI2C->writeI2C(buffer,2,mI2cAddr);
}

void Imu::readByte(U8* buffer, U8 fromReg)
{
  mpI2C->writeI2C(&fromReg,1,mI2cAddr);
  mpI2C->readI2C(buffer,1,mI2cAddr);
}

signed short Imu::readShort(U8 fromReg)
{
  U8 wData[2] = {0,0};
  readData(wData,2,fromReg);
  signed short retVal = ((signed short)(wData[0]<<8|wData[1])); //Have to switch because of endian
  return retVal;
}


void Imu::readData(U8* buffer, unsigned int readLength, U8 fromReg)
{
  mpI2C->writeI2C(&fromReg,1,mI2cAddr);
  mpI2C->readI2C(buffer,readLength,mI2cAddr);
}

signed short Imu::getAccX(void)
{
  return readShort(MPU6050_ACCEL_X_H);
}

signed short Imu::getAccY(void)
{
  return readShort(MPU6050_ACCEL_Y_H);
}


signed short Imu::getAccZ(void)
{
  return readShort(MPU6050_ACCEL_Z_H);
}


signed short Imu::getGyroX(void)
{
  return readShort(MPU6050_GYRO_X_H);
}

signed short Imu::getGyroY(void)
{
  return readShort(MPU6050_GYRO_Y_H);
}


signed short Imu::getGyroZ(void)
{
  return readShort(MPU6050_GYRO_Z_H);
}

U8 Imu::getRegisterValue(U8 regAddress)
{
  U8 buffer = 0;
  readByte(&buffer,regAddress);
  return buffer;
}