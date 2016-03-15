/*
 * DiscreteLurenbergerEstimator_take2.cpp
 *
 * Code generation for function 'DiscreteLurenbergerEstimator_take2'
 *
 * C source code generated on: Fri Jun 12 15:48:30 2015
 *
 */

/* Include files */
#include "rt_nonfinite.hpp"
#include "DiscreteLurenbergerEstimator_take2.h"

/* Type Definitions */
typedef struct {
  real_T O_Obv2_A[16];
  real_T O_Obv2_B[4];
  real_T O_Obv2_C[16];
  real_T O_Obv2_L[16];
} O_Obv2_b_struct_T;

typedef struct {
  char_T O_Obv2_description[19];
  real_T O_Obv2_g;
  real_T O_Obv2_m_b;
  real_T O_Obv2_m_w;
  real_T O_Obv2_l_b;
  real_T O_Obv2_l_w;
  real_T O_Obv2_Ic_w;
  real_T O_Obv2_Ia_w;
  real_T O_Obv2_Ia_b;
  real_T O_Obv2_Ia;
  real_T O_Obv2_I_b;
  real_T O_Obv2_B_b;
  real_T O_Obv2_B_w;
  real_T O_Obv2_R_m;
  real_T O_Obv2_K_e;
  real_T O_Obv2_K_m;
  real_T O_Obv2_U_m_max;
  real_T O_Obv2_I_m_max;
  real_T O_Obv2_RPM_m_max;
  real_T O_Obv2_p1;
  real_T O_Obv2_p2;
  real_T O_Obv2_p3;
  real_T O_Obv2_p4;
  real_T O_Obv2_p5;
  real_T O_Obv2_p6;
  real_T O_Obv2_DTheta_B_SwingUp;
  real_T O_Obv2_DTheta_W_SwingUp;
  real_T O_Obv2_NoiseAngle;
  real_T O_Obv2_NoiseWheelVel;
  real_T O_Obv2_NoiseGyro;
  real_T O_Obv2_IMU_p[6];
  real_T O_Obv2_IMU_theta[3];
  real_T O_Obv2_IMU_noiseOn;
  real_T O_Obv2_IMU_noiseGyro;
  real_T O_Obv2_IMU_noiseAcc;
  real_T O_Obv2_IMU_noiseWheel;
  real_T O_Obv2_x1_offset;
  O_Obv2_b_struct_T O_Obv2_O;
} O_Obv2_c_struct_T;

/* Variable Definitions */
static O_Obv2_c_struct_T O_Obv2_PARM;
static uint32_T O_Obv2_PARM_dirty;

/* Function Definitions */
void DiscreteLurenbergerEstimator_take2(real_T, const real_T O_Obv2_x_hat_last[4],
  const O_Obv2_struct_T *O_Obv2_u_last, const real_T O_Obv2_y[4], real_T
  O_Obv2_x_hat[4])
{
  real_T O_Obv2_dv0[4];
  int32_T O_Obv2_i0;
  real_T O_Obv2_d0;
  int32_T O_Obv2_i1;
  real_T O_Obv2_dv1[4];
  real_T O_Obv2_dv2[4];
  for (O_Obv2_i0 = 0; O_Obv2_i0 < 4; O_Obv2_i0++) {
    O_Obv2_d0 = 0.0;
    for (O_Obv2_i1 = 0; O_Obv2_i1 < 4; O_Obv2_i1++) {
      O_Obv2_d0 += O_Obv2_PARM.O_Obv2_O.O_Obv2_C[O_Obv2_i0 + (O_Obv2_i1 << 2)] *
        O_Obv2_x_hat_last[O_Obv2_i1];
    }

    O_Obv2_dv0[O_Obv2_i0] = O_Obv2_d0 - O_Obv2_y[O_Obv2_i0];
  }

  for (O_Obv2_i0 = 0; O_Obv2_i0 < 4; O_Obv2_i0++) {
    O_Obv2_d0 = 0.0;
    for (O_Obv2_i1 = 0; O_Obv2_i1 < 4; O_Obv2_i1++) {
      O_Obv2_d0 += O_Obv2_PARM.O_Obv2_O.O_Obv2_A[O_Obv2_i0 + (O_Obv2_i1 << 2)] *
        O_Obv2_x_hat_last[O_Obv2_i1];
    }

    O_Obv2_dv2[O_Obv2_i0] = O_Obv2_d0 + O_Obv2_PARM.O_Obv2_O.O_Obv2_B[O_Obv2_i0]
      * O_Obv2_u_last->O_Obv2_U_m;
  }

  for (O_Obv2_i0 = 0; O_Obv2_i0 < 4; O_Obv2_i0++) {
    O_Obv2_dv1[O_Obv2_i0] = 0.0;
    for (O_Obv2_i1 = 0; O_Obv2_i1 < 4; O_Obv2_i1++) {
      O_Obv2_dv1[O_Obv2_i0] += O_Obv2_PARM.O_Obv2_O.O_Obv2_L[O_Obv2_i0 +
        (O_Obv2_i1 << 2)] * O_Obv2_dv0[O_Obv2_i1];
    }

    O_Obv2_x_hat[O_Obv2_i0] = O_Obv2_dv2[O_Obv2_i0] - O_Obv2_dv1[O_Obv2_i0];
  }
}

void DiscreteLurenbergerEstimator_take2_initialize()
{
  static O_Obv2_c_struct_T O_Obv2_r0 = { { 'P', 'a', 'r', 'a', 'm', 'e', 't',
      'e', 'r', 's', ' ', 'f', 'o', 'r', ' ', 'A', 'A', 'U', '3' }, 9.82, 0.354,
    0.222, 0.076, 0.093, 0.0006012627, 0.0025213407, 0.002808,
    0.0053293407000000008, 0.004728078, 0.0030985, 1.20317E-5, 1.03, 0.0335,
    0.0335, 4.0, 3.883495145631068, 104.71975511965977, 97.3469, 0.9628,
    2.3999E-5, 4.2159, 0.0338, 67.5546, 7.6060354371074892, 59.810676460402924,
    3.473556415E-6, 0.009132509954428, 0.0008726646259971648, { -0.1,
      0.12000000000000001, 0.02, 0.2, 0.1, 0.08 }, { 0.0, 0.0, 0.0 }, 1.0,
    0.0008726646259971648, 0.03928, 0.009132509954428, 0.05235987755982989,
    { {
        1.0048556958210293, 0.97037019475769659, -0.97020620724293138, 0.0,
        0.0099681685937242533, 0.9952583442514088, 0.0047405807474822552, 0.0,
        1.1969432916992142E-9, 2.3918562139752893E-7, 0.99966205787929285, 0.0,
        0.0, 0.0, 0.0, 1.0 }, { -0.00021029024446552345, -0.042024721115256784,
        0.67529766479398723, 0.0 }, { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 },
       /* { 0.012440362159019995, 0.086471686031808534, 0.21681185565637007, 0.081438136913460218,
        0.00929142482511081, 0.34885428392213258, -1.914708905678256,
        -0.0028188093868286796, 0.0092914248251108229, 0.34885428392213297,
        -1.9147089056782511, -0.0028188093868286852, 0.00022550342708393405,
        -0.017783592954515304, 0.736109888293709, -0.00031894158141692735 }*/
        // L:start
        {0.012419,0.082704,0.17508,0.08144,0.0091706,0.38086,-1.5515,-0.0025266,0.0091706,0.38086,-1.5515,-0.0025266,0.00021044,-0.014381,0.79254,-0.00028542}
        //{0.012473,0.089939,0.24679,0.081423,0.0093686,0.31885,-2.1902,-0.0030596,0.0093686,0.31885,-2.1902,-0.0030596,0.00023647,-0.020364,0.6815,-0.00034453}
    	} // L:end
  	  };

  O_Obv2_PARM = O_Obv2_r0;
  rt_InitInfAndNaN(8U);
  O_Obv2_PARM_dirty = 0U;
}

void DiscreteLurenbergerEstimator_take2_terminate()
{
  /* (no terminate code required) */
}

/* End of code generation (DiscreteLurenbergerEstimator_take2.cpp) */
