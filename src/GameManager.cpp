#include <string>
#include <iostream>
#include <limits>
#include "GameManager.h"

// constructor
GameManager::GameManager(const Player &player) : player(player)
{
    // player ya está inicializado mediante la lista de inicialización
    this->round = 0;
}

// funcion principal a ejecutar
void GameManager::execute()
{
    initGame();
    loadEnemies();

    // Loop principal del juego
    while (player.getHP() > 0)
    {
        this->round++;
        std::cout << "\n\n";
        std::cout << "======================================================\n";
        std::cout << "                   RONDA " << this->round << "\n";
        std::cout << "======================================================\n\n";

        Monster enemy = selectEnemie();
        bool victory = combat(enemy);

        if (!victory)
        {
            // El jugador perdió
            std::cout << "\nSobreviviste " << (this->round - 1) << " rondas.\n";
            break;
        }

        // El jugador ganó, continuar a la siguiente ronda
        std::cout << "\nPresiona ENTER para continuar a la siguiente ronda...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    std::cout << "\n======================================================\n";
    std::cout << "            FIN DEL JUEGO\n";
    std::cout << "======================================================\n";
}

// cargar los datos del csv
void GameManager::loadEnemies()
{
    Utils utils;
    try
    {
        this->enemies = utils.reader("data/bestiario.csv");
        cout << "datos cargados: " << this->enemies.size() << " enemigos" << endl;
    }
    catch (const runtime_error &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

int GameManager::getRound()
{
    return this->round;
}

void GameManager::initGame()
{
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

    std::cout << "\n======================================================\n";
    std::cout << "JUGADOR: " << player.getName() << "\n";
    std::cout << "======================================================\n";
    std::cout << "HP:      " << player.getHP() << " / " << player.getStats().HPMax << "\n";
    std::cout << "Ataque:  " << player.getStats().attack << "\n";
    std::cout << "Defensa: " << player.getStats().defense << "\n";
    std::cout << "======================================================\n\n";

    std::cout << "Presiona ENTER para seleccionar enemigo...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// algoritmo de seleccion de enemigo
Monster GameManager::selectEnemie()
{
    // int actualRound = getRound();
    int power;
    vector<Monster> enemiesPool;

    if (enemies.empty())
    {
        throw runtime_error("No hay enemigos disponibles");
    }

    for (Monster actualEenemie : enemies)
    {
        // hacer el calculo de poder para dividir el pool
        power = actualEenemie.getHP() + actualEenemie.getAttack() + actualEenemie.getDefense();
        cout << power << endl;
    }

    std::cout << "\n======================================================\n";
    std::cout << "ENEMIGO SELECCIONADO: " << enemies[0].getName() << "\n";
    std::cout << "======================================================\n";
    std::cout << "HP:      " << enemies[0].getHP() << "\n";
    std::cout << "Ataque:  " << enemies[0].getAttack() << "\n";
    std::cout << "Defensa: " << enemies[0].getDefense() << "\n";
    std::cout << "======================================================\n\n";

    return enemies[0];
}

// sistema de combate
bool GameManager::combat(Monster &enemy)
{
    std::cout << "COMIENZA EL COMBATE\n\n";

    while (player.getHP() > 0 && enemy.isAlive())
    {
        // Mostrar estado actual
        std::cout << "======================================================\n";
        std::cout << player.getName() << " HP: " << player.getHP() << "/" << player.getStats().HPMax;
        std::cout << " | " << enemy.getName() << " HP: " << enemy.getHP() << "\n";
        std::cout << "======================================================\n";

        // Menú de opciones
        std::cout << "\n Que deseas hacer\n";
        std::cout << "1. Atacar\n";
        std::cout << "2. Defender\n";
        std::cout << "Opcion: ";

        int opcion;
        std::cin >> opcion;

        int playerDamage = 0;

        // Turno del jugador
        if (opcion == 1)
        {
            playerDamage = player.attack();
            int damageDealt = max(1, playerDamage - enemy.getDefense() / 2);
            enemy.setHP(damageDealt);
            std::cout << "\n"
                      << player.getName() << " ataca y causa " << damageDealt << " de dano \n";
        }
        else if (opcion == 2)
        {
            player.defend();
            std::cout << "\n"
                      << player.getName() << " se defiende \n";
        }

        // Verificar si el enemigo sigue vivo
        if (!enemy.isAlive())
        {
            std::cout << "\n Has derrotado a " << enemy.getName() << "!\n";
            std::cout << "======================================================\n";
            std::cout << "VICTORIA\n";
            std::cout << "======================================================\n";
            break;
        }

        // Turno del enemigo
        std::cout << "\n"
                  << enemy.getName() << " ataca!\n";
        int enemyDamage = enemy.getAttack();

        if (player.isDefending())
        {
            int damageReceived = max(1, enemyDamage - player.getDefense());
            player.setHP(damageReceived);
            std::cout << player.getName() << " recibe " << damageReceived << " de daño (defendiendo)!\n";
        }
        else
        {
            player.takeDamage(enemyDamage);
            int damageReceived = max(1, enemyDamage - player.getDefense() / 2);
            std::cout << player.getName() << " recibe " << damageReceived << " de dano!\n";
        }

        std::cout << "HP actual de " << player.getName() << ": " << player.getHP() << "/" << player.getStats().HPMax << "\n\n";

        // Verificar si el jugador sigue vivo
        if (player.getHP() <= 0)
        {
            std::cout << "\n======================================================\n";
            std::cout << "DERROTA\n";
            std::cout << "======================================================\n";
            std::cout << "Has sido derrotado por " << enemy.getName() << "...\n";
            return false;
        }
    }

    // Si llegamos aquí, el jugador ganó
    return true;
}