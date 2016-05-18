/*
 * controller_base.hpp
 *
 *  Created on: 28/10/2014
 *      Author: benjaminkrebs
 */

#ifndef CONTROLLER_BASE_HPP_
#define CONTROLLER_BASE_HPP_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <cstddef>

#include "../shell_if/shell_client.hpp"
#include "controller_factory.hpp"
#include "../posix_thread/posix_thread.hpp"
#include "../../inc/i2c.hpp"
#include "../../inc/imu.hpp"
#include "../../inc/momentum_motor.hpp"


using namespace std;

enum ControllerType
{
	LSF,
	LSF2,
	PROP,
	SISOT
};

class ControllerCbIf;

class ControllerArgs
{
public:
	ControllerArgs(ControllerCbIf* pControllerIf, bool* debugEnable, bool* log2FileEnable, string* logFilename, Imu *imu1, Imu *imu2, bool *compFilterEnable, MomentumMotor *motor, BbbAdc *potAdc, BbbAdc *motorAdc1, BbbAdc *motorAdc2, BbbGpio* awesomeGpio, BbbGpio* raisePin, ControllerType* controlType)
		:
		mImu1(imu1),
		mImu2(imu2),
		mCompFilterEnable(compFilterEnable),
		mMotor(motor),
		mPotAdc(potAdc),
		mMotorAdc1(motorAdc1),
		mMotorAdc2(motorAdc2),
		mpControllerIf(pControllerIf),
		mDebugEnable(debugEnable),
		mAwesomeGpio(awesomeGpio),
		mRaisePin(raisePin),
		mControlType(controlType),
		mLog2FileEnable(log2FileEnable),
		mLogFilename(logFilename)
	{

	}
	~ControllerArgs() {}

	Imu* mImu1;
	Imu* mImu2;
	bool* mCompFilterEnable;
	bool* mLog2FileEnable;
	string* mLogFilename;
	MomentumMotor* mMotor;
	BbbAdc* mPotAdc;
	BbbAdc* mMotorAdc1;
	BbbAdc* mMotorAdc2;
	ControllerCbIf* mpControllerIf;
	bool* mDebugEnable;
	BbbGpio* mAwesomeGpio;
	BbbGpio* mRaisePin;
	ControllerType* mControlType;
};


class ControllerCbIf
{
public:
	virtual ~ControllerCbIf()	{}

	virtual const char* getControllerName() = 0;
	virtual void writeDebug() = 0;
	virtual void runController(ControllerArgs* args) = 0;
	virtual unsigned int getPeriodicityMus() = 0;
};


class ControllerBase : public ShellClientInterface {
public:

	/*
	 * Controllers inheriting the base class must implement a creation function having this outline:
	 * static bool createController(string controllerName);
	 */
	ControllerBase(ControllerCbIf* pControllerIf);
	virtual ~ControllerBase();

	void* controller(void* args);
	static void* controllerStatic(void* args);

	/**
	 * Checks for extra arguments which would be options to run the controller
	 * @param  argv string array with all the space-separated arguments (argv[0] is the controller itself)
	 * @param  argc number of supplementary arguments than the controller itself
	 * @return      boolean indicating whether help is asked or not
	 */
	bool checkForRunOptions(string* argv, unsigned int& argc);
	string getCmdOption(string* begin, string* end, const std::string& option);
	bool cmdOptionExists(string* begin, string* end, const std::string& option);
	string getFileName(string filepath);

public: // Implementing ShellClientInterface
	void receiveShellCommand(string* argv, unsigned int& argc);
	const char* getClientName();

private:
	bool mDebugEnable;
	bool mCompFilterEnable;
	bool mLog2FileEnable;
	string mLogFilename;

	ControllerCbIf* mpControllerIf;
	ShellClient mShell;
	PosixThread* mpThread;
	I2C mI2c;
	Imu mImu1;
	Imu mImu2;
	BbbAdc mPotAdc;
	BbbAdc mMotorRpm;
	BbbAdc mMotorPower;
	MomentumMotor mMotor;

	BbbGpio mAwesomeGpio;
	BbbGpio mRaisePin;
	ControllerType mControlType;
	ControllerArgs mControllerArgs;
};



#endif /* CONTROLLER_BASE_HPP_ */
