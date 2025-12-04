// Clase Jugador (Manejo de inventario)
#pragma once
#include <vector>
#include "Stats.h"
#include "Item.h"

using namespace std;

class Player
{
private:
    string name;
    Stats stats;
    vector<Item> inventory;
    bool defending;
    bool counterAttackReady; 

public:
    // Constructor
    Player() = default;
    Player(string name,Stats stats);

    // Métodos
    int attack();
    int getDefense();
    int getHP();
    void setHP(int netDamage);
    void heal(int amount);
    void defend();
    void takeDamage(int damage);
    string getName();
    void resetCounterAttack();
    void resetDefending();
    // void usarItem(int indice);

    // Getters
    Stats getStats() const;
    bool isDefending() const;
    bool isCounterAttackReady() const;
    const vector<Item> &getInventory() const;
};