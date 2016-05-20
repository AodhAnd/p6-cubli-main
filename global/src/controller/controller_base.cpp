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
	mLog2FileEnable(false),
	mLogFilename("log.csv"),
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
	mControllerArgs(mpControllerIf, &mDebugEnable, &mLog2FileEnable, &mLogFilename, &mImu1, &mImu2, &mCompFilterEnable, &mMotor, &mPotAdc, &mMotorRpm, &mMotorPower, &mAwesomeGpio, &mRaisePin, &mControlType)
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
	bool helpWanted;

	if (argc == 0)
	{
		cout << endl << mpControllerIf->getControllerName() << " commands:" << endl;
		cout << "+" << "stop" << "\t Stops the controller" << endl;
		cout << "+" << "run" << "\t Launches the controller with specified options" << endl;
		cout << "+" << "compfilter" << "\t Toggles the complementary filter" << endl;

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

		// Restoring initial default parameters
		mDebugEnable = false;
		* (mControllerArgs.mDebugEnable) = mDebugEnable;
		mLog2FileEnable = false;
		* (mControllerArgs.mLog2FileEnable) = mLog2FileEnable;
		mCompFilterEnable = true;
		* (mControllerArgs.mCompFilterEnable) = mCompFilterEnable;

	}
	else if (argv[1].compare("run") == 0)
	{
		// Checking for supplementary arguments
		helpWanted = checkForRunOptions(argv, argc);

		if (helpWanted) {
			cout << endl;
			cout << "SYNOPSIS" << endl;
			cout << argv[0] << " run [-nc/-c] [-t [controller type]] [-d] [-l2f [filename]]" << endl << endl;
			cout << "ARGUMENTS" << endl;
			cout << "-c\t" <<  "Enables the complementary filter. Has priority over -nc." << endl;
			cout << "-nc\t" << "Disables the complementary filter and uses the potentiometer instead. Is cancelled by -c." << endl;
			cout << "--no-comp\t" << "Equivalent to -nc." << endl;
			cout << "-t\t" << "Allows to choose the desired type of controller. [controller type] should be either one of {lsf, lsf2, prop, sisot}." << endl;
			cout << "-d\t" << "Enables the debug option. Prints sensor readings and current applied to the motor." << endl;
			cout << "-l2f\t" << "Enables logging into a file which should be specified right after (default is log.csv). All log files are situated in the logs/ folder." << endl;
			cout << "EXAMPLE" << endl << endl;
			cout << "c run -c -t sm -d -l2f test.csv" << endl;
			cout << "This will run the Sliding Mode controller with the complementary filter. It will log data from the sensors and the desired current both on the screen and in a csv file named test.csv located in the logs/ folder." << endl;
		}
		else if (mpThread == NULL)
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

bool ControllerBase::checkForRunOptions(string* argv, unsigned int& argc)
{
	string optionBuffer;
	stringstream temp;

	if (argc < 2) {
		return false;
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
			else if (optionBuffer.compare("flin") == 0) {
				mControlType = FLIN;
			}
			else if (optionBuffer.compare("sm") == 0) {
				mControlType = SM;
			}
			else {
				cerr << "Wrong options! -t only works with:" << endl;
				cout << "lsf" << endl;
				cout << "lsf2" << endl;
				cout << "prop" << endl;
				cout << "sisotool" << endl;
				cerr << "Now running with default lsf2..." << endl;
			}
			* (mControllerArgs.mControlType) = mControlType;
		}
	}
	else if (cmdOptionExists(&argv[1], &argv[sizeof(argv)], "-d")) {
		mDebugEnable = true;
		*(mControllerArgs.mDebugEnable) = mDebugEnable;
	}
	else if (cmdOptionExists(&argv[1], &argv[sizeof(argv)], "-l2f")) {
		mLog2FileEnable = true;
		*(mControllerArgs.mLog2FileEnable) = mLog2FileEnable;
		optionBuffer = getCmdOption(&argv[1], &argv[sizeof(argv)], "-l2f");
		optionBuffer = getFileName(optionBuffer);
		if (optionBuffer.compare("") == 0) {
			temp << "logs/" << mLogFilename;
		}
		else {
			temp << "logs/" << optionBuffer;
		}
		mLogFilename = temp.str();
		*(mControllerArgs.mLogFilename) = mLogFilename;
	}
	else if (cmdOptionExists(&argv[1], &argv[sizeof(argv)], "--help")) {
		return true;
	}
	else {
		cout << "Wrong argument(s) ! Try to run again with the --help option." << endl;
		cout << "Running with defaults..." << endl;
	}

	return false;
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


/****************************
 * Command-line utilities
 ***************************/

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

string ControllerBase::getFileName(string filepath)
{
	string result;
	std::size_t found = filepath.find_last_of("/\\");
	try {
		result = filepath.substr(found + 1);
	}
	catch (const std::out_of_range& oore) {
		std::cerr << oore.what() << '\n';
	}
	return result;
}
