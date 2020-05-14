#include "producto.h"

string producto::getNombre() const
{
    return nombre;
}

void producto::setNombre(const string &value)
{
    nombre = value;
}

int producto::getCantidad() const
{
    return cantidad;
}

void producto::setCantidad(int value)
{
    cantidad = value;
}

double producto::getPrecio() const
{
    return precio;
}

void producto::setPrecio(double value)
{
    precio = value;
}


producto::producto()
{

}

producto::producto(string, int, double)
{

}
