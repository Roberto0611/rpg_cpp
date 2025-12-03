// codigo generado 100% con inteligencia artificial, este codigo convierte el csv de pokemon al formato que queremos para nuestro juego
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <random>
#include <ctime>

std::string mapType(const std::string& t) {
    if (t == "Fire") return "Fuego";
    if (t == "Water") return "Agua";
    if (t == "Grass") return "Planta";
    if (t == "Ground") return "Tierra";
    return "Neutro";
}

// Genera fecha aleatoria entre 2023-01-01 y 2025-12-31
std::string randomDate() {
    std::tm start = {};
    std::tm end = {};

    start.tm_year = 2023 - 1900;
    start.tm_mon = 0;
    start.tm_mday = 1;

    end.tm_year = 2025 - 1900;
    end.tm_mon = 11;
    end.tm_mday = 31;

    time_t start_t = std::mktime(&start);
    time_t end_t = std::mktime(&end);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<long> dist(0, end_t - start_t);

    time_t random_time = start_t + dist(rng);
    std::tm* date = std::localtime(&random_time);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", date);
    return buffer;
}

int main() {
    std::ifstream input("pokemon_original.csv");
    std::ofstream output("bestiario.csv");

    if (!input.is_open() || !output.is_open()) {
        std::cout << "Error abriendo archivos\n";
        return 1;
    }

    std::unordered_set<int> usedIDs;

    std::string line;
    std::getline(input, line); // saltar encabezado

    while (std::getline(input, line)) {
        std::stringstream ss(line);
        std::string idStr, name, type1, type2, total, hp, atk, def, spatk, spdef, speed, gen, legendary;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, type1, ',');
        std::getline(ss, type2, ',');
        std::getline(ss, total, ',');
        std::getline(ss, hp, ',');
        std::getline(ss, atk, ',');
        std::getline(ss, def, ',');
        std::getline(ss, spatk, ',');
        std::getline(ss, spdef, ',');
        std::getline(ss, speed, ',');
        std::getline(ss, gen, ',');
        std::getline(ss, legendary, ',');

        int id = std::stoi(idStr);

        // Si el ID ya fue usado → lo saltamos
        if (usedIDs.count(id)) {
            continue;
        }

        usedIDs.insert(id);

        std::string mappedType = mapType(type1);
        std::string date = randomDate();

        output << id << ","
               << name << ","
               << mappedType << ","
               << hp << ","
               << atk << ","
               << def << ","
               << date << "\n";
    }

    std::cout << "bestiario.csv generado sin IDs repetidos.\n";
    return 0;
}
