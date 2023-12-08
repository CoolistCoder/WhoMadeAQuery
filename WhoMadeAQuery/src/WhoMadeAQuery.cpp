//Simple program that connects to a DB that logs every time a query was made.
//PLEASE FOLLOW THE README FILE IF YOU WANT TO REPRODUCE THIS IMPLEMENTATION
//Ver0.01 Not finished yet build
//Written by Alec

#include "WMAQ/DB.h"

#include <iostream>
using namespace std;

int main() {
	//Local DB object for connecting to a database.
	DB* mydbo; //For this object: user is 'dummyuser' and pw is 'password'
			  //Schema is WhoMadeAQueryDB

	//Give a status update on whether or not we're connected to a server
	cout << "Connecting to the DB:" << endl;
	mydbo = new DB();
	//failure to connect results in error catch going off

	//some clean output for users
	cout << "Welcome to WhoMadeAQuery!  Please select an option:" << endl;

	//So long as we have our connection, I want to continue allowing user inputs
	while(mydbo->getRunstate()){
		//if we're not logged in, query input for the login screen
		if (!mydbo->getLoggedIn()){
			loginMenu();
			mydbo->handleLogin((LOGIN_CODES)getUsrInt());

		}
		else{
			optionsMenu();
			mydbo->handleOptions((OPTION_CODES)getUsrInt());

		}
	}


	delete mydbo;
	return 0;
}
