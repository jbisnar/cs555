/* unitTest.cpp                                              *
 * Main file that runs the unit tests for the gedcom project */

#include <iostream>
#include <list>
#include <string.h>

#include "globals.h"
#include "monaco.h"
#include "parser.h"

int failed = 0;
int lineNumber = 3;
list <string> errorStatements;

/* US22: Unique ID's */
void US2201(){
    printf("Starting Test US22-01: ");
    unordered_map<string, individual> indiList;
    indiList["US2201"] = {"", '\0', "N/A", true, "N/A", {}, "N/A"};
    string key = "US2201";

    if(uniqueID(key, indiList) == true){
        failed++;
        printf("FAILED\n");
    }else{
        printf("PASSED\n");
    }
    return;
}

void US2202(){
    printf("Starting Test US22-02: ");
    unordered_map<string, family> indiList;
    indiList["US2201"] = {"", "N/A", "N/A", "N/A", {}};
    string key = "US2201";

    if(uniqueFamID(key, indiList) == true){
        failed++;
        printf("FAILED\n");
    }else{
        printf("PASSED\n");
    }
    return;
}

void US4001(){
    printf("Starting Test US40-01: ");

    errorStatements.clear();
    parse("0 US-40-01 INDI");
    parse("1 NAME Matthew Monaco");
    parse("0 US-40-01 INDI");
    lineNumber = 3;
    if(strcmp(errorStatements.front().c_str(), 
            "ERROR: INDIVIDUAL: US22: 3: US-40-01: ID already exists. May effect later results") != 0){
printf(errorStatements.front().c_str());
        failed++;
        printf("FAILED\n");
    }else{
        printf("PASSED\n");
    }
    lineNumber = 0;
    indiMap.clear();
    return;
}

int main(int argc, char** argv) {
    US2201();
    US2202();
    US4001();
    printf("%i Tests Failed\n", failed);
}
