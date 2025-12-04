// archivo principal para iniciar el juego, solo debe de llamar al manager

#include <iostream>
using namespace std;

#include "Monster.h"
#include "Player.h"
#include "Utils.h"
#include "GameManager.h"

int main()
{
    GameManager game;
    game.execute();

    return 0;
}