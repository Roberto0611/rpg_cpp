// archivo principal para iniciar el juego, solo debe de llamar al manager

#include <iostream>
using namespace std;

#include "Monster.h"
#include "Utils.h"

int main() {

    std::cout << "--- PRUEBA: CLASE MONSTER ---\n";
    Stats charmeleonStats = {
        .HPCurrent = 0,    
        .HPMax = 58,      
        .attack = 64,     
        .defense = 58,    
    };

    FechaRegistro fecha = parseFecha("2025-03-12");

    Monster charmeleon(
        5,
        "Charmeleon",  
        Element::Fuego,
        charmeleonStats,            
        fecha                       
    );

    cout << charmeleon.getName() << endl;
    cout << charmeleon.getHP() << endl;
    cout << charmeleon.getDefense() << endl;
    charmeleon.takeDamage(40);
    cout << charmeleon.getHP() << endl;

    cout << charmeleon << endl;

    return 0;
}