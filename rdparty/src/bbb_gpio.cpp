/*
 * bbb_gpio.cpp
 *
 *  Created on: 16/11/2014
 *      Author: benjaminkrebs
 */

#include "bbb_gpio.hpp"

BbbGpio::BbbGpio(gpio_port_t port, bool activeLow, gpio_direction_t direction)
{
	/*
	char exportCmd[200];
	sprintf(exportCmd,"echo %d >> \\sys\\class\\gpio\\export",port);
	system(exportCmd);
*/
	char path[200];
	sprintf(path,"/sys/class/gpio/gpio%d/",port);
	mPath.append(path);

	char dirPath[200];
	sprintf(dirPath,"%sdirection",mPath.c_str());
	mDirFile = open(dirPath,O_WRONLY);
	if(mDirFile <0)
		perror("mDirFile file open");

	char valPath[200];
	sprintf(valPath,"%svalue",mPath.c_str());
	mValFile = open(valPath,O_RDWR);
	if(mValFile <0)
		perror("mValFile file open");

	char activeLowPath[200];
	sprintf(activeLowPath,"%sactive_low",mPath.c_str());
	mActiveLowFile = open(activeLowPath,O_WRONLY);
	if(mActiveLowFile <0)
		perror("ActiveLow file open");


	setActiveLow(activeLow);

	if(direction==BBB_GPIO_DIRECTION_IN)
		setDirection(false);
	else
		setDirection(true);

	setValue(false);

	std::cout<<"Gpio"<<port<<" initialized with path: " << mPath << std::endl;
}

BbbGpio::~BbbGpio()
{
	close(mValFile);
	close(mDirFile);
	close(mActiveLowFile);
}

void BbbGpio::setValue(bool value)
{
	if(value)
		write(mValFile,"1",1);
	else
		write(mValFile,"0",1);
}

bool BbbGpio::getValue()
{
	char buf[2];
	buf[1] = 0;
	read(mValFile,buf,1);
	if(strcmp("1",buf) == 0)
		return true;
	else
		return false;

}

bool BbbGpio::init()
{

}

void BbbGpio::setDirection(bool outEnable)
{
	if(outEnable)
		write(mDirFile,"out",3);
	else
		write(mDirFile,"in",2);
}

void BbbGpio::setActiveLow(bool enable)
{
	if(enable)
		write(mActiveLowFile,"1",1);
	else
		write(mActiveLowFile,"0",1);
}
