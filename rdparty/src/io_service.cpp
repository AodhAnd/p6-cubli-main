/*
 * io_service.cpp
 *
 *  Created on: 03/09/2014
 *      Author: benjaminkrebs
 */


#include <iostream>

#include "../inc/io_service.hpp"



IoService* IoService::mpInstance(NULL);

IoService* IoService::getInstance()
{

	if(mpInstance == NULL)
	{
		std::cout<<"IoService Initialized..."<<std::endl;
		static IoService self;
		mpInstance = &self;
	}

	return mpInstance;
}

IoService::IoService()
{
	mOutFile.open(OUT_STREAM,std::ofstream::out);
	mInFile.open(IN_STREAM,std::ifstream::in);
	std::cout<<"IoService: Succesfully opened in/out stream..."<<std::endl;
}

IoService::~IoService()
{
	mOutFile.close();
	mInFile.close();
}




void IoService::tx(const char* strData) //All data to the web interface is sent as clear text
{
	mOutFile<<strData;
}

int IoService::rx(char buf[],unsigned int bufLen)
{
	//This should be a thread!!
	unsigned int bytesRead=0;
	while(mInFile.good() && bufLen>bytesRead)
	{
		char c = mInFile.get();
		if(!mInFile.eof())
		{
			buf[bytesRead] = c;
		}
		bytesRead++;
	}
	return bytesRead;

}
