#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>
#include <thread>
#include <chrono>

#define up_arrow 72
#define down_arrow 80
#define enter_key 13

using namespace std;
/**
 *Esta función se encarga de mover el cursor en la consola
 * @param x Variable para la coordenada en x (columnas)
 * @param y Variable para la coordenada en y (filas)
 */
void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

/**
*Esta función se encarga de esperar a que el usuario ingrese una tecla
*khbit se utiliza pra determinar si una tecla ha sido presionada o no. Si el usuario presiona una tecla regresa un valor diferente de cero,
*si no lo presiona regresa un cero
* @return se retorna la variable pressed, es decir se debe retornar el valor de la tecla que presiona el usuario
*/
int waitForAnyKey()
{
    int pressed;                //se declara una variable de tipo int ya que se utilizara el codigo ascii
    while(!kbhit());            //Mientras no se presione una tecla no se regresara un valor diferente de cero, si se presiona,
    //se regresara lo que este en el return, que es la variable pressed
    pressed = getch();          //Se recoge el valor de pressed con la funcion getch
    //Lee un caracter directamente de la consola sin hacer uso del buffer, y sin mostrar salida
    return pressed;             //se pide que se retorne int pressed para poder hacer la accion que se pida en la funcion que la llama
}

/**
*La función se encarga de imprimir el marco en la consola
*/
void MARCO()
{
    int ancho =140, alto=30;             //Se declaran dos variable de tipo entero
    int x = 1, y = 1;                   //Se inicializan dos variables
    int pared = 177;                    //La variable entera se iguala con un valor para despues se usada como codigo ascii
    char tecla;                         //se declara una variable de tipo char
    tecla=pared;                        //Se iguala la variable entera a la variable tipo char
    int alturarectagunlo= alto-4;       //Se crea una nueva variable que sera la altura del rectangulo
    system("cls");                      //Se limpia la pantalla
    gotoxy(x,y);                        //Se va a las coordenas x,y

    for (; y<alturarectagunlo; y++) //Se inicia un ciclo for para imprimir la parte de arrina del rectangulo
        //Se escibe un punto y coma antes de y porque la sintaxis del ciclo for no permite escribir
        //si no hay un punto y coma ANTES
        //Y debe ser menor a la altura del rectangulo
    {
        gotoxy(x, y);                //Se devuelve a las coordenadas inciales
        cout<<tecla;                 //A partir de ahi se comienza a imrpir las teclas
        gotoxy(ancho, y);            //Se va a las coordenas donde inicia el ancho y donde inicia y
        cout<<tecla;                 //Se imprime la tecla
    }
    y = 1;                           //Este y igual con uno permite imprimir la linea de arriba de teclas
    for (; x < ancho+1; x++)         //Se vuelve a correr un ciclo for en donde x debe ser menor al ancho +1, seria lo mismo poner que
        //x fuera menor o igual a ancho y x avanza
    {
        gotoxy(x, y);                 //Inicia la coordenada en x , y y aumenta el ancho
        cout<<tecla;                  //Imprime el character
        gotoxy(x, alturarectagunlo);  //Avanza
        cout<<tecla;
    }
}


/**
* La función se encarga de mover el cursor en el menú de temas
* @param x
* @param y
* @param yStart
* @return i, retorna el valor que se moverá el cursor en las y
*/
int menuSelector2(int x, int y, int yStart)
{
    int llave;                                  //Se declara una variable de tipo int
    int i = 0;                                  //Se inicializa la variable i con cero
    x = x-3 ;                                   //X toma el valor de X-3 para que el cursos aparezca separado del texto del menu
    gotoxy(x,yStart);                           //Se lleva al cursos a la posicion de yStart y a la nueva posicion de x
    cout<<">"<<endl;                            //Se imprime el cursor
    do                                          //se crea un ciclo do while para el movimeinto del cursor
    {
        llave = waitForAnyKey();                //La variable llave se inicializa a la funcion de waitforanykey porque el cursor
        //estara a la expectativa de si el usuario ingresa una tecla

        if ( llave == up_arrow )                //En este primer if se dice que si llave es igual a up_arrow el cursor se mantendra en el
            //ancho que dice x,
            //pero aumentara un entero su posicion en yStart
        {
            gotoxy(x,yStart+i);                 //Si en lugar de yStart se pusiera la variable y, al momento de mover el cursor hacia arriba no
            cout<<" "<<endl;                    //se eliminaria el cursor como se estipula en el siguiente

            if (yStart >= yStart+i )            //En este if statement se considera la situción en donde si el cursor
                //qusiera avanzar más all� de donde esta la primera opcion, el cursor iria hacia la ultima
                //opcion del menu. esto funciona asi: Si yStar es mayor o igual a yStart+i se realiza la correcion
                //en donde i tomara el valor de yStart-(yStart-1) que seria (10-10-1) que son los lugares que avanzara el cursor
                i = y - yStart -1;              //Como yStart sera menos que yStart+1 cuando baje en el menu se declara la siguiente conidicion.
            //Esto quiere decir que como yStart es igual a , solamente
            //habra un momento que pueda valer mas o igual que yStart+i que es, si quiere avanzar mas
            //arriba de la primera opcion del menu.
            else                                //Si la condicion anterior propuesta no es verdad entonces i disminuir� y se restar� el valor de yStart con i
                i--;
            gotoxy(x,yStart+i);                 //Imprimira el cursor en donde se encuentra la nueva coordenada
            cout<<">"<<endl;                    //Imprime la flecha
        }
        else                                     //En el siguiente if statmente se dice que si llave es igual a la tecla de abajo se hara lo siguiente
            if ( llave == down_arrow )
            {
                gotoxy(x,yStart+i);
                cout<<" "<<endl;                  //Imprimira un vacio en donde antes estaba el cursor
                if (i+1 >= y - yStart ) //Se vuelve a realizar un if statement para revisar que el cursor no vaya mas arriba de la ultima opcion
                    i = 0;              //Si i+2 es mayor o igual a y-yStart i debera valer cero, lo que significa que no se movera yStart, se quedara inmovil
                //en esa posicion
                else                    //En cambio si i+2 es menor o igual que y-yStart el cursor si se imprimira en la linea de codigo arriba de en la que este
                    i++;                // I debe aumentar
                gotoxy(x,yStart+i);     //Se mueve hacia la coordenada e imprime el cursor
                cout<<">"<<endl;
            }
    }
    while(llave != enter_key);           //Hasta aqui llega el final del do while y la condicion se cumple siempre y cuando la llave sea diferente de la tecla
    //enter (mas arriba se definio)
    return i;
}

/**
* La función se encarga de mover el cursor en el menú de temas
* @param x
* @param y
* @param yStart
* @return i, retorna el valor que se moverá el cursor en las y
*/
int menuSelector(int x, int y, int yStart)
{
    int llave;                                      //Se declara una variable de tipo int
    int i = 0;                                      //Se inicializa la variable i con cero
    x = x-3 ;                                       //X toma el valor de X-2 para que el cursos aparezca separado del texto del menu
    gotoxy(x,yStart);                               //Se lleva al cursos a la posicion de yStart y a la nueva posicion de x
    cout<<">"<<endl;                                //Se imprime el cursos
    do                                              //se crea un ciclo do while para el movimeinto del cursor
    {
        llave = waitForAnyKey();                    //La variable char se inicializa a la funcion de waitforanykey porque el cursor estara a la expectativa
        //de si el usuario ingresa una tecla
        //Si en lugar de yStart se pusiera la variable y, al momento de mover el cursor hacia arriba no se eliminaria
        //el cursor como se estipula en el siguienete
        if ( llave == up_arrow )                    //En este primer if se dice que si llave es igual a up_arrow el cursor se mantendra en el ancho que
            //dice x, pero aumentara un entero su posicion en yStart
        {
            gotoxy(x,yStart+i);
            cout<<" "<<endl;
            if (yStart >= yStart+i )       //En este if statement se considera la situcion en donde si el cursor
                //qusiera avanzar mas all� de donde esta la primera opcion, el cursor iria hacia la ultima opcion del menu.
                i = y - yStart -2;         //Esto funciona asi: Si yStar es mayor o igual a yStart+i se realiza la correcion en donde i tomara el valor
            //de yStart-(yStart-2) que seria 5-2=3 que son los lugares que avanzara el cursor
            //Como yStart sera menos que yStart+1 cuando baje en el menu se declara la siguiente conidicion.
            //Esto quiere decir que como yStart es igual a 5, solamente habra un momento que pueda valer mas o igual que yStart+i
            //que es, si quiere avanzar mas arriba de la primera opcion del menu.
            else                           //Si la condicion anterior propuesta no es verdad entonces i disminuir� y se restar� el valor de yStart con i
                i--;
            gotoxy(x,yStart+i);             //Imprimira el cursor en donde se encuentra la nueva coordenada
            cout<<">"<<endl;                //Imprimirá el cursor en la nueva coordenada
        }
        else if ( llave == down_arrow )     //En el siguiente if statmente se dice que si llave es igual a la tecla de abajo se hara lo siguiente
        {
            gotoxy(x,yStart+i);
            cout<<" "<<endl;            //Imprimira un vacio en donde antes estaba el cursor
            if (i+2 >= y - yStart )     //Se vuelve a realizar un if statement para revisar que el cursor no vaya mas arriba de la ultima opcion
                //Si i+2 es mayor o igual a y-yStart i debera valer cero, lo que significa que no se movera yStart,
                //se quedara inmovil en esa posicion
                i = 0;
            else                         //En cambio si i+2 es menor o igual que y-yStart el cursor si se imprimira en la linea de codigo arriba de en la que este
                i++;
            gotoxy(x,yStart+i);          //Va hacia la cordenada e imprime el cursor
            cout<<">"<<endl;
        }
    }
    while(llave != enter_key);              //Hasta aqui llega el final del do while y la condicion se cumple siempre y cuando la llave sea diferente de la
    //tecla enter (mas arriba se definio)
    return i;
}

/**
*   La funcion se encarga de imrpimir el menú de temas
* @return pressed retorna la opcion presionada del main que contiene el switch de temas
*/
int temas()
{
    system("cls");                               //Se limpia la pantalla
    MARCO();                                     //Se vuelve a llamar a la función Marco
    int selected, x=18, y=10;                    //Se declara tres variables, una para las coordenadas y otra para la selección del tema
    int yStart=y;                                //Se declara una nueva variable que quede igualada a y
    gotoxy(38,3);
    cout<<"TEMAS"<<endl;
    gotoxy(18,7);
    cout<<"Escoge primero un tema: "<<endl;
    gotoxy(18,y++);
    cout<<"1.-Videojuegos"<<endl;//mas 17
    gotoxy(x,y++);
    cout<<"2.-Deportes"<<endl;//mas 14
    gotoxy(x,y++);
    cout<<"3.-Musica"<<endl;
    gotoxy(x,y++);
    cout<<"4.-Arte"<<endl;
    selected=menuSelector2(x,y,yStart);         //se iguala la variable pressed a menuSelector2 y se realiza un pase de parametros
    return selected;
}

/**
*La función se encarga de imprimir los controles para el juego
*/
void controles()
{
    int x = 10, y = 5;                                     //Se declara dos variables que serán las coordenadas
    system("cls");                                         //Se limpia la pantalla
    MARCO();                                               //Se vuelve a llamar la función Marco porque se ha borrado la pantalla
    gotoxy(x,y++);
    cout<<"Comandos:\n"<<endl;
    gotoxy(x++,y++);
    cout<<"Usa las siguientes teclas para jugar: "<<endl;
    gotoxy(x,y++);
    cout<<"Flecha derecha"<<endl;
    gotoxy(x,y++);
    cout<<"Flecha izquierda"<<endl;
    gotoxy(x,y++);
    cout<<"Flecha hacia arriba"<<endl;
    gotoxy(x,y++);
    cout<<"Flecha hacia abajo"<<endl;
    gotoxy(x,y++);
    cout<<"Presiona cualquier tecla para continuar..."<<endl;
    waitForAnyKey();                                            //Al final se llama a la función wait for any key para esperar a que el usuario ingrese una tecla
    //Y salga de esa sección
}

/**
*La función se encarga de imprimir los controles para el juego
*/
void reglas()
{
    int x = 10, y = 5;                                     //Se declara dos variables que serán las coordenadas
    system("cls");                                         //Se limpia la pantalla
    MARCO();                                               //Se vuelve a llamar la función Marco porque se ha borrado la pantalla
    gotoxy(x,y++);
    cout<<"Reglas del juego:\n"<<endl;
    gotoxy(x++,y++);
    cout<<"1.-Para empezar a jugar deberas escoger uno de los 4 temas que son: Videojuegos, Arte, Musica y Deportes "<<endl;
    gotoxy(x,y++);
    cout<<"2.-Una vez escogido el tema, el juego te hara 10 preguntas de cuatro subtemas diferentes"<<endl;
    gotoxy(x,y++);
    cout<<"3.-Las respuestas que aciertes de las preguntas sera tu puntuacion"<<endl;
    gotoxy(x,y++);
    cout<<"Presiona cualquier tecla para continuar..."<<endl;
    waitForAnyKey();                                            //Al final se llama a la función wait for any key para esperar a que el usuario ingrese una tecla
    //Y salga de esa sección
}

/**
*La funcion se encarga de preguntarle al usuario si desea o no salir del programa
*/
int  exitYN()
{
    system("cls");                                      //se limpia la pantalla
    MARCO();                                            //se llama a la funcion MARCO para que vuelva a imprimirse el marco pues se limpio la pantalla
    int pressed;                                       //se declara una variable de tipo int
    gotoxy(9,8);                                        //se va a esta coordenada
    cout<<"Seguro que deseas salir?(Y/N)\n"<<endl;      //Se imprime la linea de codigo
    do                                                  //inicia el ciclo do while en donde se iguala la variable pressed con la funcion wait for any key y esta a la
        //expectativa de que presione una opcion el usuario
    {
        pressed = waitForAnyKey();                      //Este ciclo do while dura hasta que el usuario ingrese la respuesta de si quiere seguir o no jugando
    }
    while (!(pressed == 'y' || pressed == 'n'));
    if (pressed == 'y')                                  //Si la opcion es "y" el juegp debera terminar
    {

        gotoxy(13,10);
        cout<<"Saliendo del juego"<<endl;
        gotoxy(13,11);
        cout<<"Hasta luego"<<endl;
        gotoxy(13,12);

    }

}

/**
* Esta función se encarga de desplegar el menú y dejar que usuario escoga la opción
* @return Retorna la variable selected. Esta variable despiega la opción que el usuario haya escogido en el menu
*/
int menu()
{
    MARCO();                                        //se llama a la funcion MARCO para que se imprima al mismo tiempo que el menu
    int x = 10, y = 5;                              //Se declaran las variables x y como enteros
    int yStart = y;                                 //se crea una nueva variable ystart igualada a y
    int selected;                                   //se declara una varia de tipo entero
    gotoxy(x,y++);                                  //La posicion de x(que es el ancho) se encontrara siempre en 5, mientras que y ira aumentando
    cout<<"Nueva partida\n"<<endl;
    gotoxy(x,y++);
    cout<<"Reglas\n"<<endl;
    gotoxy(x,y++);
    cout << "Controles\n"<<endl;
    gotoxy(x,y++);
    cout<<"Salir\n"<<endl;
    gotoxy(x,y++);
    selected = menuSelector(x, y, yStart);          //Para que el menu sea dinamico se debe llamar a la funcion menuSelector. Se pone hasta el final
    //pues debe imprimirse primero el texto para despues poder seleccionar la opcion.
    //Se pasan tres parametros que son las posiciones del cursor.
    return selected;                                //se pide que se retorne la seleccion, para asi, por medio del subrpograma correspondiente
    //se ejecute la opcion elegiga de manera correcta.
}
/**
 * Funcion utilizada para leer la pregunta al usuario
 * @param posRand  ingresa un numero random que determina la posicion de la pregunta a leer
 */
void leerPregunta(int posRand){

    int x = 10, y = 5;
	system("cls");
	MARCO();

    int rand;
    ifstream myFile;
    string pregunta;
    string prev = "";
    string trash; //se usa solo para recorrer el archivo en las lineas que no se necesitan
    try{
        myFile.open("Preguntas1.txt", ios::in);
        if(myFile.is_open()) {
            rand = posRand / 5;
            rand = rand * 5;
            for (int i = 0; i < rand; i++){
                getline(myFile, trash);
            }
            for (int i = 0; i < 5; i++) {
                getline(myFile, pregunta);
                if (pregunta != prev) {
                    prev = pregunta;
                    size_t pos = pregunta.find('*');
                    if (pos != string::npos)
                    {
                        pregunta = pregunta.substr(pos + 1);
                    }
                    gotoxy(x,y++);
                    cout << pregunta << endl;

                }
            }
        } else{
            throw (ifstream::failbit);
        }

    }
    catch(ifstream::failbit& e){
        cout << "No se pudo leer el archivo de las preguntas"<<endl;
    }

}
/**
 * Funcion utilizada para poder comprobar si la respuesta ingresada es la  correcta. Acepta como Parametros el numero de la
 * pregunta y la respuesta que ingreso el usuario. Regresa un entero que es utilizado para sumar la puntuacion.
 * @param posRand
 * @param respuesta
 * @return
 */
int checarRespuesta(int posRand, char respuesta){
    ifstream myFile;
    string pregunta;
    string prev = "";
    string trash;
    int rand;
    int numRespuesta;
    numRespuesta = respuesta - 64;
    if(numRespuesta > 4){
        numRespuesta = respuesta - 96;
    }
    myFile.open("Preguntas1.txt", ios::in);
    if(myFile.is_open()) {
        rand = posRand / 5;
        rand = rand * 5;
        for (int i = 0; i < rand; i++){
            getline(myFile, trash);
        }
        int i = 0;
        while (i < 5){
            getline(myFile, pregunta);
            if (pregunta != prev) {
                prev = pregunta;
                size_t pos = pregunta.find('*');
                if (pos != string::npos)
                {
                    if(i == numRespuesta){
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            i++;
        }
    } else{
        cout << "hla"<<endl;
    }
}

void actualizarPuntuacion(int puntuacion){
    gotoxy(35, 13);
    cout << "Puntuacion Actual: " << puntuacion;
    this_thread::sleep_for(chrono::seconds(2));
    gotoxy(10, 13);
}

void jugarVideoJuegos(){
    int x = 10, y = 5;
    int cont=0;

    srand(time(NULL));
    char respuesta;
    int puntuacion = 0;


    while(cont < 10){

    int numRand = 1 + rand() % 200;
    leerPregunta(numRand);


    do {
        char temp;
        gotoxy(x,y+5);
        cout << "Ingresa la respuesta: ";
        cin >> temp;

        respuesta = toupper(temp);

        if((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D')){
            gotoxy(x,y+7);
            cout << "Respuesta no valida, verifique e intente de nuevo";

        }

    } while((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D'));
    puntuacion += checarRespuesta(numRand, respuesta);
    thread hiloPuntuacion(actualizarPuntuacion, puntuacion);
    cont++;

    hiloPuntuacion.join();
    }
    system("cls");
    gotoxy(10,5);
    MARCO();
    gotoxy(10,6);
    cout << "Gracias por jugar!";
    gotoxy(10,7);
    cout << "Tu Puntuacion fue de: " << puntuacion;
    gotoxy(10,8);
    cout << "Presione una tecla para volver al menu principal";
    gotoxy(10,9);
    waitForAnyKey();

}

void jugarDeportes(){
    int x = 10, y = 5;
    int cont=0;

    srand(time(nullptr));
    char respuesta;
    int puntuacion = 0;


    while(cont < 10){

        int numRand = 601 + rand() % 200;
        leerPregunta(numRand);


        do {
            char temp;
            gotoxy(x,y+5);
            cout << "Ingresa la respuesta: ";
            cin >> temp;

            respuesta = toupper(temp);

            if((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D')){
                gotoxy(x,y+7);
                cout << "Respuesta no valida, verifique e intente de nuevo";

            }

        } while((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D'));

        puntuacion += checarRespuesta(numRand, respuesta);
        thread hiloPuntuacion(actualizarPuntuacion, puntuacion);

        hiloPuntuacion.join();
        cont++;
    }
    system("cls");
    gotoxy(10,5);
    MARCO();
    gotoxy(10,6);
    cout << "Gracias por jugar!";
    gotoxy(10,7);
    cout << "Tu Puntuacion fue de: " << puntuacion;
    gotoxy(10,8);
    cout << "Presione una tecla para volver al menu principal";
    gotoxy(10,9);
    waitForAnyKey();

}

void jugarMusica(){
    int x = 10, y = 5;
    int cont=0;

    srand(time(nullptr));
    char respuesta;
    int puntuacion = 0;


    while(cont < 10){

    int numRand = 401 + rand() % 200;
    leerPregunta(numRand);


    do {
        char temp;
        gotoxy(x,y+5);
        cout << "Ingresa la respuesta: ";
        cin >> temp;

        respuesta = toupper(temp);

        if((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D')){
            gotoxy(x,y+7);
            cout << "Respuesta no valida, verifique e intente de nuevo";

        }

    } while((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D'));

    puntuacion += checarRespuesta(numRand, respuesta);
    thread hiloPuntuacion(actualizarPuntuacion, puntuacion);
    cont++;
    this_thread::sleep_for(chrono::seconds(2));
    hiloPuntuacion.join();
    }
    system("cls");
    gotoxy(10,5);
    MARCO();
    gotoxy(10,6);
    cout << "Gracias por jugar!";
    gotoxy(10,7);
    cout << "Tu Puntuacion fue de: " << puntuacion;
    gotoxy(10,8);
    cout << "Presione una tecla para volver al menu principal";
    gotoxy(10,9);
    waitForAnyKey();

}

void jugarArte(){
    int x = 10, y = 5;
    int cont=0;

    srand(time(nullptr));
    char respuesta;
    int puntuacion = 0;


    while(cont < 10){

    int numRand = 201 + rand() % 200;
    leerPregunta(numRand);


    do {
        char temp;
        gotoxy(x,y+5);
        cout << "Ingresa la respuesta: ";
        cin >> temp;

        respuesta = toupper(temp);

        if((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D')){
            gotoxy(x,y+7);
            cout << "Respuesta no valida, verifique e intente de nuevo";

        }

    } while((respuesta != 'A') && (respuesta != 'B') && (respuesta != 'C') && (respuesta != 'D'));

    puntuacion += checarRespuesta(numRand, respuesta);
    thread hiloPuntuacion(actualizarPuntuacion, puntuacion);
    cont++;
    this_thread::sleep_for(chrono::seconds(2));
    hiloPuntuacion.join();

    }
    system("cls");
    gotoxy(10,5);
    MARCO();
    gotoxy(10,6);
    cout << "Gracias por jugar!";
    gotoxy(10,7);
    cout << "Tu Puntuacion fue de: " << puntuacion;
    gotoxy(10,8);
    cout << "Presione una tecla para volver al menu principal";
    gotoxy(10,9);
    waitForAnyKey();

}

/**
*La función main se encarga de ejecutar el menú y sus funciones correspondientes
* @return Al final cuando el usuario decida salir del menú devolverá un cero la función
*/

int main(){
    int x=10, y=5;
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1200, 500, TRUE);


{
    do                                      //Se declara un do que ejecutará el menú hasta que el valor que regresen no sea 1

    {
        switch(menu())                      //Se pone dentro del switch la función menú que
        {
        case 0:
            switch(temas())         //dentro de este case se declara otro switch que nos permite llamar a los subtemas y a las funciones
            {
                case 0:
                    jugarVideoJuegos();

                    break;

                case 1:
                    jugarDeportes();

                    break;

                case 2:
                    jugarMusica();

                    break;

                case 3:
                    jugarArte();

                    break;
            }
            break;
        case 1:
            reglas();               //se llama a la función reglas
            break;
        case 2:
            controles();                //se llama a la función controles
            break;
        case 3:
            exitYN();                   //se llama a la función exitYN
            return 0;
            break;
        }
    }
    while(1);

    return 0;
}
}
