#include "../include/Player.h"
#include <iostream>

using namespace std;

// Constructor
Player::Player(int hpMax, int attack, int defense)
{
    stats.HPMax = hpMax;
    stats.HPCurrent = hpMax;
    stats.attack = attack;
    stats.defense = defense;
    defendiendo = false;
}


int Player::atacar()
{
    return stats.attack;
}

void Player::defender()
{
    defendiendo = true;
}

void Player::recibirDanio(int danioEntrante)
{
    if (defendiendo)
    {
        danioEntrante /= 2;
        defendiendo = false;
    }

    stats.HPCurrent -= danioEntrante;
    if (stats.HPCurrent < 0)
    {
        stats.HPCurrent = 0;
    }
}

// Getters
Stats Player::getStats() const
{
    return stats;
}

bool Player::isDefendiendo() const
{
    return defendiendo;
}

const vector<Item> &Player::getInventario() const
{
    return inventario;
}