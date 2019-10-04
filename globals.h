/* globals.h                                                                    *
 * Contains all variables that need to be accessed and edited by multiple files *
 * I pledge my honor that I have abided by the Stevens Honor System             */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <list>
#include <string>
#include <unordered_map>

using namespace std;

struct individual{
    string name;
    char gender;
    string birthday;
    bool alive;
    string death;
    list<string> SID;
    string CID;
    int lineNumbers[6];
};

struct family{
    string married;
    string divorced;
    string husbandID;
    string wifeID;
    list<string> children;
    int lineNumbers[4];
};

/* Map of all families */
extern unordered_map<string, family> famMap;

/* Map of all individuals */
extern unordered_map<string, individual> indiMap;

/* Current line number is GEDCOM file */
extern int lineNumber;

/* List of error statements */
extern list <string> errorStatements;

#endif
