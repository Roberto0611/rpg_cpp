// Clase Monstruo
#if !defined(Monster_h)
#define Monster_h

#include <string>
#include <iostream>
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
        int getDefense();
        void setHP(int netDamage);
        int getHP();
        string getName();
        
        // sobrecarga
        friend ostream& operator << (ostream &o, const Monster &m);
};
#endif // Monster_h
