#include "producto.h"

int producto::getPrecio() const
{
    return precio;
}

void producto::setPrecio(int value)
{
    precio = value;
}

int producto::getCantidad() const
{
    return cantidad;
}

void producto::setCantidad(int value)
{
    cantidad = value;
}

string producto::getNombre() const
{
    return nombre;
}

void producto::setNombre(const string &value)
{
    nombre = value;
}

producto::producto()
{

}

producto::producto(string, int, int)
{

}
