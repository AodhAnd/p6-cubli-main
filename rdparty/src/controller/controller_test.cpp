/*
 * controller_test.cpp
 *
 *  Created on: 29/10/2014
 *      Author: benjaminkrebs
 */


#include "controller_test.hpp"
#include "controller_factory.hpp"
#include <math.h>

#include "controller_code/AAU3_DiscLinObserver.hpp" // Discrete lurenberger observer
#include "controller_code/AAU3_DiscLinFeedback.hpp"
#include "controller_code/AAU3_DiscSlidingModeController.hpp"
#include "controller_code/AAU3_InOutLinearization.hpp"
#include "controller_code/AAU3_DiscSlidingModeController_new.hpp"
#include "controller_code/DiscreteLurenbergerEstimator_take2.h"

ControllerTest::ControllerTest()
:
ControllerBase(this)
{
	ControllerFactory::registerController(&createController);
}

const char* ControllerTest::getControllerNameStatic()
{
	return "c";
}

unsigned int ControllerTest::getPeriodicityMsStatic()
{
	 //Given in us!
	//  2500 => 400 Hz
	//  3333 => 300 Hz
	//  5000 => 200 Hz
	// 10000 => 100 Hz
	return 10000;
}


//Implementing ControllerCbIf
const char* ControllerTest::getControllerName()
{
	return getControllerNameStatic();
}

unsigned int ControllerTest::getPeriodicityMs()
{
	return getPeriodicityMsStatic();
}

void ControllerTest::writeDebug()
{
	std::cout<<"This is DEBUG for TestCtrl"<<std::endl;
}

void ControllerTest::runController(ControllerArgs* args)
{
	static double Ts = this->getPeriodicityMsStatic()/1e6, x_hat_last[4] = {0,0,0,0}, x_hat[4] = {0,0,0,0};
	static ofstream logfile("data.csv", ios::app );


		static bool value = true;
		value=!value;

		static long count = 0;

		signed int i_m_out = 0;
		static bool brake = true, brake_next = true;
		static double i_m = 0, i_m_next = 0;

		/* ################################
		 * ## 1. Apply control
		 * ################################ */

		i_m = i_m_next;

		i_m_out = (signed int)((i_m*1000));

		args->mMotor->setRpm(i_m_out);

		/* ################################
		 * ## 2. Perform Readings
		 * ################################ */
		static double xAcc1, yAcc1, gyroZ1, xAcc2, yAcc2, gyroZ2, potAdc, powerAdc, tachAdc, gyroRads1, gyroRads2, accX1, accX2, accY1, accY2;

		tachAdc = (double) args->mMotorAdc1->get(); // The last part is to correct an offset
		powerAdc  = args->mMotorAdc2->get(); //must be there or we get errors.. don't ask why; just believe in the code!
		potAdc   = (double) args->mPotAdc->get();

		xAcc1    = (double) args->mImu1->getAccX();
		yAcc1    = (double) args->mImu1->getAccY();
		gyroZ1   = (double) args->mImu1->getGyroZ();

		xAcc2    = (double) args->mImu2->getAccX();
		yAcc2    = (double) args->mImu2->getAccY();
		gyroZ2   = (double) args->mImu2->getGyroZ();



		//Convert potentiometer reading to radians
		double potRad;
		static double potOffset1 = -0.025,
				      tachOffset1 = 0;

		if(1){ // New circuit board
			potRad = (potAdc-655)*0.001068569;

			if(1){ //This flag enables the Auto-Zeroing feature
				if( !(potRad<-0.35 || potRad>0.35)){
					potOffset1 = potOffset1*0.9990 + potRad*0.0009995;
				}
			}

		}else{ // Old circuit "board" (hospitals patienten)

			const double potOffset = 0.08629 - 0.0199902 + 0.0034 - 0.005; //+ 0.0034
			potRad = -(potAdc-1564.5)*0.00339999205 + potOffset;
		}

		//Convert tachometer reading to radians/sec
		double tachRads;
		tachRads = (tachAdc - 882)*0.240734983;
		if(1){
			tachRads = (tachAdc - 882)*0.240734983;

		}else{ // This code is legacy code for an earlier version. It is keept for sentimental reasons :)
			const double a1 = 51.5489, b1 = -97.9109; //+ 4.3046
			const double a2 = -24.4500, b2 = 286.0935, c2 = 439.7612;
			tachRads = b1 - (a1*(b2 - sqrt(b2*b2 - 4*a2*c2 + 4*a2*tachAdc)))/(2*a2);
			if(tachAdc>=1237) tachRads = 143.5; // because of the sqrt, it is not defined for values higher than this.
		}

		// Old conversion
		// const double tachOffset = 1.67165 -0.25;
		// tachRads = (tachAdc-880)*0.238807583786 + tachOffset;

		// Convert gyroscopes
		const double PI = 3.141592653589793;
		gyroRads1 = -gyroZ1*PI/(131*180);
		gyroRads2 = -gyroZ2*PI/(131*180);
		// Convert Accelerometers
		accX1 = xAcc1*9.82/16384;
		accX2 = xAcc2*9.82/16384;
		accY1 = yAcc1*9.82/16384;
		accY2 = yAcc2*9.82/16384;



		static bool init = false;
		if(!init){
			init = true;
			//Open read file
			ofstream myfile ("data.csv", ios::app );


			// Init controller and Observer
			AAU3_DiscLinObserver_initialize();
			AAU3_DiscLinFeedback_initialize();
			AAU3_DiscSlidingModeController_initialize();
			AAU3_InOutLinearization_initialize();
			AAU3_DiscSlidingModeController_new_initialize();
			DiscreteLurenbergerEstimator_take2_initialize();
		}

		/* ################################
		 * ## 3. Run observer
		 * ################################ */
		x_hat_last[0] = x_hat[0]; x_hat_last[1] = x_hat[1]; x_hat_last[2] = x_hat[2]; x_hat_last[3] = x_hat[3];


		double y[2] = {potRad,tachRads};
		double y_[4] = {potRad, gyroRads1, gyroRads2, tachRads - tachOffset1};


		if(0){ // Observer

			//x_hat_last[3] = 0;
			double O_Take2_OffsetRegion = 0.2;
			if(x_hat[3] > O_Take2_OffsetRegion)
				x_hat[3] = O_Take2_OffsetRegion;
			else if(-O_Take2_OffsetRegion > x_hat[0]){
				x_hat[3] = -O_Take2_OffsetRegion;
			}

			//x_hat[3] = 0;

			O_Obv2_struct_T ObTake_u_last;
			ObTake_u_last.O_Obv2_U_m = i_m;
			ObTake_u_last.O_Obv2_Brake = 0;
			DiscreteLurenbergerEstimator_take2(Ts, x_hat_last, &ObTake_u_last, y_, x_hat);

			if(potRad<-O_Take2_OffsetRegion || potRad>O_Take2_OffsetRegion){
				x_hat[3] = x_hat_last[3];
			}

		}else{
			//x_hat[1] = (potRad-x_hat_last[0])/Ts;
			x_hat[1] = (gyroRads1+gyroRads2)/2;
			x_hat[0] = potRad - potOffset1;
			x_hat[2] = tachRads - tachOffset1;
		}


		/* ################################
		 * ## 4. Run controller
		 * ################################ */


		if(0){ //The linear state feedback controller
			C_Lin_struct_T u_next_obs = AAU3_DiscLinFeedback(Ts,x_hat);
			i_m_next = u_next_obs.C_Lin_U_m;
		}else if(0){ // The feedback linearization
			C_InOut_struct_T u_next_inout = AAU3_InOutLinearization(Ts,x_hat);
			i_m_next = u_next_inout.C_InOut_U_m;
		}else if(1){ // The sliding mode controller
			C_SMC_new_struct_T u_next_SMC_new = AAU3_DiscSlidingModeController_new(Ts,x_hat);
			i_m_next = u_next_SMC_new.C_SMC_new_U_m;
		}else{ //An early attempt of the Sliding mode controller. It is preserved for semtinental reasons :)
			C_SM_struct_T u_next_SMC = AAU3_DiscSlidingModeController(Ts,x_hat);
			i_m_next = u_next_SMC.C_SM_U_m;
		}


		// Controller tester
		static long ct_count = 0;
		static double i_m_add = 0;
		if(0){
			ct_count++;
			if(ct_count<450){
				//Nothing happends in this region
			}else if(ct_count<500){
				i_m_next = i_m_next + i_m_add;
			}else{
				ct_count = 0;
				i_m_add += 0.5;
			}
		}

		//if(potRad>0.4){
		//	i_m_next = 0;
		//}

		static bool goingPos = true;
		const double testLim = 80;
		static double testLim_n = 0;
		static double count__=0;

		if( 0 ){
			count__++;
			if(count__>100){
				if(goingPos){
					if(x_hat[2]>testLim){
						goingPos = !goingPos;
						testLim_n++;
					}
				}else{
					if(x_hat[2]<-testLim){
						goingPos = !goingPos;
						testLim_n++;
					}
				}

				if(goingPos)
					i_m_next = 0.5*(1+testLim_n/2);
				else
					i_m_next = -0.5*(1+testLim_n/2);
			}else
				i_m_next = 0;
		}

		if(1){ // 1 = set first part. 0 = set second part
			// If fallen over, then stop the wheel
			const double act_region = 0.35;
			if(potRad<-act_region || potRad>act_region){
				i_m_next = -0.15*tachRads;
				if(-2 < tachRads && tachRads < 2 ){
					i_m_next = 0;
				}
			}
		}else{ // keep constant velocity
			double error = 90 - tachRads; // reference error
			const double act_region2 = 0.35;
			if(potRad<-act_region2 || potRad>act_region2){
				i_m_next = 0.15*error;
			}

		}


		const double i_m_sat = 4;
		if(i_m_next>i_m_sat) i_m_next = i_m_sat;
		if(i_m_next<-i_m_sat) i_m_next = -i_m_sat;


		/* ################################
		 * ## 5. Logging
		 * ################################ */

		// Toggle
		static bool enableSchedIO = false;
		enableSchedIO = !enableSchedIO;
		args->mAwesomeGpio->setValue(enableSchedIO);


		if(1){
			std::cout << potOffset1 << ", " << goingPos << ", " << ct_count << "\ti_m: " << i_m_next << "\ti_m_c: " << i_m_next << "\tPot: " << potRad << "\tTach: " << tachRads << "\tx_hat: " << x_hat[0] << ",\t" << x_hat[1] << ",\t" << x_hat[2] <<
					accX1 << ", " << accY1 << ", " << accX2 << ", " << accY2 << ", " << potAdc << endl;
			if(1){
				if (logfile.is_open())
				{
					static long count = 0;
					count++;
					logfile <<  count << ", " << potRad << ", " << tachRads << ", " << i_m_next << ", " << x_hat[0] << ", " << x_hat[1] << ", " << x_hat[2] << ", " << gyroRads1 << ", " << gyroRads2 << ", "
							<< accX1 << ", " << accY1 << ", " << accX2 << ", " << accY2 << ", " << i_m_add <<  endl;
				}
			}

		}

}

ControllerBase* ControllerTest::createController(string& name)
{
	return new ControllerTest;
}

//REGISTER_CONTROLLER(ControllerTest);
