#include "../include/Player.h"
#include "Stats.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor
Player::Player(string name, Stats stats)
{
    this->name = name;
    this->stats = stats;
    this->stats.HPCurrent = this->stats.HPMax;
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

string Player::getName(){
    return this->name;
}

int Player::getDefense(){
    return this->stats.defense;
}

int Player::getHP(){
    return this->stats.HPCurrent;
}

void Player::setHP(int netDamage){
    if(netDamage > getHP()){
        netDamage = getHP();
    }

    this->stats.HPCurrent -= netDamage;
}

void Player::takeDamage(int damage)
{
    int netDamage = max(1, damage - getDefense()/2);
    setHP(netDamage);
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