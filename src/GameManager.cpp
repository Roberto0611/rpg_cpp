#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <thread>
#include <chrono>
#include "GameManager.h"
#include "Player.h"

// constructor
GameManager::GameManager()
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

        // El jugador ganó, curación entre rondas (25% del HP máximo)
        int currentHP = player.getHP();
        int maxHP = player.getStats().HPMax;
        int healAmount = maxHP * 0.25;
        
        if (currentHP < maxHP)
        {
            player.heal(healAmount);
            int newHP = player.getHP();
            int actualHeal = newHP - currentHP;
            
            std::cout << "\n[+] " << player.getName() << " se recupera +" << actualHeal << " HP\n";
            std::cout << "HP: " << currentHP << " -> " << newHP << " / " << maxHP << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        showRewards();

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

// crear jugador
void GameManager::createPlayer(){
    std::string Pname;
    cout << "Para comenzar ingresa tu nombre: ";
    cin >> Pname;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer después de leer nombre

    Stats playerStats = {
        .HPCurrent = 0,
        .HPMax = 100,
        .attack = 45,
        .defense = 35,
    };

    this->player = Player(Pname, playerStats);
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

    createPlayer();

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
    int actualRound = getRound();
    int power;
    vector<Monster> pool1;
    vector<Monster> pool2;
    vector<Monster> pool3;

    srand(time(NULL));

    if (enemies.empty())
    {
        throw runtime_error("No hay enemigos disponibles");
    }

    // usar referencia para evitar copias masivas
    for (const Monster& actualEenemie : enemies)
    {
        // hacer el calculo de poder para dividir el pool
        power = actualEenemie.getHP() + actualEenemie.getAttack() + actualEenemie.getDefense();

        // dividir en 3 niveles
        if (power <= 150)
        {
            pool1.push_back(actualEenemie);
        }
        else if(power <= 250)
        {
            pool2.push_back(actualEenemie);
        }
        else
        {
            pool3.push_back(actualEenemie);
        }
    }
    
    //seleccionar el enemigo según la ronda
    // Inicializar con el primer enemigo disponible
    Monster selected = !pool1.empty() ? pool1[0] : (!pool2.empty() ? pool2[0] : pool3[0]);
    
    if (actualRound >= 1 && actualRound <= 3)
    {
        // Rondas iniciales: pool de enemigos débiles
        if (pool1.empty()) {
            selected = pool2.empty() ? pool3[0] : pool2[0];
        } else {
            int num = rand() % pool1.size();
            selected = pool1[num];
        }
    }
    else if (actualRound >= 4 && actualRound <= 7)
    {
        // Rondas medias: pool de enemigos medianos
        if (pool2.empty()) {
            selected = pool1.empty() ? pool3[0] : pool1[0];
        } else {
            int num = rand() % pool2.size();
            selected = pool2[num];
        }
    }
    else
    {
        // Rondas avanzadas: pool de enemigos fuertes
        if (pool3.empty()) {
            selected = pool2.empty() ? pool1[0] : pool2[0];
        } else {
            int num = rand() % pool3.size();
            selected = pool3[num];
        }
    }
    
    std::cout << "\n======================================================\n";
    std::cout << "ENEMIGO SELECCIONADO: " << selected.getName() << "\n";
    std::cout << "======================================================\n";
    std::cout << "HP:      " << selected.getHP() << "\n";
    std::cout << "Ataque:  " << selected.getAttack() << "\n";
    std::cout << "Defensa: " << selected.getDefense() << "\n";
    std::cout << "======================================================\n\n";
    
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return selected;
}

// sistema de combate
bool GameManager::combat(Monster &enemy)
{
    std::cout << "COMIENZA EL COMBATE\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (player.getHP() > 0 && enemy.isAlive())
    {
        // Mostrar estado actual
        std::cout << "======================================================\n";
        std::cout << player.getName() << " HP: " << player.getHP() << "/" << player.getStats().HPMax;
        std::cout << " | " << enemy.getName() << " HP: " << enemy.getHP() << "\n";
        
        // Mostrar si hay contraataque listo
        if (player.isCounterAttackReady())
        {
            std::cout << " [!] CONTRAATAQUE LISTO - Dano +50%";
        }
        std::cout << "\n======================================================\n";

        // Menú de opciones
        std::cout << "\n Que deseas hacer\n";
        std::cout << "1. Atacar";
        if (player.isCounterAttackReady())
        {
            std::cout << " [!] +50% dano";
        }
        std::cout << "\n2. Defender (proximo ataque +50%)\n";
        std::cout << "Opcion: ";

        int opcion;
        std::cin >> opcion;

        int playerDamage = 0;

        // Turno del jugador
        if (opcion == 1)
        {
            playerDamage = player.attack();
            
            // Aplicar bonus de contraataque si está listo
            if (player.isCounterAttackReady())
            {
                playerDamage = playerDamage * 1.5;
                std::cout << "\n[!] CONTRAATAQUE! ";
                player.resetCounterAttack();
            }
            
            // Sistema de críticos (20% de probabilidad)
            int critChance = rand() % 100;
            bool isCritical = critChance < 20;
            
            if (isCritical)
            {
                playerDamage = playerDamage * 2;
                std::cout << "\n[***] GOLPE CRITICO! ";
            }
            
            int damageDealt = max(1, playerDamage - enemy.getDefense() / 2);
            enemy.setHP(damageDealt);
            std::cout << player.getName() << " ataca y causa " << damageDealt << " de dano";
            
            if (isCritical)
            {
                std::cout << " (x2)";
            }
            std::cout << "\n";
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if (opcion == 2)
        {
            player.defend();
            std::cout << "\n[DEFENSA] "
                      << player.getName() << " se defiende y prepara un contraataque!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Verificar si el enemigo sigue vivo
        if (!enemy.isAlive())
        {
            std::cout << "\n Has derrotado a " << enemy.getName() << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "======================================================\n";
            std::cout << "VICTORIA\n";
            std::cout << "======================================================\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }

        // Turno del enemigo
        std::cout << "\n"
                  << enemy.getName() << " ataca!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int enemyDamage = enemy.getAttack();

        if (player.isDefending())
        {
            int damageReceived = max(1, enemyDamage - player.getDefense());
            player.setHP(damageReceived);
            std::cout << player.getName() << " recibe " << damageReceived << " de daño (defendiendo)!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            player.takeDamage(enemyDamage);
            int damageReceived = max(1, enemyDamage - player.getDefense() / 2);
            std::cout << player.getName() << " recibe " << damageReceived << " de dano!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "HP actual de " << player.getName() << ": " << player.getHP() << "/" << player.getStats().HPMax << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Resetear estado de defensa para el próximo turno
        player.resetDefending();

        // Verificar si el jugador sigue vivo
        if (player.getHP() <= 0)
        {
            std::cout << "\n======================================================\n";
            std::cout << "DERROTA\n";
            std::cout << "======================================================\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Has sido derrotado por " << enemy.getName() << "...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return false;
        }
    }

    // Si llegamos aquí, el jugador ganó
    return true;
}

// Sistema de recompensas después de ganar combate
void GameManager::showRewards()
{
    std::cout << "\n======================================================\n";
    std::cout << "           [RECOMPENSA POR VICTORIA!]\n";
    std::cout << "======================================================\n";
    std::cout << "Elige una mejora permanente:\n\n";
    std::cout << "1. [+HP] Vida Maxima +15 HP (y te cura 15 HP)\n";
    std::cout << "2. [ATK] Ataque +3\n";
    std::cout << "3. [DEF] Defensa +3\n";
    std::cout << "4. [HEAL] Curacion Completa (restaura todo el HP)\n";
    std::cout << "\nOpcion: ";

    int choice;
    std::cin >> choice;

    Stats currentStats = player.getStats();

    switch(choice)
    {
        case 1:
            player.increaseMaxHP(15);
            std::cout << "\n[+HP] HP Maximo aumentado!\n";
            std::cout << "HP Maximo: " << currentStats.HPMax << " -> " << player.getStats().HPMax << "\n";
            std::cout << "HP Actual: " << player.getHP() << " / " << player.getStats().HPMax << "\n";
            break;
        
        case 2:
            player.increaseAttack(3);
            std::cout << "\n[ATK] Ataque aumentado!\n";
            std::cout << "Ataque: " << currentStats.attack << " -> " << player.getStats().attack << "\n";
            break;
        
        case 3:
            player.increaseDefense(3);
            std::cout << "\n[DEF] Defensa aumentada!\n";
            std::cout << "Defensa: " << currentStats.defense << " -> " << player.getStats().defense << "\n";
            break;
        
        case 4:
            {
                int currentHP = player.getHP();
                int maxHP = player.getStats().HPMax;
                player.heal(maxHP);
                std::cout << "\n[HEAL] Curacion completa!\n";
                std::cout << "HP: " << currentHP << " -> " << player.getHP() << " / " << maxHP << "\n";
            }
            break;
        
        default:
            std::cout << "\n[X] Opcion invalida. No se otorgo recompensa.\n";
            break;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "======================================================\n";
}