/* dytioco.cpp
** All functions needed for the user stories completed by Ethan DyTioco for the gedcom project
** I pledge my honor that I have abided by the Stevens Honor System
*/

#include <unordered_map>

#include "globals.h"
#include "dytioco.h"

using namespace std;

bool marriageAfter14(individual person, int birthline, int deathline){
    if (indis.find(key) != indis.end()){
        errorStatements.push_back("ERROR: INDIVIDUAL: US07: " + to_string(lineNumber) + ": " + key.c_str() + 
                ": The person is married before 14 years of age, which is illegal in the US."); 
        return false;
    }
    return true;
}

bool notOlderThan150(individual person, int birthline, int deathline){
    if (indis.find(key) != indis.end()){
        errorStatements.push_back("ERROR: INDIVIDUAL: US10: " + to_string(lineNumber) + ": " + key.c_str() + 
                ": The person is listed as being older than 150 years old, which today is highly improbable."); 
        return false;
    }
    return true;
}