// W6 Lab 6 Tic Tac Toe
// MattGet 7/25/21
// CSC 121

#include <iostream>                                                                 //header files to include strings and windows for color, and fstream for files, and ctime and chrono for the date
#include <string>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <chrono>
#include "account.h"
using namespace std;                                                               //enable standard headers

void display();                                                                     //define the display function
void pchoose(std::string);                                                          //define the pchoose function
void win();                                                                         //define the win function
void toeAI();                                                                       //define the ToeAI (Computer) function
bool isplayerturn{};                                                                //define the player determination boolean
void history();                                                                     //define the history function to output the history file
void end();                                                                         //define the end funtion to be called when the game has ended
bool evaluate();                                                                    //define an evaluate function, simmilar to win function but used by toeAI to predict wins
std::string first(std::string);
int i = 1;
string user{ "nodata" };
string fname;
/*Color Codes Reference
* 12 Green player
* 11 Cyan  narrator / computer outputs
* 10 Red   toeAI function or a critical error
* 14 Yellow general output or error message
*/

char sq[] = { '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };         //define the variable for each sqaure 1-9 using an array so that the variable can be swiched in a loop

void Color(int color)                                                                                           //start a function which allows the system to understand color as a variable and change parts of the output throught the script
{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
std::string Lower(std::string word)														//creating a function which will convert an entire string to lowercase, like toupper/tolower commands but much more powerful
{
    std::transform(word.begin(), word.end(), word.begin(), tolower);
    return word;
}
string date(std::string date) 
{
    auto start = std::chrono::system_clock::now();                                                              //use the ctime and chronos libraries to set the system clock to the local time based on https://stackoverflow.com/a/62226067
    auto legacyStart = std::chrono::system_clock::to_time_t(start);
    char buffer[30];                                                                                            //creating a buffer to be compatible with the "safe" ctime_s
    ctime_s(buffer, sizeof(buffer), &legacyStart);                                                              //using ctime_s to convert time to a readable array 
        for (int i = 0; i < 11; i++) {                                                                          //using a loop to write only the current date to a string
            date = date + buffer[i];
        }
    return date;
}
void login() {                                                                                                  //start the login function
    Color(11);                                                                                                  //output date adn greeting (this is the first function to run at the start of the program (with outputs)
    cout << "\n" << date("");
    cout << "\n\nMattGet Tic Tac Toe Project\nAvailable for use under MIT";                                      //greet user
    cout << "\n\nHello and Welcome to Tic Tac Toe!\n";
    string temp;
    do {
        Color(13);
        cout << "\n\n\tWhould you like to \"Login\" or \"Create\" an account?: ";                         //prompt the user to create an account or login to their account
        cin >> temp;
            if (Lower(temp) == "login" || Lower(temp) == "create") break;
            else {
                Color(14);
                cout << string(35, '\n');
                cout << "\n\tYou must choose \"Login\" or \"Create\" try again";
            }
    } while (true);
    account login;
    if (Lower(temp) == "create") {
        login.create();                                                                     //if they chose create account call the create method, if they chose login call the login method
    }
    if (Lower(temp) == "login") {
        login.login();
    }
    user = login.get_user();
    fname = login.get_filename();
}
int main()                                                                                                      //start the main function
{
    if (user == "nodata") {
        login();
    }
    Color(11);                                                                                                  //set color to light blue for narrator
    
    srand(time(NULL));                                                                                               //establish a time for the rand function used later
    
    std:string p = first("\n\n\tWho Shoud go first, you (enter \"me\"), or ToeAI ? : ");
    Color(11);
    if (p == "me") {                                                                                                     //if the player is selected
        cout << "\n\nYou are playing first!";
        isplayerturn = false;
    }
    else {                                                                                                              //if computer was selcted
        cout << "\n\nToeAI is playing first!";
        isplayerturn = true;
    } 
    display();                                                                                                          //display the blank board
    i = 0;                                                                                                              //ensure i is equal to 0
    while (i <= 9) {                                                                                                    //repeat the following lines for 9 turns
        if (isplayerturn == false) {                                                                                    //if it is the players turn
            pchoose("\n\tPlease choose a square from 1-9: ");                                                           //prompt user for a square they want to play
            display();                                                                                                  //display their choice
            isplayerturn = true;                                                                                        //sets bool player turn to true
            i++;                                                                                                        //increaces the value of i
            win();                                                                                                      //calls win function
        }
                                                                                                                   
        if (isplayerturn == true) {                                                                                     //if it is the computers turn
            toeAI();                                                                                                    //has the function/computer ToeAI play a turn 
            display();                                                                                                  //displays the computers choice
            isplayerturn = false;                                                                                       //sets player turn to false
            i++;                                                                                                        //increaces the value of i
            win();                                                                                                      //calls win function
        }                                                                                                           
    }
    return 0;                                                                                                //ends main function
}
std::string first(std::string gofirst) {
    string p;                                                                                                      //define an integral that will be used to determine which player goes first
        do {
            Color(11);
            cout << gofirst;                                                                                            //prompt user to pick who goes first
            cin >> p;
            if (Lower(p) == "me" || Lower(p) == "toeai") break;
            else {
                Color(14);
                cout << string(35, '\n');
                cout << "\n\tYou must choose \"me\" or \"toeai\" try again";
            }
        } while (true);
    return p;                                                                                                       //return the value of p and end the function
}
void display()                                                                                              //starts display function
{                                                                                                           //outputs the board variables using a for loop that prints each horizonal row
    cout << "\n\n\t|-------|-------|-------|";
    for (int i = 1; i <= 7; i += 3) {
        cout << "\n\t|   " << sq[i] << "   |   " << sq[i + 1] << "   |   " << sq[i + 2] << "   |";
        cout << "\n\t|-------|-------|-------|";
    }
}
void pchoose(std::string prompt) {                                                                          //starts the players choice function
    int temp;                                                                                               //define int temp
    string error1{ "" };                                                                                        //define the string for error prompts
    bool pcheck{};                                                                                          //define bool pcheck
    while (pcheck == false) {                                                                               //loop while pcheck is false
        cout << "\n" << prompt << error1;                                                                   //outputs prompt and error1
        cin >> temp;                                                                                        //store input as temp
        Color(10);                                                                                          //sets color to green
        int n = 1;                                                                                          //set an int n = 1 so that the while loop below starts at the value 1
        while (n <= 9) {                                                                                    //for numbers 1-9(the squares on the board)
            if ((temp == n) && !(sq[n] == 79) && !(sq[n] == 88)) {                                          //check if the entered integral is equal to a square and if that square is open (not already X(88) or O(79))
                sq[n] = 'X';                                                                                //set that square to X
                pcheck = true;                                                                              //set pcheck to true so that the turn is ended
            }
            n++;                                                                                            // increase the count of the while loop so that it only runs for 1 - 9
        }
        if (pcheck == false) {                                                                          //if the chosen value does not match an untaken square then the error variable is set to the error message
            cout << string(45, '\n');                                                                   //"clears" the screen, using this instead of system(CLS) as system is a terrible way of doing things
            display();                                                                                  //re-displays the current tic tac toe board
            Color(14);
            error1 = "The number you entered was already chosen or incorrect try again: ";              //prompts user with error and to try again
            cin.clear();                                                                                //cin.ignore and cin.clear in this position protect the system from crashing if invalid data such as a letter is input as a selection
            cin.ignore();
        }
    }

}
void toeAI() {                                                                                         //starts the ToeAI function (*LINES REMARKED OUT ARE FOR DEBUGGING*)
    Color(12);                                                                                         //sets color to red
    int a;                                                                                             //defines integral a
    bool check{};                                                                                      //defines bool check
    char enter[] = { '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };                              //copy of default board array
    memcpy(enter, sq, 10);
    int tai;                                                                                           //tai integral
    for (tai = 1; tai < 10; tai++) {                                                                   //loop for all squares on the board
        if ((!(sq[tai] == 79) && !(sq[tai] == 88))) {                                                  //if the square is open
            sq[tai] = 'O';                                                                             //set the square to O and send that occourance to the evaluate function
            evaluate();
            if (!(evaluate())) {                                                                        //if the evaluate function was false
                //cout << " toeai cannot win ";
                memcpy(sq, enter, 10);                                                                  //undo the change to the board
            }
            else {                                                                                      //otherwise if evaluate was true
                //cout << " toeai can win ";
                a = tai;                                                                                //save the value to output to the user & do not revert the change
                check = true;
                break;                                                                                  //exit the loop
            }
        }
    }
    for (tai = 1; tai < 10; tai++){                                                                     //repeat the same process as above but with X instead, thus determining if the player is about to win
        if ((!(sq[tai] == 79) && !(sq[tai] == 88))) {
            sq[tai] = 'X';
            evaluate();
            if (!(evaluate())) {
                memcpy(sq, enter, 10);
                //cout << " toeai cannot block ";
            }
            else {
                //cout << " toeai can block ";
                sq[tai] = 'O';
                a = tai;
                check = true;
                break;
            }
        }
    }
                                                                                    
    while (check == false) {                                                                           //loop while check is false (if the AI does not produce a move use rand as normal)
        a = rand() % 9 + 1;                                                                            //sets a to a random number from 1 to 9
        int n = 1;                                                                                     //define an integral n as 1 so that the wile loop starts as 1
        while (n <= 9) {                                                                               //checks all numbers 1-9 to represent each square
            if ((a == n) && !(sq[n] == 79) && !(sq[n] == 88)) {                                        //if the entered int is equal to a square and that same square is not an X or O
                //cout << " random numb selected ";
                sq[n] = 'O';                                                                           //then replace with an O and set check to true
                check = true;
            }
            n++;                                                                                        //increase the count of the while loop every time it runs so that is only runs 1-9
            //cout << n;
        }
        //cout << " check false ";
    }

    cout << "\n\n\tToeAI has chosen square " << a;                                                      //output the square chosen by the computer

}
void win() {                                                                                            //starts the win function
    string pyn;                                                                                         //defines the string player yes no
    Color(11);                                                                                          //sets color to cyan
    if (isplayerturn == true) {                                                                         //if it is the players turn string pyn is set to Player
        pyn = user;
    }
    if (isplayerturn == false) {                                                                        //if it is not the players turn the string pyn is set to ToeAI
        pyn = "ToeAI";
    }
    fstream account;                                                                                                                //create an object
    account.open(fname, ios::app);                                                                                        //open filename file using append permission
    if (!account) {                                                                                                                 //check if there was an error opeining 
        cerr << "\nError when opening file";
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= 7; i += 3) {                                                                                                       //win check for the three rows using a loop
        if ((sq[i] == sq[i + 1]) && (sq[i + 1] == sq[i + 2])) {
            cout << "\n\n\t" << pyn << " Was the winner using squares: " << i << ", " << i + 1 << ", and " << i + 2 << endl;
            account << "\n\n\t" << date("") << pyn << " Was the winner using squares: " << i << ", " << i + 1 << ", and " << i + 2;     //write win to tictactoe file along with the date
            account.close();                                                                                                                //close the file
            end();                                                                                                                          //call the end function
        }
    }
    for (int i = 1; i <= 3; i += 1) {                                                                                                       //win check for the three columns using the loop
        if ((sq[i] == sq[i + 3]) && (sq[i + 3] == sq[i + 6])) {
            cout << "\n\n\t" << pyn << " Was the winner using squares: " << i << ", " << i + 3 << ", and " << i + 6 << endl;
            account << "\n\n\t" << date("") << pyn << " Was the winner using squares: " << i << ", " << i + 3 << ", and " << i + 6;     //write win to tictactoe file
            account.close();                                                                                                                //close the file
            end();
        }
    }
    if ((sq[1] == sq[5]) && (sq[5] == sq[9])) {                                                                                             //win check for diagnal left to right
        cout << "\n\n\t" << pyn << " Was the winner using squares: " << 1 << ", " << 5 << ", and " << 9 << endl;
        account << "\n\n\t" << date("") << pyn << " Was the winner using squares: " << 1 << ", " << 5 << ", and " << 9;                 //write win to tictactoe file
        account.close();                                                                                                                //close the file
        end();
    }
    if ((sq[3] == sq[5]) && (sq[5] == sq[7])) {                                                                                             //win check for diagnal right to left
        cout << "\n\n\t" << pyn << " Was the winner using squares: " << 3 << ", " << 5 << ", and " << 7 << endl;
        account << "\n\n\t" << date("") << pyn << " Was the winner using squares: " << 3 << ", " << 5 << ", and " << 7;                 //write win to tictactoe file
        account.close();                                                                                                                //close the file
        end();
    }
    else if (i >= 9) {                                                                                                 //if there was not a win, and the game is finished, then declare a tie
        account << "\n\n\t" << date("") << "The game was a Tie!";                                                        //write tie to tictactoe file along with the date
        cout << "\n\n\tThe game was a Tie!\n";                                                                   // output that the game is a tie
        account.close();                                                                                         //close the file
        end();                                                                                                   //call the end function
    }
}
void history()
{
    cout << "\n\n\tFetching history ";
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
    fstream account;                                                                                                                //create an object
    account.open(fname);                                                                                                  //open filename file using append permission
    if (!account) {                                                                                                                 //check if there was an error opeining 
        cerr << "\nError when opening file";
        exit(EXIT_FAILURE);
    }
    string data{};                                                                                                                  //define a string data
    while (getline(account, data))                                                                                                  //loop if there is a getline, store the line to string data
    {
        cout << data << '\n';                                                                                                       //output the line from data and go to a new line
    }
    account.close();                                                                                                                //close the file
    end();                                                                                                                          //call end function
}
void end()
{
    string end;                                                                                                                        //define an integral end                                                                                                               //store the input
        do {
            Color(11);
            cout << "\n\n\tWould you like to \"play again\" , veiw your game \"history\" , or \"quit\" ? ";              //prompt user to play again, veiw history, or quit
            cin >> end;
            if (Lower(end) == "play again" || Lower(end) == "history" || Lower(end) == "quit") break;
            else {
                Color(14);
                cout << string(35, '\n');
                cout << "\n\tYou must choose \"play again\", \"history\", or \"quit\" try again";
            }
        } while (true);
    if (end == "play again") {                                                                                                             //if the input is 1
            char v[] = { '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };                                                       //copy of default board array
            memcpy(sq, v, 10);                                                                                                      //reset the global array by copying the backup into the global
            main();                                                                                                                 //call main function
    }
    if (end == "history") {                                                                                                        //otherwise if the input is 2
            history();                                                                                                    //call the history function
    }
    else {
        exit(0);                                                                                                     //if no function has been called exit the program
    }
}
bool evaluate() {                                                                             //starts the evaluate function, nearely identical logic to win function but without any outputs, only return of true or false
    for (int i = 1; i <= 7; i += 3) {                                                         //win check for the three rows using a loop
        if ((sq[i] == sq[i + 1]) && (sq[i + 1] == sq[i + 2])) {
            return true;
        }
    }
    for (int i = 1; i <= 3; i += 1) {                                                        //win check for the three columns using the loop
        if ((sq[i] == sq[i + 3]) && (sq[i + 3] == sq[i + 6])) {
            return true;
        }
    }
    if ((sq[1] == sq[5]) && (sq[5] == sq[9])) {                                              //win check for diagnal left to right
        return true;
    }
    if ((sq[3] == sq[5]) && (sq[5] == sq[7])) {                                              //win check for diagnal right to left
        return true;
    }
    else
        return false;
}
