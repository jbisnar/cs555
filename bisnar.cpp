#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <stdlib.h>

#include <unordered_map>
#include <list>

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

bool BirthB4Death (individual person) {
	if (strcmp(person.death.c_str(), "") == 0) {
		//printf ("This mf still alive");
		return true;
	}
	if ( strcmp(person.birthday.c_str(), person.death.c_str()) > 0) {
		errorStatements.push_back("ERROR: INDIVIDUAL: US03: "
		+ to_string(person.lineNumbers[2]) + " and " + to_string(person.lineNumbers[4]) + ": "
		+ person.name + "'s death date is before their birth date"); 
		return false;
	}
	return true;
}

bool BirthB4Marriage (family fam) {
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
			+ to_string(fam.lineNumbers[0]) +": "
			+ "Marry date is before someone's birthday"); 
			return false;
			return false;
			//printf ("BB4M Checkpoint 2\n");
		}
	}
	//printf ("BB4M Checkpoint 3\n");
	return true;
}

bool MarriageB4Death (family fam) {
	if (indiMap.find(fam.husbandID) != indiMap.end() && indiMap.find(fam.wifeID) != indiMap.end()) {
		string hdeath = indiMap.find(fam.husbandID)->second.death;
		string wdeath = indiMap.find(fam.wifeID)->second.death;
		if ( ((strcmp(hdeath.c_str(), fam.married.c_str()) < 0 && (strcmp(hdeath.c_str(), "N/A") != 0))
		|| ( (strcmp(wdeath.c_str(), fam.married.c_str())) < 0 && (strcmp(wdeath.c_str(), "N/A") != 0)))) {
			errorStatements.push_back("ERROR: FAMILY:     US05: "
			+ to_string(fam.lineNumbers[0]) +": "
			+ "Marry date is after someone died"); 
			return false;
		}
	}
	return true;
}

bool DivorceB4Death (family fam) {
	if (indiMap.find(fam.husbandID) != indiMap.end() && indiMap.find(fam.wifeID) != indiMap.end()) {
		string hdeath = indiMap.find(fam.husbandID)->second.death;
		string wdeath = indiMap.find(fam.wifeID)->second.death;
		if (strcmp("N/A", fam.divorced.c_str()) == 0) {
			return true;
		} else if ( ((strcmp(hdeath.c_str(), fam.divorced.c_str()) < 0 && (strcmp(hdeath.c_str(), "N/A") != 0))
		|| ( (strcmp(wdeath.c_str(), fam.divorced.c_str())) < 0 && (strcmp(wdeath.c_str(), "N/A") != 0)))) {
			errorStatements.push_back("ERROR: FAMILY:     US06: "
			+ to_string(fam.lineNumbers[1]) +": "
			+ "Divorce date is after someone died"); 
			return false;
		}
	}
	return true;
}

bool MarriageB4Divorce (family fam) {
	//printf("MarriageB4Divorce called \n");
	if ( (strcmp(fam.married.c_str(), fam.divorced.c_str()) > 0) && (strcmp(fam.divorced.c_str(),"N/A") != 0)) {
		errorStatements.push_back("ERROR: FAMILY:     US04: "
			+ to_string(fam.lineNumbers[0]) +" and "+ to_string(fam.lineNumbers[1]) +": "
			+ "Divorce date is before marriage date");
			return false;
	}
	return true;
}

bool BirthB4ParentsDeath () {
	bool noerrors = true;
	unordered_map<string, family>:: iterator fam;
	for(fam = famMap.begin(); fam != famMap.end(); fam++){
		string hdeath = indiMap.find(fam->second.husbandID)->second.death;
		//printf("Processing family %s\n", fam->first.c_str());
		string fathergrace = NineMonthsLater(hdeath);
		string wdeath = indiMap.find(fam->second.wifeID)->second.death;
		//printf("Family %s: father died %s, mother died %s\n",
		//		fam->first.c_str(), hdeath.c_str(), wdeath.c_str());
		//printf("But the father can have a child until %s\n",fathergrace.c_str());
		list<string> kidlist = fam->second.children;
		list<string>::iterator kid;
		for (kid = kidlist.begin(); kid != kidlist.end(); ++kid) {
			string cbirth = indiMap.find(kid->c_str())->second.birthday;
			//printf("Child %s was born %s\n", kid->c_str(), cbirth.c_str());
			if ( strcmp(wdeath.c_str(), cbirth.c_str()) < 0 && strcmp(wdeath.c_str(), "N/A") != 0 && strcmp(wdeath.c_str(), "") != 0 ) {
				errorStatements.push_back("ERROR: INDIVIDUAL: US09: "
				+ to_string(indiMap.find(kid->c_str())->second.lineNumbers[2]) +": "
				+ indiMap.find(kid->c_str())->second.name + " born after mother died");
				noerrors = false;
			} else if ( strcmp(fathergrace.c_str(), cbirth.c_str()) < 0 && strcmp(hdeath.c_str(), "N/A") != 0 && strcmp(hdeath.c_str(), "") != 0) {
				errorStatements.push_back("ERROR: INDIVIDUAL: US09: "
				+ to_string(indiMap.find(kid->c_str())->second.lineNumbers[2]) +": "
				+ indiMap.find(kid->c_str())->second.name + " born over 9 months after father died");
				noerrors = false;
			}
		}
	}
	return noerrors;
}

string NineMonthsLater (string date) {
	// Assumes format "yyyy-mm-dd"
	//printf("Nine Months Later Called on string %s\n",date.c_str());
	if (date.length() != 10) {
		//printf("NML Return Checkpoint 1\n");
		return date;
	}
	string yearstr = date.substr(0,4);
	//printf("year string is %s\n",yearstr.c_str());
	string monthstr = date.substr(5,2);
	//printf("month string is %s\n",monthstr.c_str());
	string daystr = date.substr(8,2);
	//printf("day string is %s\n",daystr.c_str());
	int year = atoi(yearstr.c_str());
	int month = atoi(monthstr.c_str());
	//int day = atoi(daystr.c_str());
	int newmonth = (month+9)%12;
	//printf("NML Checkpoint 1\n");
	char newmonthstr[3];
	char newdate[11];
	//printf("NML Checkpoint 2\n");
	if (newmonth < 10) {
		//printf("0%i",newmonth);
		sprintf(newmonthstr,"0%i",newmonth);
	} else {
		//printf("0%i",newmonth);
		sprintf(newmonthstr,"%i",newmonth);
	}
	//printf("NML Checkpoint 3\n");
	if (newmonth < month) {
		//printf("%i-%s-%s",year+1,newmonthstr,daystr.c_str());
		sprintf(newdate,"%i-%s-%s",year+1,newmonthstr,daystr.c_str());
	} else {
		//printf("%i-%s-%s",year,newmonthstr,daystr.c_str());
		sprintf(newdate,"%i-%s-%s",year,newmonthstr,daystr.c_str());
	}
	//printf("NML Return Checkpoint 2\n");
	return newdate;
}

bool BirthB4ParentsMarriage () {
	bool noerrors = true;
	unordered_map<string, family>:: iterator fam;
	for(fam = famMap.begin(); fam != famMap.end(); fam++){
		//printf("Processing family %s\n", fam->first.c_str());
		string marrday = fam->second.married;
		string divday = fam->second.divorced;
		string divgrace = NineMonthsLater(divday);
		list<string> kidlist = fam->second.children;
		list<string>::iterator kid;
		for (kid = kidlist.begin(); kid != kidlist.end(); ++kid) {
			string cbirth = indiMap.find(kid->c_str())->second.birthday;
			//printf("Comparing %s's birthday %s with marriage day %s\n", indiMap.find(kid->c_str())->first.c_str(), cbirth.c_str(), marrday.c_str());
			if ( strcmp(cbirth.c_str(), marrday.c_str()) < 0 && strcmp(marrday.c_str(), "N/A") != 0 && strcmp(marrday.c_str(), "") != 0 ) {
				errorStatements.push_back("ERROR: INDIVIDUAL: US08: "
				+ to_string(indiMap.find(kid->c_str())->second.lineNumbers[2]) +": "
				+ indiMap.find(kid->c_str())->second.name + " born before parents married");
				noerrors = false;
			} else if ( strcmp(divgrace.c_str(), cbirth.c_str()) < 0 && strcmp(divday.c_str(), "N/A") != 0 && strcmp(divday.c_str(), "") != 0) {
				errorStatements.push_back("ERROR: INDIVIDUAL: US08: "
				+ to_string(indiMap.find(kid->c_str())->second.lineNumbers[2]) +": "
				+ indiMap.find(kid->c_str())->second.name + " born over 9 months after parents divorced");
				noerrors = false;
			}
		}
	}
	return noerrors;
}

bool DatesB4Today (string date, string override, int lineNumber, int type) {
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	char todate[11];
	char monthstr[3];
	if (timeinfo->tm_mon+1 < 10) {
		sprintf(monthstr,"0%i",timeinfo->tm_mon+1);
	} else {
		sprintf(monthstr,"%i",timeinfo->tm_mon+1);
	}
	char daystr[3];
	if (timeinfo->tm_mday < 10) {
		sprintf(daystr,"0%i",timeinfo->tm_mday);
	} else {
		sprintf(daystr,"%i",timeinfo->tm_mday);
	}
	sprintf(todate,"%i-%s-%s",timeinfo->tm_year+1900,monthstr,daystr);
	if (strcmp(override.c_str(), "") != 0) {
		sprintf(todate,"%s",override.c_str());
	}
	//printf ("Comparing given date %s with today's date %s\n", date.c_str(), todate);
	if (strcmp(todate, date.c_str()) < 0) {
		if (type == 0) {
			errorStatements.push_back("ERROR: INDIVIDUAL: US01: " + to_string(lineNumber) + ": "
									+ "date " + date + " is after today's date " + todate);
		} else {
			errorStatements.push_back("ERROR: FAMILY:     US01: " + to_string(lineNumber) + ": "
									+ "date " + date + " is after today's date " + todate);
		}
		return false;
	} else {
		return true;
	}
}