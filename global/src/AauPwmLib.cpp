/*
 * AauPwmLib.cpp
 *
 *  Created on: 16/11/2014
 *      Author: frederik
 */

#include "AauPwmLib.hpp"

using namespace std;

AauPwm::AauPwm(int P,int numPin)
:
mPercent(0),
mMode(false),
mPeriod(0),
mDuty(0){
	switch(P){
	case 8:
		switch(numPin){
		case 13:
			mPath ="/sys/devices/ocp.3/pwm_test_P8_13.15/";
			break;
		default:
			cout << "PWM: numPin not recognized. May not be set up" <<endl;
			break;
		}
		break;
	case 9:
		switch(numPin){
		case 14:
			mPath ="/sys/devices/ocp.3/pwm_test_P9_14.16/";
			break;
		case 16:
			mPath ="/sys/devices/ocp.3/pwm_test_P9_16.17/";
			break;
		case 22:
			mPath ="/sys/devices/ocp.3/pwm_test_P9_22.15/";
			break;
		default:
			cout << "PWM: numPin not recognized. May not be set up" <<endl;
			break;
		}
		break;
	default:
		cout << "PWM: Header not recognized" << endl;
	}
}
AauPwm::~AauPwm(){
	FILE *fp;
	char p[200];
	sprintf(p,"%srun",mPath);
	fp = fopen(p,"w");
	fprintf(fp,"%i",0);
	fclose(fp);
}

int AauPwm::setPeriod(int Period){
	FILE *fp;
	char p[200];
	sprintf(p,"%speriod",mPath);
	fp = fopen(p, "w");
	if(fp == NULL){
		return -1;
	}
	fprintf(fp,"%i",Period);
	fclose(fp);
	return Period;
}

int AauPwm::setDuty(int duty){
	FILE *fp;
	char p[200];
	sprintf(p,"%sduty",mPath);
	fp = fopen(p, "w");
	if(fp == NULL){
		return -1;
	}

	fprintf(fp,"%i",duty);
	fclose(fp);
	return duty;
}

float AauPwm::setPercent(float percent){
	FILE *fp;
	char p[200];
	int period = 0;
	sprintf(p,"%speriod",mPath);
	fp = fopen(p,"r");
	if(fp == NULL)
		return -1;
	fscanf(fp,"%d",&period);
	fclose(fp);
	int duty = (int)(percent*period/100);

	sprintf(p,"%sduty",mPath);
	fp = fopen(p,"w");
	if(fp == NULL)
		return -1;
	fprintf(fp,"%i",duty);
	fclose(fp);
	return percent;
}

int AauPwm::setPolarity(int pol){
	FILE *fp;
	char p[200];
	sprintf(p,"%spolarity",mPath);
	fp = fopen(p, "w");
	if(fp == NULL){
		return -1;
	}

	fprintf(fp,"%i",!!pol);
	fclose(fp);
	return !!pol;
}

float AauPwm::getPercent(){
	FILE *fp;
	char p[200];
	int period = 0;
	int duty = 0;

	sprintf(p,"%speriod",mPath);
	fp = fopen(p,"r");
	if(fp == NULL)
		return -1;
	fscanf(fp,"%d",&period);
	fclose(fp);
	sprintf(p,"%sduty",mPath);
	fp = fopen(p,"r");
	if(fp == NULL)
		return -1;
	fscanf(fp,"%d",&duty);
	fclose(fp);

	mPercent = duty/period*100;

	return mPercent;
}

int AauPwm::getPeriod(){
	FILE *fp;
	char p[200];
	int r= 0;
	sprintf(p,"%speriod",mPath);
	fp = fopen(p, "r");
	if(fp == NULL){
		return -1;
	}
	fscanf(fp,"%d",&r);
	fclose(fp);
	return r;
}

int AauPwm::getDuty(){
	FILE *fp;
	char p[200];
	int r= 0;
	sprintf(p,"%sduty",mPath);
	fp = fopen(p, "r");
	if(fp == NULL){
		return -1;
	}
	fscanf(fp,"%d",&r);
	fclose(fp);
	return r;
}

int AauPwm::getPolarity(){
	FILE *fp;
	char p[200];
	int r= 0;
	sprintf(p,"%spolarity",mPath);
	fp = fopen(p, "r");
	if(fp == NULL){
		return -1;
	}
	fscanf(fp,"%d",&r);
	fclose(fp);
	return !!r;
}

int AauPwm::run(){
	FILE *fp;
	char p[200];
	sprintf(p,"%srun",mPath);
	fp = fopen(p, "w");
	if(fp == NULL){
		return -1;
	}
	fprintf(fp,"%i",1);
	fclose(fp);
	return 1;
}

int AauPwm::stop(){
	FILE *fp;
	char p[200];
	sprintf(p,"%srun",mPath);
	fp = fopen(p, "w");
	if(fp == NULL){
		return -1;
	}
	fprintf(fp,"%i",0);
	fclose(fp);
	return 1;
}
