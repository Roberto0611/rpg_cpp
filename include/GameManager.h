// Lógica del juego (Loop, Menú, Combate)
#if !defined(GameManager_h)
#define GameManager_h

#include <string>
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Monster.h"

using namespace std;

class GameManager
{
private:
    Player player;
    vector<Monster> enemies;
    int round; // numero de ronda, util para el algoritmo de azar

public:
    // constructor
    GameManager();

    // metodos
    void execute();
    void initGame();
    void loadEnemies();
    int getRound();
    Monster selectEnemie();
    bool combat(Monster &enemy);
    void createPlayer();
    void showRewards();
};

#endif // GameManager_h
