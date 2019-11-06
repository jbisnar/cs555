/* parser.h */

#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>
#include <unordered_map>

using namespace std;

void finalStore();

void printFamilies(list<string> idList);

void printIndividuals(list<string> idList);

void parse(string nextLine);

list<string> sortIndividuals(unordered_map<string, individual> inputMap);

list<string> sortFamilies(unordered_map<string, family> inputMap);

string getAge(string birthDate, string deathDate);

#endif
