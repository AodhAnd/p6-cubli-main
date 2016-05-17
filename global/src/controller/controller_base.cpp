/*
 * controller_base.cpp
 *
 *  Created on: 29/10/2014
 *      Author: benjaminkrebs
 */

#include "controller_base.hpp"

#define IMU1_PATH "/dev/i2c-1"

ControllerBase::ControllerBase(ControllerCbIf* pControllerIf)
	:
	mpControllerIf(pControllerIf),
	mShell("", this),
	mDebugEnable(false),
	mpThread(NULL),
	mI2c(IMU1_PATH),
	mImu1(0x69, &mI2c),
	mImu2(0x68, &mI2c),
	mCompFilterEnable(true),
	mMotor("m", BbbGpio::BBB_GPIO_2, 9, 14, 8, 13),
	mPotAdc(BbbAdc::AIN5),
	mMotorRpm(BbbAdc::AIN1),
	mMotorPower(BbbAdc::AIN3),
	mAwesomeGpio(BbbGpio::BBB_GPIO_60, false, BbbGpio::BBB_GPIO_DIRECTION_OUT),
	mRaisePin(BbbGpio::BBB_GPIO_61, false, BbbGpio::BBB_GPIO_DIRECTION_OUT),
	mControlType(LSF2),
	mControllerArgs(&mImu1, &mImu2, &mCompFilterEnable, &mMotor, &mPotAdc, &mMotorRpm, &mMotorPower, mpControllerIf, &mDebugEnable, &mAwesomeGpio, &mRaisePin, &mControlType)
{
//mShell(mpControllerIf->getControllerName(),this),

}

ControllerBase::~ControllerBase()
{
	delete mpThread;
}



// Implementing ShellClientInterface
void ControllerBase::receiveShellCommand(string* argv, unsigned int& argc)
{
	if (argc == 0)
	{
		cout << endl << mpControllerIf->getControllerName() << " commands:" << endl;
		cout << "+" << "stop" << endl;
		cout << "+" << "run" << endl;

		cout << endl;
	}
	else if (argv[1].compare("stop") == 0)
	{

		if (mpThread != NULL)
		{
			mpThread->stopThread();
			delete mpThread;
			mpThread = NULL;
		}

	}
	else if (argv[1].compare("run") == 0)
	{
		// Checking for supplementary arguments
		checkForRunOptions(argv, argc);

		if (mpThread == NULL)
		{
			mpThread = new PosixThread(&controllerStatic, mpControllerIf->getPeriodicityMus(), 2);
			mpThread->startThread((void*)&mControllerArgs);
		}
		else
			cout << "Controller is already running... Stop it and run it again." << endl;

	}
	else if (argv[1].compare("debug") == 0)
	{
		mDebugEnable = !mDebugEnable;

		if (mDebugEnable)
			cout << "Debug Enabled" << endl;
		else
			cout << "Debug Disabled" << endl;

		*(mControllerArgs.mDebugEnable) = mDebugEnable;
	}
	else if (argv[1].compare("compfilter") == 0) 
	{
		if (argc >= 2) 
		{
			if (argv[2].compare("on") == 0) 
			{
				mCompFilterEnable = true;
			}
			else if (argv[2].compare("off") == 0) 
			{
				mCompFilterEnable = false;
			}
		}
		else {
			mCompFilterEnable = !mCompFilterEnable;
		}
		if (mCompFilterEnable)
			cout << "Complementary Filter Enabled" << endl;
		else
			cout << "Complementary Filter Disabled" << endl;

		*(mControllerArgs.mCompFilterEnable) = mCompFilterEnable;
	}
	else
	{
		cout << mpControllerIf->getControllerName() << " received an unknown command" << endl;
	}
}

void ControllerBase::checkForRunOptions(string* argv, unsigned int& argc)
{
	string optionBuffer;
	if (argc < 2) {
		return;
	}

	if (cmdOptionExists(&argv[1], &argv[sizeof(argv)], "--no-comp") || cmdOptionExists(&argv[1], &argv[sizeof(argv)], "-nc")) {
		mCompFilterEnable = false;
		*(mControllerArgs.mCompFilterEnable) = mCompFilterEnable;
		cout << "Complementary Filter Disabled" << endl;
	}
	else if (cmdOptionExists(&argv[1], &argv[sizeof(argv)], "-c")) {
		mCompFilterEnable = true;
		*(mControllerArgs.mCompFilterEnable) = mCompFilterEnable;
		cout << "Complementary Filter Enabled" << endl;
	}
	else if (cmdOptionExists(&argv[1], &argv[sizeof(argv)], "-t")) {
		optionBuffer = getCmdOption(&argv[1], &argv[sizeof(argv)], "-t");
		if (optionBuffer.c_str() != NULL) {
			if (optionBuffer.compare("lsf") == 0) {
				mControlType = LSF;
			}
			else if (optionBuffer.compare("lsf2") == 0) {
				mControlType = LSF2;
			}
			else if (optionBuffer.compare("prop") == 0) {
				mControlType = PROP;
			}
			else if (optionBuffer.compare("sisotool") == 0) {
				mControlType = SISOT;
			}
			else {
				cout << "Wrong options, -l works with:" << endl;
				cout << "lsf" << endl;
				cout << "lsf2" << endl;
				cout << "prop" << endl;
				cout << "sisotool" << endl;
				cout << "Now running with default lsf2..." << endl;
			}
			* (mControllerArgs.mControlType) = mControlType;
		}
	}
}

void* ControllerBase::controllerStatic(void* args)
{

	ControllerArgs* controllerArgs = (ControllerArgs*)args;

	if (controllerArgs->mpControllerIf != NULL)
	{
		//controllerArgs->mpControllerIf->writeDebug();
		controllerArgs->mpControllerIf->runController(controllerArgs);
	}
	return NULL;
}

const char* ControllerBase::getClientName()
{
	return mpControllerIf->getControllerName();
}

string ControllerBase::getCmdOption(string* begin, string* end, const std::string& option)
{
	string* itr = std::find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

bool ControllerBase::cmdOptionExists(string* begin, string* end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}