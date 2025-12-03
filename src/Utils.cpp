#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>

#include "Utils.h"
#include "Monster.h"
#include "Stats.h"


void Utils::reader(const string& file){
    string line;
    char delimitador = ',';
    ifstream in(file);
    if (!in) throw runtime_error("No se pudo abrir el csv");
    getline(in, line);

    while (getline(in, line)){
        Stats stats;
        stringstream stream(line);
        string temp;

        getline(stream, temp, delimitador); //id
        stats.id = stoi(temp);


        getline(stream, stats.name, delimitador); //nombre

        getline(stream, stats.elemento, delimitador); // Elemento

        getline(stream, temp, delimitador); // hp
        stats.HPMax = stoi(temp);

        getline(stream, temp, delimitador); // ataque
        stats.attack = stoi(temp);

        getline(stream, temp, delimitador); // defensa
        stats.defense = stoi(temp);

        getline(stream, stats.fecha, delimitador); // fecha

        

    }
};