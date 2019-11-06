/* main.cpp                                                         *
 * contains the main function for the gedcom checker                *
 * I pledge my honor that I have abided by the Stevens Honor System */

#include <fstream>
#include <iostream>
#include <list>

#include "globals.h"
#include "monaco.h"
#include "parser.h"

using namespace std;

int lineNumber;
list <string> errorStatements;

int main(int argc, char** argv) {

    string nextLine;
    ifstream gedcomFile;
    gedcomFile.open(argv[1]);


    lineNumber = 1;
    while(getline(gedcomFile, nextLine)){
        parse(nextLine);
        printf("%s\n",nextLine.c_str());
        lineNumber++;
    }
    
    printf("hello\n");
    finalStore();
 
    printf("hello\n");
    correctGender(indiMap, famMap);
    printf("hello\n");
    maleLastNames(indiMap, famMap);
    printf("hello\n");
    lessThan15Kids(famMap, indiMap);

    printf("LIST OF ALL INDIVIDUALS:\n");
    printIndividuals(sortIndividuals(indiMap));
    printf("\n");
    printf("LIST OF ALL FAMILIES:\n");
    printFamilies(sortFamilies(famMap));
    printf("\n");
    printf("US30: LIST OF ALL LIVING MARRIED INDIVIDUALS:\n");
    printIndividuals(getLivingMarried(famMap, indiMap));
    printf("\n");
    printf("US29: LIST OF ALL DECEASED PERSONS:\n");
    printIndividuals(getDeceased(indiMap));
    printf("\n");
    printf("LIST OF ALL KNOWN ERRORS:\n");
    list <string> :: iterator it;
    for(it = errorStatements.begin(); it !=errorStatements.end(); ++it){
        cout << *it << endl;
    }
    return 0;
}
