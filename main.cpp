//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void displayMenu(){

    cout << "=======Main Menu=======" << endl;
    cout << "1. Populate hash tables" << endl;
    cout << "2. Search for a course" << endl;
    cout << "3. Search for a professor" << endl;
    cout << "4. Display all courses" << endl;
    cout << "5. Exit" << endl;


}

int main (int argc, char* argv[])
{
    if(argc != 3){// making sure there are the correct number of arguments

        cout << "Invalid number of arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        cout << "Run the program again but with the correct format" << endl;
        return -1;
    } 

    HashOpenAddressing openAddress = HashOpenAddressing(stoi(argv[2]));
    HashChaining chain = HashChaining(stoi(argv[2]));

    string fileName = argv[1];
    int input = 1;
    int year;
    int courseNum;
    string profId;
    string OorC;

    while(input <= 5 && input > 0){

        displayMenu();


        cout << "Enter an option: ";
        cin >> input;
        cout << endl;

        switch(input){
            case 1:

                openAddress.bulkInsert(fileName);
                chain.bulkInsert(fileName);

            break;

            case 2:

                
                cout << "Enter the course year (e.g. 2021):" << endl;
                cin >> year;
                cout << "Enter a course number (e.g. 2270):" << endl;
                cin >> courseNum;
                cout << "Enter a professor's ID (e.g. llytellf" << endl;
                cin >> profId;

                openAddress.search(year, courseNum, profId);
                chain.search(year, courseNum, profId);

            break;


            case 3:
                cout << "Enter a professor's ID (e.g. nscollan0): " << endl;
                cin >> profId;

                openAddress.profDb.displayProfessorInfo(openAddress.profDb.searchProfessor(profId));
                chain.profDb.displayProfessorInfo(chain.profDb.searchProfessor(profId));

            break;

            case 4:


                cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)?" << endl;
                cin >> OorC;
                if(OorC.substr(0,1) == "O"){
                    openAddress.displayAllCourses();
                }
                else if(OorC.substr(0,1) == "C"){
                    chain.displayAllCourses();
                }
                else{
                    cout << "Input must be O or C. Please try again" << endl;
                }


            break;

            case 5:

                openAddress.~HashOpenAddressing();
                chain.~HashChaining();
                return 0;

            break;
            
        }



    }
    return 0;
}