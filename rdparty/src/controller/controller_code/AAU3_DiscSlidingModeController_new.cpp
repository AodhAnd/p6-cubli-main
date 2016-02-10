/*
 * AAU3_DiscSlidingModeController_new.c
 *
 * Code generation for function 'AAU3_DiscSlidingModeController_new'
 *
 * C source code generated on: Sun Dec 14 11:36:36 2014
 *
 */

/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscSlidingModeController_new.hpp"

/* Type Definitions */
#ifndef typedef_C_SMC_new_b_struct_T
#define typedef_C_SMC_new_b_struct_T

typedef struct {
  char_T C_SMC_new_description[19];
  real_T C_SMC_new_g;
  real_T C_SMC_new_m_b;
  real_T C_SMC_new_m_w;
  real_T C_SMC_new_l_b;
  real_T C_SMC_new_l_w;
  real_T C_SMC_new_Ic_w;
  real_T C_SMC_new_Ia_w;
  real_T C_SMC_new_Ia_b;
  real_T C_SMC_new_Ia;
  real_T C_SMC_new_I_b;
  real_T C_SMC_new_B_b;
  real_T C_SMC_new_B_w;
  real_T C_SMC_new_R_m;
  real_T C_SMC_new_K_e;
  real_T C_SMC_new_K_m;
  real_T C_SMC_new_U_m_max;
  real_T C_SMC_new_I_m_max;
  real_T C_SMC_new_RPM_m_max;
  real_T C_SMC_new_p1;
  real_T C_SMC_new_p2;
  real_T C_SMC_new_p3;
  real_T C_SMC_new_p4;
  real_T C_SMC_new_p5;
  real_T C_SMC_new_p6;
  real_T C_SMC_new_DTheta_B_SwingUp;
  real_T C_SMC_new_DTheta_W_SwingUp;
  real_T C_SMC_new_NoiseAngle;
  real_T C_SMC_new_NoiseWheelVel;
  real_T C_SMC_new_NoiseGyro;
} C_SMC_new_b_struct_T;

#endif                                 /*typedef_C_SMC_new_b_struct_T*/

#ifndef typedef_C_SMC_new_c_struct_T
#define typedef_C_SMC_new_c_struct_T

typedef struct {
  real_T C_SMC_new_K_Slide[2];
  real_T C_SMC_new_beta0;
  real_T C_SMC_new_epsilon;
  real_T C_SMC_new_kappa0;
  real_T C_SMC_new_a6;
  real_T C_SMC_new_a7;
  real_T C_SMC_new_a8;
  real_T C_SMC_new_P1;
  real_T C_SMC_new_P2;
  real_T C_SMC_new_P3;
} C_SMC_new_c_struct_T;

#endif                                 /*typedef_C_SMC_new_c_struct_T*/

/* Variable Definitions */
static boolean_T C_SMC_new_init_not_empty;
static real_T C_SMC_new_a3_hat;
static real_T C_SMC_new_a4_hat;
static real_T C_SMC_new_a5_hat;
static C_SMC_new_c_struct_T C_SMC_new_INPUT;
static uint32_T C_SMC_new_INPUT_dirty;
static C_SMC_new_b_struct_T C_SMC_new_PARM;
static uint32_T C_SMC_new_PARM_dirty;

/* Function Definitions */
C_SMC_new_struct_T AAU3_DiscSlidingModeController_new(real_T C_SMC_new_unusedU0,
  const real_T C_SMC_new_x[3])
{
  C_SMC_new_struct_T C_SMC_new_u;
  real_T C_SMC_new_q2;
  real_T C_SMC_new_q3;
  if (!C_SMC_new_init_not_empty) {
    C_SMC_new_init_not_empty = TRUE;

    /*  Sub definitions */
    /*  Sub sub definitions */
    C_SMC_new_q2 = C_SMC_new_PARM.C_SMC_new_p3 * C_SMC_new_PARM.C_SMC_new_p6 /
      C_SMC_new_PARM.C_SMC_new_p4 - C_SMC_new_PARM.C_SMC_new_p5;
    C_SMC_new_q3 = C_SMC_new_PARM.C_SMC_new_p1 / C_SMC_new_PARM.C_SMC_new_p6 -
      C_SMC_new_PARM.C_SMC_new_p1 / C_SMC_new_PARM.C_SMC_new_p4;

    /*  sub sub sub definitions */
    C_SMC_new_q2 = (C_SMC_new_PARM.C_SMC_new_p3 * C_SMC_new_PARM.C_SMC_new_p6 /
                    C_SMC_new_PARM.C_SMC_new_p4 +
                    C_SMC_new_INPUT.C_SMC_new_K_Slide[0] * C_SMC_new_q2) +
      C_SMC_new_INPUT.C_SMC_new_K_Slide[1] * C_SMC_new_q2;
    C_SMC_new_a3_hat = (C_SMC_new_PARM.C_SMC_new_p1 /
                        C_SMC_new_PARM.C_SMC_new_p4 -
                        C_SMC_new_INPUT.C_SMC_new_K_Slide[0] * C_SMC_new_q3) -
      C_SMC_new_INPUT.C_SMC_new_K_Slide[1] * C_SMC_new_q3;
    C_SMC_new_a4_hat = ((((C_SMC_new_PARM.C_SMC_new_p2 *
      C_SMC_new_PARM.C_SMC_new_p4 - C_SMC_new_PARM.C_SMC_new_p3 *
      C_SMC_new_PARM.C_SMC_new_p6) / C_SMC_new_PARM.C_SMC_new_p4 +
                          C_SMC_new_INPUT.C_SMC_new_K_Slide[0] *
                          ((C_SMC_new_PARM.C_SMC_new_p4 +
      (C_SMC_new_PARM.C_SMC_new_p2 * C_SMC_new_PARM.C_SMC_new_p4 +
       C_SMC_new_PARM.C_SMC_new_p3 * C_SMC_new_PARM.C_SMC_new_p6) /
      C_SMC_new_PARM.C_SMC_new_p4) - (C_SMC_new_PARM.C_SMC_new_p2 *
      C_SMC_new_PARM.C_SMC_new_p4 + C_SMC_new_PARM.C_SMC_new_p5 *
      C_SMC_new_PARM.C_SMC_new_p6) / C_SMC_new_PARM.C_SMC_new_p6)) +
                         C_SMC_new_INPUT.C_SMC_new_K_Slide[1] *
                         ((C_SMC_new_PARM.C_SMC_new_p2 *
      C_SMC_new_PARM.C_SMC_new_p4 + C_SMC_new_PARM.C_SMC_new_p3 *
      C_SMC_new_PARM.C_SMC_new_p6) / C_SMC_new_PARM.C_SMC_new_p4 -
                          (C_SMC_new_PARM.C_SMC_new_p2 *
      C_SMC_new_PARM.C_SMC_new_p4 + C_SMC_new_PARM.C_SMC_new_p5 *
      C_SMC_new_PARM.C_SMC_new_p6) / C_SMC_new_PARM.C_SMC_new_p6)) -
                        C_SMC_new_q2) / C_SMC_new_PARM.C_SMC_new_p4;
    C_SMC_new_a5_hat = C_SMC_new_q2 / C_SMC_new_PARM.C_SMC_new_p4;
  }

  /* % */
  /*  Sliding Manifold */
  C_SMC_new_q2 = ((-C_SMC_new_x[1] / C_SMC_new_PARM.C_SMC_new_p4 +
                   C_SMC_new_INPUT.C_SMC_new_K_Slide[0] * ((-C_SMC_new_x[0] +
    C_SMC_new_x[1] / C_SMC_new_PARM.C_SMC_new_p4) + C_SMC_new_x[2] /
    C_SMC_new_PARM.C_SMC_new_p6)) + C_SMC_new_INPUT.C_SMC_new_K_Slide[1] *
                  (C_SMC_new_x[1] / C_SMC_new_PARM.C_SMC_new_p4 + C_SMC_new_x[2]
                   / C_SMC_new_PARM.C_SMC_new_p6)) /
    C_SMC_new_INPUT.C_SMC_new_epsilon;
  if (C_SMC_new_q2 < 0.0) {
    C_SMC_new_q3 = -1.0;
  } else if (C_SMC_new_q2 > 0.0) {
    C_SMC_new_q3 = 1.0;
  } else if (C_SMC_new_q2 == 0.0) {
    C_SMC_new_q3 = 0.0;
  } else {
    C_SMC_new_q3 = C_SMC_new_q2;
  }

  if (fabs(C_SMC_new_q2) <= 1.0) {
    C_SMC_new_q3 = C_SMC_new_q2;
  }

  C_SMC_new_u.C_SMC_new_U_m = ((C_SMC_new_a4_hat * C_SMC_new_x[1] +
    C_SMC_new_a5_hat * C_SMC_new_x[2]) + C_SMC_new_a3_hat * sin(C_SMC_new_x[0]))
    + -C_SMC_new_q3 * (((C_SMC_new_INPUT.C_SMC_new_a6 +
    C_SMC_new_INPUT.C_SMC_new_a7 * fabs(C_SMC_new_x[1])) +
                        C_SMC_new_INPUT.C_SMC_new_a8 * fabs(C_SMC_new_x[2])) /
                       (1.0 - C_SMC_new_INPUT.C_SMC_new_kappa0) +
                       C_SMC_new_INPUT.C_SMC_new_beta0);
  C_SMC_new_u.C_SMC_new_Brake = 0.0;
  return C_SMC_new_u;
}

void AAU3_DiscSlidingModeController_new_initialize(void)
{
  static C_SMC_new_c_struct_T C_SMC_new_r0 = {
		      { 1.6651, -1.794}, //K
		  	  3.0, //beta0
		  	  0.3, //Epsilon
		  	  0.1508, //kappa0
		  	  1.5831, // a6
		  	  0.1648, // a7
		  	  0.0005, // a8
		  	  25.8816, // P1
		  	  0.0047919, //P2
		      5.9454 };  //P3

  static C_SMC_new_b_struct_T C_SMC_new_r1 = { { 'P', 'a', 'r', 'a', 'm', 'e',
      't', 'e', 'r', 's', ' ', 'f', 'o', 'r', ' ', 'A', 'A', 'U', '3' }, 9.82,
    0.354, 0.222, 0.076, 0.093, 0.0006012627, 0.0025213407, 0.002808,
    0.0053293407000000008, 0.004728078, 0.0030985, 1.20317E-5, 1.03, 0.0335,
    0.0335, 4.0, 3.883495145631068, 104.71975511965977, 98.759157526589007,
    0.65534028837933722, 0.0025447338220731552, 7.0853315025682742,
    0.022555454593542933, 62.801410347971469, 7.6060354371074892,
    59.810676460402924, 3.473556415E-6, 0.009132509954428, 0.0 };

  C_SMC_new_INPUT = C_SMC_new_r0;
  C_SMC_new_PARM = C_SMC_new_r1;
  rt_InitInfAndNaN(8U);
  C_SMC_new_PARM_dirty = 0U;
  C_SMC_new_INPUT_dirty = 0U;
  C_SMC_new_init_not_empty = FALSE;
}

void AAU3_DiscSlidingModeController_new_terminate(void)
{
  /* (no terminate code required) */
}

/* End of code generation (AAU3_DiscSlidingModeController_new.c) */
