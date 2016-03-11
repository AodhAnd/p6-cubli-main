/*
 * AAU3_DiscLinObserver.c
 *
 * Code generation for function 'AAU3_DiscLinObserver'
 *
 * C source code generated on: Wed Dec 03 13:19:04 2014
 *
 */

/* Include files */
#include "rt_nonfinite.hpp"
#include "AAU3_DiscLinObserver.hpp"

/* Type Definitions */
#ifndef typedef_O_Lin_b_struct_T
#define typedef_O_Lin_b_struct_T

typedef struct {
  real_T O_Lin_K[3];
  real_T O_Lin_A[9];
  real_T O_Lin_B[3];
  real_T O_Lin_C[6];
  real_T O_Lin_L[6];
  real_T O_Lin_Ad[9];
  real_T O_Lin_Bd[3];
  real_T O_Lin_Cd[6];
} O_Lin_b_struct_T;

#endif                                 /*typedef_O_Lin_b_struct_T*/

/* Variable Definitions */
static O_Lin_b_struct_T O_Lin_INPUT;
static uint32_T O_Lin_INPUT_dirty;

/* Function Definitions */
void AAU3_DiscLinObserver(real_T O_Lin_Ts, const real_T O_Lin_x_hat_last[3],
  const O_Lin_struct_T *O_Lin_u_last, const real_T O_Lin_y[2], real_T
  O_Lin_x_hat[3])
{
  real_T O_Lin_b_y[2];
  int32_T O_Lin_i0;
  real_T O_Lin_d0;
  int32_T O_Lin_i1;
  real_T O_Lin_dv0[3];
  real_T O_Lin_dv1[3];

  /*     %% First */
  /*     %% Second */
  /*     %% Third */
  for (O_Lin_i0 = 0; O_Lin_i0 < 2; O_Lin_i0++) {
    O_Lin_d0 = 0.0;
    for (O_Lin_i1 = 0; O_Lin_i1 < 3; O_Lin_i1++) {
      O_Lin_d0 += O_Lin_INPUT.O_Lin_Cd[O_Lin_i0 + (O_Lin_i1 << 1)] *
        O_Lin_x_hat_last[O_Lin_i1];
    }

    O_Lin_b_y[O_Lin_i0] = O_Lin_y[O_Lin_i0] - O_Lin_d0;
  }

  for (O_Lin_i0 = 0; O_Lin_i0 < 3; O_Lin_i0++) {
    O_Lin_d0 = 0.0;
    for (O_Lin_i1 = 0; O_Lin_i1 < 3; O_Lin_i1++) {
      O_Lin_d0 += O_Lin_INPUT.O_Lin_Ad[O_Lin_i0 + 3 * O_Lin_i1] *
        O_Lin_x_hat_last[O_Lin_i1];
    }

    O_Lin_dv1[O_Lin_i0] = O_Lin_d0 + O_Lin_INPUT.O_Lin_Bd[O_Lin_i0] *
      O_Lin_u_last->O_Lin_U_m;
  }

  for (O_Lin_i0 = 0; O_Lin_i0 < 3; O_Lin_i0++) {
    O_Lin_dv0[O_Lin_i0] = 0.0;
    for (O_Lin_i1 = 0; O_Lin_i1 < 2; O_Lin_i1++) {
      O_Lin_dv0[O_Lin_i0] += O_Lin_INPUT.O_Lin_L[O_Lin_i0 + 3 * O_Lin_i1] *
        O_Lin_b_y[O_Lin_i1];
    }

    O_Lin_x_hat[O_Lin_i0] = O_Lin_dv1[O_Lin_i0] + O_Lin_dv0[O_Lin_i0];
  }
}

void AAU3_DiscLinObserver_initialize(void)
{
  static O_Lin_b_struct_T O_Lin_r0 = { { -22.887257202402029,
      -2.4936506282645254, -0.044809648854561991 },
		  {0   ,  0  ,   0 ,    1  ,   0  ,   0 ,    0 ,    0 ,    0}, //{ 0.0, 88.770736859795591, -88.770736859795591, 1.0, -0.19391347428688319, 0.19391347428688319, 0.0, 0.21132635424724056, -2.1614896995035857 },
		  { 0, 0, 0}, //{ 0.0, -6.368726851579007, 65.140656676140409 },
		  { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
      //{0.9300 ,  21.6200   ,      0   ,      0    ,     0  ,  0.4500}, // L - Best
		  //{0.9300 ,  21.6200   ,      0   ,      0    ,     0  ,  0.4500},
		  {1.0388, 4.7384, 0, 1.0399E-05, 0.0020824, 0.97851},
      { //L
      1.0044358415957408, 0.88722848266692567, -0.878633829842384,
      0.010005096949635322, 1.0024977529457395, -0.0024878308653438624,
      1.0491586967065723E-5, 0.002091663205095861, 0.97861595780769584 }, //Ad
      { - 0.00031618418758435713, -0.063036300731184186, 0.64444931248892712 }, //Bd
      { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 } }; // Cd

  O_Lin_INPUT = O_Lin_r0;
  rt_InitInfAndNaN(8U);
  O_Lin_INPUT_dirty = 0U;
}

void AAU3_DiscLinObserver_terminate(void)
{
  /* (no terminate code required) */
}

/* End of code generation (AAU3_DiscLinObserver.c) */
