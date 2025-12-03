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
    vector<Item> inventario;
    bool defendiendo;

public:
    // Constructor
    Player(int hpMax, int attack, int defense);

    // Métodos
    int atacar();
    void defender();
    void recibirDanio(int danioEntrante);
    // void usarItem(int indice);

    // Getters
    Stats getStats() const;
    bool isDefendiendo() const;
    const vector<Item> &getInventario() const;
};