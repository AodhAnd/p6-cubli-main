/*
 * controller_test.hpp
 *
 *  Created on: 28/10/2014
 *      Author: benjaminkrebs
 */

#ifndef CONTROLLER_TEST_HPP_
#define CONTROLLER_TEST_HPP_

#include "controller_base.hpp"
#include <iostream>
#include "../bbb_gpio.hpp"
#include "../bbb_adc.hpp"

using namespace std;

class ControllerTest: public ControllerCbIf,public ControllerBase {
public:
	ControllerTest();
	~ControllerTest(){}

	static const char* getControllerNameStatic();
	static unsigned int getPeriodicityMsStatic();
	static ControllerBase* createController(string& name);


public: //Implementing ControllerCbIf
	unsigned int getPeriodicityMs();
	const char* getControllerName();
	void writeDebug();
	void runController(ControllerArgs* args);

private:
	string mControllerName;
};



#endif /* CONTROLLER_TEST_HPP_ */
