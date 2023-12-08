/*
 * UserIO.h
 *
 *  Created on: Dec 7, 2023
 *      Author: alec
 */

//These functions are only used for simple user input and outputs
#ifndef WMAQ_USERIO_H_
#define WMAQ_USERIO_H_
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

//standard user io stuff
inline void flushin(){
	std::cin.ignore();
}

//simple user input
unsigned int getUsrInt();
std::string getUsrTxt();

//Simple menu to determine who's doing what
void loginMenu(); //login as user, create new or quit
void optionsMenu(); //options post login




#endif /* WMAQ_USERIO_H_ */
