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

    void mostrarPantalla(string texto, const vector<string> &opciones, int seleccion, bool animar, bool mostrarMenu);
    void lecturaLenta(string texto);
    

public:
    Controlador(Modelo &m) : motor(m) {}
    void iniciarJuego();
};