/* main.cpp                                                         *
 * contains the main function for the gedcom checker                *
 * I pledge my honor that I have abided by the Stevens Honor System */

#include <fstream>
#include <iostream>
#include <list>

#include "globals.h"
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
        lineNumber++;
    }
    finalStore();
    
    printf("\n");
    printIndividuals(sortIndividuals(indiMap));
    cout << endl;
    printFamilies(sortFamilies(famMap));
    printf("\n");
    list <string> :: iterator it;
    for(it = errorStatements.begin(); it !=errorStatements.end(); ++it){
        cout << *it << endl;
    }
    return 0;
}
