/*
 * momentumMotor.hpp
 *
 *  Created on: 26/08/2014
 *      Author: benjaminkrebs
 */

#ifndef MOMENTUMMOTOR_HPP_
#define MOMENTUMMOTOR_HPP_

#include "../src/shell_if/shell_client.hpp"
#include <stdlib.h>
#include <iostream>
#include "../src/bbb_gpio.hpp"
#include "../src/bbb_adc.hpp"
#include "../src/AauPwmLib.hpp"

using namespace std;

class MomentumMotor: public ShellClientInterface
{
public:
	enum motor_state
	{	MOTOR_STATE_IDLE,
		MOTOR_STATE_ROTATING,
		MOTOR_STATE_BREAKING
	};
	enum motor_direction {
		MOTOR_DIRECTION_CW,
		MOTOR_DIRECTION_CCW
	};

	MomentumMotor(const char* idName,BbbGpio::gpio_port_t gpioPort, int pwmMotorP, int pwmMotorPin, int pwmServoP, int pwmServoPin);
	~MomentumMotor();

	bool hasState(motor_state state);
	void setBreak(bool enable);
	void emergencyBreak();
	void setRpm(signed int rpm);
	void startMotorController(void);
	void stopMotorController(void);

public: //Implementing Shell
	void receiveShellCommand(string* argv,unsigned int& argc);
	const char* getClientName();

private:
	motor_state mState;
	const char* mName;
	ShellClient mShellClient;
	BbbGpio mEnableGpio;
	AauPwm mServoPwm;
	AauPwm mMotorPwm;

};



#endif /* MOMENTUMMOTOR_HPP_ */
