/*
 * AAU3_InOutLinearization.c
 *
 * Code generation for function 'AAU3_InOutLinearization'
 *
 * C source code generated on: Tue Dec 02 16:07:14 2014
 *
 */

/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_InOutLinearization.hpp"

/* Type Definitions */
#ifndef typedef_C_InOut_b_struct_T
#define typedef_C_InOut_b_struct_T

typedef struct {
  char_T C_InOut_description[19];
  real_T C_InOut_g;
  real_T C_InOut_m_b;
  real_T C_InOut_m_w;
  real_T C_InOut_l_b;
  real_T C_InOut_l_w;
  real_T C_InOut_Ic_w;
  real_T C_InOut_Ia_w;
  real_T C_InOut_Ia_b;
  real_T C_InOut_Ia;
  real_T C_InOut_I_b;
  real_T C_InOut_B_b;
  real_T C_InOut_B_w;
  real_T C_InOut_R_m;
  real_T C_InOut_K_e;
  real_T C_InOut_K_m;
  real_T C_InOut_U_m_max;
  real_T C_InOut_I_m_max;
  real_T C_InOut_RPM_m_max;
  real_T C_InOut_p1;
  real_T C_InOut_p2;
  real_T C_InOut_p3;
  real_T C_InOut_p4;
  real_T C_InOut_p5;
  real_T C_InOut_p6;
  real_T C_InOut_DTheta_B_SwingUp;
  real_T C_InOut_DTheta_W_SwingUp;
  real_T C_InOut_NoiseAngle;
  real_T C_InOut_NoiseWheelVel;
} C_InOut_b_struct_T;

#endif                                 /*typedef_C_InOut_b_struct_T*/

#ifndef typedef_C_InOut_c_struct_T
#define typedef_C_InOut_c_struct_T

typedef struct {
  real_T C_InOut_K_InOut[3];
} C_InOut_c_struct_T;

#endif                                 /*typedef_C_InOut_c_struct_T*/

/* Variable Definitions */
static C_InOut_b_struct_T C_InOut_PARM;
static uint32_T C_InOut_PARM_dirty;
static C_InOut_c_struct_T C_InOut_INPUT;
static uint32_T C_InOut_INPUT_dirty;

/* Function Definitions */
C_InOut_struct_T AAU3_InOutLinearization(real_T C_InOut_Ts, const real_T
  C_InOut_x[3])
{
  C_InOut_struct_T C_InOut_u;
  real_T C_InOut_b[3];
  real_T C_InOut_v;
  int32_T C_InOut_i0;

  /*  From the system */
  C_InOut_b[0] = C_InOut_x[1] / C_InOut_PARM.C_InOut_p4 + C_InOut_x[2] /
    C_InOut_PARM.C_InOut_p6;
  C_InOut_b[1] = C_InOut_x[0];
  C_InOut_b[2] = C_InOut_x[1];
  C_InOut_v = 0.0;
  for (C_InOut_i0 = 0; C_InOut_i0 < 3; C_InOut_i0++) {
    C_InOut_v += -C_InOut_INPUT.C_InOut_K_InOut[C_InOut_i0] *
      C_InOut_b[C_InOut_i0];
  }

  C_InOut_u.C_InOut_U_m = -((//(C_InOut_PARM.C_InOut_p3 * C_InOut_x[2] -
    //C_InOut_PARM.C_InOut_p2 * C_InOut_x[1]) +
		  C_InOut_PARM.C_InOut_p1 * sin(C_InOut_x[0]) ) - C_InOut_v) / -C_InOut_PARM.C_InOut_p4;
  C_InOut_u.C_InOut_Brake = 0.0;
  return C_InOut_u;
}

void AAU3_InOutLinearization_initialize(void)
{
  static C_InOut_b_struct_T C_InOut_r0 = { { 'P', 'a', 'r', 'a', 'm', 'e', 't',
      'e', 'r', 's', ' ', 'f', 'o', 'r', ' ', 'A', 'A', 'U', '3' }, 9.82, 0.354,
    0.222, 0.076, 0.093, 0.00057, 0.002490078, 0.00334, 0.0058300780000000007,
    0.0052600780000000005, 0.00102, 2.203E-5, 1.03, 0.0335, 0.0335, 4.0,
    3.883495145631068, 104.71975511965977,
    97.3469, 0.9628, 0.2113263542472405, 4.2159, 0.0338, 67.5546,
    7.2111506509443446,
    66.545991041610577, 1.0E-5, 0.0001 };

  static C_InOut_c_struct_T C_InOut_r1 =   //{30.6622*0.6 ,  107.4441*1.5  , 15.3207*1.5}
  { {18.3973 , 161.1662 ,  22.9811}}; //{18.5934*0.3 ,  47.9320*2 ,   9.5494*1.3}}; //{ 1.4487*1.7  , 20.9428*1.5  ,  3.2595*0.6 } };
  // Best so far: {23.4209*0.125  , 74.7714*1 ,  12.4498*0.4}
  // Best no noise so far: {30.6622*0.3 ,  107.4441*1.3  , 15.3207},

  C_InOut_PARM = C_InOut_r0;
  C_InOut_INPUT = C_InOut_r1;
  rt_InitInfAndNaN(8U);
  C_InOut_INPUT_dirty = 0U;
  C_InOut_PARM_dirty = 0U;
}

void AAU3_InOutLinearization_terminate(void)
{
  /* (no terminate code required) */
}

/* End of code generation (AAU3_InOutLinearization.c) */
