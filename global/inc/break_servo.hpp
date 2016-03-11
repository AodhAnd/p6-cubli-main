/*
 * break_servo.hpp
 *
 *  Created on: 26/08/2014
 *      Author: benjaminkrebs
 */

#ifndef BREAK_SERVO_HPP_
#define BREAK_SERVO_HPP_

class BreakServo {
public:
	BreakServo(unsigned int pwmPin);
	~BreakServo();
    
    typedef enum {
        BREAK_ON,
        BREAK_OFF
    } break_state_t;
    
    bool isOn();
    void setState(break_state_t state);

private:
};


#endif /* BREAK_SERVO_HPP_ */
