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
    defending = false;
}


int Player::attack()
{
    return stats.attack;
}

void Player::defend()
{
    defending = true;
}

void Player::takeDamage(int danioEntrante)
{
    if (defending)
    {
        danioEntrante /= 2;
        defending = false;
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

bool Player::isDefending() const
{
    return defending;
}

const vector<Item> &Player::getInventory() const
{
    return inventory;
}