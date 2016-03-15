/*
 * AAU3_DiscLinFeedback.c
 *
 * Code generation for function 'AAU3_DiscLinFeedback'
 *
 * C source code generated on: Fri Nov 21 13:36:15 2014
 *
 */

/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscLinFeedback.hpp"

/* Type Definitions */
#ifndef typedef_C_Lin_b_struct_T
#define typedef_C_Lin_b_struct_T

typedef struct {
  real_T C_Lin_K[3];
  real_T C_Lin_A[9];
  real_T C_Lin_B[3];
  real_T C_Lin_C[6];
  real_T C_Lin_L[6];
} C_Lin_b_struct_T;

#endif                                 /*typedef_C_Lin_b_struct_T*/

/* Variable Definitions */
static C_Lin_b_struct_T C_Lin_INPUT;
static uint32_T C_Lin_INPUT_dirty;

/* Function Definitions */
C_Lin_struct_T AAU3_DiscLinFeedback(real_T C_Lin_Ts, const real_T C_Lin_x_hat[3])
{
  C_Lin_struct_T C_Lin_u;
  real_T C_Lin_y;
  int32_T C_Lin_i0;

  /* AAU3_DISCLINFEEDBACK Summary of this function goes here */
  /*    Detailed explanation goes here */
  C_Lin_y = 0.0;
  for (C_Lin_i0 = 0; C_Lin_i0 < 3; C_Lin_i0++) {
    C_Lin_y += -C_Lin_INPUT.C_Lin_K[C_Lin_i0] * C_Lin_x_hat[C_Lin_i0];
  }

  C_Lin_u.C_Lin_U_m = C_Lin_y;
  C_Lin_u.C_Lin_Brake = 0.0;
  return C_Lin_u;
}

void AAU3_DiscLinFeedback_initialize(void)
{									//	-25.4856   -2.5171   -0.0222 //-26.9399*3 ,  -2.9095*1.4 ,  -0.0564*1.3
  static C_Lin_b_struct_T C_Lin_r0 = { {   -34.4385 ,  -3.3871*0.9  , -0.0616*0.6}, //{   -26.9399*1.3 ,  -2.9095 ,  -0.0564}, // -18.6035,    -1.4,    -10.4106/1000
		  { 0.0, 97.761443273601827,
      -97.761443273601827, 1.0, -0.19982775631044303, 0.19982775631044303, 0.0,
      0.0097954782505119131, -0.097514776496125957 }, { 0.0, -6.5629704278429815,
      65.3349002524044 }, { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
      {   0.181266716419802*1000,   5.799198776879221*1000,  -0.065926992230969*1000,   0.037997349392054*1000,   1.752025449097445*1000,   0.058435941047391*1000 } };

  C_Lin_INPUT = C_Lin_r0;
  rt_InitInfAndNaN(8U);
  C_Lin_INPUT_dirty = 0U;
}

void AAU3_DiscLinFeedback_terminate(void)
{
  /* (no terminate code required) */
}

/* End of code generation (AAU3_DiscLinFeedback.c) */
