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
            cout << "\n" << texto << endl;
            return;
        }
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(40));
    }
    cout << endl;
}

void Controlador::iniciarJuego()
{
    string nodoActual = "inicio";
    bool escenaN = true;

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
            cout << "\n--- FIN DE LA HISTORIA ---" << endl;
            break; //
        }

        // FASE 2: Selección de opciones
        int seleccion = 0;
        bool eligiendo = true;
        while (eligiendo)
        {
            mostrarPantalla(parrafos.back(), opciones, seleccion, false, true);
            char c = _getch();

            if (c == -32 || c == 0)
            { // Teclas especiales (Flechas)
                c = _getch();
                if (c == TECLA_ARRIBA)
                    seleccion = (seleccion > 0) ? seleccion - 1 : opciones.size() - 1;
                if (c == TECLA_ABAJO)
                    seleccion = (seleccion < (int)opciones.size() - 1) ? seleccion + 1 : 0;
            }
            else if (c == TECLA_ENTER)
            {
                nodoActual = opciones[seleccion];
                escenaN = true;
                eligiendo = false; // Salir del bucle de selección para ir al siguiente nodo
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
