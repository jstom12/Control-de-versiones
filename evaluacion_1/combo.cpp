#include "combo.h"

string combo::getNombre() const
{
    return nombre;
}

void combo::setNombre(const string &value)
{
    nombre = value;
}

vector<producto> combo::getComponentes() const
{
    return componentes;
}

void combo::setComponentes(const vector<producto> &value)
{
    componentes = value;
}

int combo::getPrecio() const
{
    return precio;
}

void combo::setPrecio(int value)
{
    precio = value;
}

combo::combo()
{

}
