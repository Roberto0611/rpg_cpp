#include "Monster.h"
#include <iostream>
#include <algorithm>
#include "Utils.h"

using namespace std;

// logica del enum
string elementToString(Element e) {
    switch(e) {
        case Element::Fuego: return "Fuego";
        case Element::Agua: return "Agua";
        case Element::Planta: return "Planta";
        case Element::Tierra: return "Tierra";
        case Element::Neutro: return "Neutro";
        default: return "Desconocido";
    }
}


// constructor
Monster::Monster(int id, string name, Element element, Stats stats, FechaRegistro registerDate){
    this->id = id;
    this->name = name;
    this->element = element;
    this->stats = stats;
    this->stats.HPCurrent = this->stats.HPMax;
    this->registerDate = registerDate;
}

// getters y setters
int Monster::getAttack(){
    return this->stats.attack;
}

int Monster::getDefense(){
    return this->stats.defense;
}

int Monster::getHP(){
    return this->stats.HPCurrent;
}

void Monster::setHP(int netDamage){
    if(netDamage > getHP()){
        netDamage = getHP();
    }

    this->stats.HPCurrent -= netDamage;
}

string Monster::getName(){
    return this->name;
}

// metodos

// recibir danio (siempre debe ser minimo 1 si no es ataque - defensa / 2)
void Monster::takeDamage(int damage){
    int netDamage = max(1, damage - getDefense()/2);
    setHP(netDamage);
}

bool Monster::isAlive(){
    return getHP() > 0;
}

// sobrecargar operador
ostream& operator << (ostream &out, const Monster &m){
    out << "Nombre: " << m.name << endl;
    out << "Elemento: " << elementToString(m.element) << endl;
    out << "HP: " << m.stats.HPCurrent << "/" << m.stats.HPMax << endl;
    out << "Ataque: " << m.stats.attack << endl;
    out << "Defensa: " << m.stats.defense << endl;
    out << "Fecha registro: " << (int)m.registerDate.fecha.year() << "-" << (unsigned)m.registerDate.fecha.month() << "-" << (unsigned)m.registerDate.fecha.day() << endl;
    return out;
}