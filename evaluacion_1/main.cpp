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
#include <conio.h>

using namespace std;

bool administrador_inicio();
void anadir_clave();
void ver_inventario();
void modificar_inventario();
void agregar_producto();
void eliminar_producto();
void reporte_diario();
vector<producto> obtener_productos_disponibles();
void combos(vector<producto> );
vector<string> separar_string(string );


int main()
{
    obtener_productos_disponibles();
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
            cout<<"opcion:\n1)Ver inventario.\n2)Modificar inventario.\n3)Crear combos.\n4)modificar un producto en el inventario.\n5)Ver reporte del dia.."<<endl;
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
            case 4:
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

    De no tener datos el archivo, se imprime un mensaje que avisa que el inventario esta vacio.
    */
    fstream archivo("data.txt");
    string linea;
    int contador=0;
    cout<<"Producto   Cantidad   Precio"<<endl;
    while(getline(archivo,linea))
    {
        vector<string> linea_actual;
        linea_actual=separar_string(linea);
        for(int i=0;i<3;i++)
        {
            cout<<linea_actual[i]<<"    ";
        }
        cout<<endl;
        contador++;
        /*istringstream isstream(linea);
        while(!isstream.eof())
        {
           string temp , aux;
           isstream >> temp;
           cout<<temp<<"     ";

        }
        cout<<endl;
        contador++;*/
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
    /*
    En esta funcion solo se muestra el menu donde estan las opciones para modificar el inventario;
    elegida una opcion se procede entonces a invocar la funcion que realiza tal accion.
    */
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
    en modo lectura y creamos un nuevo archivo en modo escritura donde procederemos a escribir todos
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
            //int limite=0;
            vector<string> linea_actual;
            linea_actual=separar_string(linea);
            for(int i=0;i<linea_actual.size();i++)
            {
                if(producto==linea_actual[i])
                {
                    break;
                }
            }

            /*istringstream isstream(linea);
            while(!isstream.eof())
            {

               string temp__;

               isstream >> temp__;
               if(limite==0)
               {
                   if(producto!=temp__)
                   {
                       temp << linea << endl;
                       limite++;
                   }
               }
               else if(limite!=0)
               {
                   break;
               }
               limite++;
            }*/
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
        Para agregar un producto a la base de datos, lo que hacemos es abrir el archivo en modo
        escritura con las funciones ios::app|ios::ate que sirven para empezar la escritura al
        final del archivo, procedemos a pedirle al usuario el nombre del producto, la cantidad
        de este que hay y el valor de este; mientras se va obteniendo la informacion se va escribiendo en
        el archivo, por lo tanto al pedir el ultimo dato el archivo se cierra y el producto queda agregado
        a la base de datos.
    */
    ofstream archivo("data.txt",ios::app|ios::ate);
    string producto;
    int proceso=1;
    while(proceso==1)
    {
        cout<<"Ingrese el nombre del nuevo producto:"<<endl;
        getline(cin,producto);
        getline(cin,producto);
        archivo << producto <<";";
        cout<<"Ingrese la cantidad de unidades del producto"<<endl;
        getline(cin,producto);
        archivo << producto <<";";
        cout<<"Ingrese el costo que tiene el producto"<<endl;
        getline(cin,producto);
        archivo << producto << ";" << endl;
        cout<<"¿Desea continuar agregando elementos?(1/si 0/no"<<endl;
        cin>>proceso;
    }
    archivo.close();
}
vector<producto> obtener_productos_disponibles()
{
    //int contador=0;
    ifstream archivo("data.txt");
    string linea,aux_temp;
    producto producto_temporal;
    vector<producto>products;
    vector<string> linea_actual;
    //vector<string>auxiliar;
    while(getline(archivo,linea))
    {

        linea_actual=separar_string(linea);
        producto_temporal.setNombre(linea_actual[0]);
        string auxliar=aux_temp;
        int size_1=linea_actual[1].size();
        char aux_convertir[size_1];
        for(int i=0;i<size_1;i++)
        {
            aux_convertir[i]=linea_actual[1][i];
        }
        int number = atoi(aux_convertir);
        producto_temporal.setCantidad(number);
        size_1=linea_actual[2].size();
        char aux_convertir2[size_1];
        for(int i=0;i<size_1;i++)
        {
            aux_convertir2[i]=linea_actual[2][i];
        }
        number = atoi(aux_convertir2);
        producto_temporal.setPrecio(number);
        if(producto_temporal.getCantidad()>0)
        {
           products.push_back(producto_temporal);
        }
        linea_actual.clear();
        //contador=0;
        /*stringstream isstream(linea);
        while(!isstream.eof())
        {
            contador++;
           isstream >> aux_temp;
           //auxiliar.push_back(aux_temp);
           if(contador==1)
           {
               string auxliar=aux_temp;
               producto_temporal.setNombre(auxliar);
           }
           else if(contador==2)
           {
               string auxliar=aux_temp;
               int size_1=auxliar.size();
               char aux_convertir[size_1];
               for(int i=0;i<size_1;i++)
               {
                   aux_convertir[i]=aux_temp[i];
               }
               int number = atoi(aux_convertir);
               producto_temporal.setCantidad(number);
           }
           else if(contador==3)
           {
               string auxliar=aux_temp;
               int size_1=auxliar.size();
               char aux_convertir[size_1];
               for(int i=0;i<size_1;i++)
               {
                   aux_convertir[i]=aux_temp[i];
               }
               int number = atoi(aux_convertir);
               producto_temporal.setPrecio(number);
           }      
        }*/
    }
    archivo.close();
    return products;
}
void combos(vector<producto> productos)
{
    fstream archivo;
    archivo.open("dataCombos.txt");
    cout<<"1)Crear combo.\n2)Eliminar combo."<<endl;
    int choose;
    cin>>choose;
    if(choose==1)
    {
        string linea;
        int contador=1;
        while(getline(archivo,linea))
        {
            istringstream isstream(linea);
            while(!isstream.eof() && contador==1)
            {

            }
        }
        cout<<"Productos disponibles: "<<endl;
        vector<producto>::iterator it;
        it=productos.begin();
        while(it!=productos.end())
        {
            if(it->getCantidad()>0)cout<<it->getNombre()<<endl;

        }
        int opcion=1;
        while(opcion==1)
        {
        cout<<"ingrese el primer producto y la cantidad que quiere en el combo: (ejemplo: gaseosa 1)"<<endl;
        string producto_1;
        getline(cin,producto_1);
        archivo << producto_1 <<" ";
        cout<<"Ingrese el segundo producto y la cantidad que quiere en el combo: (ejemplo: papas 2"<<endl;
        getline(cin,producto_1);
        archivo << producto_1<<endl;
        cout<<endl;
        cout<<"Combo creado."<<endl;
        cout<<"¿Desea seguir creando combos?(1/si 0/no)"<<endl;
        cin>>opcion;
        }

    }
    else if(choose==2)
    {
        string linea;
        while(getline(archivo,linea))
        {
            istringstream isstream(linea);
            while(!isstream.eof())
            {

            }
        }
    }
    else
    {
        cout<<"saliendo..."<<endl;
    }
    archivo.close();
}
vector<string> separar_string(string linea)
{
    vector<string> string_separate;
    stringstream strTemp(linea);
    string segment;
    while(getline(strTemp,segment,';'))
    {
        string_separate.push_back(segment);
    }
    return string_separate;
}







