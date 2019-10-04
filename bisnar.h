/*bisnar.h*/

#ifndef BISNAR_H
#define BISNAR_H

#include "globals.h"

using namespace std;

bool BirthB4Death (individual person, int birthline, int deathline);

bool BirthB4Marriage (family fam, int marryline);

bool MarriageB4Death (family fam, int marryline);

bool DivorceB4Death (family fam, int divorceline);

#endif