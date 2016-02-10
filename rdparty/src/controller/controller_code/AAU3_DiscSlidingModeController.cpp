/*
 * AAU3_DiscSlidingModeController.c
 *
 * Code generation for function 'AAU3_DiscSlidingModeController'
 *
 * C source code generated on: Fri Nov 28 10:38:59 2014
 *
 */

/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscSlidingModeController.hpp"

/* Type Definitions */
#ifndef typedef_C_SM_b_struct_T
#define typedef_C_SM_b_struct_T

typedef struct {
  char_T C_SM_description[19];
  real_T C_SM_g;
  real_T C_SM_m_b;
  real_T C_SM_m_w;
  real_T C_SM_l_b;
  real_T C_SM_l_w;
  real_T C_SM_Ic_w;
  real_T C_SM_Ia_w;
  real_T C_SM_Ia_b;
  real_T C_SM_Ia;
  real_T C_SM_I_b;
  real_T C_SM_B_b;
  real_T C_SM_B_w;
  real_T C_SM_R_m;
  real_T C_SM_K_e;
  real_T C_SM_K_m;
  real_T C_SM_U_m_max;
  real_T C_SM_I_m_max;
  real_T C_SM_RPM_m_max;
  real_T C_SM_p1;
  real_T C_SM_p2;
  real_T C_SM_p3;
  real_T C_SM_p4;
  real_T C_SM_p5;
  real_T C_SM_p6;
  real_T C_SM_DTheta_B_SwingUp;
  real_T C_SM_DTheta_W_SwingUp;
  real_T C_SM_NoiseAngle;
  real_T C_SM_NoiseWheelVel;
} C_SM_b_struct_T;

#endif                                 /*typedef_C_SM_b_struct_T*/

#ifndef typedef_C_SM_c_struct_T
#define typedef_C_SM_c_struct_T

typedef struct {
  real_T C_SM_K_Slide[2];
  real_T C_SM_beta;
  real_T C_SM_epsilon;
  real_T C_SM_P1;
  real_T C_SM_P2;
  real_T C_SM_P3;
  real_T C_SM_A1;
  real_T C_SM_A2;
  real_T C_SM_A3;
} C_SM_c_struct_T;

#endif                                 /*typedef_C_SM_c_struct_T*/

/* Variable Definitions */
static C_SM_b_struct_T C_SM_PARM;
static uint32_T C_SM_PARM_dirty;
static C_SM_c_struct_T C_SM_INPUT;
static uint32_T C_SM_INPUT_dirty;

/* Function Definitions */
C_SM_struct_T AAU3_DiscSlidingModeController(real_T C_SM_unusedU0, const real_T
  C_SM_x[3])
{
  C_SM_struct_T C_SM_u;
  real_T C_SM_eta1;
  real_T C_SM_eta2;
  real_T C_SM_zeta1;
  real_T C_SM_y;
  real_T C_SM_b_x;

  /*  From the system */
  C_SM_eta1 = (-C_SM_x[0] + C_SM_x[1] / C_SM_PARM.C_SM_p4) + C_SM_x[2] /
    C_SM_PARM.C_SM_p6;
  C_SM_eta2 = C_SM_x[1] / C_SM_PARM.C_SM_p4 + C_SM_x[2] / C_SM_PARM.C_SM_p6;
  C_SM_zeta1 = -C_SM_x[1] / C_SM_PARM.C_SM_p4;

  /* % */
  /*  Sliding Manifold */
  /* % */
  /*  Sliding mode gain calculation */
  C_SM_y = ((C_SM_zeta1 + C_SM_INPUT.C_SM_K_Slide[0] * C_SM_eta1) +
            C_SM_INPUT.C_SM_K_Slide[1] * C_SM_eta2) / C_SM_INPUT.C_SM_epsilon;
  if (C_SM_y < 0.0) {
    C_SM_b_x = -1.0;
  } else if (C_SM_y > 0.0) {
    C_SM_b_x = 1.0;
  } else if (C_SM_y == 0.0) {
    C_SM_b_x = 0.0;
  } else {
    C_SM_b_x = C_SM_y;
  }

  if (fabs(C_SM_y) <= 1.0) {
    C_SM_b_x = C_SM_y;
  }

  C_SM_u.C_SM_U_m = -((C_SM_INPUT.C_SM_P1 * sin(C_SM_eta1 - C_SM_eta2) +
                       C_SM_INPUT.C_SM_P2 * C_SM_eta2) + C_SM_INPUT.C_SM_P3 *
                      C_SM_zeta1) - C_SM_b_x * (((C_SM_INPUT.C_SM_A1 +
    C_SM_INPUT.C_SM_A2 * fabs(C_SM_eta2)) + C_SM_INPUT.C_SM_A3 * fabs(C_SM_zeta1))
    + C_SM_INPUT.C_SM_beta);
  C_SM_u.C_SM_Brake = 0.0;
  return C_SM_u;
}

void AAU3_DiscSlidingModeController_initialize(void)
{
  static C_SM_b_struct_T C_SM_r0 = { { 'P', 'a', 'r', 'a', 'm', 'e', 't', 'e',
      'r', 's', ' ', 'f', 'o', 'r', ' ', 'A', 'A', 'U', '3' }, 9.82, 0.354,
    0.222, 0.076, 0.093, 0.00057, 0.002490078, 0.00334, 0.0058300780000000007,
    0.0052600780000000005, 0.00102, 5.0E-5, 1.03, 0.0335, 0.0335, 4.0,
    3.883495145631068, 104.71975511965977, 88.770736859795591,
    0.19391347428688319, 0.0095055624650432942, 6.368726851579007,
    0.097224860710657335, 65.140656676140409, 7.2111506509443446,
    66.545991041610577, 1.0E-5, 0.0001 };

  static C_SM_c_struct_T C_SM_r1 = {
		  { 2.8723, -3.2186}, //K
		    0.5, //Beta
		    0.2, //Epsilon
		    30.586, 0.01222, 10.8464, //P
		    1.5831, // A1
		    0.1648, // A2
		    0.0005  // A3
  	  	  };

  C_SM_PARM = C_SM_r0;
  C_SM_INPUT = C_SM_r1;
  rt_InitInfAndNaN(8U);
  C_SM_INPUT_dirty = 0U;
  C_SM_PARM_dirty = 0U;
}

void AAU3_DiscSlidingModeController_terminate(void)
{
  /* (no terminate code required) */
}

/* End of code generation (AAU3_DiscSlidingModeController.c) */
