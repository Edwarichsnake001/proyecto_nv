#include "include/Controlador.hpp"
#include <conio.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include "Controlador.hpp"

using namespace std;

void Controlador::lecturaLenta(string texto)
{
    for (char c : texto)
    {
        if (_kbhit())
        {
            _getch();
            system("cls");
            cout << "====================================" << texto << endl;
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
        vector<string> opciones = motor.getOpciones(nodoActual);

        mostrarPantalla(motor.getContenido(nodoActual), opciones, 0, escenaN, false);
        while (_getch() != TECLA_ENTER)
            ;

        if (opciones.empty())
        {
            break;
        }

        int seleccion = 0;
        while (true)
        {
            mostrarPantalla(motor.getContenido(nodoActual), opciones, seleccion, false, true);
            char c = _getch();
            if (c == -32 || c == 0)
            {
                c = _getch();
                if (c == TECLA_ARRIBA)
                    seleccion = (seleccion > 0) ? seleccion - 1 : opciones.size() - 1;
                if (c == TECLA_ABAJO)
                    seleccion = (seleccion < (int)opciones.size() - 1) ? seleccion + 1 : 0;
            }
            else if (c = TECLA_ENTER)
            {
                nodoActual = opciones[seleccion];
                escenaN = true;
                break;
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
    else
        cout << texto << endl;

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
