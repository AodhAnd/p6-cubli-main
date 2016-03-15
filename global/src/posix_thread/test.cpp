/*
 * test.cpp
 *
 *  Created on: 10/10/2014
 *      Author: benjaminkrebs
 */

#include "posix_thread.hpp"
#include <unistd.h>
#include <iostream>

using namespace std;

void* workerFunc(void* args)
{
	cout<< "Hello from thread 1!" << endl;
	usleep(1000000);
	return NULL;
}

void* workerFunc1(void* args)
{
	cout<< "Hello from thread 2!" << endl;
	return NULL;
}

int main()
{
	PosixThread thread(&workerFunc);
	PosixThread thread2(&workerFunc1,500000);

	thread.startThread();
	thread2.startThread();

	usleep(500000*10);
	thread2.stopThread();
	thread.stopThread();


	return 0;
}
