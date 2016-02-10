/*
 * io_service.hpp
 *
 *  Created on: 03/09/2014
 *      Author: benjaminkrebs
 */

/*
 * The main purpose of this service is to deliver the data displayed by the web interface.
 */

#include <fstream>


#ifndef IO_SERVICE_HPP_
#define IO_SERVICE_HPP_

class IoService {

public:
	#define OUT_STREAM "../aau3_out"
	#define IN_STREAM "../aau3_in"

	static IoService* getInstance();

	void tx(const char* strData);
	int rx(char buf[],unsigned int bufLen); //returns how many bytes received


	~IoService();
private:
	IoService();
	static IoService* mpInstance;

	std::ofstream mOutFile;
	std::ifstream mInFile;

};




#endif /* IO_SERVICE_HPP_ */
