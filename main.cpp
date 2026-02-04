#include <iostream>
#include <iomanip> // Para que la tabla se vea bonita
#include "include/Modelo.hpp"
#include "include/Controlador.hpp"

using namespace std;

// Función auxiliar para imprimir los resultados de forma clara
void imprimirResultado(const Resultado& res) {
    cout << "\n==========================================" << endl;
    cout << " ANALISIS DE RECORRIDO: " << res.tipo << endl;
    cout << "==========================================" << endl;
    
    cout << "Orden de visita: ";
    for (size_t i = 0; i < res.ruta.size(); ++i) {
        cout << res.ruta[i] << (i == res.ruta.size() - 1 ? "" : " -> ");
    }
    
    cout << "\n\nDetalles tecnicos:" << endl;
    cout << "- Nodos explorados: " << res.ruta.size() << endl;
    cout << "- Operaciones realizadas: " << res.operaciones << endl;
    cout << "- Complejidad teorica: O(V + E)" << endl;
    cout << "------------------------------------------" << endl;
}

int main() {
   Modelo motor; // Instancia del modelo
    
    try {
        motor.cargarDatos("data/historia.json"); //
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Aquí es donde saltaba el error:
    Controlador juego(motor); 
    juego.iniciarJuego();

    /*

    // 3. Ejecutar y comparar algoritmos desde el punto inicial
    string puntoInicial = "inicio";

    // Prueba de BFS (Anchura)
    Resultado resBFS = motor.ejecutarBFS(puntoInicial);
    imprimirResultado(resBFS);

    // Prueba de DFS (Profundidad)
    Resultado resDFS = motor.ejecutarDFS(puntoInicial);
    imprimirResultado(resDFS);

    // 4. Seccion de comparacion (Requisito del proyecto)
    cout << "\n >>> COMPARATIVA DE EFICIENCIA <<<" << endl;
    cout << left << setw(15) << "Metodo" << setw(15) << "Operaciones" << "Resultado" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << left << setw(15) << "BFS" << setw(15) << resBFS.operaciones << "Encuentra finales mas cercanos." << endl;
    cout << left << setw(15) << "DFS" << setw(15) << resDFS.operaciones << "Explora rutas completas." << endl;

    cout << "\nProceso de Arquitectura de Datos finalizado." << endl;*/
    
    return 0;
}