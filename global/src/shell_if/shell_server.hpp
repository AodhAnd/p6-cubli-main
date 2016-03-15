/*
 * shell_server.hpp
 *
 *  Created on: 11/10/2014
 *      Author: benjaminkrebs
 */

#ifndef SHELL_SERVER_HPP_
#define SHELL_SERVER_HPP_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "shell_client.hpp"


#define MAX_NOF_CLIENTS 100

using namespace std;

class ShellServer
{
public:
	static ShellServer* getInstance();

	bool registerNewClient(ShellClientInterface* shell_if);

	void startShell();

	void setShellName(const char* shellName);

	typedef struct{
		ShellClientInterface* shellIf;
		const char* clientName;
	}client_info_t;

private:
	//The ShellServer is a singleton
	ShellServer();
	~ShellServer();
	static ShellServer* mInstance;
	client_info_t mClients[MAX_NOF_CLIENTS];

	unsigned int mNofRegisteredClients;

	const char* mShellName;

	string* parseArguments(string& command,unsigned int& nofCommands);

	bool shellDebug;
};



#endif /* SHELL_SERVER_HPP_ */
