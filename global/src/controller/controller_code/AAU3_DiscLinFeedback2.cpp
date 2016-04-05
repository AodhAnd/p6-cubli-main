/*
* AAU3_DiscLinFeedback2.hpp
* Simple LTI discrete proportional controller
* 
* Code written by 16gr630 
* @ Aalborg University - March 2016
*
*/


/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscLinFeedback2.hpp"

/* Type definitions */
#ifndef typedef_Lin_Controller_struct_T
#define typedef_Lin_Controller_struct_T

typedef struct {
  real_T K_p;
  real_T theta_ref;
} Lin_Controller_struct_T ;

#endif // typedef_Lin_Controller_struct_T

static Lin_Controller_struct_T LinC;

/** Runs the controller based on the feedback signal in x_hat */
Lin_Out_Sig_struct_T AAU3_DiscLinFeedback2(const real_T x_hat[3])
{
  /** Variable declarations */
  // Output signal(s)
  static Lin_Out_Sig_struct_T Lin_U;
  // Error signal(s)
  real_T Lin_e = 0.0;

  /** Calculations */
  // Error
  Lin_e = LinC.theta_ref - x_hat[0];
  // Controller job
  Lin_U.I_m = Lin_e * LinC.K_p;

  return Lin_U;
}

/** 
* Initializes the controller parameters with the reference input and
* the controller specifics.
*/
void AAU3_DiscLinFeedback2_initialize(real_T sys_ref)
{
  /*-- Controller parameters --*/
  // Proportional gain
  LinC.K_p   = -1;

  /*-- Reference signals --*/
  // Angle reference
  LinC.theta_ref  = sys_ref;

  // Some math define requirements
  rt_InitInfAndNaN(8U);
}

void AAU3_DiscLinFeedback2_terminate(void)
{
  // Nothing to do really...
}