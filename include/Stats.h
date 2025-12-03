// Structs compartidos (Stats, Fechas, Enums)
// definiciones pequeñas que usan tanto el Jugador como el Monstruo. Sirve para cumplir el requisito de Enums y Composición.

// enum class Elemento
// enum class TipoItem
// Struct FechaRegistro
// Struct Stats (Variables: hpActual, hpMax, ataque, defensa, velocidad.)
#pragma once
#include <chrono>


// enums
enum class Element{
    Fuego,
    Agua,
    Planta,
    Tierra,
    Neutro
};

enum class ItemType{
    Curacion,
    BuffAtaque,
    BuffDefensa
};

struct FechaRegistro {
    std::chrono::year_month_day fecha; 
};

// struct
struct Stats{
    int HPCurrent;
    int HPMax;
    int attack;
    int defense;
    int id;
    std::string name, tipo, date, elemento, fecha;
};