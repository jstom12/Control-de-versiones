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
void reporte_diario(string,vector<producto>, int); //hecho
vector<producto> obtener_productos_disponibles(); //hecho
vector<string> separar_string(string ); //hecho
void compras(vector<producto> , string); //hecho
void pago_productos(int ); //hecho
void cambio_inventario(vector<producto> ); //hecho
void actualizar_inventario(map<int,producto> ); //hecho
void ver_reporte();
void asiento_cine();

int main()
{
    int proceso_activo=1;
    while(proceso_activo==1)
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
                cout<<"opcion:\n1)Ver inventario.\n2)Modificar inventario.\n3)Ver reporte del dia."<<endl;
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
                    ver_reporte();
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
            compras(productos_disp , usuario);
            cout<<"a continuacion digite su asiento"<<endl;
            asiento_cine();
        }
        default:
            break;

        }
        cout<<"Desea seguir en el programa?(si/1 no/0)"<<endl;
        cin>>proceso_activo;
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
            cout<<"clave incorrecta"<<endl;
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
        /*
        En esta parte, se recibe una linea del texto que equivale a un producto del inventario,
        el nombre, la cantidad en inventario y el precio estan separados por el char ';',
        por lo que se invoca una funcion que separa esta linea en un vector de strings y así
        se maneja mas facil la impresion del producto.
        */
        vector<string> linea_actual;//Se elije usar un tipo vector porque hay que recorrer el vector entero y esto
        linea_actual=separar_string(linea);//es una ventaja frente al tipo list.
        for(int i=0;i<3;i++)
        {
            cout<<linea_actual[i]<<"    ";
        }
        cout<<endl;
        contador++;
        /*
         * -IGNORAR CONDIGO OBSOLETO-
         *
         * istringstream isstream(linea);
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
    ingrese la clave que desea para almacenarla en el archivo.
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
    elegida una opcion se procede entonces a invocar la funcion que realiza tal accion. Ninguna
    de las funciones recibe algo parametro porque dentro de ellas se opera directamente con el archivo
    de texto.
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
    while(getline(archivo,linea))
    { /*
        empezamos a recorrer el archivo linea por linea y
        con la funcion .find, buscamos conocer si el producto no se encuentra
        en la linea donde se posiciona el archivo, esto de ser cierto se pasa entonces
        a escribir en el otro archivo la linea de texto que no correspondría a la linea
        que buscamos.
        */
        int pos=linea.find(producto);
        if(pos==-1)
        {
            temp << linea << endl;
        }
        else if(pos!=-1)
        {/*
        si pos es != -1 significa que se encontró en la linea el producto que deseamos eliminar,
        por lo tanto separamos la linea en un vector de string como se viene haciendo y
        procedemos a recorrer el vector para chequear que el nombre del producto en la linea
        y el que ingresó el usuario para eliminar sean iguales y así no copiar esta linea al nuevo
        archivo .txt
        */

            vector<string> linea_actual;
            linea_actual=separar_string(linea);
            for(int i=0;i<linea_actual.size();i++)
            {
                if(producto==linea_actual[i])
                {
                    break;
                }
            }

            /*-IGNORAR CODIGO OBSOLETO-
             * istringstream isstream(linea);
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
    /*
    se cierran los archivos y acá se elimina el viejo data.txt y se le cambia el nombre al
    nuevo archivo que corresponde al inventario menos el producto que se quiso eliminar.
    */
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
    /*
    Lo que pretende esta funcion es: abrir el archivo de texto donde esta almacenado los datos
    de los productos en inventario y pasarlos a un vector compuesto por el tipo producto que es
    una clase creada en este codigo.
    Para ello abrimos el archivo en modo lectura, creamos una variable producto que será usada
    para almacenas el producto que se vaya recogiendo en el ciclo, un vecto<producto> que es donde se
    agregaran los productos que se van obteniendo y un vector<string> para separar la linea
    de codigo y manejarla de manera mas sencilla.
    */
    ifstream archivo("data.txt");
    string linea;
    producto producto_temporal;
    vector<producto>products;
    vector<string> linea_actual;
    //vector<string>auxiliar;
    while(getline(archivo,linea))
    {
        /*
        la posicion 0 del vector<string> equivale al nombre del producto, la posicion 1 a la cantidad
        disponible en el inventario de este y la posicion 3 equivale al precio del producto.
        para la posicion 0 solo hay que invocar la funcion para obtener el nombre de la clase producto
        pero para la cantidad y el precio, dado que la clase los recibe como enteros, se debe pasar
        a un arreglo de char para poder usar la funcion atoi() que convierte un arreglo de char en
        entero. Hecho esto se agregan al producto y este producto se agrega al vector<producto> así hasta
        acabar las lineas del archivo.
        */
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
        if(producto_temporal.getCantidad()>0) // verificamos que la cantidad sea mayor a 0 y agregamos al vector<producto>
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
    /*
    La funcion de separar string fue necesaria para facilitar el manejo del archivo de texto
    por lo que se encontró esta funcion en internet que no es propia pero usa un elemento de la
    clase stringstream que recorre un string cada que encuentro un char declarado en la funcion
    y se añade a un vector<string> para luego retornar ese vector<string>.
    */
    vector<string> string_separate;
    stringstream strTemp(linea);
    string segment;
    while(getline(strTemp,segment,';'))
    {
        string_separate.push_back(segment);
    }
    return string_separate;
}
void compras(vector<producto> productos , string usuario)
{
    /*
    En esta funcion se realiza la compra por parte del usuario, obtiene como parametros un vector<producto>
    que corresponde a los productos disponibles en el inventario, y un string que corresponde al nombre del
    usuario.
    Primero se recorre el vector<producto> y se va agregando cada posicion a un map<int,producto>
    para facilitar la compra del usuario.
    luego se imprime el menu para la comprar del usuario con el map recien creado, por lo tanto,
    para comprar algo basta con introducir el ID del producto.

    */
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
    //vector<int> opciones;
    while(comprando==1)
    {
        /*
        Se entra entonces a este ciclo que es para que el usuario elija los productos que va a comprar,
        se almacena esa decision en un int que equivale a la clave en el mapa y se verifica que el producto
        al que corresponde el valor de esa clave tenga una cantidad disponible mayor a 1, esto porque puede
        ser el caso que en el inventario hayan 5 elementos y el usuario quisiera comprar 6, solo permitiría
        comprar 5.
        durante el ciclo se cambia entonces el valor de la cantidad disponible del producto
        borrando la clave actual y creando una identica pero con la diferencia que la cantidad del producto
        es igual a una menos.
        */
        cout<<"elija el producto que desea comprar"<<endl;
        int op;
        cin>>op;
        producto aux = productos_eleccion[op];
        if(aux.getCantidad()>=1)
        {
            int cant = aux.getCantidad();
            cant -=1;
            aux.setCantidad(cant);
            compras.push_back(aux);
            productos_eleccion.erase(op);
            productos_eleccion.insert(pair<int,producto>(op,aux));
            //opciones.push_back(op);
        }
        cout<<"Desea seguir comprando?(si/1 no/0)"<<endl;
        cin>>comprando;
    }
    it = compras.begin();
    clave=0;
    while(it!=compras.end())
    {
        /*
        En este ciclo lo que se hace es extraer el precio de los productos elegidos
        para darle el total a pagar al usuario.
        */
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
    if(pago>=clave)
    {
        /*
        Si el pago que introduce el usuario es mayor o igual al total a pagar, entonces
        se procede a actualizar el inventario y a imprimir los billetes y monedas que hay que
        devolverle al usuario.
        */
        reporte_diario(usuario,compras,clave);
        pago = pago-clave;
        actualizar_inventario(productos_eleccion);
        pago_productos(pago);
    }
    /*itm = productos_eleccion.begin();
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
    }*/

}
void pago_productos(int numero)
{
    /*
    Funcion para dar las vueltas de manera real, recibe un entero que corresponde a la diferencia entre
    el pago que realiza el usuario y el valor total de su compra.
    se coge el entero y se va dividiendo mientras se saca el modulo de esa division, si el modulo es un entero
    pues se almacena en esa variable y al final muestra cuando billetes y monedas se necesitan.
    funcion reciclada de la practica 1.
    */
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
void actualizar_inventario(map<int,producto> productos)
{
    /*
    Para actualizar el inventario se recibe un map<int,producto> que se obtiene en la funcion de las compras
    y equivale a los productos menos las cantidades compradas, obviamente los productos que no fueron comprados
    se mantienen igual.

    Se itera entonces en el mapa y se va escribiendo en el archivo linea por linea
    con el orden que ya se tiene en la base de datos.

    Al terminar el ciclo se cierra el archivo y ya estaría listos los cambios dentro del txt.
    */
    ofstream archivo("data.txt");
    map<int,producto>::iterator it;
    it=productos.begin();
    while(it!=productos.end())
    {
        archivo << it->second.getNombre() <<";"<<it->second.getCantidad() <<";"<<it->second.getPrecio()<<";"<<endl;
        it++;
    }
    archivo.close();
}
void reporte_diario(string usuario ,vector<producto> compras , int pago)
{
    /*
    El reporte diario recibe un string correspondiente al nombre del usuario, un vecto<producto>
    correspondiente a las compras que realizó dicho usuario y un entero correspondiente al valor de
    su compra.

    Se abre el archivo en modo lectura y en ios::app|ios::ate para que el puntero se ubique en la ultima
    posicion del archivo y empiece a escribis desde ahí. empiece a interar en el vector<producto> obteniendo
    los nombres de estos y escribiendolos simultaneamente, todo en la misma linea, por ultimo se escribe el
    valor de la compra y un salto de linea dejando así listo el archivo para el siguiente usuario.
    */
    ofstream archivo("ventas.txt",ios::app|ios::ate);
    archivo << usuario<<":";
    vector<producto>::iterator it;
    it=compras.begin();
    while(it!=compras.end())
    {
        archivo<<it->getNombre()<<";";
        it++;
    }
    string prize = to_string(pago);
    archivo << prize <<";";
    archivo.close();
}
void ver_reporte()
{
    /*
    Esta funcion imprime entonces los reportes guardados en el archivo correspondiente a las ventas que
    se le realizan a los usuarios.
    abre el archivo donde se guarda esta informacion y comienza a iterar en el
    linea por linea y, como anteriormente se ha mostrado, se separa el string en un vector<string>
    y procede a imprimir la posicion 0 de este que corresponde al nombre del usuario, luego itera
    en las demas posiciones que corresponden a las compras de este mismo y el valor que pagó por esto.
    */
    ifstream archivo("ventas.txt");
    string linea;
    cout<<"usuario     "<<"productos comprados     "<<"precio venta"<<endl;
    while(getline(archivo,linea))
    {
        vector<string> linea_sep = separar_string(linea);
        cout<<linea_sep[0]<<"     ";
        vector<string>::iterator it;
        it=linea_sep.begin();
        it++;
        while(it!=linea_sep.end())
        {
            cout<<*it<<"  ";
            it++;
        }
        cout<<endl;
    }
    archivo.close();
}
void asiento_cine()
{
    /*
    Funcion reciclada de la practica 2.

    se crea un arreglo char de 15x20 donde 15 equivale a las filas y 20 equivale a las columnas
    de la sala de cine; se llenan todos los espacios con el valor 45 de la tabla ascii que corresponde
    a '-' y se deja lista la sala para empezas a elegir los asientos del usuario.


    */
    char cine[15][20] ;
        int asiento=0 , aux_numeros=0 , opcion_2=1;
        char fila=0 , aux=65;
        int opcion=1;
        for (int i=0 ; i<15 ; i++){ // se genera la sala de cine con ningun asiento reservado.
            for (int j=0 ; j<20 ; j++){
                cine[i][j]=45;
            }
        }
        do{ // se le pide al usuario la reserva que va a realizar.
        cout<<"ingrese la fila (A-O)"<<endl;
        cin>>fila;
        cout<<"ingrese el asiento (1-20)"<<endl;
        cin>>asiento;
        asiento = asiento-1; //se le resta 1 al numero ingresado para que coincida con las posiciones del vector.
        opcion=1;
        while(opcion==1)
        {
            if(fila==aux){ // si la fila es exactamente igual al auxiliar, se marca la reserva en el vector.
                cine[aux_numeros][asiento]='+';
                opcion=0;
            }
            else //de lo contrario,se le suma uno al caracter del auxiliar y uno al auxiliar_numeros.
            {
                aux_numeros++;
                aux++;
            }
        }
        for(int i=0;i<15;i++) //se imprime la matriz.
        {
            for(int j=0;j<20;j++)
                cout<<cine[i][j];
        cout<<endl;
        }
        cout<<"desea seleccionar mas asientos?(si/1 no/0)"<<endl;//se le pregunta al usuario si quiere seguir reservando.
        cin>>opcion_2;
        }while(opcion_2==1);
}
