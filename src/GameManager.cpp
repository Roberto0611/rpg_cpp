#include <string>
#include <iostream>
#include <limits>
#include "GameManager.h"

// constructor
GameManager::GameManager(const Player& player) : player(player) {
    // player ya está inicializado mediante la lista de inicialización
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