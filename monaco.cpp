/* monaco.cpp                                                                                   *
 * All functions needed for the user stories completed by Matthew Monaco for the gedcom project *
 * I pledge my honor that I have abided by the Stevens Honor System                             */


#include <string.h>
#include <unordered_map>

#include "globals.h"
#include "monaco.h"

using namespace std;

bool uniqueID(string key, unordered_map<string, individual> indis) {
    
    if (indis.find(key) != indis.end()){
        errorStatements.push_back("ERROR: INDIVIDUAL: US22: " + to_string(lineNumber) + ": " + 
                key.c_str() + ": ID already exists. May effect later results"); 
        return false;
    }
    
    return true;
}

bool uniqueFamID(string key, unordered_map<string, family> indis) {
    
    if (indis.find(key) != indis.end()){
        errorStatements.push_back("ERROR: FAMILY:     US22: " + to_string(lineNumber) + ": " + 
                key.c_str() + ": ID already exists. May effect later results"); 
        return false;
    }
    
    return true;
}

list<string> getLivingMarried(unordered_map<string, family> fams, 
        unordered_map<string, individual> indis) {
    
    unordered_map<string, family>:: iterator itr;
    list<string> livingMarried;

    for(itr = fams.begin(); itr != fams.end(); itr++){
        if(strcmp(itr->second.divorced.c_str(), "N/A") == 0){
            if(indis.at(itr->second.husbandID).alive && indis.at(itr->second.wifeID).alive){
                livingMarried.push_back(itr->second.husbandID); 
                livingMarried.push_back(itr->second.wifeID);
            }
        }
    }

    return livingMarried;
}

list<string> getDeceased(unordered_map<string, individual> indis) {

    unordered_map<string, individual>:: iterator itr;
    list<string> deceased;

    for(itr = indis.begin(); itr != indis.end(); itr++){
        if(strcmp(itr->second.death.c_str(), "N/A") != 0){
            deceased.push_back(itr->first);
        }
    }

    return deceased;
}

void correctGender(unordered_map<string, individual> indis, unordered_map<string, family> fams) {

    unordered_map<string, family>:: iterator itr;
    
    for(itr = fams.begin(); itr != fams.end(); itr++){
        if(indis.at(itr->second.husbandID).gender == 'F'){
            errorStatements.push_back("ERROR: FAMILY:     US21: " + 
                    to_string(itr->second.lineNumbers[2]) + ": " + itr->first.c_str() + 
                    ": Husband is a female");
        }
        if(indis.at(itr->second.wifeID).gender == 'M'){
            errorStatements.push_back("ERROR: FAMILY:     US21: " + 
                    to_string(itr->second.lineNumbers[3]) + ": " + itr->first.c_str() + 
                    ": Wife is a male");
        }
    }

    return;
}

string getLastName(string name){
    return name.substr(name.find(' '));
}

bool maleLastNames(unordered_map<string, individual> indis, unordered_map<string, family> fams) {
    bool noError = true; 
    unordered_map<string, family>:: iterator itr;
    
    for(itr = fams.begin(); itr != fams.end(); itr++){
        string curLastName = getLastName(indis.at(itr->second.husbandID).name);
        list<string>::iterator it;
        for(it = (itr->second.children).begin(); it != (itr->second.children).end(); ++it){
            if(indis.at(*it).gender = 'M' && 
                    (strcmp(getLastName(indis.at(*it).name).c_str(), curLastName.c_str()) != 0)){
                errorStatements.push_back("ERROR: FAMILY:     US16: " +
                    to_string(indis.at(*it).lineNumbers[0]) + ": " + 
                    "Child's last name does not match male parent");
                noError = false;
            }
        }
    }
    return noError;
}
