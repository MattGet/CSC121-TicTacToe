#pragma once
//MattGet CSC 121 7/25
#include <iostream>                                               //header files to include strings and windows for color, and fstream for files, algorithm and cctype for the Lower function(transform)
#include <string>
#include <Windows.h>
#include <fstream>
#include <algorithm>
#include <cctype>
using namespace std;												//std namespace
class account
{
private:															//list private variabels in private class structure
	string _user{ "bob" };
	string _pass{ "pass123" };
	string _fname{ "exe.txt" };
	string filename(){
		_fname = _user + "_" + _pass[0] + _pass[1] + _pass[2] + ".txt";
		return _fname;
	}	
	void admnAccounts() {																	//start void admin accounts function, which writes all accounts and passwords to a private administrative log
		fstream accounts;
		accounts.open("admnAccounts.txt", ios::app);
		if (!accounts) {                                                                    //check if there was an error opeining 
			cerr << "\nError when opening file";
			exit(EXIT_FAILURE);
		}
		accounts << "\n" << _user << " " << _pass;
		accounts.close();
	}
	bool crossCheck() {																		//start crossCheck bool function, which determines if the account details entered are in the admin database
		ifstream test;
		test.open("admnAccounts.txt");														//test object is designed to create a .txt file if one does not exist, this is because read commands will not create a file
		if (!test) {
			Color(12);
			cout << "\n\tNo logs detected.... creating file....";
			fstream fix;
			test.open("admnAccounts.txt", ios::app);
			test.close();
		}
		fstream check;																		//open admin file with read perms
		check.open("admnAccounts.txt", ios::in);
		if (!check) {                                                                       //check if there was an error opeining 
			cerr << "\nError when opening file";
			exit(EXIT_FAILURE);
		}
		string line;
		string data = _user + " " + _pass;													//format current credentials to match the format in logs
		while (std::getline(check, line))									
		{
			cout << "\r	verifying data ";
			for (int x = 0; x < 3; x++)
			{
				Sleep(100);
				cout << "." << flush;
				Sleep(100);
				cout << "." << flush;
				Sleep(100);
				cout << "." << flush;
				Sleep(100);
				cout << "\b\b\b   \b\b\b" << flush;
			}
			if (line.find(data) != std::string::npos)										//loop through all the lines and look for a match using the find command
			{
				Color(14);
				std::cout << "\n\t" << line << " confirmed to exist." << endl;
				check.close();
				return true;																//return true if there is a match
			}
		}
		check.close();
		return false;																		//return fale if there is no match
	}
public:
	void Color(int color)                                                                  //start a function which allows the system to understand color as a variable and change parts of the output throught the script
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	explicit account() {																	//list all required constructors

	}
	explicit account(std::string in) {
		_user = in;
	}
	explicit account(std::string in, std::string in2) {
		_user = in;
		_fname = in2;
	}
	std::string Lower(std::string word)														//creating a function which will convert an entire string to lowercase, like toupper/tolower commands but much more powerful
	{
		std::transform(word.begin(), word.end(), word.begin(), tolower);
		return word;
	}
	void create() {																														//start a create method, this walks the user through creating an account
		string check;
		while (!(Lower(check) == "yes")) {
		label:
			Color(13);
			cout << "\n\tPlease enter a username: ";																					//prompt user for a name and password
			cin >> _user;
			cout << "\n\tPlease choose a password thats at least 5 characters long: ";
			cin >> _pass;
			if (crossCheck() == true) {																									//if the account already exists re-prompt them
				Color(12);
				cout << "\n\tThat account already exists! Try again.";
				goto label;
			}
			do {
				Color(13);
				cout << "\n\tYour Username was " << _user << " and your password was " << _pass << " is this correct yes or no? ";		//confirm with the user the account details are what they want
				cin >> check;
				if (Lower(check) == "yes" || Lower(check) == "no") break;
				else {
					Color(12);
					cout << "\n\tYou must choose \"yes\" or \"no\" try again";
				}
			} while (true);
			if (Lower(check) == "no") {
				goto label;
			}
			if (Lower(check) == "yes") break;
		}
		Color(10);
		cout << "\n\tAccount created sucessfully, you are now logged in as: " << _user << endl;
		admnAccounts();
	}
	void login() {																								//start login function
	label1:
		Color(13);
		cout << "\n\tPlease enter your username: ";																//prompt for their user and password
		cin >> _user;
		cout << "\n\tPlease enter your password: ";
		cin >> _pass;
		if (crossCheck() == true) {																				//if their account is in the database log them in
			cout << "\n\tYou are now logged in as: " << _user << endl;
		}
		else {																									//otherwise inform them there is no account in that nam, then give them the coice to try again or create a new account
			int temp;				
			do {
				Color(14);
				cout << "\n\tNo such account exists enter 1 to try again or 2 to create a new account: ";
				cin >> temp;
				if (cin.fail() || temp < 1 || temp > 2) {
					cout << string(35, '\n');
					Color(12);
					cout << "\n\n\tThere was an error with your choice, pick '1' to try again or '2' to create a new account!\n";           //clear the screen and output an error
					cin.clear();
					cin.ignore();
				}
				else break;
			} while (true);
			if (temp == 1) {
				goto label1;
			}
			if (temp == 2) {
				create();
			}
		}
	}
	std::string get_filename() {								//getters for filename and username, there is no getter for the password as that information is kept as secure as possible
		string temp;
		temp = filename();
		return temp;
	}
	std::string get_user() {									
		return _user;
	}
	void set_filename(std::string in){							//setters for filename and username, these are never used, but are there for redundency, again password is not included for security
		_fname = in;
	}
	void set_user(std::string in) {
		_user = in;
	}
};

