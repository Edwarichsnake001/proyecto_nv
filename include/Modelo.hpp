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
    map<string, string> textos;

public:
    void cargarDatos(string ruta);
    Resultado ejecutarBFS(string inicio);
    Resultado ejecutarDFS(string inicio);
    // En la sección public de la clase Modelo:
    vector<string> getOpciones(string id);
    bool existeConexion(string actual, string destino);

    string getContenido(string id) { return textos[id]; }
};