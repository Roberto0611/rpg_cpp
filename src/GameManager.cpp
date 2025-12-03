#include <string>
#include <iostream>
#include <limits>
#include "GameManager.h"

// constructor
GameManager::GameManager(const Player& player) : player(player) {
    // player ya está inicializado mediante la lista de inicialización
    this->round = 0;
}

// funcion principal a ejecutar
void GameManager::execute(){
    initGame();
    loadEnemies();
    selectEnemie();
}

// cargar los datos del csv
void GameManager::loadEnemies(){
    Utils utils;
    try {
        this->enemies = utils.reader("data/bestiario.csv");
        cout << "datos cargados: " << this->enemies.size() << " enemigos" << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int GameManager::getRound(){
    return this->round;
}

void GameManager::initGame(){
    std::cout << R"(
======================================================
||                                                  ||
||                  ARENA INFINITA                  ||
||                                                  ||
======================================================
||         (Simulador de Supervivencia Roguelike)   ||
||                                                  ||
|| OBJETIVO: Sobrevivir la mayor cantidad de rondas ||
||           posible con recursos limitados.        ||
||                                                  ||
======================================================
)" << '\n';

std::cout << "Presiona ENTER para continuar...";
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

// algoritmo de seleccion de enemigo
Monster GameManager::selectEnemie(){
    int actualRound = getRound();
    int power;
    vector<Monster> enemiesPool;
    
    if (enemies.empty()) {
        throw runtime_error("No hay enemigos disponibles");
    }

    for(Monster actualEenemie : enemies){
        // hacer el calculo de poder para dividir el pool
        power = actualEenemie.getHP() + actualEenemie.getAttack() + actualEenemie.getDefense();
        cout << power << endl;

        
    }
    
    cout << "Enemigo seleccionado: " << enemies[0].getName() << endl;
    return enemies[0];
}