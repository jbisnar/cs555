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

    if (ids.empty()){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");

    return;

}

void US2701(){
    printf("Starting Test US27-02: ");
    if(strcmp(getAge("1998-10-13", "2019-11-5").c_str(), "21") != 0){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");
}

void US1501(){
    printf("Starting Test US15-01: ");
    unordered_map<string, individual> indiList;
    indiList["15"] = {"The Last", '\0', "N/A", false, "2000-01-01", {}, "N/A", {0,0,0,0,0,0}};
    unordered_map<string, family> famList;
    list <string> kids;
    for(int i = 0; i<15; i++){
        kids.push_back("15");
    }
    famList["Family"] = {"", "2000-01-01", "Husband", "Wife", kids, {0,0,0,0}};
    
    if(lessThan15Kids(famList, indiList)){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");
}

void US2702(){
    printf("Starting Test US27-02: ");
    if(strcmp(getAge("N/A", "2019-11-5").c_str(), "N/A") != 0){
        failed++;
        printf("FAILED\n");
        return;
    }
    printf("PASSED\n");
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

void US01_01() {
	printf("Starting Test US01-01: ");
	string past = "1946-12-07";
	string future = "2019-11-23";
	string override = "2020-01-01";
	string blank = "";
	if (DatesB4Today(past,blank,0,0) && !DatesB4Today(future,blank,0,0) && DatesB4Today(future,override,0,0)) {
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
	if (BirthB4Marriage(illegal)) {
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
	if (BirthB4Marriage(illegal)) {
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
	if (BirthB4Death(born)) {
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
	if (BirthB4Death(unborn)) {
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
	if (BirthB4Death(alive)) {
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
	if (BirthB4Death(stillborn)) {
		printf("PASSED\n");
	} else {
		failed++;
        printf("FAILED\n");
	}
}

void US04_01() {
	printf("Starting Test US04-01: ");
	individual predivm;
	individual predivf;
	indiMap.insert({"TEST04-husband", predivm});
	indiMap.insert({"TEST04-wife", predivf});
	family breakup;
	breakup.husbandID = "TEST04-husband";
	breakup.wifeID = "TEST04-wife";
	breakup.married = "2009-09-09";
	breakup.divorced = "2009-09-08";
	if (!MarriageB4Divorce(breakup)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
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
	if (!MarriageB4Death(illegal)) {
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
	if (!MarriageB4Death(illegal)) {
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
	if (!DivorceB4Death(illegal)) {
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
	if (!DivorceB4Death(illegal)) {
		printf("PASSED\n");
    } else {
    	failed++;
        printf("FAILED\n");
	}
}

void US08_01() {
	printf("Starting Test US08-01: ");
	individual mom;
	individual dad;
	individual bastard;
	bastard.birthday = "2007-08-11";
	individual bastard2;
	bastard2.birthday = "2008-07-20";
	indiMap.insert({"TEST09-mom", mom});
	indiMap.insert({"TEST09-dad", dad});
	indiMap.insert({"TEST09-child1", bastard});
	indiMap.insert({"TEST09-child2", bastard2});
	family premarital;
	premarital.married = "2008-12-30";
	premarital.wifeID = "TEST09-mom";
	premarital.husbandID = "TEST09-dad";
	premarital.children.push_back("TEST09-child1");
	premarital.children.push_back("TEST09-child2");
	famMap.insert({"TEST09-premarital", premarital});
	if (!BirthB4ParentsMarriage()) {
		printf("PASSED\n");
		famMap.erase("TEST09-premarital");
	} else {
		failed++;
    	printf("FAILED\n");
    	famMap.erase("TEST09-premarital");
    }
}

void US08_02() {
	printf("Starting Test US08-02: ");
	individual mom;
	individual dad;
	individual postdivorce;
	postdivorce.birthday = "2007-08-11";
	indiMap.insert({"TEST09-mom", mom});
	indiMap.insert({"TEST09-dad", dad});
	indiMap.insert({"TEST09-child1", postdivorce});
	family predivorce;
	predivorce.married = "2005-09-09";
	predivorce.divorced = "2008-02-29";
	predivorce.wifeID = "TEST09-mom";
	predivorce.husbandID = "TEST09-dad";
	predivorce.children.push_back("TEST09-child1");
	famMap.insert({"TEST09-predivorce", predivorce});
	if (BirthB4ParentsMarriage()) {
		printf("PASSED\n");
		famMap.erase("TEST09-predivorce");
	} else {
		failed++;
    	printf("FAILED\n");
    	famMap.erase("TEST09-predivorce");
    }
}

void US08_03() {
	printf("Starting Test US08-03: ");
	individual mom;
	individual dad;
	individual scandal;
	scandal.birthday = "2011-08-11";
	indiMap.insert({"TEST09-mom", mom});
	indiMap.insert({"TEST09-dad", dad});
	indiMap.insert({"TEST09-child1", scandal});
	family postdivorce;
	postdivorce.married = "2005-09-09";
	postdivorce.divorced = "2008-02-29";
	postdivorce.wifeID = "TEST09-mom";
	postdivorce.husbandID = "TEST09-dad";
	postdivorce.children.push_back("TEST09-child1");
	famMap.insert({"TEST09-postdivorce", postdivorce});
	if (BirthB4ParentsMarriage()) {
		printf("PASSED\n");
		famMap.erase("TEST09-postdivorce");
	} else {
		failed++;
    	printf("FAILED\n");
    	famMap.erase("TEST09-postdivorce");
    }
}

void US09_01() {
	printf("Starting Test US09-01: ");
	individual deadmom;
	deadmom.death = "2006-06-09";
	individual deaddad;
	deaddad.death = "2006-06-09";
	individual impossiblechild;
	impossiblechild.birthday = "2007-08-11";
	individual impossiblechild2;
	impossiblechild.birthday = "2008-07-20";
	indiMap.insert({"TEST09-deadmom", deadmom});
	indiMap.insert({"TEST09-deaddad", deaddad});
	indiMap.insert({"TEST09-child1", impossiblechild});
	indiMap.insert({"TEST09-child2", impossiblechild2});
	family bothdead;
	bothdead.wifeID = "TEST09-deadmom";
	bothdead.husbandID = "TEST09-deaddad";
	bothdead.children.push_back("TEST09-child1");
	bothdead.children.push_back("TEST09-child2");
	famMap.insert({"TEST09-bothdead", bothdead});
	if (!BirthB4ParentsDeath()) {
		printf("PASSED\n");
		famMap.erase("TEST09-bothdead");
	} else {
		failed++;
    	printf("FAILED\n");
    	famMap.erase("TEST09-bothdead");
    }
}

void US09_02() {
	printf("Starting Test US09-02: ");
	individual livemom;
	individual deaddad;
	deaddad.death = "2006-06-09";
	individual possiblechild;
	possiblechild.birthday = "2007-01-11";
	indiMap.insert({"TEST0902-livemom", livemom});
	indiMap.insert({"TEST0902-deaddad", deaddad});
	indiMap.insert({"TEST0902-child1", possiblechild});
	family singlemom;
	singlemom.wifeID = "TEST0902-livemom";
	singlemom.husbandID = "TEST09-deaddad";
	singlemom.children.push_back("TEST0902-child1");
	famMap.insert({"TEST09-singlemom", singlemom});
	//Unsure if we will handle the case where the father dies during the mother's pregnancy
	if (BirthB4ParentsDeath()) {
		printf("PASSED\n");
		famMap.erase("TEST09-singlemom");
	} else {
		failed++;
    	printf("FAILED\n");
    	famMap.erase("TEST09-singlemom");
    }
}

void US09_03() {
	printf("Starting Test US09-03: ");
	individual deadmom;
	deadmom.death = "2006-06-09";
	individual livedad;
	individual impossiblechild;
	impossiblechild.birthday = "2007-01-11";
	indiMap.insert({"TEST0903-deadmom", deadmom});
	indiMap.insert({"TEST0903-livedad", livedad});
	indiMap.insert({"TEST0903-child1", impossiblechild});
	family impossdad;
	impossdad.wifeID = "TEST0903-deadmom";
	impossdad.husbandID = "TEST0903-livedad";
	impossdad.children.push_back("TEST0903-child1");
	famMap.insert({"TEST0903-impossdad",impossdad});
	if (!BirthB4ParentsDeath()) {
		printf("PASSED\n");
		famMap.erase("TEST0903-impossdad");
	} else {
		failed++;
    	printf("FAILED\n");
    	famMap.erase("TEST0903-impossdad");
    }
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

// checks if siblings are not married: one child only
// US 18
void US1801(){
	printf("Starting Test US18-01: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	
	
	indiList["Husband"] = {"Soap MacTavish", 'M', "1920-01-02", true, "N/A", {"Fam1"}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"Missus MacTavish", 'F', "1940-01-02", true, "N/A", {"Fam1"}, "N/A", {0,0,0,0,0,0}};
	indiList["Child1"] = {"John MacTavish", 'M', "2000-01-01", true, "N/A", {"Fam2"}, "Fam1", {0,0,0,0,0,0}};
	famList["Fam1"]= {"", "N/A", "Child1", "N/A", {}, {0,0,0,0}};
	
	if (siblingsNotMarried(indiList, famList))
		printf("PASSED\n");
	else
	{
		failed++;
		printf("FAILED\n");
	}
}

// checks if siblings are not married: family has more than one child
// US 18
void US1802(){
	printf("Starting Test US18-02: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	
	indiList["Husband"] = {"Soap MacTavish", 'M', "1920-01-02", true, "N/A", {"Fam1"}, "N/A", {0,0,0,0,0,0}};
    indiList["Wife"] = {"Missus MacTavish", 'F', "1940-01-02", true, "N/A", {"Fam1"}, "N/A", {0,0,0,0,0,0}};
	indiList["Child1"] = {"John MacTavish", 'M', "2000-01-01", true, "N/A", {"Fam2"}, "Fam1", {0,0,0,0,0,0}};
	indiList["Child2"] = {"Anna MacTavish", 'F', "2000-01-01", true, "N/A", {"Fam2"}, "Fam1", {0,0,0,0,0,0}};
	indiList["Sierra"] = {"Sierra Price", 'F', "2000-01-01", true, "N/A", {"Fam2"}, "Fam3", {0,0,0,0,0,0}};
	famList["Fam1"]= {"", "N/A", "Child1", "Sierra", {}, {0,0,0,0}};
	
	if (siblingsNotMarried(indiList, famList))
		printf("PASSED\n");
	else
	{
		failed++;
		printf("FAILED\n");
	}
}

// checks if cousins are not married
void US1901(){
	printf("Starting Test US19-01: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	family curFam = {"", "N/A", "N/A", "N/A", {}, {0,0,0,0}};
	
	
	indiList["1_Gramps"] = {"First Last", 'M', "N/A", true, "N/A", {"Grand1"}, "N/A", {0,0,0,0,0,0}};
	indiList["1_Gramms"] = {"First Last", 'F', "N/A", true, "N/A", {"Grand1"}, "N/A", {0,0,0,0,0,0}};
	indiList["2_Gramps"] = {"First Last", 'M', "N/A", true, "N/A", {"Grand2"}, "N/A", {0,0,0,0,0,0}};
	indiList["2_Gramms"] = {"First Last", 'F', "N/A", true, "N/A", {"Grand2"}, "N/A", {0,0,0,0,0,0}};
	indiList["3_Gramps"] = {"First Last", 'M', "N/A", true, "N/A", {"Grand3"}, "N/A", {0,0,0,0,0,0}};
	indiList["3_Gramms"] = {"First Last", 'F', "N/A", true, "N/A", {"Grand3"}, "N/A", {0,0,0,0,0,0}};
	indiList["1A_Dad"] = {"First Last", 'M', "N/A", true, "N/A", {"Paternal"}, "Grand1", {0,0,0,0,0,0}};
	indiList["1A_Mom"] = {"First Last", 'F', "N/A", true, "N/A", {"Paternal"}, "Grand2", {0,0,0,0,0,0}};
	indiList["2A_Dad"] = {"First Last", 'M', "N/A", true, "N/A", {"Maternal"}, "Grand2", {0,0,0,0,0,0}};
	indiList["2A_Mom"] = {"First Last", 'F', "N/A", true, "N/A", {"Maternal"}, "Grand3", {0,0,0,0,0,0}};
	indiList["1B_Husb"] = {"First Last", 'M', "N/A", true, "N/A", {"Current"}, "Paternal", {0,0,0,0,0,0}};
	indiList["2B_Wife"] = {"First Last", 'F', "N/A", true, "N/A", {"Current"}, "N/A", {0,0,0,0,0,0}};
	
	famList["Grand1"] = {"", "N/A", "1_Gramps", "1_Gramms", {"1A_Dad"}, {0,0,0,0}};
	famList["Grand2"] = {"", "N/A", "2_Gramps", "2_Gramms", {"1A_Mom", "2A_Dad"}, {0,0,0,0}};
	famList["Grand3"] = {"", "N/A", "3_Gramps", "3_Gramms", {"2A_Mom"}, {0,0,0,0}};
	famList["Paternal"] = {"", "N/A", "1A_Dad", "1A_Mom", {"1B_Husb"}, {0,0,0,0}};
	famList["Maternal"] = {"", "N/A", "2A_Dad", "2A_Mom", {}, {0,0,0,0}};
	famList["Current"] = {"", "N/A", "1B_Husb", "2B_Wife", {}, {0,0,0,0}};
	
	curFam.husbandID = "1B_Husb";
	curFam.wifeID = "2B_Wife";
	
	if (cousinsNotMarried(indiList, famList))
		printf("PASSED\n");
	else
	{
		failed++;
		printf("FAILED\n");
	}
}

// US 13: correct spacing between sibling birthdays
// test 1: 1 sibling
void US1301(){
	printf("Starting Test US13-01: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	
	indiList["Dad"] = {"Dad Calendar", 'M', "1980-01-01", true, "N/A", {"Current"}, "N/A", {0,0,0,0,0,0}};
	indiList["Mom"] = {"Mom Calendar", 'F', "1980-01-01", true, "N/A", {"Current"}, "N/A", {0,0,0,0,0,0}};
	indiList["c1"] = {"Daughter Calendar", 'F', "2000-01-01", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	famList["Current"] = {"", "N/A", "Dad", "Mom", {"c1"}, {0,0,0,0}};
	
	if(correctSiblingBirthdaySpacing(indiList, famList))
		printf("PASSED\n");
	else{
		failed++;
		printf("FAILED\n");
	}
}

// US 13: correct spacing between sibling birthdays
// test 2: many siblings, last has no birthday inputted (have a bool flag to catch this)
void US1302(){
	printf("Starting Test US13-02: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	
	indiList["Dad"] = {"Dad Calendar", 'M', "1980-01-01", true, "N/A", {"Current"}, "N/A", {0,0,0,0,0,0}};
	indiList["Mom"] = {"Mom Calendar", 'F', "1980-01-01", true, "N/A", {"Current"}, "N/A", {0,0,0,0,0,0}};
	indiList["c1"] = {"Dau1 Calendar", 'F', "1999-01-01", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	indiList["c2"] = {"Dau2 Calendar", 'F', "2000-03-01", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	indiList["c3"] = {"Dau3 Calendar", 'F', "2000-01-01", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	indiList["c4"] = {"Dau4 Calendar", 'F', "2004-04-03", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	indiList["c5"] = {"Son1 Calendar", 'M', "2004-05-03", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	indiList["c6"] = {"Son2 Calendar", 'M', "N/A", true, "N/A", {}, "Current", {0,0,0,0,0,0}};
	famList["Current"] = {"", "N/A", "Dad", "Mom", {"c1", "c2", "c3", "c4", "c5", "c6"}, {0,0,0,0}};
	
	if(correctSiblingBirthdaySpacing(indiList, famList))
		printf("PASSED\n");
	else{
		failed++;
		printf("FAILED\n");
	}
}

// US 17: parents don't marry their own children
void US1701(){
	printf("Starting Test US17-01: ");
    unordered_map<string, individual> indiList;
	unordered_map<string, family> famList;
	
	indiList["Dad"] = {"Sicco Mode", 'M', "N/A", true, "N/A", {"Fam-1", "Fam-2"}, "N/A", {0,0,0,0,0,0}};
	indiList["Mom-1"] = {"PoorWife Mode", 'F', "N/A", true, "N/A", {"Fam-1"}, "N/A", {0,0,0,0,0,0}};
	indiList["Son"] = {"Richard Mode", 'M', "N/A", true, "N/A", {}, "Fam-1", {0,0,0,0,0,0}};
	indiList["Daughter"] = {"Rip Mode", 'F', "N/A", true, "N/A", {"Fam-2"}, "Fam-1", {0,0,0,0,0,0}};
	indiList["Mom-2"] = {"Guava Mode", 'F', "N/A", true, "N/A", {"Fam-2"}, "Fam-obscure", {0,0,0,0,0,0}};
	
	famList["Fam-1"] = {"1990-01-01", "1992-01-01", "Dad", "Mom-1", {"Son", "Daughter"}, {0,0,0,0}};
	famList["Fam-2"] = {"2010-06-06", "N/A", "Dad", "Mom-2", {}, {99,99,99,99}};
	
	if (parentsDidntMarryChildren(indiList, famList) == true){
		printf("PASSED\n");
	}
	else{
		failed++;
		printf("FAILED\n");
	}
}


int main(int argc, char** argv) {
	US01_01();
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
    US08_01();
    US08_02();
    US08_03();
    US09_01();
    US09_02();
    US09_03();
    US1001();
    US1201();
    US1501();
    US1601();
    US2101();
    US2102();
    US2201();
    US2202();
    US2701();
    US2702();
    US2901();
    US2902();
    US3001();
    US3002();
    US4001();
    US4201();
	US1801();
	US1802();
	US1901();
	US1701();
	US1301();
	US1302();
    printf("%i Tests Failed\n", failed);
}
