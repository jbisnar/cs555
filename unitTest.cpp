/* unitTest.cpp                                              *
 * Main file that runs the unit tests for the gedcom project */

#include <iostream>
#include <list>
#include <string.h>
#include <string>

#include "globals.h"
#include "monaco.h"
#include "bisnar.h"
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



void US03_01() {
	printf("Starting Test US03-01: ");
	individual born;
	born.birthday = "2012-04-29";
	born.death = "2049-07-22";
	if (BirthB4Death(born, 0, 0)) {
		printf("PASSED\n");
	} else {
		failed++;
        printf("FAILED\n");
	}
}

void US03_02() {
	printf("Starting Test US03-02: ");
	individual unborn;
	unborn.birthday = "2012-04-29";
	unborn.death = "2010-07-22";
	if (BirthB4Death(unborn, 0, 0)) {
		failed++;
        printf("FAILED\n");
	} else {
		printf("PASSED\n");
	}
}

void US03_03() {
	printf("Starting Test US03-03: ");
	individual alive;
	alive.birthday = "2012-04-29";
	//printf("birthday string: %s\n", alive.birthday.c_str());
	//printf("death string: %s\n", alive.death.c_str());
	if (BirthB4Death(alive, 0, 0)) {
		printf("PASSED\n");
	} else {
		failed++;
        printf("FAILED\n");
	}
}

void US03_04() {
	printf("Starting Test US03-04: ");
	individual stillborn;
	stillborn.birthday = "2012-04-29";
	stillborn.death = "2012-04-29";
	if (BirthB4Death(stillborn, 0, 0)) {
		printf("PASSED\n");
	} else {
		failed++;
        printf("FAILED\n");
	}
}

void US02_01() {
	printf("Starting Test US02-01: ");
	individual fetus;
	fetus.birthday = "2000-06-09";
	individual pedo;
	indiMap.insert({"TEST02-c", fetus});
	indiMap.insert({"TEST02-a", pedo});
	family illegal;
	illegal.married = "1999-09-09";
	illegal.husbandID = "TEST02-a";
	illegal.wifeID = "TEST02-c";
	if (BirthB4Marriage(illegal, 0)) {
		failed++;
        printf("FAILED\n");
    } else {
    	printf("PASSED\n");
	}
}

void US02_02() {
	printf("Starting Test US02-02: ");
	individual born;
	born.birthday = "2000-06-09";
	individual pedo;
	indiMap.insert({"TEST02-c", born});
	indiMap.insert({"TEST02-a", pedo});
	family illegal;
	illegal.married = "20099-09-09";
	illegal.husbandID = "TEST02-a";
	illegal.wifeID = "TEST02-c";
	if (BirthB4Marriage(illegal, 0)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
}

/* US07: Less than 150 years old */
void US0701()){
	unordered_map<string, individual> indiList;
    indiList["US0701"] = {"", '\0', "N/A", true, "N/A", {}, "N/A"};
    string key = "US0701";

    if(notOlderThan150(/*invid, birthline*/) != true){ // in dytioco.cpp, return false is when there's an error.
        failed++;
        printf("FAIL: US0701\n");
    }
}

/* US10: Marriage after 14 years old */
void US1001()){
	unordered_map<string, individual> indiList;
    indiList["US1001"] = {"", '\0', "N/A", true, "N/A", {}, "N/A"};
    string key = "US1001";

    if(marriageAfter14(/*indiv, birthline, marriageline*/) != true){
        failed++;
        printf("FAIL: US1001\n");
    }
}

int main(int argc, char** argv) {
    US2201();
    US2202();
    US4001();
    US03_01();
    US03_02();
    US03_03();
    US03_04();
    US02_01();
    US02_02();
	US0701();
	US1001();
    printf("%i Tests Failed\n", failed);
}
