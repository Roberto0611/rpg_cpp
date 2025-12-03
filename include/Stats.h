// Structs compartidos (Stats, Fechas, Enums)
// definiciones pequeñas que usan tanto el Jugador como el Monstruo. Sirve para cumplir el requisito de Enums y Composición.

// enum class Elemento
// enum class TipoItem
// Struct FechaRegistro
// Struct Stats (Variables: hpActual, hpMax, ataque, defensa, velocidad.)

#pragma once
#include <chrono>

// enums
enum class Elemento{
    fuego,
    Agua,
    Planta,
    Tierra,
    Neutro
};

enum class TipoItem{
    Curacion,
    BuffAtaque,
    BuffDefensa
};

// struct
struct stats{
    int HPCurrent;
    int HPMax;
    int attack;
    int defense;
};