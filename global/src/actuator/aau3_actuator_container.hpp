/*
 * aau3_actuator_container.hpp
 *
 *  Created on: 30/10/2014
 *      Author: benjaminkrebs
 */

#ifndef AAU3_ACTUATOR_CONTAINER_HPP_
#define AAU3_ACTUATOR_CONTAINER_HPP_

class Aau3ActuatorContainer
{
public:
	Aau3ActuatorContainer(){}
	~Aau3ActuatorContainer(){}

	bool setMotor(unsigned int setRpm, unsigned int motorId){return true;}
};



#endif /* AAU3_ACTUATOR_CONTAINER_HPP_ */
