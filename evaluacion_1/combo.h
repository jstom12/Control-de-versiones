#ifndef COMBO_H
#define COMBO_H
#include <producto.h>
#include <vector>

class combo
{
    string nombre;
    vector<producto> componentes;
    int precio;

public:
    combo();
    string getNombre() const;
    void setNombre(const string &value);
    vector<producto> getComponentes() const;
    void setComponentes(const vector<producto> &value);
    int getPrecio() const;
    void setPrecio(int value);
};

#endif // COMBO_H
