#include "Modelo.hpp"
#include <fstream>
#include <queue>
#include <stack>
#include <set>

void Modelo::cargarDatos(string ruta) {
    ifstream archivo(ruta);
    json j;
    archivo >> j;
    for (auto& item : j["historia"]) {
        string id = item["id"];
        textos[id] = item["texto"];
        for (string opcion : item["opciones"]) {
            adj[id].push_back(opcion);
        }
    }
}

// ALGORITMO BFS (Búsqueda en Anchura)
Resultado Modelo::ejecutarBFS(string inicio) {
    Resultado res;
    res.tipo = "BFS";
    res.operaciones = 0;
    queue<string> q;
    set<string> visitado;

    q.push(inicio);
    visitado.insert(inicio);

    while (!q.empty()) {
        string actual = q.front();
        q.pop();
        res.ruta.push_back(actual);
        res.operaciones++; 

        for (string vecino : adj[actual]) {
            res.operaciones++; 
            if (visitado.find(vecino) == visitado.end()) {
                visitado.insert(vecino);
                q.push(vecino);
            }
        }
    }
    return res;
}

// ALGORITMO DFS (Búsqueda en Profundidad)
Resultado Modelo::ejecutarDFS(string inicio) {
    Resultado res;
    res.tipo = "DFS";
    res.operaciones = 0;
    stack<string> s;
    set<string> visitado;

    s.push(inicio);

    while (!s.empty()) {
        string actual = s.top();
        s.pop();

        if (visitado.find(actual) == visitado.end()) {
            visitado.insert(actual);
            res.ruta.push_back(actual);
            res.operaciones++;

            for (string vecino : adj[actual]) {
                res.operaciones++;
                s.push(vecino);
            }
        }
    }
    return res;
}