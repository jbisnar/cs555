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
#include <list>


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


int yearsBetweenDates(struct tm date1, struct tm date2){
	int deltaDay = date2.tm_mday - date1.tm_mday;
	int deltaMonth = date2.tm_mon - date1.tm_mon;
	int deltaYear = date2.tm_year - date1.tm_year;
	
	if (deltaDay < 0)
		deltaMonth--;
	if (deltaMonth < 0)
		deltaYear--;
	
	return deltaYear;
}

bool marriageAfter14(individual person, family fam, int marryline){
	struct tm birth = String2Date(person.birthday);
	struct tm marriage = String2Date(fam.married);

    if (yearsBetweenDates(birth, marriage) < 14){
        errorStatements.push_back("ERROR: INDIVIDUAL: US07: " + to_string(marryline) + ": " +  person.name + 
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



// ================================ Sprint 2 ================================


// https://en.wikipedia.org/wiki/Leap_year#Algorithm for leap year algorithm
bool legalDate(string sdate, int dateline){
	// Feb has 28 days
	// leap year: Feb has 29 days
	// "0th" year of the century: Feb has 28 days, except for the 400th year. that leap century, Feb has 29 days.
	
	struct tm date = String2Date(sdate);
	struct tm* pointer = &date;
	
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int givenDay = pointer->tm_mday;
	int givenMonth = pointer->tm_mon - 1; // sets January to month 0.
	int givenYear = pointer->tm_year;
	
	bool isLeap = false;
	
	
	if (givenMonth >= 0 && givenMonth < 12){ // checks correct month
	
		if (givenMonth == 1){ // SPECIAL CASE: February
			if((givenYear % 4) != 0)			{ isLeap = false; }	// common year
			else if ((givenYear % 100) != 0)	{ isLeap = true; }	// leap year
			else if ((givenYear % 400) != 0)	{ isLeap = false;}	// common year
			else								{ isLeap = true; }	// leap year
				
			if (isLeap){
				if ((givenDay > 0) && (givenDay <= days[givenMonth] + 1))
					return true;
				else{
					errorStatements.push_back("ERROR: INDIVIDUAL: US42: " + to_string(dateline) + ": February can't have the day number specified according to the Gregorian calendar.");
					return false;
				}
			}
				
				return ((givenDay > 0) && (givenDay <= days[givenMonth])); // not a leap year, so treat Feb like a regular month.
		}
		
		else if ((givenDay > 0) && (givenDay <= days[givenMonth])){ // all other months
				return true;
		}
		else{
			errorStatements.push_back("ERROR: INDIVIDUAL: US42: " + to_string(dateline) + ": There is an illegal day according to the Gregorian calendar.");
			return false;
		}
	}
	else{
		errorStatements.push_back("ERROR: INDIVIDUAL: US42: " + to_string(dateline) + ": There is an illegal month according to the Gregorian calendar."); 
		return false;
	}
}

// Mother should be less than 60 years older than her children and father should be less than 80 years older than his children
// US 12
bool parentsNotTooOld(unordered_map<string, individual> indis, unordered_map<string, family> fams){
	unordered_map<string, family>:: iterator itr;
	list<string>:: iterator childItr;
	
	struct tm motherBirthDay;
	struct tm fatherBirthDay;
	struct tm childBirthDay;
    string strMotherBirthDay = "N/A", strFatherBirthDay = "N/A", strChildBirthDay = "N/A";
    for(itr = fams.begin(); itr != fams.end(); itr++){ // scan through given fam struct
		strMotherBirthDay = indis.at(itr->second.wifeID).birthday;
		strFatherBirthDay = indis.at(itr->second.husbandID).birthday;
		if (strMotherBirthDay.compare("N/A") == 0 || strFatherBirthDay.compare("N/A") == 0) // no birthday entered for parents
			;
		else{
			motherBirthDay = String2Date(strMotherBirthDay);
			fatherBirthDay = String2Date(strFatherBirthDay);
		
			// goes through the list of children in fams, and checks their individual struct to get the birthday
			for (childItr = itr->second.children.begin(); childItr != itr->second.children.end(); childItr++){
				strChildBirthDay = indis.at(*childItr).birthday;
				if (strChildBirthDay.compare("N/A") == 0) // no birthday entered for child
					break;
				
				childBirthDay = String2Date(strChildBirthDay);
				
				if (yearsBetweenDates(motherBirthDay, childBirthDay) >= 60){
					errorStatements.push_back("ERROR: INDIVIDUAL: US12: " + to_string(indis.at(*childItr).lineNumbers[2]) + ": The child is born when the mother is older than 60 years old.");
					return false;
				}
			
		
				if (yearsBetweenDates(fatherBirthDay, childBirthDay) >= 80){
					errorStatements.push_back("ERROR: INDIVIDUAL: US12: " + to_string(indis.at(*childItr).lineNumbers[2]) + ": The child is born when the father is older than 80 years old.");
					return false;
				}
			}
		}
		
		
	}
	
	
	return true;
}






// ================================ Sprint 3 ================================

// Siblings don't marry each other
// US 18
bool siblingsNotMarried(unordered_map<string, individual> indis, unordered_map<string, family> fams){
	unordered_map<string, family>:: iterator itr;
	
	for(itr = fams.begin(); itr != fams.end(); itr++){ // scan through given fam struct
		
		// only one spouse listed in the family: do nothing and move on to the next family
		if (itr->second.husbandID.compare("N/A") == 0 || itr->second.wifeID.compare("N/A") == 0)
			;
		else{
			string husbandCID = indis.at(itr->second.husbandID).CID;
			string wifeCID = indis.at(itr->second.wifeID).CID;
			
			if(husbandCID.compare("N/A") == 0 || wifeCID.compare("N/A") == 0)
				;
			else if (husbandCID.compare(wifeCID) == 0){ // spouses have the same parents >:(
				errorStatements.push_back("ERROR: FAMILY:     US18: " + to_string(itr->second.lineNumbers[2]) + ": " + indis.at(itr->second.husbandID).name + " is married to his sister.");
				return false;
			}
		}
	}

	return true;
}

// First cousins don't marry each other
// US 19
bool cousinsNotMarried(unordered_map<string, individual> indis, unordered_map<string, family> fams){
	unordered_map<string, family>:: iterator curFamItr;
	unordered_map<string, family>:: iterator itr;
	
	string curHusband, curWife;
	string husbandsDadFam, husbandsMomFam, wifesDadFam, wifesMomFam;
	
	bool incest = false;
	
	for(curFamItr = fams.begin(); curFamItr != fams.end(); curFamItr++){ // scan through given fam struct
		curHusband = curFamItr->second.husbandID;
		curWife = curFamItr->second.wifeID;
		if (curHusband.compare("N/A") == 0 || curWife.compare("N/A") == 0)
			;
		else{
			string husbandFam = indis.at(curHusband).CID;
			string wifeFam = indis.at(curWife).CID;
			
			if (husbandFam.compare("N/A") == 0 || wifeFam.compare("N/A") == 0)
				;
			else{
				// searches out the husband (male cousin)'s family roots
				itr = fams.find(husbandFam);
				husbandsDadFam = indis.at(itr->second.husbandID).CID;
				husbandsMomFam = indis.at(itr->second.wifeID).CID;
				
				// searches out the wife (female cousin)'s family roots
				itr = fams.find(wifeFam);
				wifesDadFam = indis.at(itr->second.husbandID).CID;
				wifesMomFam = indis.at(itr->second.wifeID).CID;
				
				
				if (husbandsDadFam.compare("N/A") != 0 && husbandsDadFam.compare(wifesDadFam) == 0)
					incest = true;
				else if (husbandsDadFam.compare("N/A") != 0 && husbandsDadFam.compare(wifesMomFam) == 0)
					incest = true;
				
				if (husbandsMomFam.compare("N/A") != 0 && husbandsDadFam.compare(wifesDadFam) == 0)
					incest = true;
				else if (husbandsMomFam.compare("N/A") != 0 && husbandsDadFam.compare(wifesMomFam) == 0)
					incest = true;
				
				// redundancy so that we're safe and sound: do comparison from mom's side
				if (wifesDadFam.compare("N/A") != 0 && wifesDadFam.compare(husbandsDadFam) == 0)
					incest = true;
				else if (wifesDadFam.compare("N/A") != 0 && wifesDadFam.compare(husbandsMomFam) == 0)
					incest = true;
				
				if (wifesMomFam.compare("N/A") != 0 && wifesDadFam.compare(husbandsDadFam) == 0)
					incest = true;
				else if (wifesMomFam.compare("N/A") != 0 && wifesDadFam.compare(husbandsMomFam) == 0)
					incest = true;
				
				if (incest){
					errorStatements.push_back("ERROR: FAMILY:     US19: " + to_string(curFamItr->second.lineNumbers[2]) + ": " + indis.at(curFamItr->second.husbandID).name + " is married to his cousin.");
					return false;
				}
			}
		}
	}
	return true;
}


// ================================ Sprint 4 ================================
int monthsBetweenDates(struct tm date1, struct tm date2){
	int deltaDay, deltaMonth, deltaYear, result;
	
	deltaDay = date2.tm_mday - date1.tm_mday;
	deltaMonth = date2.tm_mon - date1.tm_mon;
	deltaYear = date2.tm_year - date1.tm_year;
	
	if (deltaDay < 0)
		deltaMonth--;
	if (deltaMonth < 0){
		deltaYear--;
		deltaMonth = 0;
	}
	
	result = abs(deltaYear*12 + deltaMonth);
	
	return result;
}

int deltaDayofMonth(struct tm date1, struct tm date2){
	return date2.tm_mday - date1.tm_mday;
}

// US 13
// Birth dates of siblings should be more than 8 months apart or less than 2 days apart
// (twins may be born one day apart, e.g. 11:59 PM and 12:02 AM the following calendar day)
// looking at second to last thing using iterator: https://stackoverflow.com/questions/6430960/iterator-for-second-to-last-element-in-a-list
bool correctSiblingBirthdaySpacing(unordered_map<string, individual> indis, unordered_map<string, family> fams){
	unordered_map<string, family>:: iterator curFamItr;
	list<string>:: iterator childItr, stepItr, endList, penultimateList;
	string strBirthday1, strBirthday2;
	struct tm birthday1, birthday2;
	int count, dm1, dm2, dd;
	bool skipCompare = false;
	
	for(curFamItr = fams.begin(); curFamItr != fams.end(); curFamItr++){
		if (curFamItr->second.children.size() == 0 || curFamItr->second.children.size() == 1)
			continue; // breaks one iteration. ie, curFam moves on to the next fam.
		
		count = 0;
		childItr = curFamItr->second.children.begin();
		endList = curFamItr->second.children.end();
		penultimateList = endList;
		--penultimateList; // helps in pointing to the second-to-last thing.
		
		for (; childItr != penultimateList; childItr++, count++){
			stepItr = childItr;
			stepItr++;
			for(; stepItr != endList; stepItr++){
			
				// now: multiple kids. start recording deltas.
				strBirthday1 = indis.at(*childItr).birthday;
				strBirthday2 = indis.at(*stepItr).birthday;
				
				
				if (strBirthday1.compare("N/A") == 0 || strBirthday2.compare("N/A") == 0)
					continue;
				
				
				birthday1 = String2Date(strBirthday1);
				birthday2 = String2Date(strBirthday2);
				
				// time to do the math. call a modified yearsBetweenDates function.
				// if the months are negative, call the function but swap the parameters.
				dm1 = monthsBetweenDates(birthday1, birthday2);
				dm2 = monthsBetweenDates(birthday2, birthday1);
				
				
				if ((dm1 == 0 && dm2 != 0) || (dm1 != 0 && dm2 == 0)){ // result is something like: 0 or 9. so, isolate the 9.
					if (dm2 >= 9)
						; // passes: do nothing
					else if (dm2 == 0 && abs(deltaDayofMonth(birthday2, birthday1) <= 2)){
							; // passes: do nothing
					}
					else{
						errorStatements.push_back("ERROR: FAMILY:     US13: " + to_string(indis.at(*childItr).lineNumbers[2]) + " and " + to_string(indis.at(*stepItr).lineNumbers[2])+ ": Two non-twin siblings are born too close to each other");
						return false;
					}
					if (dm1 >= 9)
						;
					else if (dm1 == 0 && abs(deltaDayofMonth(birthday1, birthday2) <= 2)){
							;
					}
					else{
						errorStatements.push_back("ERROR: FAMILY:     US13: " + to_string(indis.at(*childItr).lineNumbers[2]) + " and " + to_string(indis.at(*stepItr).lineNumbers[2])+ ": Two non-twin siblings are born too close to each other");
						return false;
					}
					
				}
			}
		}
	}
	return true; // if you didn't catch anything in the whole scan of the map, then this is true
}







// US 17
// Parents should not marry any of their children

//	in a given fam:
//		- if parent_A's CID matches any name in parent_B's SID
//		or
//		- if parentB's CID matches any name in parent_A's SID
//	then, call the cops
bool parentsDidntMarryChildren(unordered_map<string, individual> indis, unordered_map<string, family> fams){
	unordered_map<string, family>:: iterator curFamItr;
	list<string>:: iterator sidItr;
	string husbCID, wifeCID;
	string husbCurSID, wifeCurSID;
	
	bool incest = false;
	
	for(curFamItr = fams.begin(); curFamItr != fams.end(); curFamItr++){
		
		husbCID = indis.at(curFamItr->second.husbandID).CID;
		wifeCID = indis.at(curFamItr->second.wifeID).CID;
		if (husbCID.compare("N/A") == 0 && wifeCID.compare("N/A") == 0)
			continue;
		
		// check husband's CID to wife's SID list
		for (sidItr = indis.at(curFamItr->second.wifeID).SID.begin(); sidItr != indis.at(curFamItr->second.wifeID).SID.end(); sidItr++){
			wifeCurSID = *sidItr;
			if (wifeCurSID.compare(husbCID) == 0)
				incest = true;
		}
		
		// check wife's CID to husband's SID list
		for (sidItr = indis.at(curFamItr->second.husbandID).SID.begin(); sidItr != indis.at(curFamItr->second.husbandID).SID.end(); sidItr++){
			husbCurSID = *sidItr;
			if (husbCurSID.compare(wifeCID) == 0)
				incest = true;
		}
		
		if (incest){
			errorStatements.push_back("ERROR: FAMILY:     US17: " + to_string(curFamItr->second.lineNumbers[2]) + " and " + to_string(curFamItr->second.lineNumbers[3])+ ": A parent married his/her child.");
			return false;
		}
	}
	
	return true;
}














