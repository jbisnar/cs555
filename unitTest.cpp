/* unitTest.cpp                                              *
 * Main file that runs the unit tests for the gedcom project */

#include <iostream>
#include <list>
#include <string.h>
#include <string>

#include "globals.h"
#include "monaco.h"
#include "bisnar.h"
#include "dytioco.h"
#include "parser.h"

int failed = 0;
int lineNumber = 3;
list <string> errorStatements;

/* US22: Unique ID's */
void US2201(){
    printf("Starting Test US22-01: ");
    unordered_map<string, individual> indiList;
    indiList["US2201"] = {"", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    string key = "US2201";

    if(uniqueID(key, indiList) == true){
        failed++;
        printf("FAILED\n");
    }else{
        printf("PASSED\n");
    }
    return;
}

void US2202() {
    
    printf("Starting Test US22-02: ");
    unordered_map<string, family> fList;
    fList["US2201"] = {"", "N/A", "N/A", "N/A", {}, {0,0,0,0}};
    string key = "US2201";

    if(uniqueFamID(key, fList) == true){
        failed++;
        printf("FAILED\n");
    }else{
        printf("PASSED\n");
    }
    
    return;
}

/* US40: Print Line Numbers */
void US4001() {
    
    printf("Starting Test US40-01: ");
    errorStatements.clear();
    parse("0 US-40-01 INDI");
    parse("1 NAME Matthew Monaco");
    parse("0 US-40-01 INDI");
    lineNumber = 3;
    if(strcmp(errorStatements.front().c_str(), 
            "ERROR: INDIVIDUAL: US22: 3: US-40-01: ID already exists. May effect later results") 
            != 0){
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

/* Print all Living Married Individuals */
void US3001() {

    printf("Starting Test US30-01: ");
    unordered_map<string, family> famList;
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"The Wife", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    famList["Family"] = {"", "N/A", "Husband", "Wife", {}, {0,0,0,0}};
    list<string> ids = getLivingMarried(famList, indiList);
    
    if(strcmp(ids.front().c_str(), "Husband") != 0){
        failed++;
        printf("FAILED\n");
        return;
    } else if (strcmp(ids.back().c_str(), "Wife") != 0){
        failed++;
        printf("FAILED\n");
        return;
    } else if (ids.size() != 2){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;

}

void US3002() {

    printf("Starting Test US30-02: ");
    unordered_map<string, family> famList;
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"The Wife", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    famList["Family"] = {"", "2000-01-01", "Husband", "Wife", {}, {0,0,0,0}};
    list<string> ids = getLivingMarried(famList, indiList);

    if (!ids.empty()){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;

}

/* List Deceased Individuals */
void US2901() {
    
    printf("Starting Test US29-01: ");
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"The Wife", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    list<string> ids = getDeceased(indiList);

    if (!ids.empty()){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;

}

void US2902() {

    printf("Starting Test US29-02: ");
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", '\0', "N/A", false, "2000-02-01", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"The Wife", '\0', "N/A", false, "2000-02-01", {}, "N/A", {0,0,0,0,0,0}};
    list<string> ids = getDeceased(indiList);

    if(strcmp(ids.front().c_str(), "Wife") != 0){
        failed++;
        printf("FAILED\n");
        return;
    } else if (strcmp(ids.back().c_str(), "Husband") != 0){
        failed++;
        printf("FAILED\n");
        return;
    } else if (ids.size() != 2){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;

}

/* US16: Male Last Names Match Husband */
void US1601() {
    
    printf("Starting Test US16-01: ");
    errorStatements.clear();
    
    unordered_map<string, family> famList;
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", 'M', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Son"] = {"The Son", 'M', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    famList["Family"] = {"", "2000-01-01", "Husband", "N/A", {"Son"}, {0,0,0,0}};
    
    if(maleLastNames(indiList, famList)){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;
}


/* Every spouse is the correct gender */
void US2101() {
    printf("Starting Test US21-01: ");
    errorStatements.clear();

    unordered_map<string, family> famList;
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", 'F', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"The Wife", 'F', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    famList["Family"] = {"", "2000-01-01", "Husband", "Wife", {}, {0,0,0,0}};
    correctGender(indiList, famList);

    if(strcmp(errorStatements.front().c_str(), 
            "ERROR: FAMILY:     US21: 0: Family: Husband is a female") != 0){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");
    
    return;

}

void US2102() {

    printf("Starting Test US21-02: ");
    errorStatements.clear();

    unordered_map<string, family> famList;
    unordered_map<string, individual> indiList;
    indiList["Husband"] = {"The Husband", 'M', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"The Wife", 'M', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
    famList["Family"] = {"", "2000-01-01", "Husband", "Wife", {}, {0,0,0,0}};
    correctGender(indiList, famList);

    if(strcmp(errorStatements.front().c_str(), 
            "ERROR: FAMILY:     US21: 0: Family: Wife is a male") != 0){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;

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
	illegal.married = "2009-09-09";
	illegal.husbandID = "TEST02-a";
	illegal.wifeID = "TEST02-c";
	if (BirthB4Marriage(illegal, 0)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
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

void US04_01() {
	printf("Starting Test US04-01: ");
	printf("UNIMPLEMENTED ");
	failed++;
    printf("FAILED\n");
}

void US05_01() {
	printf("Starting Test US05-01: ");
	individual deadf;
	deadf.death = "2000-06-09";
	individual necrom;
	indiMap.insert({"TEST05-dead", deadf});
	indiMap.insert({"TEST05-alive", necrom});
	family illegal;
	illegal.married = "2009-09-09";
	illegal.husbandID = "TEST05-alive";
	illegal.wifeID = "TEST05-dead";
	if (!MarriageB4Death(illegal, 0)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
}

void US05_02() {
	printf("Starting Test US05-02: ");
	individual deadm;
	deadm.death = "2000-06-09";
	individual necrof;
	indiMap.insert({"TEST05-dead2", deadm});
	indiMap.insert({"TEST05-alive2", necrof});
	family illegal;
	illegal.married = "2009-09-09";
	illegal.husbandID = "TEST05-dead2";
	illegal.wifeID = "TEST05-alive2";
	if (!MarriageB4Death(illegal, 0)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
}

void US06_01() {
	printf("Starting Test US06-01: ");
	individual deadf;
	deadf.death = "2006-06-09";
	individual widower;
	indiMap.insert({"TEST06-dead", deadf});
	indiMap.insert({"TEST06-widower", widower});
	family illegal;
	illegal.married = "2000-09-09";
	illegal.divorced = "2010-07-23";
	illegal.husbandID = "TEST06-widower";
	illegal.wifeID = "TEST06-dead";
	if (!DivorceB4Death(illegal, 0)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
}

void US06_02() {
	printf("Starting Test US06-02: ");
	individual deadm;
	deadm.death = "2006-06-09";
	individual widow;
	indiMap.insert({"TEST06-dead", deadm});
	indiMap.insert({"TEST06-widow", widow});
	family illegal;
	illegal.married = "2000-09-09";
	illegal.divorced = "2010-07-23";
	illegal.husbandID = "TEST06-dead";
	illegal.wifeID = "TEST06-widow";
	if (!DivorceB4Death(illegal, 0)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
}

void US09_01() {
	printf("Starting Test US09-01: ");
	printf("UNIMPLEMENTED ");
	failed++;
    printf("FAILED\n");
}

/* US07: Less than 150 years old */
void US0701(){
	printf("Starting Test US07-01: ");
	individual tooOld;
	tooOld.birthday = "1950-10-05";
	
	int testLine = 0;
	
    if(notOlderThan150(tooOld, testLine) != true){ // in dytioco.cpp, return false is when there's an error.
        failed++;
        printf("FAILED\n");
    }
	else
		printf("PASSED\n");
}

/* US10: Marriage after 14 years old */
void US1001(){
	printf("Starting Test US10-01: ");
	individual tooYoung;
	tooYoung.birthday = "2000-02-03";
	individual everyoneIsAPedo;
	everyoneIsAPedo.birthday = "1970-01-01";
	
	family alsoQuiteIllegal;
	alsoQuiteIllegal.married = "2014-02-03";
	alsoQuiteIllegal.wifeID = "TEST02-a";
	alsoQuiteIllegal.husbandID = "TEST02-b";
	
	int testLine = 0;

    if(marriageAfter14(tooYoung, alsoQuiteIllegal, testLine) != true){
        failed++;
        printf("FAILED\n");
    }
	else
		printf("PASSED\n");
}

/* US42: checks to see if the date is valid (eg, no Feb 29's if it's not a leap year)*/
void US4201(){
	printf("Starting Test US42-01: ");
	string date = "2020-02-29";
	int testline = 5;
	
	if (legalDate(date, testline) == true)
		printf("PASSED\n");
	else {
		failed++;
		printf("FAILED\n");
	}
}

/* US 12: checks to see if mom is less than 60 yrs older and dad is less than 80 years older their kids*/
void US1201(){
	printf("Starting Test US12-01: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	
    indiList["Husband"] = {"Soap MacTavish", 'M', "1920-01-02", true, "N/A", {"Family"}, "", {0,0,0,0,0,0}};
    indiList["Wife"] = {"Missus MacTavish", 'F', "1940-01-02", true, "N/A", {"Family"}, "", {0,0,0,0,0,0}};
	indiList["Child1"] = {"John MacTavish", 'M', "2000-01-01", true, "N/A", {}, "Family", {0,0,0,0,0,0}};
	indiList["Child2"] = {"Anna MacTavish", 'F', "2000-01-01", true, "N/A", {}, "Family", {0,0,0,0,0,0}};
    famList["Family"] = {"", "N/A", "Husband", "Wife", {"Child1", "Child2"}, {0,0,0,0}};
	
	if(parentsNotTooOld(indiList, famList)){
		printf("PASSED\n");
	}
	else{
		failed++;
		printf("FAILED\n");
	}
}

int main(int argc, char** argv) {
    US02_01();
    US02_02();
    US03_01();
    US03_02();
    US03_03();
    US03_04();
    US04_01();
    US05_01();
    US05_02();
    US06_01();
    US06_02();
    US0701();
    US09_01();
    US1001();
    US1201();
    US1601();
    US2101();
    US2102();
    US2201();
    US2202();
    US2901();
    US2902();
    US3001();
    US3002();
    US4001();
    US4201();
    printf("%i Tests Failed\n", failed);
}
