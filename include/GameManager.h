// Lógica del juego (Loop, Menú, Combate)
#if !defined(GameManager_h)
#define GameManager_h

#include <string>
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Monster.h"

using namespace std;

class GameManager{
    private:
    Player player;

    public:
    // constructor
    GameManager(const Player& player);

    // metodos
    void initGame();

};

#endif // GameManager_h
