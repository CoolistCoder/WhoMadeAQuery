/*
 * DB.h
 *
 *  Created on: Dec 7, 2023
 *      Author: alec
 */

#ifndef WMAQ_DB_H_
#define WMAQ_DB_H_
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <sstream>
#include "UserIO.h"

//These enums are used to determine what the DB should do
//Based on user input.
typedef enum LOGIN_CODES{
	LI_EXISTINGUSER = 1,
	LI_NEWUSER,
	LI_QUIT
}LOGIN_CODES;
typedef enum OPTION_CODES{
	OP_QUERYDB = 1,
	OP_CHECKHIST,
	OP_LOGOUT
}OPTION_CODES;

//This class is used to connect to the DB and perform queries
//Note: MySQL requires try catch blocks if memory serves
//So make functions small where possible.
class DB {
private:
	//Important info for validating user and connecting
	std::string dbname, username, connectName;

	//Data related to schema to connect to
	std::string schemaName;

	//determines if the program is allowed to run
	bool runstate;

	//Necessary pointers for SQL stuff
	sql::Driver* driver;
	sql::Connection* connect;
	sql::Statement* statement;
	sql::ResultSet* results;

	//once logged in, these are values that are stored
	int userID;
	std::string userFN, userLN;
	void flushUser(); //Removes user's information from the buffer


	void errHandle(sql::SQLException &e);	//just handles all the necessary error handling stuff
	bool connectToDB(std::string pwd);	//Makes an attempt to connect to the specified DB
	void test_print();	//make a little test print

	//options at login
	bool createUser();	//attempts to create user
	bool loginUser();	//attempts to find user and login
	void quitOut();		//quits the program

	//options after login
	bool queryDBforUsers(); //prints out all users
	bool checkMyHistory();	//checks all logged in user actions
	void userLogout();	//logs the user out

	//situational
	void clearQuery(); //clears the pointers used for query building

public:
	//obligatory getters/setters section
	bool getRunstate(){return this->runstate;};

	//check if we are logged in
	bool getLoggedIn();

	//login handler
	void handleLogin(LOGIN_CODES lgcode);
	//option handler
	void handleOptions(OPTION_CODES opcode);



	DB();
	DB(std::string dbname, std::string username);
	virtual ~DB();
};

#endif /* WMAQ_DB_H_ */
