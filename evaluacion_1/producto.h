#ifndef PRODUCTO_H
#define PRODUCTO_H
//#include <map>
#include <string>

using namespace std;

class producto
{
    string nombre;
    int cantidad;
    int precio;

public:
    producto();
    producto(string, int , int);

    //map<string, int> getProducto_cantidad() const;
    //void setProducto_cantidad(const map<string, int> &value);
    int getPrecio() const;
    void setPrecio(int value);
    int getCantidad() const;
    void setCantidad(int value);
    string getNombre() const;
    void setNombre(const string &value);
};

#endif // PRODUCTO_H
