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
#include "controller_code/AAU3_DiscLinFeedback2.hpp"
#include "controller_code/AAU3_PController.hpp"
#include "controller_code/AAU3_DiscSISOTool.hpp"
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

unsigned int ControllerTest::getPeriodicityMusStatic()
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

unsigned int ControllerTest::getPeriodicityMus()
{
	return getPeriodicityMusStatic();
}

void ControllerTest::writeDebug()
{
	std::cout << "This is DEBUG for TestCtrl" << std::endl;
}

void ControllerTest::runController(ControllerArgs* args)
{
	// Setting GPIO_61 up
	args->mRaisePin->setValue(true);

	static double Ts = this->getPeriodicityMusStatic() / 1e6, x_hat_last[4] = {0, 0, 0, 0}, x_hat[4] = {0, 0, 0, 0};
	static ofstream logfile("tests/potRegularity.csv", ios::app );

	// Has to be updated each time in case the controller is stopped and re-started
	static bool compFilterEnable;
	compFilterEnable = *(args->mCompFilterEnable);
	static ControllerType contType;
	contType = *(args->mControlType);

	static long count = 0;

	signed int i_m_out = 0;
	static bool brake = true, brake_next = true;
	static double i_m = 0, i_m_next = 0;

	/* ################################
	 * ## 1. Apply control
	 * ################################ */

	i_m = i_m_next;

	i_m_out = (signed int)((i_m * 1000));
	args->mMotor->setRpm(i_m_out);

	/* ################################
	 * ## 2. Perform Readings
	 * ################################ */
	static double xAcc1, yAcc1, gyroZ1, xAcc2, yAcc2, gyroZ2, potAdc, powerAdc, tachAdc, gyroRads1, gyroRads2, accX1, accX2, accY1, accY2;

	tachAdc 	= (double) args->mMotorAdc1->get(); // The last part is to correct an offset
	powerAdc  = args->mMotorAdc2->get(); //must be there or we get errors.. don't ask why; just believe in the code!
	potAdc   	= (double) args->mPotAdc->get();

	xAcc1    = (double) args->mImu1->getAccX();
	yAcc1    = (double) args->mImu1->getAccY();
	gyroZ1   = (double) args->mImu1->getGyroZ();

	xAcc2    = (double) args->mImu2->getAccX();
	yAcc2    = (double) args->mImu2->getAccY();
	gyroZ2   = (double) args->mImu2->getGyroZ();

	//Convert potentiometer reading to radians
	double potRad;
	static double potOffset1 	= -0.025,
	              tachOffset1 = 0;
	potRad = (potAdc - 655) * 0.001068569; //655 was the original value

	// static double adcRes = 0.00043945,		// ADC resolution
	// 							eqVolt = 0.6945,				// Voltage value at the equilibrium point
	// 							resRad = 3.2818;				// Voltage-to-radians coefficient
	// potRad = ((potAdc * adcRes) - eqVolt) * resRad;

	if (0) { //This flag enables the Auto-Zeroing feature
		if ( !(potRad < -0.45 || potRad > 0.45)) {
			potOffset1 = potOffset1 * 0.9990 + potRad * 0.0009995;
		}
	}

	//Convert tachometer reading to radians/sec
	double tachRads;
	tachRads = (tachAdc - 882) * 0.240734983;
	tachRads = (tachAdc - 882) * 0.240734983;

	// Convert gyroscopes
	const double PI = 3.141592653589793;
	gyroRads1 = -gyroZ1 * PI / (131 * 180);
	gyroRads2 = -gyroZ2 * PI / (131 * 180);
	// Convert Accelerometers
	accX1 = xAcc1 * 9.82 / 16384;
	accX2 = xAcc2 * 9.82 / 16384;
	accY1 = yAcc1 * 9.82 / 16384;
	accY2 = yAcc2 * 9.82 / 16384;



	static bool init = false;
	if (!init) {
		init = true;
		// Init controller and Observer
		AAU3_DiscLinFeedback_initialize();
		AAU3_PController_initialize(THETA_REF);
		AAU3_DiscSISOTool_initialize(THETA_REF);
		AAU3_DiscLinFeedback2_initialize();
	}

	/* ################################
	 * ## 3. Run observer
	 * ################################ */
	x_hat_last[0] = x_hat[0]; x_hat_last[1] = x_hat[1]; x_hat_last[2] = x_hat[2]; x_hat_last[3] = x_hat[3];


	double y[2] = {potRad, tachRads};
	double y_[4] = {potRad, gyroRads1, gyroRads2, tachRads - tachOffset1};


	x_hat[0] = potRad - potOffset1;
	//x_hat[1] = (potRad-x_hat_last[0])/Ts;
	x_hat[1] = (gyroRads1 + gyroRads2) / 2;
	x_hat[2] = tachRads - tachOffset1;

	// Enables the complementary filter
	if (compFilterEnable) {
		// The x_hat value is updated accordingly with the complementary filter output
		cout << "Using complementary filter..." << endl;
		x_hat[0] = (double) args->mImu1->getPosition((double) atan(accY1 / accX1), gyroRads1, Ts);
	}

	/* ################################
	 * ## 4. Run controller
	 * ################################ */

	if (contType == LSF) { // Simon's linear state feedback (LSF) controller
		C_Lin_struct_T u_next_obs = AAU3_DiscLinFeedback(Ts, x_hat);
		i_m_next = u_next_obs.C_Lin_U_m;
	}
	else if (contType == PROP) { // Proportional controller (unstable)
		Lin_Out_Sig_struct_T u_next_pc = AAU3_PController(x_hat);
		i_m_next = u_next_pc.I_m;
	}
	else if (contType == SISOT) { // SISOTool-designed controller (unstable)
		SISOT_P_Out_Sig_struct_T u_next_sisopc = AAU3_DiscSISOTool(x_hat);
		i_m_next = u_next_sisopc.I_m;
	}
	else if (contType == LSF2) { // 16Gr630 LSF controller
		LSF_COutput_struct_T u_next_lsf = AAU3_DiscLinFeedback2(x_hat);
		i_m_next = u_next_lsf.I_m;
	}

	// Controller tester
	static long ct_count = 0;
	static double i_m_add = 0;
	if (0) {
		ct_count++;
		if (ct_count < 450) {
			//Nothing happens in this region
		} else if (ct_count < 500) {
			i_m_next = i_m_next + i_m_add;
		} else {
			ct_count = 0;
			i_m_add += 0.5;
		}
	}

	static bool goingPos = true;
	const double testLim = 80;
	static double testLim_n = 0;
	static double count__ = 0;

	if ( 0 ) {
		count__++;
		if (count__ > 100) {
			if (goingPos) {
				if (x_hat[2] > testLim) {
					goingPos = !goingPos;
					testLim_n++;
				}
			} else {
				if (x_hat[2] < -testLim) {
					goingPos = !goingPos;
					testLim_n++;
				}
			}

			if (goingPos)
				i_m_next = 0.5 * (1 + testLim_n / 2);
			else
				i_m_next = -0.5 * (1 + testLim_n / 2);
		} else
			i_m_next = 0;
	}

	if (1) { // 1 = set first part. 0 = set second part
		// If fallen over, then stop the wheel
		const double act_region = 0.35;
		if (potRad < -act_region || potRad > act_region) {
			i_m_next = -0.15 * tachRads;
			if (-2 < tachRads && tachRads < 2 ) {
				i_m_next = 0;
			}
		}
	} else { // keep constant velocity
		double error = 90 - tachRads; // reference error
		const double act_region2 = 0.35;
		if (potRad < -act_region2 || potRad > act_region2) {
			i_m_next = 0.15 * error;
		}

	}


	const double i_m_sat = 4;
	if (i_m_next > i_m_sat) i_m_next = i_m_sat;
	if (i_m_next < -i_m_sat) i_m_next = -i_m_sat;


	/* ################################
	 * ## 5. Logging
	 * ################################ */

	// Toggle
	static bool enableSchedIO = false;
	enableSchedIO = !enableSchedIO;
	args->mAwesomeGpio->setValue(enableSchedIO);


	if (0) {
		std::cout << "Hello from the other side !\tcount:" << ct_count << "\tPotentiometer: " << potAdc << endl;//"\ti_m: " << i_m_next << "\ti_m_next: " << i_m_next << "\tTach: " << tachRads << "\tx_hat: " << endl;
		//accX1 << ", " << accY1 << ", " << accX2 << ", " << accY2 << ", " << potAdc << endl;
		if (1) {
			if (logfile.is_open())
			{
				static long count = 0;
				count++;
//					logfile <<  count << ", " << potRad << ", " << tachRads << ", " << i_m_next << ", " << x_hat[0] << ", " << x_hat[1] << ", " << x_hat[2] << ", " << gyroRads1 << ", " << gyroRads2 << ", "
//							<< accX1 << ", " << accY1 << ", " << accX2 << ", " << accY2 << ", " << i_m_add <<  endl;
			}
		}

	}
	args->mRaisePin->setValue(false);


}

ControllerBase* ControllerTest::createController(string& name)
{
	return new ControllerTest;
}

//REGISTER_CONTROLLER(ControllerTest);

