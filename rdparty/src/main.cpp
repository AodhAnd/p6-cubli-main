/*
 * main.cpp
 *
 *  Created on: 27/08/2014
 *      Author: benjaminkrebs
 */


#include <iostream>
#include <stdio.h>
using namespace std;

#include "shell_if/shell_server.hpp"
#include "../inc/momentum_motor.hpp"
#include "controller/controller_factory.hpp"
#include "controllers.hpp"
#include "bbb_gpio.hpp"
#include "bbb_adc.hpp"




int main()
{
	cout << "/****************** AAU^3 ******************/" <<endl<<endl;
	//Create necessary objects
	ShellServer* shell = ShellServer::getInstance();
	//ControllerFactory* controllerFactory = ControllerFactory::getInstance();

	// INSERT CONTROLLER HERE \\
	//**********************************************
	ControllerTest controllertest;


	//**********************************************


	//initiate the threads

	//Always start the shell as the last module
	shell->setShellName("AAU3");
	shell->startShell();

	//wait for threads to get terminated

	return 0;
}
