/*
 * controller_factory.hpp
 *
 *  Created on: 28/10/2014
 *      Author: benjaminkrebs
 */

#ifndef CONTROLLER_FACTORY_HPP_
#define CONTROLLER_FACTORY_HPP_

//#define REGISTER_CONTROLLER(T) void isRegistered_##T =  ControllerFactory::getInstance()->registerController(&T::createController)

#include "../shell_if/shell_client.hpp"

class ControllerBase;

class ControllerFactory : public ShellClientInterface{
public:
	//typedef ControllerBase* (*createFunc)(string&);
	static ControllerFactory* getInstance();
	~ControllerFactory();

	static bool registerController(ControllerBase* (*createFunc)(string&));

public:
	void receiveShellCommand(string* argv,unsigned int& argc);
	const char* getClientName();

private:
	ControllerFactory();

	static ControllerFactory* mInstance;
	ShellClient mShell;


	static ControllerBase* (*mCreateFuncArray[100])(string&);

	static unsigned int mNumControllers;
	const char* mName;

};



#endif /* CONTROLLER_FACTORY_HPP_ */
