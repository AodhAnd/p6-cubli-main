/*
 * AAU3_DiscLinObserver.h
 *
 * Code generation for function 'AAU3_DiscLinObserver'
 *
 * C source code generated on: Wed Dec 03 13:19:04 2014
 *
 */

#ifndef __AAU3_DISCLINOBSERVER_H__
#define __AAU3_DISCLINOBSERVER_H__
/* Include files */
#include <stddef.h>
#include <stdlib.h>

#include "rtwtypes.hpp"
#include "AAU3_DiscLinObserver_types.hpp"

/* Function Declarations */
extern void AAU3_DiscLinObserver(real_T O_Lin_Ts, const real_T O_Lin_x_hat_last[3], const O_Lin_struct_T *O_Lin_u_last, const real_T O_Lin_y[2], real_T O_Lin_x_hat[3]);
extern void AAU3_DiscLinObserver_initialize(void);
extern void AAU3_DiscLinObserver_terminate(void);
#endif
/* End of code generation (AAU3_DiscLinObserver.h) */
