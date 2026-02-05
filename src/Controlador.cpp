#include "Controlador.hpp"
#include <conio.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Controlador::lecturaLenta(string texto)
{
    for (char c : texto)
    {
        if (_kbhit())
        {
            _getch();
            system("cls");
            cout << "==========================================" << endl;
            cout << "            EL MISTERIO DE ELIZA          " << endl;
            cout << "==========================================" << endl;
            cout << "\n"
                 << texto << endl;
            return;
        }
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(40));
    }
    cout << endl;
}

int Controlador::gestionarSeleccion(string titulo, vector<string> opciones)
{
    int seleccion = 0;
    while (true)
    {
        system("cls");
        cout << "==========================================" << endl;
        cout << "          " << titulo << endl;
        cout << "==========================================" << endl;
        cout << "\n";

        for (int i = 0; i < (int)opciones.size(); i++)
        {
            if (i == seleccion)
                cout << "  > [ " << opciones[i] << " ] <" << endl;
            else
                cout << "      " << opciones[i] << endl;
        }

        char c = _getch();
        if (c == -32 || c == 0)
        { // Flechas
            c = _getch();
            if (c == TECLA_ARRIBA)
                seleccion = (seleccion > 0) ? seleccion - 1 : opciones.size() - 1;
            if (c == TECLA_ABAJO)
                seleccion = (seleccion < (int)opciones.size() - 1) ? seleccion + 1 : 0;
        }
        else if (c == TECLA_ENTER)
        {
            return seleccion;
        }
    }
}

int Controlador::mostrarMenuPrincipal()
{
    system("cls");
    vector<string> opciones = {"Nueva Partida", "Cargar Partida", "Salir"};
    return gestionarSeleccion("EL MISTERIO DE ELIZA", opciones);
}

int Controlador::mostrarMenuSlots(string titulo)
{
    vector<string> slots;
    for (int i = 1; i <= 5; i++)
    {
        string estado = motor.existeSlot(i) ? "[OCUPADO]" : "[VACIO]";
        slots.push_back("Slot " + to_string(i) + " " + estado);
    }
    slots.push_back("REGRESAR");

    int seleccion = 0;
    while (true)
    {
        system("cls");
        cout << "=== " << titulo << " ===\n\n";
        for (int i = 0; i < (int)slots.size(); i++)
        {
            if (i == seleccion)
                cout << "  > " << slots[i] << " <\n";
            else
                cout << "    " << slots[i] << "\n";
        }

        char c = _getch();
        if (c == -32 || c == 0)
        {
            c = _getch();
            if (c == TECLA_ARRIBA) // Cambiado 72 por la constante
                seleccion = (seleccion > 0) ? seleccion - 1 : slots.size() - 1;
            if (c == TECLA_ABAJO) // Cambiado 80 por la constante
                seleccion = (seleccion < (int)slots.size() - 1) ? seleccion + 1 : 0;
        }
        else if (c == TECLA_ENTER) // Cambiado 13 por la constante
        {
            if (seleccion == 5)
                return -1;
            return seleccion + 1;
        }
    }
}

void Controlador::generarReporteFinal()
{
    cout << "\n==========================================" << endl;
    cout << "       REPORTE TECNICO DE LA AVENTURA     " << endl;
    cout << "==========================================" << endl;

    // Ejecutar algoritmos de búsqueda desde el inicio
    Resultado resBFS = motor.ejecutarBFS("inicio");
    Resultado resDFS = motor.ejecutarDFS("inicio");

    cout << "\n1. ANALISIS DE EFICIENCIA (BFS):" << endl;
    cout << "- Nodos visitados por Eliza: " << rutaJugador.size() << endl;
    cout << "- Camino mas corto posible: " << resBFS.ruta.size() << " nodos." << endl;

    cout << "\n2. EXPLORACION DEL GRAFO (DFS):" << endl;
    cout << "- Operaciones realizadas por el motor: " << resDFS.operaciones << endl;
    cout << "- Total de escenas existentes: " << resDFS.ruta.size() << endl;

    float porcentaje = ((float)rutaJugador.size() / (float)resDFS.ruta.size()) * 100;
    cout << "- Porcentaje de historia descubierta: " << porcentaje << "%" << endl;
    cout << "==========================================" << endl;

    // Pausa para que el usuario pueda leer el reporte
    cout << "\nPresiona cualquier tecla para salir...";
    _getch();
}

void Controlador::iniciarJuego()
{
    int opcionPrincipal = mostrarMenuPrincipal();
    string nodoActual = "inicio";
    bool escenaN = true;

    if (opcionPrincipal == 2)
        return; // Salir

    if (opcionPrincipal == 1)
    {
        int slot = mostrarMenuSlots("CARGAR PARTIDA");
        if (slot > 0 && slot <= 5)
        {
            if (motor.cargarProgreso(slot, nodoActual, rutaJugador))
            {
                // DESACTIVAMOS la lectura lenta para el primer nodo cargado
                escenaN = false;
            }
            else
            {
                cout << "Error al cargar. Iniciando desde cero...";
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
        else
        {
            return;
        }
    }

    while (true)
    {
        vector<string> parrafos = motor.getContenido(nodoActual);
        vector<string> opciones = motor.getOpciones(nodoActual);

        // FASE 1: Recorrer párrafos con ENTER
        for (int i = 0; i < (int)parrafos.size(); i++)
        {
            mostrarPantalla(parrafos[i], opciones, 0, escenaN, false);
            // Esperar Enter y nada más que Enter
            while (_getch() != TECLA_ENTER)
                ;
            escenaN = true;
        }

        // Si el nodo no tiene opciones (Final de la historia), salimos del bucle principal
        if (opciones.empty())
        {
            mostrarPantalla(parrafos.back(), opciones, 0, false, false);
            cout << "\n===== FIN DE LA HISTORIA ====" << endl;
            generarReporteFinal();
            break;
        }

        // FASE 2: Selección de opciones
        int seleccion = 0;
        bool eligiendo = true;

        // 1. CREAR una copia de las opciones y agregar el botón de guardado
        vector<string> opcionesMenu = opciones;
        opcionesMenu.push_back("GUARDAR PARTIDA");

        while (eligiendo)
        {
            // 2. CAMBIAR: Usar 'opcionesMenu' para que el usuario vea la opción
            mostrarPantalla(parrafos.back(), opcionesMenu, seleccion, false, true);
            char c = _getch();

            if (c == -32 || c == 0)
            {
                c = _getch();
                if (c == TECLA_ARRIBA)
                    seleccion = (seleccion > 0) ? seleccion - 1 : opcionesMenu.size() - 1;
                if (c == TECLA_ABAJO)
                    seleccion = (seleccion < (int)opcionesMenu.size() - 1) ? seleccion + 1 : 0;
            }
            else if (c == TECLA_ENTER)
            {
                // 3. LOGICA: Si eligió el último índice, es "Guardar Partida"
                if (seleccion == (int)opcionesMenu.size() - 1)
                {
                    int slot = mostrarMenuSlots("SELECCIONA SLOT");
                    if (slot != -1)
                    {
                        motor.guardarProgreso(slot, nodoActual, rutaJugador);
                        vector<string> opcionesPost = {"Continuar Jugando", "Salir al Menu Principal"};
                        int despues = gestionarSeleccion("PARTIDA GUARDADA EN SLOT " + to_string(slot), opcionesPost);
                        if (despues == 1) // El índice 1 es "Salir al Menu Principal"
                        {
                            return;
                        }
                        cout << "\n>> Partida Guardada <<";
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                }
                else
                {
                    // Opción normal de la historia
                    nodoActual = opciones[seleccion];
                    rutaJugador.push_back(nodoActual);
                    escenaN = true;
                    eligiendo = false;
                }
            }
        }
    }
}

void Controlador::mostrarPantalla(string texto, const vector<string> &opciones, int seleccion, bool animar, bool mostrarMenu)
{
    system("cls");
    cout << "==========================================" << endl;
    cout << "            EL MISTERIO DE ELIZA          " << endl;
    cout << "==========================================" << endl;
    cout << "\n";

    if (animar)
        lecturaLenta(texto);

    if (mostrarMenu)
    {
        cout << "\n------------------------------------------" << endl;
        for (int i = 0; i < (int)opciones.size(); ++i)
        {
            if (i == seleccion)
                cout << "  > [ " << opciones[i] << " ] <" << endl;
            else
                cout << "      " << opciones[i] << endl;
        }
    }
    else
    {
        cout << "\n\n-- Presiona [ENTER] para continuar --" << endl;
    }
}
