/*
 * imu.cpp
 *
 *  Created on: 29/08/2014
 *      Author: benjaminkrebs
 */



#include <iostream>
#include <stdio.h>
#include "../inc/i2c.hpp"

//This
#include "../inc/imu.hpp"

Imu::Imu(U8 i2cAddr, I2C* i2cObj)
	:
	mpI2C(i2cObj),
	mI2cAddr(i2cAddr)
{
	setSleep(false);
	printf("IMU at 0x%X initialized...\n", i2cAddr);
}

Imu::~Imu()
{
	setSleep(true);
}

void Imu::setSleep(bool mode)
{
	U8 val = mode ? 0x40 : 0x00;
	writeByte(val, MPU6050_PWR_MGMT_1);
}

U8 Imu::getSleepMode()
{
	U8 modeOut;
	readByte(&modeOut, MPU6050_PWR_MGMT_1);
	return modeOut;
}


void Imu::writeByte(U8 val, U8 fromReg)
{
	U8 buffer[] = {fromReg, val}; //First transmit the register address to write to, then the value
	mpI2C->writeI2C(buffer, 2, mI2cAddr);
}

void Imu::readByte(U8* buffer, U8 fromReg)
{
	mpI2C->writeI2C(&fromReg, 1, mI2cAddr);
	mpI2C->readI2C(buffer, 1, mI2cAddr);
}

signed short Imu::readShort(U8 fromReg)
{
	U8 wData[2] = {0, 0};
	readData(wData, 2, fromReg);
	signed short retVal = ((signed short)(wData[0] << 8 | wData[1])); //Have to switch because of endian
	return retVal;
}


void Imu::readData(U8* buffer, unsigned int readLength, U8 fromReg)
{
	mpI2C->writeI2C(&fromReg, 1, mI2cAddr);
	mpI2C->readI2C(buffer, readLength, mI2cAddr);
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

/*
Imu::accAll_t Imu::getAccAll(void)
{
	accAll_t accel;
	U8 buffer[6];
	readData(buffer,6,MPU6050_ACCEL_X_H);
	accel.X = convertFromTwosComplement(buffer[0],buffer[1]);
	accel.Y = convertFromTwosComplement(buffer[2],buffer[3]);
	accel.Z = convertFromTwosComplement(buffer[4],buffer[5]);
	return accel;
}
*/

/** Returns the angular position of the frame using a complementary filter. */
double Imu::getPosition(double accAngleNow, double gyroVelocityNow, double Ts)
{
	//-------------- Tustin discretization ----------------//
	const double acc_off = 0.84;  	// accel meass offset
	const double tau = 0.5399;	// cut-off for the complementary filter

	// Coefficients for the complementary equation
	const double K1 = (2 * tau - Ts) / (2 * tau + Ts);
	const double K2 = Ts / (2 * tau + Ts);

	static double acc_angle[2] = {accAngleNow + acc_off, 0},
	                             gyro_angle[2] = {gyroVelocityNow, gyroVelocityNow},
	                             comp_angle[2] = {acc_angle[0], 0};

	// Set old measurement data
	acc_angle[1] = acc_angle[0];
	gyro_angle[1] = gyro_angle[0];
	gyro_angle[0] = gyroVelocityNow;
	comp_angle[1] = comp_angle[0];

	// Get angle from accel axis measurements
	acc_angle[0] = accAngleNow + acc_off;

	//Complementary equation using Tustin

	comp_angle[0] = K1 * comp_angle[1] + K2 * (acc_angle[0] + acc_angle[1] + tau * gyro_angle[0] + tau * gyro_angle[1]);


	//-------------- Euler discretization ----------------//
	// const double acc_off 	= 0.82;   	// accel measurement offset, used to correct data to 0 pos.
	//    const double tau 		= 0.1;   	// cut-off time-constant for the complementary filter
	//    const double k 			= 0.99;

	//    // Calculate the 2 constants of the complementary filter
	//    const double K1 = (2*tau-Ts)/(2*tau+Ts);
	//    const double K2 = Ts/(2*tau + Ts);

	//    static double acc_angle[2]={accAngleNow + acc_off,0},
	//        a=gyroVelocityNow,
	//        gyro_angle[9]={a,a,a,a,a,a,a,a,a},
	//        comp_angle[2]={acc_angle[0],0};

	//    // Set old measurement data
	//    acc_angle[1] = acc_angle[0];
	//    for (int i=8; i>0; i--)
	//      gyro_angle[i] = gyro_angle[i-1];
	//    gyro_angle[0] = gyroVelocityNow;
	//    comp_angle[1] = comp_angle[0];

	//    // Get angle from accel axis measurements
	//    acc_angle[0] = accAngleNow + acc_off;

	//    // Get gyro angle from gyro measurement
	//    static double sum=0;
	//    for (int i=0; i<9; i++)
	//      sum += gyro_angle[i];
	//    gyro_angle[0] =  sum * 9 * Ts;
	//    sum=0;

	//    //Complementary equation using Tustin
	//    //comp_angle[0] = K1*comp_angle[1] + K2*(acc_angle[0] + acc_angle[1] + tau*gyro_angle[0] + tau*gyro_angle[1]);
	//    //Complementry equation using backward Euler
	//    comp_angle[0] = k * (comp_angle[1] + gyroVelocityNow * Ts) + (1-k) * acc_angle[0];

	return comp_angle[0];
}
