/*
 * shell_server.cpp
 *
 *  Created on: 12/10/2014
 *      Author: benjaminkrebs
 */


#include "shell_server.hpp"

ShellServer* ShellServer::mInstance = NULL;

ShellServer* ShellServer::getInstance()
{
	if(mInstance == NULL)
	{
		mInstance = new ShellServer;
	}

	return mInstance;
}


ShellServer::ShellServer()
:
mNofRegisteredClients(0),
mShellName("shell")
{

}

void ShellServer::setShellName(const char* shellName)
{
	mShellName = shellName;
}

void ShellServer::startShell()
{
	bool shellRunning = true;
	string* args = NULL;
	unsigned int argv = 0;
	string cmdStr;

	while(shellRunning)
	{
		cout << mShellName << "# ";
		getline(cin,cmdStr);

		if(shellDebug)
			cout <<"SHELL DEBUG: " <<"Command received: " << cmdStr.c_str() << endl;

		args = parseArguments(cmdStr,argv);

		if(strcmp(cmdStr.c_str(),"quit") == 0 || strcmp(cmdStr.c_str(),"q") == 0)
		{
			shellRunning = false;
		}
		else if(strcmp(cmdStr.c_str(),"status") == 0)
		{
			cout << "Shell Name: " << mShellName << endl;
			cout << "Nof Client: " << mNofRegisteredClients << endl;
			for(unsigned int i=0;i<mNofRegisteredClients;i++)
				cout << i << ". " << mClients[i].shellIf->getClientName() << endl;
		}
		else if(cmdStr.compare("help")==0)
		{
			cout<<"Shell Status:"<<endl;
			cout << "Shell Name: " << mShellName << endl;
			cout << "Nof Client: " << mNofRegisteredClients << endl;
			for(unsigned int i=0;i<mNofRegisteredClients;i++)
				cout << i << ". " << mClients[i].shellIf->getClientName() << endl;

			cout<<endl<<"Shell Commands:"<<endl;
			cout<<"+"<<"debug"<<endl;
			cout<<"+"<<"status"<<endl;
			cout<<"+"<<"q or quit"<<endl;
			cout<<"+"<<"<Client Name>"<<endl;
		}
		else if(cmdStr.compare("debug")==0)
		{
			shellDebug = !shellDebug;
			if(shellDebug)
				cout<<"Shell Debug ON"<<endl;
			else
				cout<<"Shell Debug OFF"<<endl;
		}
		else
		{
			for(unsigned int i=0;i<mNofRegisteredClients;i++)
			{
				if(strcmp(mClients[i].shellIf->getClientName(),args[0].c_str()) == 0)
				{
					if(shellDebug)
						cout<<mClients[i].shellIf->getClientName()<<" accepted the command"<<endl;
					mClients[i].shellIf->receiveShellCommand(args,--argv);
				}
			}
		}



		cmdStr.clear();
		delete [] args;
		args = NULL;
	}
}


string* ShellServer::parseArguments(string& command,unsigned int& nofCommands)
{
	string* args = new string[10];

	int jj = 0;
	for(unsigned int i=0;i<command.size();i++)
	{
		if(command.compare(i,1," ") == 0)
		{
			jj++;
		}
		else
		{
			if(jj<10)
				args[jj]+= command.c_str()[i];
			else
				cout<<"TOO MANY ARGUMENTS"<<endl;
		}
	}
	jj++;
	nofCommands = jj;
	return args;
}


bool ShellServer::registerNewClient(ShellClientInterface* shell_if)
{
	for(unsigned int i=0;i<mNofRegisteredClients;i++)
	{
		/*
		if(strcmp(mClients[i].clientName,shell_if->getClientName()) == 0)
		{
			cout<<"SHELL DEBUG: "<<"Clients name already registered: "<< shell_if->getClientName() << endl;
			return false;
		}*/
	}

	mClients[mNofRegisteredClients].clientName = "";
	mClients[mNofRegisteredClients++].shellIf = shell_if;

	//cout<<"Shell client registered: " << clientName << endl;

	return true;
}
