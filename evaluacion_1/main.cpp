#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <map>
#include <vector>
#include <producto.h>

using namespace std;

bool administrador_inicio();
void anadir_clave();
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
    Para verificar la clave, se abre el archivo de texto donde esta contenida la clave de administrador
    (de no existir, se crea el archivo y se le pide al usuario agregar una nueva clave de administrador)
    y verifica si la clave que ingresa el usuario es igual a la clave registrada en el archivo, de ser iguales
    se retorna un true y de lo contrario retorna un false.
    */
    string clave, linea;
    fstream archivo;
    archivo.open("sudo.txt");
    if(!archivo.is_open())//al no abrirse el archivo, se entiende que es que no existe y se
    {                     // procede a agregar una nueva clave de administrador.
       anadir_clave();
    }
    archivo.open("sudo.txt");
    cout<<"Ingrese la clave de administrador: "<<endl;
    getline(cin,clave);
    getline(cin,clave);
    while(getline(archivo,linea))
    {
        if(linea==clave)
        {
            archivo.close();
            return true;
        }
        else
        {
            archivo.close();
            return false;
        }
    }
    archivo.close();
    return false;
}
void ver_inventario()
{
    /*
    La funcion para mostrar el inventario abre el archivo data.txt donde estaran los datos
    de los productos, la cantidad que hay y el precio de cada uno; se recorre el archivo linea por linea
    y luego espacio por espacio, se almacena cada string entre espacio dentro de un vector para
    despues proceder a crear un elemento de la clase producto y así mostrar cada producto de una
    manera mas ordenada.
    */
    fstream archivo("data.txt");
    string linea;
    int contador=0;
    vector<string> producto_creacion;
    vector<producto>inventary;
    cout<<"Producto     Cantidad     Precio"<<endl;
    while(getline(archivo,linea))
    {
        istringstream isstream(linea);
        while(!isstream.eof())
        {
           string temp , aux;
           isstream >> temp;
           producto_creacion.push_back(temp);
        }
        int prize,cant;
        string aux;
        aux=producto_creacion[2];
        int tamano=aux.size();
        char conversion[tamano];
        for(int i=0;i<tamano;i++)
        {
            conversion[i]=aux[i];
        }
        prize=atoi(conversion);
        aux=producto_creacion[1];
        tamano=aux.size();
        char conversion_2[tamano];
        for(int i=0;i<tamano;i++)
        {
            conversion_2[i]=aux[i];
        }
        cant=atoi(conversion_2);
        producto producto_aux(producto_creacion[0],cant,prize);
        inventary.push_back(producto_aux);
        contador++;
    }

    if(contador==0)
    {
        cout<<"---el inventario esta vacio---"<<endl;
    }
    vector<producto>::iterator it;
    it=inventary.begin();
    for(it;it<inventary.end();it++)
    {
        cout<<it->getNombre()<<"     "<<it->getCantidad()<<"     "<<it->getPrecio()<<endl;
    }
    archivo.close();
}
void anadir_clave()
{
    string clave;
    ofstream temp;
    temp.open("sudo.txt");
    cout<<"No hay clave de administrador actualmente, por favor ingrese la nueva clave de administrador"<<endl;
    getline(cin,clave);
    getline(cin,clave);
    temp << clave;
    cout<<"Procesando..."<<endl;
    cout<<"Nueva clave creada."<<endl;
    temp.close();

}
