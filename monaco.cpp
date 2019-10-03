/* monaco.cpp                                                                                   *
 * All functions needed for the user stories completed by Matthew Monaco for the gedcom project *
 * I pledge my honor that I have abided by the Stevens Honor System                             */


#include <unordered_map>

#include "globals.h"
#include "monaco.h"

using namespace std;

bool uniqueID(string key, unordered_map<string, individual> indis){
    if (indis.find(key) != indis.end()){
        errorStatements.push_back("ERROR: INDIVIDUAL: US22: " + to_string(lineNumber) + ": " + 
                key.c_str() + ": ID already exists. May effect later results"); 
        return false;
    }
    return true;
}
bool uniqueFamID(string key, unordered_map<string, family> indis){
    if (indis.find(key) != indis.end()){
        errorStatements.push_back("ERROR: FAMILY:     US22: " + to_string(lineNumber) + ": " + 
                key.c_str() + ": ID already exists. May effect later results"); 
        return false;
    }
return true;
}
