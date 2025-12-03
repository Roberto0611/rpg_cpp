#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <vector>

#include "Utils.h"
#include "Monster.h"
#include "Stats.h"

Element stringtoelement(const string& elemento){
    if (elemento == "Fuego") return Element::Fuego;
    if (elemento == "Agua") return Element::Agua;
    if (elemento == "Planta") return Element::Planta;
    if (elemento == "Tierra") return Element::Tierra;
    return Element::Neutro;
}


vector<Monster> Utils::reader(const string& file){
    vector<Monster> monsters;
    string line;
    char delimitador = ',';
    ifstream in(file);
    if (!in) throw runtime_error("No se pudo abrir el csv");
    getline(in, line); // saltar encabezado

    while (getline(in, line)){
        Stats stats;
        stringstream stream(line);
        string temp;

        getline(stream, temp, delimitador); //id
        int id = stoi(temp);

        getline(stream, temp, delimitador); //nombre
        string nombre = temp;

        getline(stream, temp, delimitador); // Elemento
        Element elemento = stringtoelement(temp);

        getline(stream, temp, delimitador); // hp
        stats.HPMax = stoi(temp);
        stats.HPCurrent = stats.HPMax;

        getline(stream, temp, delimitador); // ataque
        stats.attack = stoi(temp);

        getline(stream, temp, delimitador); // defensa
        stats.defense = stoi(temp);

        getline(stream, temp); // fecha
        FechaRegistro fecha = parseFecha(temp);

        Monster monster(id, nombre, elemento, stats, fecha);
        monsters.push_back(monster);
    }
    
    return monsters;
};