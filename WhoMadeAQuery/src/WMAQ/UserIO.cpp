/*
 * UserIO.cpp
 *
 *  Created on: Dec 7, 2023
 *      Author: alec
 */

#include "UserIO.h"

unsigned int getUsrInt(){
	//Getline can be repurposed to retrieve int values
	unsigned int usrin;
	while (!(std::cin >> usrin)){ //Just keep taking inputs till an input is valid
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "This input is not a digit value" << std::endl;
	}
	return usrin;
}

std::string getUsrTxt(){
	//getline can be used to retrieve text input
	std::string usrin;
	//std::getline(std::cin, usrin); //this breaks the code
	std::cin >> usrin;
	return usrin;
}

void loginMenu(){
	//Give list of options for user to look over
	//pertaining to logins
	std::cout << "Options: " << std::endl;
	std::cout << "1) Login with USERID" << std::endl;
	std::cout << "2) Create new user" << std::endl;
	std::cout << "3) Quit" << std::endl;
}

void optionsMenu(){
	//Give list of options for user to look over
	//pertaining to options after login
	std::cout << "Options: " << std::endl;
	std::cout << "1) Query DB" << std::endl;
	std::cout << "2) Check History" << std::endl;
	std::cout << "3) Logout" << std::endl;
}
