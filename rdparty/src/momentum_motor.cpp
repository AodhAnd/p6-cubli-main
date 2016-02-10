/*
 * momentum_motor.cpp
 *
 *  Created on: 04/09/2014
 *      Author: benjaminkrebs
 */

#define RPM_MAX 5000

#include "../inc/momentum_motor.hpp"

MomentumMotor::MomentumMotor(const char* idName, BbbGpio::gpio_port_t gpioPort,  int pwmMotorP, int pwmMotorPin, int pwmServoP, int pwmServoPin)
:
mState(MOTOR_STATE_IDLE),
mName(idName),
mShellClient(mName,this),
mEnableGpio(gpioPort,false,BbbGpio::BBB_GPIO_DIRECTION_OUT),
mServoPwm(pwmServoP,pwmServoPin),
mMotorPwm(pwmMotorP,pwmMotorPin)
{
	//Set all the motor stuff such that it doesn't run!
	mServoPwm.setDuty(0);
	mServoPwm.setPeriod(20000000); //50 Hz
	mMotorPwm.setDuty(0);
	mMotorPwm.setPeriod(250000); // 4 kHz

	mMotorPwm.run();
	mServoPwm.run();

	stopMotorController();
	setBreak(false);
	setRpm(0);

	mEnableGpio.setValue(true);
}

MomentumMotor::~MomentumMotor()
{

}


bool MomentumMotor::hasState(motor_state state)
{
	return mState;
}

void MomentumMotor::setBreak(bool enable)
{
	if(enable)
	{
		mEnableGpio.setValue(false);
		mServoPwm.setDuty(20000000-135*10000);
	}
	else
	{
		mEnableGpio.setValue(true);
		mServoPwm.setDuty(20000000-125*10000);
	}

}

void MomentumMotor::emergencyBreak()
{

}

void MomentumMotor::setRpm(signed int rpm)
{
	setBreak(false);
	if(rpm > RPM_MAX)
		rpm = RPM_MAX;
	else if(-rpm > RPM_MAX)
		rpm = -RPM_MAX;

	double rpmVal = 0;
	rpmVal = 50+(double)rpm/5000*50;

	/*
	if(rpm == 0)
		mEnableGpio.setValue(false);
	else

*/
	mMotorPwm.setPercent(rpmVal);
	mEnableGpio.setValue(true);
}

void MomentumMotor::startMotorController(void)
{

}

void MomentumMotor::stopMotorController(void)
{

}

void MomentumMotor::receiveShellCommand(string* argv,unsigned int& argc)
{
	if(argc == 0)
	{
		cout<<endl<<mName<<" commands:"<<endl;
		cout<<"+"<<"stop"<<endl;
		cout<<"+"<<"rpm <value>"<<endl;

		cout<<endl;
	}
	else if(argv[1].compare("stop") == 0)
	{
		mEnableGpio.setValue(false);
	}
	else if(argv[1].compare("break") == 0)
	{
		setBreak(true);
	}
	else if(argv[1].compare("rpm") == 0)
	{
		setRpm(atoi(argv[2].c_str()));
	}
	else if(argv[1].compare("servo") == 0)
	{
		mServoPwm.setDuty(20000000-atoi(argv[2].c_str())*100000);
	}
	else
	{
		cout << mName << " received an unknown command"<<endl;
	}
}

const char* MomentumMotor::getClientName()
{
	return mName;
}
