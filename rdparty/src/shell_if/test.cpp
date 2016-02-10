/*
 * test.cpp
 *
 *  Created on: 12/10/2014
 *      Author: benjaminkrebs
 */

#include "shell_server.hpp"
#include "shell_client.hpp"

class testClass : public ShellClientInterface
{

public:
	void receiveShellCommand(string* argv,unsigned int& argc){
		if(argc == 0)
		{
			cout<<"TestClass commands:"<<endl;
			cout<<"test"<<endl;
		}
		else if(argc > 0 && argv[1].compare("test") == 0)
		{
			cout<<"test command received"<<endl;
		}
		else
		{
			cout << "TestClass received unknown command" << endl;
		}
	}

	const char* getClientName(){
		return mName;
	}

private:
	ShellClient mShellClient;
	const char* mName;
public:
	testClass(const char* friendlyName):mName(friendlyName),mShellClient(friendlyName,this){

	}

};


int main()
{
	ShellServer* shellServer = ShellServer::getInstance();
	shellServer->setShellName("testShell");

	testClass test("test1");
	testClass test2("test2");

	shellServer->startShell();


	return 0;
}
