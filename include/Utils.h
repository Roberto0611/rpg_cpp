// Funciones herramientas (Split, Random, Validaciones)
#pragma once
#include "Stats.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Monster.h"

using namespace std;

// Función para parsear fecha desde string (formato YYYY-MM-DD o YYYY/MM/DD)
inline FechaRegistro parseFecha(const std::string& fechaStr) {
	FechaRegistro res;
	std::string s = fechaStr;

	// eliminar espacios al inicio/fin
	auto not_space = [](int ch){ return !std::isspace(ch); };
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
	s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());

	// normalizar separadores a '-'
	std::replace(s.begin(), s.end(), '/', '-');

	int y=1970, m=1, d=1;
	char sep1=0, sep2=0;
	std::istringstream iss(s);
	if ((iss >> y >> sep1 >> m >> sep2 >> d) && sep1=='-' && sep2=='-') {
	} else {
		// intentar detectar con sscanf
		if (std::sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d) != 3) {
			// fallback
			y = 1970; m = 1; d = 1;
		}
	}

	using namespace std::chrono;
	year_month_day ymd = year{y}/month{static_cast<unsigned>(m)}/day{static_cast<unsigned>(d)};
	res.fecha = ymd;
	return res;
}

// Clase Utils para lectura de archivos y otras utilidades
class Utils{
    public:
    vector<Monster> reader(const string& file);
};
