#include "Modelo.hpp"
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <set>

void Modelo::cargarDatos(string ruta)
{
    ifstream archivo(ruta);
    json j;
    archivo >> j;
    for (auto &item : j["historia"])
    {
        string id = item["id"];
        // Cambiado para usar el array de parrafos del JSON
        if (item.contains("parrafos"))
        {
            for (string p : item["parrafos"])
            {
                parrafos[id].push_back(p);
            }
        }
        for (string opcion : item["opciones"])
        {
            adj[id].push_back(opcion);
        }
    }
}

void Modelo::guardarProgreso(int slot, string nodoActual, const vector<string> &historial)
{
    json guardado;
    guardado["nodo_actual"] = nodoActual;
    guardado["ruta_jugador"] = historial;

    // Generamos el nombre: partida_1.json, partida_2.json...
    string nombreArchivo = "partida_" + to_string(slot) + ".json";
    ofstream archivo(nombreArchivo);
    if (archivo.is_open())
    {
        archivo << std::setw(4) << guardado << endl;
        archivo.close();
    }
}

bool Modelo::cargarProgreso(int slot, string &nodoActual, vector<string> &historial)
{
    string nombreArchivo = "partida_" + to_string(slot) + ".json";
    ifstream archivoLectura(nombreArchivo);

    // Si el archivo de guardado NO existe, lo creamos automáticamente
    if (!archivoLectura.is_open())
    {
        json nuevoGuardado;
        nuevoGuardado["nodo_actual"] = "inicio";
        nuevoGuardado["ruta_jugador"] = json::array({"inicio"});

        ofstream archivoEscritura(nombreArchivo);
        if (archivoEscritura.is_open())
        {
            archivoEscritura << std::setw(4) << nuevoGuardado << endl;
            archivoEscritura.close();
        }

        // Devolvemos los valores iniciales para que el juego continúe
        nodoActual = "inicio";
        historial = {"inicio"};
        return true;
    }

    // Si el archivo existe pero está vacío, evitamos el error de parseo (Error 101)
    if (archivoLectura.peek() == ifstream::traits_type::eof())
    {
        archivoLectura.close();
        return false;
    }

    try
    {
        json j;
        archivoLectura >> j;
        nodoActual = j["nodo_actual"];
        historial = j["ruta_jugador"].get<vector<string>>();
        archivoLectura.close();
        return true;
    }
    catch (json::parse_error &e)
    {
        return false; // El archivo de guardado existe pero está corrupto
    }
}

bool Modelo::existeSlot(int slot)
{
    string nombre = "partida_" + to_string(slot) + ".json";
    ifstream archivo(nombre);
    // Solo existe si el archivo abre y tiene contenido real (no solo basura o vacío)
    return archivo.is_open() && archivo.peek() != ifstream::traits_type::eof();
}

// ALGORITMO BFS (Búsqueda en Anchura)
Resultado Modelo::ejecutarBFS(string inicio)
{
    Resultado res;
    res.tipo = "BFS";
    res.operaciones = 0;
    queue<string> q;
    set<string> visitado;

    q.push(inicio);
    visitado.insert(inicio);

    while (!q.empty())
    {
        string actual = q.front();
        q.pop();
        res.ruta.push_back(actual);
        res.operaciones++;

        for (string vecino : adj[actual])
        {
            res.operaciones++;
            if (visitado.find(vecino) == visitado.end())
            {
                visitado.insert(vecino);
                q.push(vecino);
            }
        }
    }
    return res;
}

// ALGORITMO DFS (Búsqueda en Profundidad)
Resultado Modelo::ejecutarDFS(string inicio)
{
    Resultado res;
    res.tipo = "DFS";
    res.operaciones = 0;
    stack<string> s;
    set<string> visitado;

    s.push(inicio);

    while (!s.empty())
    {
        string actual = s.top();
        s.pop();

        if (visitado.find(actual) == visitado.end())
        {
            visitado.insert(actual);
            res.ruta.push_back(actual);
            res.operaciones++;

            for (string vecino : adj[actual])
            {
                res.operaciones++;
                s.push(vecino);
            }
        }
    }
    return res;
}

vector<string> Modelo::getOpciones(string id)
{
    vector<string> lista;
    if (adj.count(id))
    {
        for (const string &vecino : adj[id])
        {
            lista.push_back(vecino);
        }
    }
    return lista;
}

bool Modelo::existeConexion(string actual, string destino)
{
    if (adj.count(actual))
    {
        for (const string &vecino : adj[actual])
        {
            if (vecino == destino)
                return true;
        }
    }
    return false;
}
