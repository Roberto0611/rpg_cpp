// Definición de Pociones/Objetos
#pragma once
#include <string>
#include "Stats.h"

using namespace std;

struct Item{
    string nombre;
    int potencia;
    int cantidad;
    void getDescription();
};