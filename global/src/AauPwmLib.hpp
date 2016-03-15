/*
 * AauPwmLib.hpp
 *
 *  Created on: 16/11/2014
 *      Author: frederik
 */

#ifndef AAUPWMLIB_HPP_
#define AAUPWMLIB_HPP_

#include <string>
#include <stdio.h>
#include <iostream>



class AauPwm{
public:
	AauPwm(int P,int numPwm);
	~AauPwm();
	int getPeriod();
	int getDuty();
	float getPercent();
	int getPolarity();

	int setDuty(int duty);
	int setPeriod(int Period);
	float setPercent(float percent);
	int setPolarity(int);

	int run();
	int stop();




private:
	const char* mPath;
	float mPercent;
	bool mMode; // 1 for percent, 0 for duty
	int mPeriod;
	int mDuty;

};



#endif /* AAUPWMLIB_HPP_ */
