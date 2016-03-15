/*
 * aau3_sensor_reading.hpp
 *
 *  Created on: 30/10/2014
 *      Author: benjaminkrebs
 */

#ifndef AAU3_SENSOR_READING_HPP_
#define AAU3_SENSOR_READING_HPP_

class Aau3SensorReading
{
public:
	Aau3SensorReading(){}
	~Aau3SensorReading(){}

	unsigned int getAccX(unsigned int imuID){return 2;}

private:

};



#endif /* AAU3_SENSOR_READING_HPP_ */
