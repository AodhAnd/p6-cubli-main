/*
* AAU3_DiscSISOTool.cpp
* This is an attempt to implement the discretized version of a controller
* designed with the SISOTool from MATLAB, from the root locus plot.
* 
* Code written by 16gr630 
* @ Aalborg University - March 2016
*
*/


/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscSISOTool.hpp"
#include <iostream>

/* Type definitions */
#ifndef typedef_Lin_Controller_struct_T
#define typedef_Lin_Controller_struct_T

#define K_T 0.0335
#define TORQUE_2_CURRENT 1/K_T

/**
 * This structure contains all the elements relative to the controller.
 * (real_T) K is the proportional gain
 * (real_T*) a regroups all coefficients relative to the controller input (error)
 * (real_T*) b regroups all coefficients relative to the controller output (current)
 * (real_T*) im_del regroups all the output signals with different delays
 * (real_T*) e_del regroups all the input signals with different delays
 * For e_del and im_del, the index n indicates the signal delayed by n*Ts
 * (real_T) theta_ref is the angle reference signal to the feedback system
 */
typedef struct {
  real_T K;
  real_T a[4];
  real_T b[4];
  real_T taum_del[4];
  real_T e_del[4];
  real_T theta_ref;
} SISOT_Lin_PController_struct_T ;

#endif // typedef_Lin_Controller_struct_T

/** 
 * This variable contains all the parameters for the controller 
 * and is strictly internal to this file (it is not accessible from outside).
 * This is thanks to the `static` keyword.
 */
static SISOT_Lin_PController_struct_T SISOT_PComp;

/** Runs the controller based on the feedback signal in x_hat */
SISOT_P_Out_Sig_struct_T AAU3_DiscSISOTool(const real_T x_hat[3])
{
  /** Variable declarations */
  SISOT_P_Out_Sig_struct_T SISOT_P_U;
  
  /** Signal shifting */
  SISOT_PComp.e_del[3] = SISOT_PComp.e_del[2];
  SISOT_PComp.e_del[2] = SISOT_PComp.e_del[1];
  SISOT_PComp.e_del[1] = SISOT_PComp.e_del[0];

  SISOT_PComp.taum_del[3] = SISOT_PComp.taum_del[2];
  SISOT_PComp.taum_del[2] = SISOT_PComp.taum_del[1];
  SISOT_PComp.taum_del[1] = SISOT_PComp.taum_del[0];
  
  /** New calculations */
  // On-the-instant error
  SISOT_PComp.e_del[0] = SISOT_PComp.theta_ref - x_hat[0]; 
  // Enlarging the tolerant zone
//  if(SISOT_PComp.e_del[0] > -0.005 && SISOT_PComp.e_del[0] < 0.005) {
//	  SISOT_PComp.e_del[0] = 0;
//  }
//  else {
//	  if(SISOT_PComp.e_del[0] < 0)
//		  SISOT_PComp.e_del[0] -= -0.005;
//	  else
//		  SISOT_PComp.e_del[0] -= 0.005;
//  }

  // Controller job
  SISOT_PComp.taum_del[0] = SISOT_PComp.K * (SISOT_PComp.a[0] * SISOT_PComp.e_del[0] + SISOT_PComp.a[1] * SISOT_PComp.e_del[1] + SISOT_PComp.a[2] * SISOT_PComp.e_del[2] + SISOT_PComp.a[3] * SISOT_PComp.e_del[3] +
		  SISOT_PComp.b[1] * SISOT_PComp.taum_del[1] + SISOT_PComp.b[2] * SISOT_PComp.taum_del[2] + SISOT_PComp.b[3] * SISOT_PComp.taum_del[3]);
  
  if(TORQUE_2_CURRENT * SISOT_PComp.taum_del[0] > 4)
	  SISOT_PComp.taum_del[0] = K_T * 4;//SISOT_PComp.taum_del[1];
  else if(TORQUE_2_CURRENT * SISOT_PComp.taum_del[0] < -4)
	  SISOT_PComp.taum_del[0] = K_T * -4;//SISOT_PComp.taum_del[1];
  
  SISOT_P_U.I_m = TORQUE_2_CURRENT * SISOT_PComp.taum_del[0];
  
 
  std::cout << "Controller: "<< "I_m: " << SISOT_P_U.I_m << "\tTau_m: " << SISOT_PComp.taum_del[0] << "\tError: " << SISOT_PComp.e_del[0] << std::endl;
  
  return SISOT_P_U;
}

void AAU3_DiscSISOTool_print(){
  std::cout << "Controller: "<< "I_m: " << TORQUE_2_CURRENT * SISOT_PComp.taum_del[0] << "\tTau_m: " << SISOT_PComp.taum_del[0] << "\tError: " << SISOT_PComp.e_del[0] << std::endl;
}


/** 
* Initializes the controller parameters with the reference input and
* the controller specifics.
*/
void AAU3_DiscSISOTool_initialize(const real_T sys_ref)
{
  static SISOT_Lin_PController_struct_T PC0;

  /*-- Controller parameters --*/
  // Proportional gain
  PC0.K   = 1;
  // Difference equations coefficients
//  // a
//  PC0.a[0] = -8.311;
//  PC0.a[1] = 7.42;
//  PC0.a[2] = -8.299;
//  PC0.a[3] = 7.432;
//  // b
//  PC0.b[0] =  1; // More symoblic than useful, see report
//  PC0.b[1] = 1.383;
//  PC0.b[2] = -0.3435;
//  PC0.b[3] = -0.001351;

  //a
  PC0.a[0] = -8.314;
  PC0.a[1] = 7.422;
  PC0.a[2] = 8.302;
  PC0.a[3] = -7.434;
  //b
  PC0.b[0] =  1; // More symoblic than useful, see report
  PC0.b[1] = +1,382;//1.383;
  PC0.b[2] = -0.3415;//-0.3435;
  PC0.b[3] = -0.001638;//-0.001351;

  /*-- Initial signals --*/
  // Angle reference
  PC0.theta_ref  = sys_ref;

  // Initial input/output signals of the controller
  PC0.e_del[0] = 0;
  PC0.e_del[1] = 0;
  PC0.e_del[2] = 0;
  PC0.e_del[3] = 0;
  PC0.taum_del[0] = 0;
  PC0.taum_del[1] = 0;
  PC0.taum_del[2] = 0;

  SISOT_PComp = PC0;
  // Some math define requirements
  rt_InitInfAndNaN(8U);
}

void AAU3_DiscSISOTool_terminate(void)
{
  // Nothing to do really...
}

