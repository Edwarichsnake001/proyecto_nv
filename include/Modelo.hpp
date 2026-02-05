#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include "../json.hpp"

using json = nlohmann::json;
using namespace std;

struct Resultado
{
    vector<string> ruta;
    int operaciones;
    string tipo;
};

class Modelo
{
private:
    map<string, list<string>> adj;
    map<string, vector<string>> parrafos;

public:
    void cargarDatos(string ruta);
    void guardarProgreso(int slot, string nodoActual, const vector<string> &historial);
    bool cargarProgreso(int slot, string &nodoActual, vector<string> &historial);
    bool existeSlot(int slot); // Para saber si mostrar "Vacío" en el menú

    Resultado ejecutarBFS(string inicio);
    Resultado ejecutarDFS(string inicio);
    // En la sección public de la clase Modelo:
    vector<string> getOpciones(string id);
    bool existeConexion(string actual, string destino);

    vector<string> getContenido(string id) { return parrafos[id]; }
};