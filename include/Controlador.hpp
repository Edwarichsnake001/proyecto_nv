#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h> // Para las teclas ASCII
#include "Modelo.hpp"

using namespace std;

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13

class Controlador
{
private:
    Modelo &motor;

    void mostrarPantalla(string texto, const vector<string> &opciones, int seleccion)
    {
        system("cls");
        cout << "==========================================" << endl;
        cout << "            PROYECTO: AVENTURA            " << endl;
        cout << "==========================================" << endl;
        cout << "\n"
             << texto << "\n"
             << endl;

        for (int i = 0; i < opciones.size(); ++i)
        {
            if (i == seleccion)
            {
                cout << "  > [ " << opciones[i] << " ] <" << endl;
            }
            else
            {
                cout << "      " << opciones[i] << endl;
            }
        }
        cout << "\n(Flechas para navegar | Enter para elegir)" << endl;
    }

public:
    Controlador(Modelo &m) : motor(m) {}
    void iniciarJuego()
    {
        string nodoActual = "inicio";

        while (true)
        {
            vector<string> opciones = motor.getOpciones(nodoActual);

            if (opciones.empty())
            {
                system("cls");
                cout << motor.getContenido(nodoActual) << endl;
                cout << "\n--- FIN DE LA PARTIDA ---" << endl;
                break;
            }

            int seleccion = 0;
            while (true)
            {
                mostrarPantalla(motor.getContenido(nodoActual), opciones, seleccion);

                char c = getch();
                if (c == 0 || c == -32)
                {
                    c = getch();
                    if (c == TECLA_ARRIBA)
                        seleccion = (seleccion > 0) ? seleccion - 1 : opciones.size() - 1;
                    if (c == TECLA_ABAJO)
                        seleccion = (seleccion < opciones.size() - 1) ? seleccion + 1 : 0;
                }
                else if (c == TECLA_ENTER)
                {
                    nodoActual = opciones[seleccion];
                    break;
                }
            }
        }
    }
};