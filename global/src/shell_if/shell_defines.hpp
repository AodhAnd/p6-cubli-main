/*
 * shell_defines.hpp
 *
 *  Created on: 14/10/2014
 *      Author: benjaminkrebs
 */

#ifndef SHELL_DEFINES_HPP_
#define SHELL_DEFINES_HPP_

#include <iostream>
using namespace std;


#ifdef DEBUG_ON
#define DEBUG_MSG(moduleName,msg) cout << moduleName << ":" << msg << endl;
#endif



#endif /* SHELL_DEFINES_HPP_ */
