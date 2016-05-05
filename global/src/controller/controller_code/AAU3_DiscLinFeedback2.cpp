/*
* AAU3_DiscLinFeedback2.hpp
* This is an implementation of a state space linearized feedback 
* controller
* 
* Code written by 16gr630
* @ Aalborg University - March 2016
*
*/


/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscLinFeedback2.hpp"
#include <iostream>

/* Type definitions */
#ifndef typedef_LSF_Controller_Param_struct_T
#define typedef_LSF_Controller_Param_struct_T

#define K_T 0.0335
#define TORQUE_2_CURRENT 1/K_T

/**
 * This structure contains all the elements relative to the controller.
 * (real_T [3]) K is the gain vector of the LSF controller
 */
typedef struct {
  real_T K[3];
  real_T tau_m;
} LSF_Controller_Param_struct_T;

#endif // typedef_LSF_Controller_Param_struct_T

/** 
 * This variable contains all the parameters for the controller 
 * and is strictly internal to this file (it is not accessible from outside).
 */
static LSF_Controller_Param_struct_T LSF_Controller;

/** Runs the controller based on the feedback signal in x_hat */
LSF_COutput_struct_T AAU3_DiscLinFeedback2(const real_T x_hat[3])
{
  /** Variable declarations */
  LSF_COutput_struct_T LSF_Sig_Out;
  
  /** Controller calculations */
  LSF_Controller.tau_m = 0;
  for (int i = 0; i < 3; i++)
  {
    LSF_Controller.tau_m += LSF_Controller.K[i] * x_hat[i];
  }

  /** Print output */
  AAU3_DiscLinFeedback2_print();

  LSF_Sig_Out.I_m = LSF_Controller.tau_m * TORQUE_2_CURRENT;
  
  return LSF_Sig_Out;
}

void AAU3_DiscLinFeedback2_print(){
  std::cout << "LSF Controller: "<< "I_m: " << TORQUE_2_CURRENT * LSF_Controller.tau_m << "\tTau_m: " << LSF_Controller.tau_m << std::endl;
}


/** 
* Initializes the controller parameters
*/
void AAU3_DiscLinFeedback2_initialize()
{
  static  LSF_Controller_Param_struct_T LSF0;

  /** Controller parameters - Uncomment the part you want */
  // Poles: -6, -7 and -15
  LSF0.K[0] = -2.3021;
  LSF0.K[1] = -0.227;
  LSF0.K[2] = -0.0039;
  // Poles: -4, -5 and -15
  // LSF0.K[0] = 1.7252;
  // LSF0.K[1] = 0.1759;
  // LSF0.K[2] = 0.0019;
  // Poles: -2, -3 and -11
  // LSF0.K[0] = 2.0354;
  // LSF0.K[1] = 0.217;
  // LSF0.K[2] = 0.0025;
  // Poles: -4, -5 and -13
  // LSF0.K[0] = 1.0752;
  // LSF0.K[1] = 0.1047;
  // LSF0.K[2] = 0.0004;
  // Poles: -4, -5 and -10
  // LSF0.K[0] = 1.6011;
  // LSF0.K[1] = 0.1595;
  // LSF0.K[2] = 0.0016;

  LSF0.tau_m = 0;

  LSF_Controller = LSF0;
  // Some math define requirements
  rt_InitInfAndNaN(8U);
}

void AAU3_DiscLinFeedback2_terminate(void)
{
  // Nothing to do really...
}

