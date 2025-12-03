#include "Monster.h"
#include <algorithm>

using namespace std;

// constructor
Monster::Monster(int id, string name, Element element, Stats stats, FechaRegistro registerDate){
    this->id = id;
    this->name = name;
    this->element = element;
    this->stats = stats;
    this->registerDate = registerDate;
}

// recibir danio (siempre debe ser minimo 1 si no es ataque - defensa / 2)
