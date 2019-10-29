/* parser.cpp                                                                                    *
 * Contains the parser that breaks up each line of the gedcom file and correctly stores the data *
 * I pledge my honor that I have abided by the Stevens Honor System                              */

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <stdio.h>
#include <string>
#include <string.h>
#include <unordered_map>

#include "globals.h"
#include "monaco.h"
#include "bisnar.h"
#include "dytioco.h"

using namespace std;

individual curIndi = {"", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};

family curFam = {"", "N/A", "N/A", "N/A", {}, {0,0,0,0}};

string curIDFam;
string curIDInd;
string curTag;

unordered_map<string, individual> indiMap;
unordered_map<string, family> famMap;

int maxIDLength = 12;
int maxNameLength = 4;

// Variables for user stories
int birthline = 0;
int deathline = 0;
int marryline = 0;
int divorceline = 0;

/* Turn the date from the gedcom file into all numbers */
string improveDate(string inputDate){

    string day = inputDate.substr(0, inputDate.find_first_of(" "));
    inputDate = inputDate.substr(inputDate.find_first_of(" ") + 1);
    
    string month = inputDate.substr(0, inputDate.find_first_of(" "));
    inputDate = inputDate.substr(inputDate.find_first_of(" ") + 1);

    if(day.length() == 1){
        day = "0" + day;
    }
    
    if(strcmp(month.c_str(), "JAN") == 0){
        month = "01";
    }else if(strcmp(month.c_str(), "FEB") == 0){
        month = "02";
    }else if(strcmp(month.c_str(), "MAR") == 0){
        month = "03";
    }else if(strcmp(month.c_str(), "APR") == 0){
        month = "04";
    }else if(strcmp(month.c_str(), "MAY") == 0){
        month = "05";
    }else if(strcmp(month.c_str(), "JUN") == 0){
        month = "06";
    }else if(strcmp(month.c_str(), "JUL") == 0){
        month = "07";
    }else if(strcmp(month.c_str(), "AUG") == 0){
        month = "08";
    }else if(strcmp(month.c_str(), "SEP") == 0){
        month = "09";
    }else if(strcmp(month.c_str(), "OCT") == 0){
        month = "10";
    }else if(strcmp(month.c_str(), "NOV") == 0){
        month = "11";
    }else if(strcmp(month.c_str(), "DEC") == 0){
        month = "12";
    }
    return inputDate + "-" + month + "-" + day;
}

/* Given an unordered list of individuals, this returns a list of the ids in alphabetical order */
list<string> sortIndividuals(unordered_map<string, individual> inputMap){
    
    unordered_map<string, individual> outputMap;
    unordered_map<string, individual>:: iterator itr;
    list<string> ids;
    
    for(itr = inputMap.begin(); itr != inputMap.end(); itr++){
        ids.push_front(itr->first);
    }
    ids.sort();
    
    return ids;
}

/* Given an unordered list of families, this returns a list of the ids in alphabetical order */
list<string> sortFamilies(unordered_map<string, family> inputMap){
    
    unordered_map<string, family> outputMap;
    unordered_map<string, family>:: iterator itr;
    list<string> ids;

    for(itr = inputMap.begin(); itr != inputMap.end(); itr++){
        ids.push_front(itr->first);
    }
    ids.sort();

    return ids;

}

/* Print given families in a table */
void printFamilies(list<string> idList){
    
    cout << setw(maxIDLength+1) << "ID" << " |" 
        << setw(11) << "MARRIED" << " |" 
        << setw(11) << "DIVORCED" << " |"
        << setw(maxIDLength+1) << "HUSBAND ID" << " |"
        << setw(maxNameLength+1) << "HUSBAND NAME" << " |"
        << setw(maxIDLength+1) << "WIFE ID" << " |"
        << setw(maxNameLength+1) << "WIFE NAME" << " | CHILDREN"
        << endl;
    cout << endl;
    
    list<string>:: iterator nextID;
    for (nextID = idList.begin(); nextID != idList.end(); nextID++){
        family itr = famMap.at(*nextID); 
        cout << setw(maxIDLength+1) << *nextID << " |" 
            << setw(11) << itr.married << " |" 
            << setw(11) << itr.divorced << " |"
            << setw(maxIDLength+1) << itr.husbandID << " |"
            << setw(maxNameLength+1) << indiMap.at(itr.husbandID).name << " |"
            << setw(maxIDLength+1) << itr.wifeID << " |"
            << setw(maxNameLength+1) << indiMap.at(itr.wifeID).name << " | ";
        list <string> :: iterator child;
        for(child = itr.children.begin(); child != itr.children.end(); ++child){
            cout << "{\'" << *child << "\'} ";
        }
        cout << endl;
    }
    
    return;
}

/* Print given individuals in a table */
void printIndividuals(list<string> idList){
    
    cout << setw(maxIDLength+1) << "ID" << " |" 
        << setw(maxNameLength+1) << "NAME" << " |"
        << setw(7) << "GENDER" << " |"
        << setw(11) << "BIRTHDAY" << " |" 
        << setw(6) << "ALIVE" << " |"
        << setw(11) << "DEATH" << " |"
        << setw(maxIDLength+1) << "CHILD" << " | SPOUSE"
        << endl;
    cout << endl;

    list<string>:: iterator nextID; 
    for (nextID = idList.begin(); nextID != idList.end(); nextID++){
        individual itr = indiMap.at(*nextID); 
        string alive;
        if(itr.alive){
            alive = "True";
        }else{
            alive = "False";
        }
        cout <<  setw(maxIDLength+1) << *nextID << " |" 
            << setw(maxNameLength+1) << itr.name << " |"
            << setw(7) << itr.gender << " |"
            << setw(11) << itr.birthday << " |" 
            << setw(6) << alive << " |"
            << setw(11) << itr.death << " |"
            << setw(maxIDLength+1) << itr.CID << " | ";
        list <string> :: iterator spouse;
        for(spouse = itr.SID.begin(); spouse != itr.SID.end(); ++spouse){
            cout << "{\'" << *spouse << "\'} ";
        }
        cout << endl;
    }
    
    return;
}

/* Store the last individual and family that were being edited */
void finalStore(){
    
    if(strcmp(curIndi.name.c_str(), "") != 0){
    	BirthB4Death(curIndi);
        indiMap[curIDInd.c_str()] = curIndi;
    }
    if(strcmp(curFam.married.c_str(), "") != 0){
    	BirthB4Marriage(curFam);
    	MarriageB4Death(curFam);
    	DivorceB4Death(curFam);
    	MarriageB4Divorce(curFam);
        famMap[curIDFam.c_str()] = curFam;
    }
    parentsNotTooOld(indiMap, famMap);
	siblingsNotMarried(indiMap, famMap);
	cousinsNotMarried(indiMap, famMap);
	BirthB4ParentsDeath(curFam);
    return;
}

/* Store each line into unordered maps for individuals and families */
void store(string level, string tag, string args){
    
    if(strcmp(tag.c_str(), "INDI") == 0){
        if(strcmp(curIndi.name.c_str(), "") != 0){
        	BirthB4Death(curIndi);
            indiMap[curIDInd.c_str()] = curIndi;
        }
        individual temp = {"N/A", '\0', "N/A", true, "N/A", {}, "N/A", {0,0,0,0,0,0}};
        curIndi = temp;
        uniqueID(args, indiMap);
        curIDInd = args;
        if(args.length() > maxIDLength){
            maxIDLength =  args.length();
        }
    }else if(strcmp(tag.c_str(), "NAME") == 0){
        curIndi.lineNumbers[0] = lineNumber;
        curIndi.name = args.c_str();
        if(args.length() > maxNameLength){
            maxNameLength = args.length();
        }
    }else if(strcmp(tag.c_str(), "SEX") == 0){
        curIndi.lineNumbers[1] = lineNumber;
        curIndi.gender = *args.c_str();
    }else if(strcmp(tag.c_str(), "BIRT") == 0){
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "DEAT") == 0){
        curTag = tag.c_str();
        curIndi.lineNumbers[3] = lineNumber;
        curIndi.alive = false;
    }else if(strcmp(tag.c_str(), "FAMC") == 0){
        curIndi.lineNumbers[5] = lineNumber;
        curIndi.CID = args.c_str();
    }else if(strcmp(tag.c_str(), "FAMS") == 0){
        curIndi.SID.push_back(args);
    }else if(strcmp(tag.c_str(), "FAM") == 0){
        if(strcmp(curFam.married.c_str(), "") != 0){
        	BirthB4Marriage(curFam);
        	MarriageB4Death(curFam);
        	DivorceB4Death(curFam);
        	//MarriageB4Divorce(curFam);
            famMap[curIDFam.c_str()] = curFam;
        }
        family ftemp = {"N/A", "N/A", "N/A", "N/A", {}, {0,0,0,0}};
        curFam = ftemp;
        uniqueFamID(args, famMap);
        curIDFam = args;
        if(args.length() > maxIDLength){
            maxIDLength =  args.length();
        }
    }else if(strcmp(tag.c_str(), "MARR") == 0){
        marryline = lineNumber;
        curTag = tag.c_str();
    }else if(strcmp(tag.c_str(), "HUSB") == 0){
        curFam.lineNumbers[2] = lineNumber;
        curFam.husbandID = args.c_str();
    }else if(strcmp(tag.c_str(), "WIFE") == 0){
        curFam.lineNumbers[3] = lineNumber;
        curFam.wifeID = args.c_str();
    }else if(strcmp(tag.c_str(), "CHIL") == 0){
        curFam.children.push_back(args);
		
    }else if(strcmp(tag.c_str(), "DIV") == 0){
        curTag = tag.c_str();
        // divorceline = lineNumber;
    }else if(strcmp(tag.c_str(), "DATE") == 0){
        if(strcmp(curTag.c_str(), "BIRT") == 0){
            curIndi.birthday = improveDate(args.c_str());
            curIndi.lineNumbers[2] = lineNumber;
            birthline = lineNumber;
			notOlderThan150(curIndi, birthline);
			legalDate(curIndi.birthday, birthline);
        }else if(strcmp(curTag.c_str(), "DEAT") == 0){
            curIndi.death = improveDate(args.c_str());
            curIndi.lineNumbers[4] = lineNumber;
            deathline = lineNumber;
			legalDate(curIndi.death, deathline);
        }else if(strcmp(curTag.c_str(), "DIV") == 0){
            curFam.lineNumbers[1] = lineNumber;
            curFam.divorced = improveDate(args.c_str());
			legalDate(curFam.divorced, lineNumber);
			DivorceB4Death(curFam);
			MarriageB4Divorce(curFam);
        }else if(strcmp(curTag.c_str(), "MARR") == 0){
            curFam.lineNumbers[0] = lineNumber;
            curFam.married = improveDate(args.c_str());
			marryline = lineNumber;
			marriageAfter14(curIndi, curFam, marryline);
			legalDate(curFam.married, lineNumber);
        }
    }
    
    return;
}

/* Parse each line of the ged file into the level, tag, and arguments */
void parse(string nextLine){
    
    char* line = new char [nextLine.length() + 1];
    strcpy(line, nextLine.c_str());
    
    string args;
    string tag;
    string level = nextLine.substr(0, nextLine.find_first_of(" "));
    nextLine = nextLine.substr(nextLine.find_first_of(" ") + 1);
    if(nextLine.find_first_of(" ") == -1){
        tag = nextLine;
        args = "";
    }else{
        tag = nextLine.substr(0, nextLine.find_first_of(" "));
        args = nextLine.substr(nextLine.find_first_of(" ") + 1);
    }

    if(strcmp(args.c_str(), "INDI") == 0 || strcmp(args.c_str(), "FAM") == 0){
        store(level, args, tag);
    }else if(strcmp(tag.c_str(), "INDI") == 0 || strcmp(tag.c_str(), "FAM") == 0){
        store(level, tag, args);
    }else{
        store(level, tag, args);
    }

    return;
}
