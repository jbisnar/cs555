/* dytioco.cpp
** All functions needed for the user stories completed by Ethan DyTioco for the gedcom project
** I pledge my honor that I have abided by the Stevens Honor System
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <ctime>
#include <unordered_map>


#include "globals.h"
#include "dytioco.h"

using namespace std;

// developed by Jared Bisnar and Ethan DyTioco
// input: 1958-02-23
// return: struct tm
// you will have to do <object>.tm_year for example, to grab the 
//
// sdate:	1998-03-15 << 15 MAR 1998
// index:	0123456789
// indices 0-3 has the year, 5-6 has the month, 8-9 has the day. sdate[4], sdate[7] are ignored because they're dashes.
struct tm String2Date (string sdate) {
	struct tm  givendate;
	
	char syear[5] = {'0', '0', '0', '0', '0'};
	syear[0] = sdate[0];
	syear[1] = sdate[1];
	syear[2] = sdate[2];
	syear[3] = sdate[3];
	syear[4] = '\0';			// nullptr at the end of char arrays
	
	char smonth[3] = {'0', '0', '0'};
	smonth[0] = sdate[5];
	smonth[1] = sdate[6];
	smonth[2] = '\0';			// ditto
	
	char sday[3] = {'0', '0', '0'};
	sday[0] = sdate[8];
	sday[1] = sdate[9];
	sday[2] = '\0';
	
	string stringYear = syear;
	string stringMonth = smonth;
	string stringDay = sday;
	
	
	givendate.tm_mday = stoi(stringDay);
	givendate.tm_mon = stoi(stringMonth);
	givendate.tm_year = stoi(stringYear);
	
	return givendate;
}

bool marriageAfter14(individual person, family fam, int marryline){
	struct tm birth = String2Date(person.birthday);
	struct tm marriage = String2Date(fam.married);
	
	int deltaDay = marriage.tm_mday - birth.tm_mday;
	int deltaMonth = marriage.tm_mon - birth.tm_mon;
	int deltaYear = marriage.tm_year - birth.tm_year;
	
	if (deltaDay < 0)
		deltaMonth--;
	if (deltaMonth < 0)
		deltaYear--;
		
	
    if (deltaYear < 14){
        errorStatements.push_back("ERROR: INDIVIDUAL: US07: " + to_string(marryline) + ": this marriage line means that " +  person.name + 
                " is married before 14 years of age, which is illegal in the US."); 
        return false;
    }
    return true;
}

bool notOlderThan150(individual person, int birthline){
	struct tm birth = String2Date(person.birthday);
	
	time_t rawTime;
	struct tm rawTimeStruct;
	struct tm* tmPointer = &rawTimeStruct;
	
	
	time(&rawTime); // sets rawTime to the current time when this compiles
	
	tmPointer = localtime(&rawTime); // tm* tmPointer now has the tm values of time_t currentTime
	
	int deltaDay = tmPointer->tm_mday - birth.tm_mday;
	int deltaMonth = tmPointer->tm_mon - birth.tm_mon + 1;
	int deltaYear = tmPointer->tm_year - birth.tm_year + 1900;
	
	if (deltaDay < 0)
		deltaMonth--;
	if (deltaMonth < 0)
		deltaYear--;
    if (deltaYear > 150){
        errorStatements.push_back("ERROR: INDIVIDUAL: US10: " + to_string(birthline) + ": " +  person.name + 
                " is listed as being older than 150 years old, which today is highly improbable."); 
        return false;
    }
    return true;
}
