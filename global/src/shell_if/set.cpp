/*
 * set.cpp
 *
 *  Created on: 30/10/2014
 *      Author: frederik
 */

#include "shell_client.hpp"
#include "shell_server.hpp"
#include <string>
#include "AauPwmLib.hpp"
#include <stdlib.h>

class getClass : public ShellClientInterface{
public:
	void receiveShellCommand(string* argv, unsigned int& argc){
		if(argc == 0){
			cout << "get commands:" << endl;
			cout << "get pwm <num> period" << endl;
			cout << "get pwm <num> duty" << endl;
			cout << "get pwm <num> polarity" << endl;
		}
		else{
			if(argv[1] == "pwm"){
				int P = atoi(argv[2].c_str());
				int num = atoi(argv[3].c_str());
				AauPwm pwm(P,num);
				if(argv[4] == "period"){
					cout << pwm.getPeriod() << endl;
				} else if(argv[4] == "duty"){
					cout << pwm.getDuty() << endl;
				} else if(argv[4] == "polarity"){
					cout << pwm.getPolarity() << endl;
				}
			}
		}
	}

	const char* getClientName(){
		return mName;

	}
private:
	ShellClient mShellClient;
	const char* mName;

public:
	getClass(const char* name="get"):mShellClient(name,this)
{
		mName = name;
}
};


class setClass : public ShellClientInterface{

public:
	void receiveShellCommand(string* argv, unsigned int& argc){
		if(argc == 0){
			cout << "set commands:"<<endl;
			cout << "set pwm <P> <num> polarity 0/1" <<endl;
			cout << "set pwm <P> <num> period 0-mange" <<endl;
			cout << "set pwm <P> <num> duty 0-period" <<endl;
			cout << "set pwm <P> <num> percent 0-100" <<endl;
			cout << "set pwm <P> <num> start" <<endl;
			cout << "set pwm <P> <num> stop" <<endl;
		} else if (argc == 4){
			if(argv[1] == "pwm"){
				int P = atoi(argv[2].c_str());
				int num = atoi(argv[3].c_str());
				AauPwm pwm(P,num);
				if(argv[4] == "start"){
					pwm.run();
				}
				else if(argv[4] == "stop"){
					pwm.stop();
				}
			}

		} else if(argc == 5){
			int P = atoi(argv[2].c_str());
			int num = atoi(argv[3].c_str());
			AauPwm pwm(P,num);
			if(argv[4] == "period") {
				pwm.setPeriod(atoi(argv[5].c_str()));
			} else if(argv[4] == "duty") {
				pwm.setDuty(atoi(argv[5].c_str()));
			} else if(argv[4] == "polarity") {
				pwm.setPolarity(atoi(argv[5].c_str()));
			} else if(argv[4] == "percent") {
				pwm.setPercent(atof(argv[5].c_str()));
			}
			else{
				cout << "set: command not recognized." << endl;
			}
		}
		else{
			cout << "Command not recognized" << endl;
		}

	}

	const char* getClientName(){
		return mName;

	}
private:
	ShellClient mShellClient;
	const char* mName;

public:
	setClass(const char* name="set"):mShellClient(name,this)
{
		mName = name;
}

};

class test: public ShellClientInterface
{
public:
	void receiveShellCommand(string* argv,unsigned int& argc){cout<<"hej"<<endl;}
	const char* getClientName(){return "test";}
	test():mClient("test",this){}
private:
	ShellClient mClient;
};

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


int main(){
	ShellServer* shellServer = ShellServer::getInstance();
	shellServer->setShellName("aaush");

	setClass set;
	getClass get;
	test test1;
	testClass test2("test2");

	shellServer->startShell();

	return 0;
}


