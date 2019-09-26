#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>

#include <unordered_map>

#include "globals.h"
#include "bisnar.h"

/*
time_t String2Date (string sdate) {
	struct tm * givendate;
	
	char* syear = new char[5];
	syear[0] = sdate[0];
	syear[4] = '\0';
	char* smonth = new char[3];
	smonth[0] = sdate[5];
	smonth[2] = '\0';
	char* sday = new char[3];
	sday[0] = sdate[8];
	sday[2] = '\0';
	
	givendate->tm_day = atoi(sday);
	givendate->tm_mon atoi(smon);
	givendate->tm_year atoi(syear);
	
	return mktime(givendate);
}
*/

bool BirthB4Death (individual person, int birthline, int deathline) {
	if ( strcmp(person.birthday.c_str(), person.death.c_str()) > 0) {
		errorStatements.push_back("ERROR: INDIVIDUAL: US03: lines "
		+ to_string(birthline) + " and " + to_string(deathline) + ": "
		+ person.name + "'s death date is before their birth date"); 
		return false;
	}
	return true;
}

bool BirthB4Marriage (time_t marrydate, time_t currentdate) {
	return false;
}