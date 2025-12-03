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

public:
    // Constructor
    Player(string name,Stats stats);

    // Métodos
    int attack();
    int getDefense();
    int getHP();
    void setHP(int netDamage);
    void defend();
    void takeDamage(int damage);
    string getName();
    // void usarItem(int indice);

    // Getters
    Stats getStats() const;
    bool isDefending() const;
    const vector<Item> &getInventory() const;
};