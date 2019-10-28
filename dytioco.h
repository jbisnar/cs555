/*dytioco.h*/

#ifndef DYTIOCO_H
#define DYTIOCO_H

#include "globals.h"

using namespace std;

bool marriageAfter14(individual person, family fam, int marryline);
bool notOlderThan150(individual person, int birthline);
bool legalDate(string sdate, int dateline);
bool parentsNotTooOld(unordered_map<string, individual> indis, unordered_map<string, family> fams);
bool siblingsNotMarried(unordered_map<string, individual> indis, unordered_map<string, family> fams);
bool cousinsNotMarried(unordered_map<string, individual> indis, unordered_map<string, family> fams);

#endif
