#include "pch.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#define MAXFILAS 17
#define MAXCOL 25
using namespace std;
using namespace System;

//estructura para establecer el nombre y el dado
typedef struct {
	char nombre[20];
	char p;
	int dado;
}t_jugador;

//funciona que genera el tablero
void generar_mapa(char** Mmapa) {
	char matriz[MAXFILAS][MAXCOL] = {
									{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','A',' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','A',' ','A',' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ','A',' ','A',' ','A',' ','A',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{'B',' ','B',' ','B',' ','B',' ','O',' ','O',' ','O',' ','O',' ','O',' ','F',' ','F',' ','F',' ','F'},
									{' ','B',' ','B',' ','B',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','F',' ','F',' ','F',' '},
									{' ',' ','B',' ','B',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','F',' ','F',' ',' '},
									{' ',' ',' ','B',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','F',' ',' ',' '},
									{' ',' ',' ',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ',' ',' ',' '},
									{' ',' ',' ','C',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','E',' ',' ',' '},
									{' ',' ','C',' ','C',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','E',' ','E',' ',' '},
									{' ','C',' ','C',' ','C',' ','O',' ','O',' ','O',' ','O',' ','O',' ','O',' ','E',' ','E',' ','E',' '},
									{'C',' ','C',' ','C',' ','C',' ','O',' ','O',' ','O',' ','O',' ','O',' ','E',' ','E',' ','E',' ','E'},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ','D',' ','D',' ','D',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ','D',' ','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
									};

	int fila, columna;
	for (fila = 0; fila < MAXFILAS; fila++) { //inicializa el mapa
		for (columna = 0; columna < MAXCOL; columna++) {
			Mmapa[fila][columna] = matriz[fila][columna]; 
		}
	}
}

void dibujar_mapa(char** Mmapa) {
	//PARA LOS COLORES
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbi;

	int fila, columna;
	cout << "\t0123456789012345678901234" << "\n";

	for (fila = 0; fila < MAXFILAS; fila++) { //controla las filas

		if (fila >= 0 && fila < MAXCOL) cout << fila << "\t"; 
		else cout << fila << "\t";

		for (columna = 0; columna < MAXCOL; columna++) { //controla las columnas

			switch (Mmapa[fila][columna]) { //switch para controlar los colores
			
			case 'A':
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); //color verde
				break;
			case 'B':
				SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY); //color azul
				break;
			case 'O':
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //color blanco
				break;
			case 'C':
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); //color red
				break;
			case 'D':
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //color amarillo
				break;
			case 'E':
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE); //color celeste
				break;
			case 'F':
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); //color fucsia
				break;

			}

			cout << Mmapa[fila][columna];
		}
		
		cout << endl;
	}

	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //restablecer color
	cout << "\t0123456789012345678901234" << "\n";
	cout << endl;
}


void mover_ficha(int coordx, int coordy, int destx, int desty, int direccion, char** Mmapa) {
	char aux;
	switch (direccion) {
	case 1:
		destx = coordx - 1;
		desty = coordy - 1;
		break;
	case 2:
		destx = coordx - 1;
		desty = coordy + 1;
		break;
	case 3:
		destx = coordx;
		desty = coordy + 2;
		break;
	case 4:
		destx = coordx;
		desty = coordy - 2;
		break;
	case 5:
		destx = coordx + 1;
		desty = coordy + 1;
		break;
	case 6:
		destx = coordx + 1;
		desty = coordy - 1;
		break;
	}
	aux = Mmapa[destx][desty];
	Mmapa[destx][desty] = Mmapa[coordx][coordy];
	Mmapa[coordx][coordy] = aux;
}


//funcion para generar el menu
int menu() {
	int opcion;
	cout << "      .:MENU:." << endl;
	cout << "--------------------" << endl;
	cout << "1) Bienvenida" << endl;
	cout << "2) Instrucciones" << endl;
	cout << "3) Cartel winner" << endl;
	cout << "4) Creditos" << endl;
	cout << "5) Empezar juego" << endl << endl;

	do { //bucle para controlar el ingreso de opcione
		cout << ">_Ingrese su opcion: ";
		cin >> opcion;
	} while (opcion < 1 || opcion>5);

	cout << endl;
	return opcion;
}

bool victoria(char** Mmapa) {
	if (Mmapa[0][12] == Mmapa[1][11] == Mmapa[1][13] == Mmapa[2][10] == Mmapa[2][12] ==
		Mmapa[2][14] == Mmapa[3][9] == Mmapa[3][11] == Mmapa[3][13] == Mmapa[3][15] == 'D') {
		return false;
	}

	else if (Mmapa[13][9] == Mmapa[13][11] == Mmapa[13][13] == Mmapa[13][15] == Mmapa[14][10] ==
		Mmapa[14][12] == Mmapa[14][14] == Mmapa[15][11] == Mmapa[15][13] == Mmapa[16][12] == 'A' ) {
		return false;
	}
	else return true;
}

void pedir_datos(t_jugador* Vjugadores) {
	int i;
	cout << "DATOS DE LOS JUGADORES" << endl;
	cout << "-----------------------\n\n";
	for (i = 1; i <= 2; i++) {
		cout << "Jugador " << i << "\n";
		cout << "  Digite su nickname: ";
		cin >> Vjugadores[i].nombre;
	}
	cout << endl;
}

void bienvenida() {
	char b = 219;
	cout << "\n            " << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b;
	cout << "\n            " << b << "BIENVENIDOS AL JUEGO DE DAMAS CHINAS" << b << endl;
	cout << "            " << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << endl << endl << endl;
	cout << "                             *                         " << endl;
	cout << "                           +**                         " << endl;
	cout << "                          :***                          " << endl;
	cout << "                          *****                         " << endl;
	cout << "                *         ******                        " << endl;
	cout << "               *          ********            *         " << endl;
	cout << "              :*           ********           **         " << endl;
	cout << "              **:           ********          **         " << endl;
	cout << "              ***            *******         +**         " << endl;
	cout << "              ***              *****         ***         " << endl;
	cout << "              ****              ****        ****         " << endl;
	cout << "              -****             :**        *****         " << endl;
	cout << "               ******            *       -*****          " << endl;
	cout << "                ******+                +******           " << endl;
	cout << "                 *********=        .*********             " << endl;
	cout << "                  *************************             " << endl;
	cout << "                    **********************               " << endl;
	cout << "                       ****************                  " << endl;
	cout << "                            ******          " << endl;
}

void generar_cartel(int** Mcartel) {
	int cartel[23][15] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,1,0,1,0,1,1,1,0,1,0,1,0,0},
							{0,0,0,1,0,0,1,0,1,0,1,0,1,0,0},
							{0,0,0,1,0,0,1,0,1,0,1,0,1,0,0},
							{0,0,0,1,0,0,1,1,1,0,1,1,1,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,2,0,0,0,2,0,2,0,2,0,0,0,2,0},
							{0,2,0,0,0,2,0,2,0,2,0,0,0,2,0},
							{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0},
							{0,2,0,0,0,2,0,2,0,2,2,0,0,2,0},
							{0,2,0,0,0,2,0,2,0,2,2,0,0,2,0},
							{0,2,0,2,0,2,0,2,0,2,2,0,0,2,0},
							{0,2,0,2,0,2,0,2,0,2,0,2,0,2,0},
							{0,2,0,2,0,2,0,2,0,2,0,2,0,2,0},
							{0,2,0,2,0,2,0,2,0,2,0,2,0,2,0},
							{0,2,0,2,0,2,0,2,0,2,0,0,2,2,0},
							{0,2,0,2,0,2,0,2,0,2,0,0,2,2,0},
							{0,2,0,2,0,2,0,2,0,2,0,0,2,2,0},
							{0,2,2,2,2,2,0,2,0,2,0,0,0,2,0},
							{0,2,2,2,2,2,0,2,0,2,0,0,0,2,0},
							{0,2,2,2,2,2,0,2,0,2,0,0,0,2,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };


	int fila, columna;
	for (fila = 0; fila < 23; fila++) { //inicializa el cartel
		for (columna = 0; columna < 15; columna++) {
			Mcartel[fila][columna] = cartel[fila][columna];
		}
	}
}

void dibujar_cartel(int** Mcartel) {
	//PARA LOS COLORES
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	int fila, columna;

	for (fila = 0; fila < 23; fila++) { //controla las filas

		for (columna = 0; columna < 15; columna++) { //controla las columnas

			switch (Mcartel[fila][columna]) { //switch para controlar los colores

			case 0:
				cout << "      ";
				break;
			case 1:
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY); //color verde
				cout << "XXXXXX";
				break;
			case 2:
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE); //color celeste
				cout << "XXXXXX";
				break;
			}

		}

		cout << endl;
	}

	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); //restablecer color
	cout << endl;
}



void instrucciones() {
	cout << ".:INSTRUCCIONES:." << endl;
	cout << "------------------" << endl;
	cout << "\nLa finalidad del juego es trasladar todas las fichas desde una punta de la estrella\n";
	cout << "hasta la punta opuesta, antes que los demas jugadores.\n";

	cout << "\nLos jugadores deben colocar sus fichas en triangulos (o puntas de estrella) opuestas\n";
	cout << "y mover susfichas hasta el triangulo donde ha empezado su competidor.\n";

	cout << "\nMOVIMIENTOS BASICOS:\n\tCada jugador puede mover solo una ficha por turno.\n";
	cout << "\tLas fichas pueden moverse a una casilla que se encuentre libre adelante o a un lado de donde se\n";
	cout << "\tencuentran, pero no pueden retroceder. Tambien pueden ?saltar? sobre otra ficha para caer en una\n";
	cout << "\tcasilla vacia junto a esta. Si el movimiento es de este segundo tipo (un salto), y conduce la ficha a\n";
	cout << "\tuna casilla contigua a otra ocupada, puede volver a ?saltar? esta segunda ficha en el mismo turno,\n";
	cout << "\ty asi sucesivamente. De esta manera, en un solo turno, una ficha puede avanzar de una punta del\n";
	cout << "\ttablero a otra si la situaci?n es propicia.\n";
	cout << "\tEl jugador que tenga la habilidad de colocar sus canicas en forma parecida a una escalera podr? ir\n";
	cout << "\tsaltando de una a otra, incluso usando las fichas de sus contrincantes, y ocupar la punta de\n";
	cout << "\testrella opuesta mas rapidamente.\n";

	cout << "\nEl juego termina cuando uno de los jugadores logra colocar sus 6 fichas en el triangulo opuesto al suyo.\n";
}

void creditos() {
	cout << ".:CREDITOS:." << endl;
	cout << "------------" << endl << endl;
	cout << "Trabajo Final de Programacion I elaborado por:" << endl;
	cout << "- Alumno 1" << endl;
	cout << "- Alumno 2" << endl;
	cout << "- kurumii002"<< endl << endl;
}

int main() {
	char** Mmapa, matriz;
	int** Mcartel;
	int opcion,volver;
	char j1ficha, j2ficha, auxficha, aux;
	int i, j, dado1, dado2, turno, coordx, coordy, destx, desty, direccion;

	t_jugador* Vjugadores = new t_jugador[2];
	srand(time(NULL));

	//generar mapa
	Mmapa = new char* [MAXFILAS];
	for (i = 0; i < MAXFILAS; i++) {
		Mmapa[i] = new char[MAXCOL];
	}

	//generar cartel
	Mcartel = new int* [23];
	for (i = 0; i < 23; i++) {
		Mcartel[i] = new int[15];
	}

	//buvle para controlar las opciones del menu
	do { 
		opcion = menu();
		switch (opcion) {
			case 1: {
				do {
					system("cls");
					bienvenida();
					cout << endl << ">_Presione 0 para volver al menu: ";
					cin >> volver;
				} while (volver != 0);
				system("cls");
				//system("pause>NULL");
				//system("cls");
				break;
			}
			case 2: {
				do {
					system("cls");
					instrucciones();
					cout << endl << ">_Presione 0 para volver al menu: ";
					cin >> volver;
				} while (volver != 0);
				system("cls");
				break;
			}
				
			case 3: {
				do {
					system("cls");
					generar_cartel(Mcartel);
					dibujar_cartel(Mcartel);
					cout << endl << ">_Presione 0 para volver al menu: ";
					cin >> volver;
				} while (volver != 0);
				system("cls");
				break;
			}

			case 4: {
				do {
					system("cls");
					creditos();
					cout << endl << ">_Presione 0 para volver al menu: ";
					cin >> volver;
				} while (volver != 0);
				system("cls");
				break;
			}
			
		}
	} while (opcion != 5);
	
	if (opcion == 5) {
		system("cls");
		pedir_datos(Vjugadores);
		do {
			generar_mapa(Mmapa);
			dibujar_mapa(Mmapa);
			cout << ">_Escoja una region (A / B / C / D / E / F): ";
			cin >> j1ficha; j1ficha = toupper(j1ficha);

		} while ((j1ficha != 'A') && (j1ficha != 'B') && (j1ficha != 'C') && (j1ficha != 'D') && (j1ficha != 'E') && (j1ficha != 'F'));

		//setea la region del P1 Y P2
		switch (j1ficha) {
		case 'A':
			j2ficha = 'D';
			break;
		case 'B':
			j2ficha = 'E';
			break;
		case 'C':
			j2ficha = 'F';
			break;
		case 'D':
			j2ficha = 'A';
			break;
		case 'E':
			j2ficha = 'B';
			break;
		case 'F':
			j2ficha = 'C';
			break;
		}

		cout << "\t> " << Vjugadores[1].nombre << " -> " << j1ficha << endl;
		cout << "\t> " << Vjugadores[2].nombre << " -> " << j2ficha << endl << endl;
		cout << ">>>> RESULTADO DE LOS DADOS: \n";

		do {
			//obtiene el valor
			for (i = 1; i <= 2; i++) {
				Vjugadores[i].dado = rand() % 6 + 1;
			}

		} while (Vjugadores[1].dado == Vjugadores[2].dado);


		for (i = 1; i <= 2; i++) {
			cout << "\t> " << Vjugadores[i].nombre << ": " << Vjugadores[i].dado << endl;
		}

		cout << endl;

		if (Vjugadores[2].dado > Vjugadores[1].dado) {
			cout << "> Comienza " << Vjugadores[2].nombre << endl;
			auxficha = j1ficha;
			j1ficha = j2ficha;
			j2ficha = auxficha;
		}
		else {
			cout << "> Comienza " << Vjugadores[1].nombre << endl;
		}

		while (victoria(Mmapa)) {
			for (turno = 1; turno > 0; turno++) {

				if ((turno % 2) == 1) {
					do {
						cout << ">_Ingrese la fila de la ficha a mover: "; cin >> coordx;
						cout << ">_Ingrese la columna de la ficha a mover: "; cin >> coordy;

					} while ((Mmapa[coordx][coordy]) != j1ficha);
					do {
						cout << "\n>>> Mover Ficha" << endl;
						cout << "\t\t\t\t" << "   [1]  [2]" << endl;
						cout << "\t\t\t\t" << "[4]        [3]" << endl;
						cout << "\t\t\t\t" << "   [6]  [5]" << endl << endl;
						cout << "(1: up-left, 2: up-right, 3: right, 4: left, 5: down-right, 6: down-left): ";
						cin >> direccion;
					} while ((direccion < 1) || (direccion > 6));
					mover_ficha(coordx, coordy, destx, desty, direccion, Mmapa);


				}
				if ((turno % 2) == 0) {
					do {
						cout << ">_Ingrese la fila de la ficha a mover: "; cin >> coordx;
						cout << ">_Ingrese la columna de la ficha a mover: "; cin >> coordy;

					} while ((Mmapa[coordx][coordy]) != j2ficha);
					do {
						cout << "\n>>> Mover Ficha" << endl;
						cout << "\t\t\t\t" << "   [1]  [2]" << endl;
						cout << "\t\t\t\t" << "[4]        [3]" << endl;
						cout << "\t\t\t\t" << "   [6]  [5]" << endl << endl;
						cout << "(1: up-left, 2: up-right, 3: right, 4: left, 5: down-right, 6: down-left): ";
						cin >> direccion;
					} while ((direccion < 1) || (direccion > 6));
					mover_ficha(coordx, coordy, destx, desty, direccion, Mmapa);


				}
				system("cls");
				dibujar_mapa(Mmapa);

			}

		}

		//generar_mapa(Mmapa);
		//dibujar_mapa(Mmapa);

	}





	//delete
	for (i = 0; i < MAXFILAS; i++) {
		delete[]Mmapa[i];
	}
	delete[]Mmapa;

	system("pause");

	return 0;
}

