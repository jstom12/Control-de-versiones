#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
using namespace std;

bool administrador_inicio();
void ver_inventario();
void modificar_inventario();
void reporte_diario();
int main()
{
    cout<<"-----¡Bienvenido!-----"<<endl;
    cout<<"---Ingrese una opcion---"<<endl;
    cout<<"1) Ingresar como administrador.\n2) Ingresar como usuario.\n"<<endl;
    int opcion;
    cin>>opcion;
    switch (opcion) {
    case 1:
    {
        if(administrador_inicio()==true)
        {
            cout<<"opcion:\n1)Ver inventario.\n2)Modificar inventario.\3)Ver reporte del dia"<<endl;
            int opcion_administrador;
            cin>>opcion_administrador;
            switch (opcion_administrador) {
            case 1:
            {
                ver_inventario();
            }

            }

        }

    }
        break;
    case 2:
    {
        cout<<"Bienvenido, por favor indentifiquese:"<<endl;
        string usuario;
        getline(cin,usuario);
        getline(cin,usuario);
        cout<<"¡Hola "<<usuario<<"!\n ¿Que deseas realizar?"<<endl;
    }
    default:
        break;

    }

}

bool administrador_inicio()
{
    /*
    La clave como administrador es predeterminada y para cambiarla basta con
    modificar la variable clave pero por facilidad se deja una clave estandar.

    el usuario al ingresar la clave, si esta coincide retorna un true, de lo contrario
    un false.
    clave: hola24
    */
    string clave, aux;
    clave="hola24";
    cout<<"Ingrese la clave de administrador predeterminada"<<endl;
    getline(cin,aux);
    getline(cin,aux);
    if(clave==aux)
    {
        return true;
    }
    else
        return false;
}
void ver_inventario()
{
    fstream archivo("data.txt");
    archivo << "hola";
    archivo.close();
}
