/* monaco.h*/

#ifndef MONACO_H
#define MONACO_H

#include "globals.h"

using namespace std;


bool uniqueID(string key, unordered_map<string, individual> indis);

bool uniqueFamID(string key, unordered_map<string, family> indis);

list<string> getLivingMarried(unordered_map<string, family> fams, 
        unordered_map<string, individual> indis); 

void correctGender(unordered_map<string, individual> indis, unordered_map<string, family> fams);

#endif
