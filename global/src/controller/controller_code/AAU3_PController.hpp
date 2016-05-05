/*
* AAU3_PController.hpp
* Code written by 16gr630
* at Aalborg University
*
*/

#ifndef AAU3_PCONTROLLER_HPP
#define AAU3_PCONTROLLER_HPP

/* Include files */
#include <stddef.h>
#include <stdlib.h>

#include "rtwtypes.hpp"
#include "AAU3_DiscLinFeedback_types.hpp"

/* Type Definitions */
#ifndef typedef_Lin_Sig_struct_T
#define typedef_Lin_Sig_struct_T

typedef struct
{
  real_T I_m;
} Lin_Out_Sig_struct_T;

#endif /*typedef_Lin_Sig_struct_T*/

/* Function Declarations */

/** 
 * Runs the controller based on the feedback signal in x_hat
 * @param
 */
extern Lin_Out_Sig_struct_T AAU3_PController(const real_T x_hat[3]);

/**
 * Initializes the controller parameters with the reference input and
 * the controller specifics.
 */

extern void AAU3_PController_initialize(real_T sys_ref);
extern void AAU3_PController_terminate(void);

#endif // AAU3_PCONTROLLER_HPP
