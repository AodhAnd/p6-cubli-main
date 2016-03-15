/*
 * controller_factory.cpp
 *
 *  Created on: 28/10/2014
 *      Author: benjaminkrebs
 */


#include "controller_factory.hpp"
#include "controller_base.hpp"


ControllerFactory* ControllerFactory::mInstance = NULL;
unsigned int ControllerFactory::mNumControllers = 0;
ControllerBase* (*ControllerFactory::mCreateFuncArray[100])(string&);

ControllerFactory* ControllerFactory::getInstance()
{
	if(mInstance == NULL)
		return new ControllerFactory;
	else
		return mInstance;
}

ControllerFactory::~ControllerFactory()
{ }

void ControllerFactory::receiveShellCommand(string* argv,unsigned int& argc)
{
	if(argc == 0)
	{
		cout<<endl<<"**********" <<mName<< "**********" <<endl;
		cout<<"->The purpose of " << mName << " is to create controllers"<<endl;
		cout<<"->To create a controller write:"<<endl;
		cout<<"\t"<<mName<<" <controllerName> create"<<endl;
		cout<<"->When a controller is initiated you can run it by writing:"<<endl;
		cout<<"\t <controllerName> run"<<endl<<endl;
		cout<<"->Further commands:"<<endl;
		cout<<"+list       : Lists all available controllers."<<endl;
		cout<<"+setDefault : Sets a new default controller."<<endl;

		cout<<endl;
	}
	else if(argv[1].compare("list") == 0)
	{

	}
	else if(argv[1].compare("setDefault") == 0)
	{

	}
	else if(argv[1].compare("createController") == 0)
	{
		//std::string testStr("hej");
		//ControllerBase * currentController = mCreateFuncArray[0](testStr);
	}
	else
	{
		cout << mName << " received an unknown command"<<endl;
	}
}

const char* ControllerFactory::getClientName()
{
	return mName;
}

ControllerFactory::ControllerFactory():
mName("CtrlFactory"),
mShell("CtrlFactory",this)
{

}

bool ControllerFactory::registerController(ControllerBase* (*createFunc)(string&))
{
	if(createFunc!=NULL)
	{
		mCreateFuncArray[mNumControllers++] = createFunc;
		//std::cout<<"Controller Registered!"<<std::endl;
	}
	return true;
}



