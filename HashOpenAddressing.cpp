//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

/**
 * 
 * split - split function i wrote in csci 1300 that splits a string to_be_split based on a seperator.
 * Puts the different sections of the string into an array: split_apart_storage
 * 
 * @param - to_be_split, seperator, split_apart_storage, size_of_array
 * @return int
 */

int splitOpenAddressing(string to_be_split, char separator, string split_apart_storage[], int size_of_array){
    int counter1 = 0;
    int counter2 = 0;
    int length_of_initial_string = to_be_split.length();
    int position_finder = 0;
    
    if(separator < 32 || separator > 255){
        return 1;
    }
    else if(to_be_split == ""){
        return 0;
    }
    else{
        for(int i = 0; i <= length_of_initial_string; i++){
            if(to_be_split[i] == separator || i == length_of_initial_string){
                counter1++;
                split_apart_storage[counter2] = to_be_split.substr(position_finder, i - position_finder);
                position_finder = i+1;
                counter2++;

                if(size_of_array < counter1){
                    return -1;
                }
            } 
        }

        return counter1;
    }   
}

/**
 * 
 * HashOpenAddressing - constructor for HashOpenAddressing
 * 
 * @param - size
 * @return 
 */
HashOpenAddressing::HashOpenAddressing(int size)
{
    hashTableSize = size;
    hashTable = new Course*[hashTableSize];
    for(int i = 0; i < size; i++){
        hashTable[i] = nullptr;
    }

}


/**
 * 
 * HashOpenAddressing - deconstructor for HashOpenAddressing
 * 
 * @param 
 * @return 
 */
HashOpenAddressing::~HashOpenAddressing()
{
    for(int i = 0; i < hashTableSize; i++){
        delete hashTable[i];
        hashTable[i] = nullptr;
    }
    delete hashTable;
}


/**
 * 
 * hash - calculates the hash value of a courseNumber
 * 
 * @param - courseNumber
 * @return - int
 */
int HashOpenAddressing::hash(int courseNumber)
{
    return (courseNumber % hashTableSize);
}


/**
 * 
 * bulkInsert - inserts courses that are read from a file
 * 
 * @param - filename
 * @return - void
 */
void HashOpenAddressing::bulkInsert(string filename)
{
    string line = "";

    ifstream file;
    file.open(filename);

    string splitStorage[7];
    int collisions = 0;
    int hashVal;
    int numElements = 0;

    
    if(file.is_open()){ //make sure the file opens correctly
        while(getline(file, line) && numElements < hashTableSize){ //loops while there are still lines to read in the file

            splitOpenAddressing(line, ',', splitStorage, 7);


            //Course(int newYear, string newDepartment, int newCourseNum, string newCourseName, Professor *newProf = nullptr)

            //year,department,couse_num,course_name,prof_id,prof_fname,prof_lname
            string profFullName;
            Course *newCourse = new Course;
            hashVal = hash(stoi(splitStorage[2]));
            newCourse->courseName = splitStorage[3];
            newCourse->courseNum = stoi(splitStorage[2]);
            newCourse->year = stoi(splitStorage[0]);
            newCourse->department = splitStorage[1];
            newCourse->prof->profId = splitStorage[4];
            profFullName = splitStorage[5] + " " + splitStorage[6];
            newCourse->prof->profName = profFullName;


            if(hashTable[hashVal] == NULL){
                hashTable[hashVal] = newCourse;
            }
            else{ //could throw a while statement in here (while table[index]->next != nullptr))
                int i = 0;
                while(hashTable[hashVal] == NULL){
                    hashVal = hash((hashVal + (i * i)));
                }
                collisions++;
            }
            numElements++;

        }



           
        file.close();
    }
    else{
        cout << "Failed to open the file." << endl;
    }

    cout << "[OPEN ADDRESSING] Hash table populated" << endl;
    cout << "-------------------------------" << endl;
    cout << "Collisions using open addressing: " << collisions << endl;
    cout << "Search operations using open addressing: " << endl;   //does this belong here?????
    
}


/**
 * 
 * search - searches for a course in the hashTable
 * 
 * @param - courseYear, courseNumber, profId
 * @return - void
 */
void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    int index = hash(courseNumber);
    int numSearches = 0;
    int i = 1;

    while(courseYear != hashTable[index]->year && courseNumber != hashTable[index]->courseNum && profId != hashTable[index]->prof->profId){
        index = hash((index + (i * i)));
        i++;
    }

    cout << "[OPEN ADDRESSING] Search for a course" << endl;
    cout << "---------------------" << endl;
    cout << "Search operations using open addressing: " << i;
    displayCourseInfo(hashTable[index]);
}


/**
 * 
 * displayAllCourses - displays all of the courses in the hashTable
 * 
 * @param 
 * @return - void
 */
void HashOpenAddressing::displayAllCourses()
{
    cout << "[OPEN ADDRESSING] displayAllCourses()" << endl;
    Course* temp;


    for(int i = 0; i < hashTableSize; i++){
        if(hashTable[i] != NULL){
            displayCourseInfo(hashTable[i]);
        }
    }
}


/**
 * 
 * displayCourseInfo - prints all of the info about a course c
 * 
 * @param - c
 * @return - void
 */
void HashOpenAddressing::displayCourseInfo(Course* c)
{
    cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
}