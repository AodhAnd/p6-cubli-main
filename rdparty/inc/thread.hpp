/*
 * thread_interface.hpp
 *
 *  Created on: 07/09/2014
 *      Author: benjaminkrebs
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

class Thread
{
public:
	Thread();
	static void setPeriodic(unsigned int period);
	static void waitPeriod();
	void timerLog();
	void createThreat();
private:
	int mTimerfd;
	unsigned long long mWakeupsMissed;
	int mSignal;
	sigset_t alarm_sig;
	unsigned long long mTimerMissed;
};



#endif /* THREAD_INTERFACE_HPP_ */
