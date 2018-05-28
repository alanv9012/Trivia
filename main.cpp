
#include <iostream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>
#include <thread>

#define _WIN32_WINNT 0x0500
#define up_arrow 72
#define down_arrow 80
#define left_arrow 75
#define right_arrow 77
#define exit 27
#define pause 112
#define enter_key 13 //valor ascii de enter

using namespace std;

int puntuacionMala;

/**
 * Funcion utilizada para poder leer la pregunta y las respuestas de un archivo de texto.
 * Recibe de parametros un numero que ayuda a encontrar la pregunta.
 * @param posRand
 */


void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
 }

//khbit se utiliza pra determinar si una tecla ha sido presionada o no. Si el usuario presiona una tecla regresa un valor diferente de cero, si no lo presiona regresa un cero


char waitForAnyKey(void)//En esta funcion se utiliza la funcion khbit ya que estamos a la expectativa de saber si el usuario presionara una tecla
{
    //se declara la funcion como int ya que queremos regresar una tecla
	int pressed;//se declara una variable de tipo int ya que se utilizara el codigo ascii
	while(!kbhit());//Mientras no se presione una tecla no se regresara un valor diferente de cero, si se presiona, se regresara lo que este en el return, que es
	//el entero pressed pero se imprime como char para que sea el simbolo en su codigo ascii
	//https://www.quora.com/What-is-KBHIT-in-C-language
	pressed = getch();//Se recoge el valor de pressed con la funcion getch
	//Lee un caracter directamente de la consola sin hacer uso del buffer, y sin mostrar salida
	return pressed;//se pide que se retorne int pressed para poder hacer la accion que se pida en la funcion que
	//invoque esta funcion
}

/*void  pausa()
{
	int i;
	gotoxy(20,13);
	printf("**Pausa**");
	waitForAnyKey();
	gotoxy(20,13);
	printf("            ");
}
*/void MARCO()
{
	int ancho =140, alto=30;                //Se declaran dos variable de tipo entero
	int x = 1, y = 1;                       //Se inicializan dos variables
	int pared = 177;                        //La variable entera se iguala con un valor para despues se usada como codigo ascii
	char tecla;                             //se declara una variable de tipo char
	tecla=pared;                            //Se iguala la variable entera a la variable tipo char
	int alturarectagunlo= alto-4;           //Se crea una nueva variable que sera la altura del rectangulo
	system("cls");                          //Se limpia la pantalla
	gotoxy(x,y);                            //Se va a las coordenas x,y
                                            //Se inicia un ciclo for para imprimir la parte de arrina del rectangulo
                                            //Se escibe un punto y coma antes de y porque la sintaxis del ciclo for no permite escribir si no hay un punto y coma
                                            //Y debe ser menor a la altura del rectangulo y yaumenta
	for (;y<alturarectagunlo; y++)
	{
    //Se devuelve a las coordenadas inciales
		gotoxy(x, y);
		//A partir de ahi se comienza a imrpir las teclas
		cout<<tecla;
    //Se va a las coordenas donde inicia el ancho y donde inicia y
		gotoxy(ancho, y);
    //Se imprime la tecla
		cout<<tecla;
	}
	//Este y igual con uno permite imprimir la linea de arriba de teclas
	y = 1;
	for (;x < ancho+1; x++)//Se vuelve a correr un ciclo for en donde x debe ser menor al ancho +1, seria lo mismo poner que x fuera menor o igual a ancho y x avanza
	{
		gotoxy(x, y);//Inicia la coordenada en x , y y aumenta el ancho
		//Imprime el character
		cout<<tecla;
        //Avanza
		gotoxy(x, alturarectagunlo);
		cout<<tecla;
	}
}


/*void titulo(){
        MARCO();
        int i = 178;
        int x=6, y=6,x1=23,y11=10, y1=8,x2=34, y2=6, y22=8,x3=39, y3=7, x4=55, y4=6,y44=8, x5=61, y5=7,x55=61,x6=60,y6=8,x7=70;
        char tecla;
        tecla=i;
        setcolor(7);
        for(int j=0; j<13; j++){
           gotoxy(x++,y);
            cout<<tecla;
        }  for(int k=0; k<6; k++){
                gotoxy(12,y++);
                cout<<tecla;
        }
        for(int l=0; l<5; l++){
            gotoxy(x1,y1++);
            cout<<tecla;
        }
         for(int m=0; m<3; m++){
            gotoxy(x1++,y11--);
            cout<<tecla;
        }
         for(int n=0; n<3; n++){
            gotoxy(x1++,y11++);
            cout<<tecla;
        }
        for(int o=0; o<1; o++){
            gotoxy(x2,y2);
            cout<<tecla;
        }
         for(int p=0; p<5; p++){
            gotoxy(x2,y22++);
            cout<<tecla;
        }
        for(int q=0; q<5; q++){
            gotoxy(x3++,y3++);
            cout<<tecla;
        }
        for(int q=0; q<6; q++){
            gotoxy(x3++,y3--);
            cout<<tecla;
        }
        for(int o=0; o<1; o++){
            gotoxy(x4,y4);
            cout<<tecla;
        }
         for(int p=0; p<5; p++){
            gotoxy(x4,y44++);
            cout<<tecla;
        }
        for(int p=0; p<10; p++){
        gotoxy(x5++,y5);
        cout<<tecla;
        }
        for(int p=0; p<10; p++){
            gotoxy(x55++,12);
            cout<<tecla;
        }
        for(int p=0; p<4; p++){
            gotoxy(x6,y6++);
            cout<<tecla;
        }
        for(int p=0; p<4; p++){
            gotoxy(x7,y6++);
            cout<<tecla;
        }
}*/


int menuSelector(int x, int y, int yStart)
{
	int llave;//Se declara una variable de tipo int
	int i = 0;//Se inicializa la variable i con cero
	x = x - 2;//X toma el valor de X-2 para que el cursos aparezca separado del texto del menu
	gotoxy(x,yStart);//Se lleva al cursos a la posicion de yStart y a la nueva posicion de x
	cout<<">"<<endl;//Se imprime el cursos
	//se crea un ciclo do while para el movimeinto del cursor

	do
	{
		llave = waitForAnyKey();//La variable char se inicializa a la funcion de waitforanykey porque el cursor estara a la expectativa de si el usuario ingresa una tecla
		//En este primer if se dice que si llave es igual a up_arrow el cursor se mantendra en el ancho que dice x, pero aumentara un entero su posicion en yStart
		//Si en lugar de yStart se pusiera la variable y, al momento de mover el cursor hacia arriba no se eliminaria el cursor como se estipula en el siguienete
		//if statement
		if ( llave == up_arrow )
		{
			gotoxy(x,yStart+i);
			cout<<" "<<endl;
        //En este if statement se considera la situción en donde si el cursor qusiera avanzar más allá de donde esta la primera opcion, el cursor iria hacia la ultima
        //opcion del menu. esto funciona asi: Si yStar es mayor o igual a yStart+i se realiza la correcion en donde i tomara el valor de yStart-(yStart-2) que seria
        //5-2=3 que son los lugares que avanzara el cursor
        //Como yStart sera menos que yStart+1 cuando baje en el menu se declara la siguiente conidicion. Esto quiere decir que como yStart es igual a 5, solamente
        //habra un momento que pueda valer mas o igual que yStart+i que es, si quiere avanzar mas arriba de la primera opcion del menu.
			if (yStart >= yStart+i )
				i = y - yStart -2;
			else
        //Si la condicion anterior propuesta no es verdad entonces i disminuirá y se restará el valor de yStart con i
				i--;
        //Imprimira el cursor en donde se encuentra la nueva coordenada
			gotoxy(x,yStart+i);
			cout<<">"<<endl;
		}
		else
        //En el siguiente if statmente se dice que si llave es igual a la tecla de abajo se hara lo siguiente
			if ( llave == down_arrow )
			{
        //Imprimira un vacio en donde antes estaba el cursor
				gotoxy(x,yStart+i);
				cout<<" "<<endl;
        //Se vuelve a realizar un if statement para revisar que el cursor no vaya mas arriba de la ultima opcion
        //Si i+2 es mayor o igual a y-yStart i debera valer cero, lo que significa que no se movera yStart, se quedara inmovil en esa posicion
				if (i+2 >= y - yStart )
					i = 0;
				else
        //En cambio si i+2 es menor o igual que y-yStart el cursor si se imprimira en la linea de codigo arriba de en la que este
					i++;
				gotoxy(x,yStart+i);
        //Va hacia la cordenada e imprime el cursor
				cout<<">"<<endl;
			}
    //Hasta aqui llega el final del do while y la condicion se cumple siempre y cuando la llave sea diferente de la tecla enter (mas arriba se definio)
	} while(llave != enter_key);
	return i;
}

void controles(){
	int x = 10, y = 5;
	system("cls");
	MARCO();
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
	waitForAnyKey();
}


void  exitYN()
{
    system("cls");//se limpia la pantalla
    MARCO();//se llama a la funcion MARCO para que vuelva a imprimirse el marco pues se limpio la pantalla
	char pressed;//se declara una variable de tipo char
	gotoxy(9,8);//se va a esta coordenada
	cout<<"Seguro que deseas salir?(Y/N)\n"<<endl;//Se imprime la linea de codigo
    //inicia el ciclo do while en donde se iguala la variable pressed con la funcion wait for any key y esta a la expectativa de que presione una opcion el usuario
	do
	{
		pressed = waitForAnyKey();
    //Este ciclo do while dura hasta que el usuario ingrese la respuesta de si quiere seguir o no jugando
	} while (!pressed == 'y' || pressed == 'n');
    //Si la opcion es "y" el juegp debera terminar
	if (pressed == 'y' || pressed == 'Y')
	{
            gotoxy(13,10);
            cout<<"Saliendo del juego"<<endl;
            gotoxy(13,11);
            cout<<"Hasta luego"<<endl;
            gotoxy(13,12);
            abort();
	}
}

int menu()
{
    MARCO();//se llama a la funcion MARCO para que se imprima al mismo tiempo que el menu
    int x = 10, y = 5;//Se declaran las variables x y como enteros
	int yStart = y;//se crea una nueva variable ystart igualada a y con el fin de que se cree un loop en donde cuando se llegue al final del menu se reinicie la posicion
	//del puntero
	int selected;//se declara una varia de tipo entero
	gotoxy(x,y++);//La posicion de x(que es el ancho) se encontrara siempre en 5, mientras que y irá aumentando para imprimir la siguiente linea de codigo
	cout<<"Nueva partida\n"<<endl;//Impresion de nueva linea de texto
	gotoxy(x,y++);//La posicion de x(que es el ancho) se encontrara siempre en 5, mientras que y irá aumentando para imprimir la siguiente linea de codigo
	cout<<"Mejores puntuaciones\n"<<endl;//Impresion de nueva linea de texto
	gotoxy(x,y++);//La posicion de x(que es el ancho) se encontrara siempre en 5, mientras que y irá aumentando para imprimir la siguiente linea de codigo
	cout<<"Controles\n"<<endl;//Impresion de nueva linea de texto
	gotoxy(x,y++);//La posicion de x(que es el ancho) se encontrara siempre en 5, mientras que y irá aumentando para imprimir la siguiente linea de codigo
	cout<<"Salir\n"<<endl;//Impresion de nueva linea de texto
	gotoxy(x,y++);//La posicion de x(que es el ancho) se encontrara siempre en 5, mientras que y irá aumentando para imprimir la siguiente linea de codigo
	selected = menuSelector(x, y, yStart);//Pra que el menu sea dinamico se debe llamar a la funcion menuSelector. Se pone hasta el final pues debe imprimirse primero
	//el texto para despues poder seleccionar la opcion. Se pasan tres parametros que son las posiciones del cursor.
	return(selected);//se pide que se retorne la seleccion, para asi, por medio del subrpograma correspondiente se ejecute la opcion elegiga de manera correcta.
}

void leerPregunta(int posRand){

    int x = 10, y = 5;
	system("cls");
	MARCO();

    int rand;
    ifstream myFile;
    string pregunta;
    string prev = "";
    string trash;
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
        cout << "hla"<<endl;
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
                        puntuacionMala = puntuacionMala + 1;
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
    gotoxy(10, 12);
    cout << "Puntuacion Actual: " << puntuacion;
}

void jugarJuego(){
    int x = 10, y = 5;
    int cont=0;

    srand(time(NULL));
    char respuesta;
    int puntuacion;
    //thread hiloPuntuacion;

    while(cont < 10){

    int numRand = 1 + rand() % 400;
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
   // hiloPuntuacion = thread(&actualizarPuntuacion, puntuacion);
    }
}

int main(){

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1200, 500, TRUE);
	do
	{
		switch(menu())
		{
		    system("color 90");
			case 0:
			    jugarJuego();


			    system("PAUSE");
				break;
			case 1:
				break;
			case 2:
                controles();
				break;
			case 3:
				exitYN();
				break;
		}
	} while(1);

	return 0;
}
