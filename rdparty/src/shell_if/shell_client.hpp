/*
 * shell_client.hpp
 *
 *  Created on: 11/10/2014
 *      Author: benjaminkrebs
 */

#ifndef SHELL_CLIENT_HPP_
#define SHELL_CLIENT_HPP_

#define DEBUG_ON

#include "shell_defines.hpp"

class ShellServer;

class ShellClientInterface
{
public:
	virtual ~ShellClientInterface(){};
	virtual void receiveShellCommand(string* argv,unsigned int& argc) = 0;
	virtual const char* getClientName() = 0;
};

class ShellClient
{
public:
	ShellClient(const char* clientName, ShellClientInterface* shell_if);
	~ShellClient();

	//bool connectToServer(const char* clientName, ShellClientInterface* shell_if);

private:
	ShellServer* mShellServer;
};



#endif /* SHELL_CLIENT_HPP_ */
