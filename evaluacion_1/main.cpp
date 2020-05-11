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
void agregar_producto();
void eliminar_producto();
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
            cout<<endl;
            cout<<"opcion:\n1)Ver inventario.\n2)Modificar inventario.\n3)Ver reporte del dia"<<endl;
            int opcion_administrador;
            cin>>opcion_administrador;
            switch (opcion_administrador) {
            case 1:
            {            
                ver_inventario();
            }
                break;
            case 2:
            {
                modificar_inventario();
            }
                break;
            case 3:
            {

            }
                break;
            default:
                break;
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
    ifstream archivo("sudo.txt");
    if(!archivo.is_open())//al no abrirse el archivo, se entiende que es que no existe y se
    {                     // procede a agregar una nueva clave de administrador.
       anadir_clave();
       archivo.open("sudo.txt");
    }
    cout<<"Ingrese la clave de administrador: "<<endl;
    getline(cin,clave);
    getline(cin,clave);
    getline(archivo,linea);
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

    archivo.close();
    return false;
}
void ver_inventario()
{
    /*
    La funcion para mostrar el inventario abre el archivo data.txt donde estaran los datos
    de los productos, la cantidad que hay y el precio de cada uno; se recorre el archivo linea por linea
    y se va imprimiendo conforme avance el ciclo, esto para que las impresiones se distingan facilmente.
    */
    fstream archivo("data.txt");
    string linea;
    int contador=0;
    cout<<"Producto   Cantidad   Precio"<<endl;
    while(getline(archivo,linea))
    {
        istringstream isstream(linea);
        while(!isstream.eof())
        {
           string temp , aux;
           isstream >> temp;
           cout<<temp<<"     ";

        }
        cout<<endl;
        contador++;
    }

    if(contador==0)
    {
        cout<<"---el inventario esta vacio---"<<endl;
    }
    archivo.close();
}
void anadir_clave()
{
    /*
    En esta funcion se abre un archivo de texto en modo escritura y se le pide al usuario que
    ingrese la clave que desea para crearla.
    */
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
void modificar_inventario()
{
    int opcion;
    cout<<"1) Agregar para agregar producto.\n2) Eliminar un producto"<<endl;
    cin>>opcion;
    if(opcion==1)
    {
        agregar_producto();
    }
    else if(opcion==2)
    {
        eliminar_producto();
    }
}
void eliminar_producto()
{
    /*
    Para eliminar un producto del inventario, procedemos a abrir el archivo donde se almacenan los datos
    en modo lectura y creamos un nuevo archivo en modo escritorio donde procederemos a escribir todos
    los productos que se almacenan en el archivos de los datos a excepcion del producto que se busca eliminar.
    al finalizar eliminamos el archivo de datos antiguo y renombramos el archivo de escritura para dejarlo
    como el nuevo archivo de datos.

    No es un modo muy eficiente pero es eficaz a la hora de modificar archivos de textos no tan sobrecargados de
    informacion.
    */
    ifstream archivo("data.txt");
    ofstream temp("dataTemp.txt");
    string linea,producto,aux_comparacion;
    cout<<"¿Que producto desea eliminar del inventario?"<<endl;
    getline(cin,producto);
    getline(cin,producto);
    while(getline(archivo,linea))//empezamos a recorrer el archivo linea por linea y
    {                           //con la funcion .find, buscamos conocer si el producto no se encuentra
        int pos=linea.find(producto);
        if(pos==-1)//en la linea donde se posiciona el archivo, esto de ser cierto se pasa entonces
        {
            temp << linea << endl; //a escribir en el otro archivo la linea de texto.
        }
        else if(pos!=-1)
        {
            int tamano=producto.size() , j=0 , limite;
            char aux[tamano];
            limite=pos+producto.size();
            for(int i=pos;i<limite;i++)
            {
                linea[i]=aux[j];
                j++;
            }
            for(int i=0;i<tamano;i++)
            {
                aux_comparacion[i]=aux[i];
            }
            if(aux_comparacion!=producto)
            {
                temp << linea << endl;
            }

        }

    }
    archivo.close();
    temp.close();
    remove("data.txt");
    rename("dataTemp.txt","data.txt");
    cout<<"Cambio en el inventario realizado"<<endl;
}
void agregar_producto()
{
    /*

    */
    ofstream archivo("data.txt",ios::app|ios::ate);
    string producto;
    int proceso=1;
    while(proceso==1){
        cout<<"Ingrese el nombre del nuevo producto:"<<endl;
        getline(cin,producto);
        getline(cin,producto);
        archivo << producto <<" ";
        cout<<"Ingrese la cantidad de unidades del producto"<<endl;
        getline(cin,producto);
        archivo << producto <<" ";
        cout<<"Ingrese el costo que tiene el producto"<<endl;
        getline(cin,producto);
        archivo << producto << endl;
        cout<<"¿Desea continuar agregando elementos?"<<endl;
        cin>>proceso;
    }
    archivo.close();
}









