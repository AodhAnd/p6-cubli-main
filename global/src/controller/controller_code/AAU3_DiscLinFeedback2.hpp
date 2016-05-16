/*
* AAU3_DiscLinFeedback2.hpp
* This is an implementation of a state space linearized feedback 
* controller
* 
* Code written by 16gr630
* @ Aalborg University - March 2016
*
*/


#ifndef AAU3_DISC_LIN_FEEDBACK2_HPP
#define AAU3_DISC_LIN_FEEDBACK2_HPP

/* Include files */
#include <stddef.h>
#include <stdlib.h>

#include "rtwtypes.hpp"

/* Type Definitions */
#ifndef typedef_LSF_COutput_struct_T
#define typedef_LSF_COutput_struct_T

typedef struct LSFControllerOutput
{
  real_T I_m; // output current = tau_m/K_t
}LSF_COutput_struct_T;

#endif /*typedef_LSF_COutput_struct_T*/

/* Function Declarations */

/**
 * Runs the controller based on the feedback signal in x_hat
 * @param (const real_T*) x_hat corresponds to the states of the state space representation 
 * @return (LSF_COutput_struct_T)
 */
extern LSF_COutput_struct_T AAU3_DiscLinFeedback2(const real_T x_hat[3]);
extern void AAU3_DiscLinFeedback2_print();

/**
 * Initializes the controller parameters with the reference input and
 * the controller specifics.
 */
extern void AAU3_DiscLinFeedback2_initialize();
extern void AAU3_DiscLinFeedback2_terminate(void);

#endif // AAU3_DISC_LIN_FEEDBACK2_HPP