/*
* AAU3_DiscSISOTool.hpp
* This is an attempt to implement the discretized version of a controller 
* designed with the SISOTool from MATLAB, from the root locus plot.
* 
* Code written by 16gr630
* @ Aalborg University - March 2016
*
*/


#ifndef AAU3_DISC_SISO_TOOL_HPP
#define AAU3_DISC_SISO_TOOL_HPP

/* Include files */
#include <stddef.h>
#include <stdlib.h>

#include "rtwtypes.hpp"

/* Type Definitions */
#ifndef typedef_SISOT_P_Out_Sig_struct_T
#define typedef_SISOT_P_Out_Sig_struct_T

typedef struct
{
  real_T I_m;
} SISOT_P_Out_Sig_struct_T;

#endif /*typedef_SISOT_P_Out_Sig_struct_T*/

/* Function Declarations */

/** 
 * Runs the controller based on the feedback signal in x_hat
 * @param
 */
extern SISOT_P_Out_Sig_struct_T AAU3_DiscSISOTool(const real_T x_hat[3]);
extern void AAU3_DiscSISOTool_print();

/**
 * Initializes the controller parameters with the reference input and
 * the controller specifics.
 */
extern void AAU3_DiscSISOTool_initialize(const real_T sys_ref);
extern void AAU3_DiscSISOTool_terminate(void);

#endif // AAU3_DISC_SISO_TOOL_HPP
