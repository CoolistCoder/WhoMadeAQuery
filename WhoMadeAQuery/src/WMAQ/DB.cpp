/*
 * DB.cpp
 *
 *  Created on: Dec 7, 2023
 *      Author: alec
 */

#include "DB.h"

void DB::flushUser(){
	//Remove the user's info from the buffer
	this->userID = 0;
	this->userFN.erase();
	this->userLN.erase();
}

void DB::errHandle(sql::SQLException &e){
	//Just output all info I need to tell what's going on
	std::cout << "SQL EXCEPTION: " << __FILE__ << std::endl;
	std::cout << "(" << __FUNCTION__ << ") LINE: " << __LINE__ << std::endl;
	std::cout << "ERROR: " << e.what() << std::endl;
	std::cout << "ERROR CODE: " << e.getErrorCode() << std::endl;
	std::cout << "STATE: " << e.getSQLState() << std::endl;
	//Remember to set the runstate to false to indicate we've run into an error and can't run
	//Author note: This might be undesireable based on circumstances.
	//You really want errors like this to be handled in some way, not crash the system.
	//Hence why the runstate is determined on a function by function basis
}

bool DB::connectToDB(std::string pwd){
	//Hopefully, we have everything we need.
	//So attempt a connection to the localhost.
	try{
		this->driver = get_driver_instance();
		this->connect = this->driver->connect(this->connectName,this->username,pwd);
		this->connect->setSchema("WhoMadeAQueryDB");
	}
	catch (sql::SQLException &e){
		this->errHandle(e);
		this->runstate = false;
	}
	//Return true by default
	return true;
}

bool DB::createUser(){
	//create a user with a unique id specified by user
	std::string customQuery;
	std::ostringstream* stream = nullptr;	//I need this in order to move ints into the string
	bool allDone = false; //If the user has achieved all they wanted, we call it a success
	std::string tryThisAgain; //If the user made a mistake, ask if they want to try again
	try{
		do{
			//code to create and login user here
			std::cout << "I need a new, unique userID in order to create a user" << std::endl;
			std::cout << "Please input an ID: ";
			this->userID = getUsrInt();

			//Once a user id is input, try to see if it's unique
			//build the query
			stream = new std::ostringstream;
			customQuery.erase();
			*stream << "SELECT usrID FROM user WHERE usrID = " << this->userID;
			customQuery = stream->str();
			delete(stream);

			//Once query is built, build statement and execute query
			this->statement = this->connect->createStatement();
			this->results = this->statement->executeQuery(customQuery);
			if (!this->results->next()){ //Nobody was found, move forward with name stuff
				std::cout << "This userID is available!" << std::endl;
				std::cout << "Please input a first and last name for the user" << std::endl;
				std::cout << "First name: ";
				this->userFN = getUsrTxt();
				std::cout << std::endl;
				std::cout << "Last name: ";
				this->userLN = getUsrTxt();
				std::cout << std::endl;

				//clear the query pointers and execute a new custom query
				this->clearQuery();
				//build the query/s that'll use our new data
				stream = new std::ostringstream;
				customQuery.erase();
				*stream << "INSERT INTO `user` (usrID, usrFirstName, usrLastName) VALUES ('"
						<< this->userID << "', '" << this->userFN << "', '" << this->userLN
						<< "');";
				customQuery = stream->str();
				delete(stream);

				//execute query
				this->statement = this->connect->createStatement();
				this->results = this->statement->executeQuery(customQuery);

				std::cout << "User creation success!" << std::endl;
				std::cout << "Welcome in, " << this->userFN << " " << this->userLN << "!" << std::endl;
				this->clearQuery();
				return true;
			}
			else{ //Someone was found.  Ask user if they would like to try again or quit
				std::cout << "The userID you used was in the system already." << std::endl;
				std::cout << "Would you like to try again? (y/n)" << std::endl;
				tryThisAgain = getUsrTxt();
				if (tryThisAgain == "n"){
					allDone = true;
				}
			}

			//Free the pointers we used
			this->clearQuery();
		}while (!allDone);
		//If we're here, a user was not created.
		std::cout << "Failed to create a user" << std::endl;
		this->clearQuery();
		return false;
	}
	catch (sql::SQLException &e){
		this->errHandle(e);
		std::cout << "Failed to create user due to an error" << std::endl;
		this->clearQuery();
		return false;
	}
}

bool DB::loginUser(){
	//Find user in DB based on provided user input
	std::string customQuery;
	std::ostringstream* stream = nullptr;	//I need this in order to move ints into the string
	try{
		//Get the user's input and see what we can find
		std::cout << "Please input the user's ID you want to find : ";
		this->userID = getUsrInt();
		std::cout << "Attempting to find the user with userID = " << this->userID << std::endl;

		//build query using stringstream and store in string
		stream = new std::ostringstream;
		customQuery.erase();
		*stream << "SELECT * FROM user WHERE usrID = " << this->userID;
		customQuery = stream->str();
		delete(stream);

		//execute built query
		this->statement = this->connect->createStatement();
		this->results = this->statement->executeQuery(customQuery);
		if (this->results->next()){
			//fill in the values where applicable:
			this->userFN = this->results->getString(2);
			this->userLN = this->results->getString(3);
			std::cout << "User found!" << std::endl;
			std::cout << "Welcome in, " << this->userFN << " " << this->userLN << "!" << std::endl;
			this->clearQuery();
			return true;
		}
		else{
			//Couldn't find the stuff we wanted, unfortunately
			std::cout << "Unable to find that user" << std::endl;
			this->flushUser();
		}
		return false;
	}
	catch(sql::SQLException &e){
		this->errHandle(e);
		std::cout << "Error logging in user" << std::endl;
		return false;
	}
}

void DB::quitOut(){
	//simply disable the run state after confirmation
	std::string usrnpt;
	std::cout << "Are you sure you want to quit? (y/n)" << std::endl;
	usrnpt = getUsrTxt();
	if (usrnpt == "y"){
		std::cout << "Goodbye!" << std::endl;
		this->runstate = false;
	}
}

bool DB::queryDBforUsers(){
	//Simply do a SELECT * to output all users in DB
	//Errors shouldn't be here but just in case,
	//error catching tells us why a SELECT * failed.
	try{
		std::cout << "Printing all users..." << std::endl;
		//code to print all users here

		std::cout << "That's everyone!" << std::endl;
		return true;
	}
	catch(sql::SQLException &e){
		this->errHandle(e);
		std::cout << "Printing users" << std::endl;
		return false;
	}
}

bool DB::checkMyHistory(){
	//Simply do a SELECT WHERE userID is current userID
	//Errors shouldn't be here but just in case,
	//error catching tells us why a SELECT * failed.
	try{
		std::cout << "Printing history..." << std::endl;
		//code to print all users here

		std::cout << "That's everything!" << std::endl;
		return true;
	}
	catch(sql::SQLException &e){
		this->errHandle(e);
		std::cout << "Error printing history" << std::endl;
		return false;
	}
}

void DB::userLogout(){
	//Flush a user's credentials after confirmation
	//returns to login screen
	std::string usrnpt;
	std::cout << "Are you sure you want to logout? (y/n)" << std::endl;
	usrnpt = getUsrTxt();
	if (usrnpt=="y"){
		std::cout << "Logging out..." << std::endl;
		//When user's credentials are flushed, we know they're logged out
		this->flushUser();
	}
	flushin();
}

void DB::clearQuery(){
	//free the query pointers
	if (this->results){
		delete this->results;
		this->results = nullptr;
	}
	if (this->statement){
		delete this->statement;
		this->statement = nullptr;
	}
}

bool DB::getLoggedIn(){
	//if we have user data>0, then we can say we're logged in
	if (this->userID && !this->userFN.empty() && !this->userLN.empty()){
		return true;
	}
	return false;
}

void DB::handleLogin(LOGIN_CODES opcode){
	//just a simple switch to determine inputs
	switch(opcode){
	case LI_EXISTINGUSER: //User wants to login to existing entry
		this->loginUser();
		break;
	case LI_NEWUSER: //User wants to add new entry
		this->createUser();
		break;
	case LI_QUIT: //Ask to quit program
		this->quitOut();
		break;
	default:
		std::cout << "Invalid input, please try again" << std::endl;
		break;
	}
}

void DB::handleOptions(OPTION_CODES lgcode){
	//just a simple switch to determine inputs
	switch(lgcode){
	case OP_QUERYDB: //User wants to know about other users
		this->queryDBforUsers();
		break;
	case OP_CHECKHIST: //User wants to see what they've done
		this->checkMyHistory();
		break;
	case OP_LOGOUT: //User wants to logout
		this->userLogout();
	break;
	default:
		std::cout << "Invalid input, please try again" << std::endl;
		break;
	}
}

DB::DB(){
	//By default, let's try to connect to the dummy user
	this->connectName = "tcp://127.0.0.1:3306"; //localhost
	this->username = "dummyuser";
	//assume we're gonna connect correctly
	this->runstate = true;

	//attempt to connect
	this->connectToDB("password");
}

DB::DB(std::string connectTo, std::string username) {
	//Attempt to connect to specified db with creds
	//Make a small check for "localhost" and overwrite with appropriate tcp link
	if (connectTo == "localhost")
		this->connectName = "tcp://127.0.0.1:3306";
	else
		this->connectName = connectTo;
	this->username = username;
	//assume we're gonna connect correctly
	this->runstate = true;

	//attempt to connect to DB using provided creds
	this->connectToDB("password");
}

DB::~DB() {
	delete this->results;
	delete this->statement;
	delete this->connect;
}

