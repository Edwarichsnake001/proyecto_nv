#include <iostream>
#include <windows.h>
#include <iomanip> // Para que la tabla se vea bonita
#include "include/Modelo.hpp"
#include "include/Controlador.hpp"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Modelo motor;

    try
    {
        motor.cargarDatos("data/historia.json");
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    Controlador juego(motor);
    juego.iniciarJuego();

    return 0;
}