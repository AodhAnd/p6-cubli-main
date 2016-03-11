/*
 * thread.cpp
 *
 *  Created on: 07/09/2014
 *      Author: benjaminkrebs
 */

#include <iostream>
#include <time.h>
#include <signal.h>

#include "../inc/thread.hpp"

Thread::Thread()
{

}

void Thread::createThreat()
{

}


void Thread::setPeriodic(unsigned int period_ms)
{
	// Is called in the start
	static int next_sig;
	int ret;
	unsigned int ns;
	unsigned int sec;
	struct sigevent sigev;
	timer_t timer_id;
	struct itimerspec itval;

	/* Initialise next_sig first time through. We can't use static
		   initialisation because SIGRTMIN is a function call, not a constant */
	if (next_sig == 0)
		next_sig = SIGRTMIN;
	/* Check that we have not run out of signals */
	if (next_sig > SIGRTMAX)
		perror("Thread encountered a problem");

	mSignal = next_sig;
	next_sig++;

	mWakeupsMissed = 0;

	/* Create the signal mask that will be used in wait_period */
	sigemptyset (&(alarm_sig));
	sigaddset (&(alarm_sig), mSignal);

	/* Create a timer that will generate the signal we have chosen */
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = mSignal;
	sigev.sigev_value.sival_ptr = (void *) &timer_id;
	ret = timer_create(CLOCK_MONOTONIC, &sigev, &timer_id);
	if (ret == -1)
		perror("Thread encountered a problem");

	/* Make the timer periodic */
	sec = period_ms/1000000;
	ns = (period_ms - (sec * 1000000)) * 1000;
	itval.it_interval.tv_sec = sec;
	itval.it_interval.tv_nsec = ns;
	itval.it_value.tv_sec = sec;
	itval.it_value.tv_nsec = ns;
	ret = timer_settime(timer_id, 0, &itval, NULL);
}

void Thread::waitPeriod()
{
	int sig;
	sigwait(&(alarm_sig), &sig);
	mWakeupsMissed += timer_getoverrun(mTimerfd);
}
