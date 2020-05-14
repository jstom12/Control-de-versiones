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

bool administrador_inicio(); //hecho
void anadir_clave(); //hecho
void ver_inventario(); //hecho
void modificar_inventario(); //hecho
void agregar_producto(); //hecho
void eliminar_producto(); //hecho
void reporte_diario(); //espera
vector<producto> obtener_productos_disponibles(); //hecho
vector<string> separar_string(string ); //hecho
void compras(vector<producto> );
void pago_productos(int );
void cambio_inventario(vector<producto> );

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
            cout<<"opcion:\n1)Ver inventario.\n2)Modificar inventario.\n3)Modificar combos.\n4)modificar un producto en el inventario.\n5)Ver reporte del dia.."<<endl;
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
        cout<<"¡Hola "<<usuario<<"!\n Mira nuestro menu y elije tu compra por favor:"<<endl;
        vector<producto> productos_disp = obtener_productos_disponibles();
        compras(productos_disp);
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
        cout<<"¿Desea continuar agregando elementos?(1/si 0/no)"<<endl;
        cin>>proceso;
    }
    archivo.close();
}
vector<producto> obtener_productos_disponibles()
{
    //int contador=0;
    ifstream archivo("data.txt");
    string linea;
    producto producto_temporal;
    vector<producto>products;
    vector<string> linea_actual;
    //vector<string>auxiliar;
    while(getline(archivo,linea))
    {
        linea_actual=separar_string(linea);
        producto_temporal.setNombre(linea_actual[0]);
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
        /*if(size_1>3)
        {
            vector<int> obt_combos;
            vector<string>::iterator it;
            it=linea_actual.begin();
            int contador=0;
            while(it!=linea_actual.end())
            {
                if(contador>2)
                {
                    string aux_iterator;
                    aux_iterator=*it;
                    char aux_con[aux_iterator.size()];
                    for(int i=0;i<aux_iterator.size();i++)
                    {
                        aux_con[i]=aux_iterator[i];
                    }
                    number = atoi(aux_con);
                    obt_combos.push_back(number);
                }
                it++;
                contador++;
            }
           producto_temporal.setCombos(obt_combos);
           obt_combos.clear();
           contador=0;
        }*/
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
void compras(vector<producto> productos)
{
    vector<producto>::iterator it;
    it= productos.begin();
    int clave = 1;
    map<int,producto> productos_eleccion;

    while(it!=productos.end())
    {
        productos_eleccion.insert(pair<int,producto>(clave,*it));
        it++;
        clave++;
    }
    map<int,producto>::iterator itm;
    itm = productos_eleccion.begin();
    cout<<"ID "<<"     NOMBRE PRODUCTO      "<<"PRECIO"<<endl;
    while(itm!=productos_eleccion.end())
    {
        cout << itm->first <<"       "<< itm->second.getNombre() <<"       "<< itm->second.getPrecio() << endl;
        itm++;
    }
    int comprando=1;
    vector<producto> compras;
    vector<int> opciones;
    while(comprando==1)
    {
        cout<<"elija el producto que desea comprar"<<endl;
        int op;
        cin>>op;
        producto compra_aux = productos_eleccion.at(op);
        compras.push_back(compra_aux);
        opciones.push_back(op);
        cout<<"Desea seguir comprando?(si/1 no/0)"<<endl;
        cin>>comprando;
    }
    it = compras.begin();
    clave=0;

    while(it!=compras.end())
    {
        clave += it->getPrecio();
        it++;
    }
    cout << "el precio total es: "<<clave<<endl;
    cout<<"digite la cantidad con la que va a pagar:"<<endl;
    int pago;
    cin>>pago;
    while(pago<clave)
    {
        cout<<"pago insuficiente "<<endl;
        cout<<"digite por favor un pago valido o introduzca 0 para salir"<<endl;
        cin>>pago;
        if(pago==0)return;
    }
    pago = pago-clave;
    itm = productos_eleccion.begin();
    while(itm!=productos_eleccion.end())
    {
        int buscador = itm->first;
        vector<int>::iterator it_numeros;
        it_numeros=opciones.begin();
        int cant=0;
        while(it_numeros!=opciones.end())
        {
            if(*it_numeros==buscador)
            {
                cant--;
                it_numeros++;
            }
            it_numeros++;
        }
        cant += itm->second.getCantidad() + cant;
        itm->second.setCantidad(cant);
        cant=0;
        itm++;
    }

    pago_productos(pago);
}
void pago_productos(int numero)
{
    int billete1=0 , billete2=0 , billete3=0 , billete4=0 , billete5=0 , billete6=0 , moneda1=0 , moneda2=0 , moneda3=0 , moneda4=0 ;
       billete1=numero/50000;
       numero=numero%50000;
       billete2=numero/20000;
       numero=numero%20000;
       billete3=numero/10000;
       numero=numero%10000;
       billete4=numero/5000;
       numero=numero%5000;
       billete5=numero/2000;
       numero=numero%2000;
       billete6=numero/1000;
       numero=numero%1000;
       moneda1=numero/500;
       numero=numero%500;
       moneda2=numero/200;
       numero=numero%200;
       moneda3=numero/100;
       numero=numero%100;
       moneda4=numero/50;
       numero=numero%50;
       cout<<"Sus vueltas son:"<<endl;
       cout<<"billete de: 50000: "<<billete1<<endl;
       cout<<"billete de: 20000: "<<billete2<<endl;
       cout<<"billete de: 10000: "<<billete3<<endl;
       cout<<"billete de: 5000: "<<billete4<<endl;
       cout<<"billete de: 2000: "<<billete5<<endl;
       cout<<"billete de: 1000: "<<billete6<<endl;
       cout<<"moneda de: 500: "<<moneda1<<endl;
       cout<<"moneda de: 200: "<<moneda2<<endl;
       cout<<"moneda de: 100: "<<moneda3<<endl;
       cout<<"moneda de: 50: "<<moneda4<<endl;
       cout<<"faltante: "<<numero<<endl;
}
void cambio_inventario(vector<producto> productos_cambio )
{

}
