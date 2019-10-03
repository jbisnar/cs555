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
	if (strcmp(person.death.c_str(), "") == 0) {
		//printf ("This mf still alive");
		return true;
	}
	if ( strcmp(person.birthday.c_str(), person.death.c_str()) > 0) {
		errorStatements.push_back("ERROR: INDIVIDUAL: US03: "
		+ to_string(birthline) + ", " + to_string(deathline) + ": "
		+ person.name + "'s death date is before their birth date"); 
		return false;
	}
	return true;
}

bool BirthB4Marriage (family fam, int marryline) {
	/*
	printf ("BB4M Checkpoint 0\n");
	printf ("Family marryline is %d\n", marryline);
	printf ("Husband exists with husbandID %s\n",fam.husbandID.c_str());
	printf ("Wife exists with wifeID %s\n",fam.wifeID.c_str());
	*/
	if (indiMap.find(fam.husbandID) != indiMap.end() && indiMap.find(fam.wifeID) != indiMap.end()) {
		//printf ("BB4M Checkpoint 1\n");
	
		if ( strcmp(indiMap.find(fam.husbandID)->second.birthday.c_str(), fam.married.c_str()) > 0
		|| strcmp(indiMap.find(fam.wifeID)->second.birthday.c_str(), fam.married.c_str()) > 0) {
			//printf ("BB4M Checkpoint 1\n");
			errorStatements.push_back("ERROR: FAMILY:     US02: "
			+ to_string(marryline) +": "
			+ "Marry date is before someone's birthday"); 
			return false;
			return false;
			//printf ("BB4M Checkpoint 2\n");
		}
	}
	//printf ("BB4M Checkpoint 3\n");
	return true;
}
