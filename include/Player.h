// Clase Jugador (Manejo de inventario)
#pragma once
#include <vector>
#include "Stats.h"
#include "Item.h"

using namespace std;

class Player
{
private:
    Stats stats;
    vector<Item> inventory;
    bool defending;

public:
    // Constructor
    Player(int hpMax, int attack, int defense);

    // Métodos
    int attack();
    void defend();
    void takeDamage(int danioEntrante);
    // void usarItem(int indice);

    // Getters
    Stats getStats() const;
    bool isDefending() const;
    const vector<Item> &getInventory() const;
};