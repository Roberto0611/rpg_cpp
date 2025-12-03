// Clase Monstruo
#if !defined(Monster_h)
#define Monster_h

#include <string>
#include "Stats.h"

using namespace std;

class Monster{
    private:
        int id;
        string name;
        Element element;
        Stats stats;
        FechaRegistro registerDate;
    public:
        // constructor
        Monster(int id, string name, Element element, Stats stats, FechaRegistro registerDate);

        // metodos
        void takeDamage(int damage);
        bool isAlive();
        int getAttack();
        int getHP();
};

#endif // Monster_h
