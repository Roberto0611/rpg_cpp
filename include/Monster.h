// Clase Monstruo
#if !defined(Monster_h)
#define Monster_h

#include <string>
#include "Stats.h"

using namespace std;

class Monster{
    int id;
    string name;
    Element element;
    Stats stats;
};

#endif // Monster_h
