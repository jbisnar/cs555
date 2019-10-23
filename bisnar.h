/*bisnar.h*/

#ifndef BISNAR_H
#define BISNAR_H

#include "globals.h"

using namespace std;

bool BirthB4Death (individual person);

bool BirthB4Marriage (family fam);

bool MarriageB4Death (family fam);

bool DivorceB4Death (family fam);

bool MarriageB4Divorce (family fam);

bool BirthB4ParentsDeath (family fam);

#endif