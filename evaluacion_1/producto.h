#ifndef PRODUCTO_H
#define PRODUCTO_H
//#include <map>
#include <string>
#include <vector>

using namespace std;

class producto
{
    string nombre;
    int cantidad;
    double precio;
    vector<int> combos;

public:
    producto();
    producto(string, int, double);

    //map<string, int> getProducto_cantidad() const;
    //void setProducto_cantidad(const map<string, int> &value);

    string getNombre() const;
    void setNombre(const string &value);
    int getCantidad() const;
    void setCantidad(int value);
    double getPrecio() const;
    void setPrecio(double value);
    vector<int> getCombos() const;
    void setCombos(const vector<int> &value);
};

#endif // PRODUCTO_H
