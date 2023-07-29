//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

ProfBST::ProfBST()
{
    root = NULL;
}

void destroyProf(Professor* prof){
    if(prof!= NULL){
        destroyProf(prof->left);
        destroyProf(prof->right);

        delete prof;
        prof = NULL;
    }
}
ProfBST::~ProfBST()
{
    destroyProf(root);
}



    // if(currNode == NULL){
    //     return createNode(data);
    // }
    // else if(currNode->key < data){
    //     currNode->right = addNodeHelper(currNode->right,data);
    // }
    // else if(currNode->key > data){
    //     currNode->left = addNodeHelper(currNode->left,data);
    // }
    // return currNode;
    
Professor* addProfessorHelper(Professor* prof, string profId, string profName){

    Professor* p = new Professor;
    p->profId = profId;
    p->profName = profName;
    if(prof == NULL){
        return p;
    }
    else if(prof->profId < profId){
        prof->right = addProfessorHelper(prof->right, profId, profName);
    }
    else if(prof->profId > profId){
        prof->left = addProfessorHelper(prof->left, profId, profName);
    }
    return prof;

}

void ProfBST::addProfessor(string profId, string profName)
{
    
    root = addProfessorHelper(root, profId, profName);
}

Professor* searchProfHelper(Professor * currProf, string profID){
    if(currProf == NULL){
        return NULL;
    }
    if(currProf->profId == profID){
        return currProf;
    }
    if(currProf->profId > profID)
        return searchProfHelper(currProf->left, profID);
    
    return searchProfHelper(currProf->right, profID);
}


Professor* ProfBST::searchProfessor(string profId)
{
    Professor* prof = searchProfHelper(root, profId);
    return prof;
}

void ProfBST::publicSearchProfessor(string profId)
{
    Professor* prof = searchProfessor(profId);

    if(prof == NULL){
        cout << "Professor not found." << endl;
        return;
    }
    else{
        displayProfessorInfo(prof);
    }


}

void ProfBST::displayProfessorInfo(Professor* p)
{

        cout << "Name: " << p->profName << endl;
        for(int i = 0; i < p->coursesTaught.size(); i++){
            cout << "-" << p->coursesTaught.at(i);
        } 
}
