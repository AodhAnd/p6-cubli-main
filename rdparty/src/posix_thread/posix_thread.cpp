/*
 * posix_thread.cpp
 *
 *  Created on: 10/10/2014
 *      Author: benjaminkrebs
 */

#include "posix_thread.hpp"
#include <unistd.h>
#define DEBUG_ON

using namespace std;

#define MODULE_NAME "Posix Thread"

#ifdef DEBUG_ON
#define DEBUG_MSG(msg) cout << MODULE_NAME << ":" << msg << endl;
#endif


PosixThread::PosixThread(void* (*func)(void*), unsigned int prio)
:
mIsPeriodic(false),
mPeriodicityUs(0),
mThreadStop(false),
mWakeUpsMissed(0),
mTimerfd(-1),
mPrio(prio)
{
	mThreadArgs.args = NULL;
	mThreadArgs.obj = this;

	if(func != NULL)
		mFunc = func;
	else
		DEBUG_MSG("Function pointer is NULL");
}

PosixThread::PosixThread(void* (*func)(void*),unsigned int periodicity_us, unsigned int prio)
:
mIsPeriodic(true),
mPeriodicityUs(periodicity_us),
mThreadStop(false),
mWakeUpsMissed(0),
mTimerfd(-1),
mPrio(prio)
{

	mThreadArgs.args = NULL;
	mThreadArgs.obj = this;

	if(func != NULL)
		mFunc = func;
	else
		DEBUG_MSG("Function pointer is NULL");
}

PosixThread::~PosixThread()
{
	stopThread();
}

void PosixThread::startThread()
{
	if(mIsPeriodic)
		pthread_create(&mPthreadStruct,NULL,&staticPeriodicThread,&mThreadArgs);
	else
		pthread_create(&mPthreadStruct,NULL,mFunc,&mThreadArgs);

	mParam.sched_priority = mPrio;
	pthread_setschedparam(mPthreadStruct, SCHED_FIFO, &mParam);
}

void PosixThread::startThread(void* args)
{
	mThreadArgs.args = args;

	if(mIsPeriodic)
		pthread_create(&mPthreadStruct,NULL,&staticPeriodicThread,&mThreadArgs);
	else
		pthread_create(&mPthreadStruct,NULL,mFunc,&mThreadArgs);

	mParam.sched_priority = mPrio;
	pthread_setschedparam(mPthreadStruct, SCHED_FIFO, &mParam);
}

void PosixThread::stopThread()
{
	mThreadStop = true;
	pthread_join(mPthreadStruct,NULL);
}

void* PosixThread::staticPeriodicThread(void* args)
{
	thread_args_t* threadArgs = (thread_args_t*)args;
	return threadArgs->obj->periodicThread(threadArgs->args);
}

void* PosixThread::periodicThread(void* args)
{
	makePeriodic();

	while(!mThreadStop)
	{
		mFunc(args);

		waitPeriod();
	}

	return NULL;
}



void PosixThread::makePeriodic()
{
	int ret;
	unsigned int ns;
	unsigned int sec;
	struct itimerspec itval;

	/* Create the timer */
	mTimerfd = timerfd_create(CLOCK_MONOTONIC, 0);
	mWakeUpsMissed = 0;

	if (mTimerfd == -1)
		DEBUG_MSG("Failed to create timerfd");

	/* Make the timer periodic */
	sec = mPeriodicityUs/1000000;
	ns = (mPeriodicityUs - (sec * 1000000)) * 1000;
	itval.it_interval.tv_sec = sec;
	itval.it_interval.tv_nsec = ns;
	itval.it_value.tv_sec = sec;
	itval.it_value.tv_nsec = ns;
	ret = timerfd_settime (mTimerfd, 0, &itval, NULL);

	if(ret == -1)
		DEBUG_MSG("Failed to set timer");
}

void PosixThread::waitPeriod()
{
	unsigned long long missed;
	int ret;

	/* Wait for the next timer event. If we have missed any the
		   number is written to "missed" */
	ret = read(mTimerfd, &missed, sizeof (missed));
	if (ret == -1)
		DEBUG_MSG("Failed to read timerfd");
	/* "missed" should always be >= 1, but just to be sure, check it is not 0 anyway */
	if (missed > 0)
		mWakeUpsMissed += (missed - 1);
}
