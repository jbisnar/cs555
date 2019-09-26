/* unitTest.cpp                                              *
 * Main file that runs the unit tests for the gedcom project */

#include <iostream>
#include <list>

#include "globals.h"
#include "monaco.h"
#include "parser.h"

int failed = 0;
int lineNumber;
list <string> errorStatements;
/* US22: Unique ID's */
void US2201(){
    unordered_map<string, individual> indiList;
    indiList["US2201"] = {"", '\0', "N/A", true, "N/A", {}, "N/A"};
    string key = "US2201";

    if(uniqueID(key, indiList) == true){
        failed++;
        printf("FAIL: US2201\n");
    }

}

int main(int argc, char** argv) {
    US2201();
    printf("\n%i Tests Failed\n", failed);
}
