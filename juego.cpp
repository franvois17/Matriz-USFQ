
/*
 * ============================================================
 *  JUEGO DEL CALAMAR - Prueba de los Vidrios
 * ============================================================
 *  Programa didactico para aprender matrices en C++.
 *
 *  Descripcion:
 *  El jugador debe cruzar un tablero saltando sobre vidrios.
 *  Algunos vidrios son seguros y otros son falsos. Si el
 *  jugador pisa un vidrio falso, pierde. Si llega al otro
 *  extremo del tablero, gana.
 *
 *  Conceptos de matrices utilizados:
 *  - Declaracion de matrices bidimensionales
 *  - Recorrido con ciclos anidados
 *  - Acceso a elementos con [i][j]
 *  - Paso de matrices a funciones
 *  - Modificacion de elementos en la matriz
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>     // Para numeric_limits
#include <windows.h>  // Para colores en consola Windows

using namespace std;

// ============================================================
// CONSTANTES GLOBALES
// ============================================================
const int FILAS = 6;
const int COLS  = 6;

const int VIDRIO_SEGURO  = 0;
const int VIDRIO_MALO    = 1;
const int JUGADOR        = 2;
const int CAMINO         = 3;

const int VIDAS_INICIAL  = 3;

// ============================================================
// COLORES PARA CONSOLA WINDOWS
// ============================================================
// Usamos la API de Windows para cambiar colores en la consola.
// Cada color es un numero que combina fondo y texto.
// Esto hace el juego mucho mas visual y atractivo.
HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

void color(int c) {
    SetConsoleTextAttribute(hConsola, c);
}

// Constantes de colores
const int BLANCO        = 15;
const int GRIS          = 8;
const int ROJO          = 12;
const int VERDE         = 10;
const int AMARILLO      = 14;
const int CYAN          = 11;
const int MAGENTA       = 13;
const int AZUL          = 9;
const int ROJO_FONDO    = 79;   // Fondo rojo, texto blanco
const int VERDE_FONDO   = 47;   // Fondo verde, texto blanco
const int AZUL_FONDO    = 31;   // Fondo azul, texto blanco
const int AMARILLO_FONDO = 110; // Fondo amarillo, texto negro

// ============================================================
// FUNCION: limpiarBuffer
// ============================================================
// Limpia completamente el buffer de entrada de cin.
// Si cin esta en estado de error (por ejemplo, el usuario
// escribio letras donde se esperaba un numero), lo resetea.
// Esto evita que el programa se crashee o entre en loop infinito.
void limpiarBuffer() {
    cin.clear();  // Resetear flags de error de cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar todo hasta el \n
}

// ============================================================
// FUNCION: pausar
// ============================================================
// Muestra "Presiona ENTER..." y espera a que el usuario presione.
// Limpia el buffer antes de esperar para evitar que se salte.
void pausar() {
    cout << "    Presiona ENTER...";
    limpiarBuffer();
    cin.get();
}

// ============================================================
// FUNCION: limpiarPantalla
// ============================================================
// Limpia la consola usando el comando cls de Windows.
void limpiarPantalla() {
    system("cls");
}

// ============================================================
// FUNCION: inicializarTablero
// ============================================================
// Recorre toda la matriz y pone cada celda en VIDRIO_SEGURO (0).
void inicializarTablero(int tablero[][COLS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLS; j++) {
            tablero[i][j] = VIDRIO_SEGURO;
        }
    }
}

// ============================================================
// FUNCION: mostrarVidas
// ============================================================
// Muestra las vidas restantes con corazones de color.
void mostrarVidas(int vidas) {
    cout << "    Vidas: ";
    for (int i = 0; i < VIDAS_INICIAL; i++) {
        if (i < vidas) {
            color(ROJO);
            cout << " <3";
        } else {
            color(GRIS);
            cout << " --";
        }
    }
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: mostrarBanner
// ============================================================
// Muestra el banner principal del juego con arte ASCII grande
// y colores. Esto hace la presentacion mas impactante.
void mostrarBanner() {
    limpiarPantalla();
    cout << endl;
    color(ROJO);
    cout << "    _______.  ______      __    __   __   _______  " << endl;
    cout << "   /       | /  __  \\    |  |  |  | |  | |       \\ " << endl;
    cout << "  |   (----`|  |  |  |   |  |  |  | |  | |  .--.  |" << endl;
    cout << "   \\   \\    |  |  |  |   |  |  |  | |  | |  |  |  |" << endl;
    cout << "    \\   \\   |  `--'  '--.|  `--'  | |  | |  '--'  |" << endl;
    cout << "     \\   \\   \\_____\\_____\\\\______/  |__| |_______/ " << endl;
    cout << "      \\   \\                                        " << endl;
    color(MAGENTA);
    cout << "    _______      ___      .___  ___.  _______     " << endl;
    cout << "   /  _____|    /   \\     |   \\/   | |   ____|    " << endl;
    cout << "  |  |  __     /  ^  \\    |  \\  /  | |  |__       " << endl;
    cout << "  |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|      " << endl;
    cout << "  |  |__| |  /  _____  \\  |  |  |  | |  |____     " << endl;
    cout << "   \\______| /__/     \\__\\ |__|  |__| |_______|    " << endl;
    cout << endl;
    color(CYAN);
    cout << "  ========================================================" << endl;
    cout << "  ||                    USFQ                            ||" << endl;
    color(AMARILLO);
    cout << "  ||           P R U E B A  D E  L O S                 ||" << endl;
    cout << "  ||               V I D R I O S                       ||" << endl;
    color(CYAN);
    cout << "  ||                                                    ||" << endl;
    color(GRIS);
    cout << "  ||   Cruza el puente de vidrio sin caer al vacio.    ||" << endl;
    cout << "  ||   Algunos vidrios son falsos... elige bien.       ||" << endl;
    color(CYAN);
    cout << "  ||                                                    ||" << endl;
    cout << "  ========================================================" << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: mostrarTablero
// ============================================================
// Imprime el tablero con colores y formato visual mejorado.
// Cada tipo de celda tiene su propio color.
void mostrarTablero(int tablero[][COLS], int vidas, int turno) {
    cout << endl;
    color(CYAN);
    cout << "  +======================================================+" << endl;
    cout << "  ||";
    color(AMARILLO);
    cout << "  SQUID GAME - Puente de Vidrio";
    color(GRIS);
    cout << "    Turno: " << setw(2) << turno;
    color(CYAN);
    cout << "    ||" << endl;
    cout << "  +======================================================+" << endl;
    color(BLANCO);
    cout << endl;

    mostrarVidas(vidas);
    cout << endl;

    // Etiqueta INICIO
    color(VERDE);
    cout << "         ";
    for (int j = 0; j < COLS; j++) {
        if (j == COLS / 2 - 1) cout << "  INICIO  ";
        else if (j != COLS / 2) cout << "    ";
    }
    cout << endl;
    color(BLANCO);

    // Numeros de columna
    cout << "         ";
    color(GRIS);
    for (int j = 0; j < COLS; j++) {
        cout << "  " << j << "  ";
    }
    cout << endl;
    color(BLANCO);

    // Linea superior
    cout << "       ";
    color(CYAN);
    for (int j = 0; j < COLS; j++) {
        cout << "+----";
    }
    cout << "+" << endl;
    color(BLANCO);

    // Filas del tablero
    for (int i = 0; i < FILAS; i++) {
        color(GRIS);
        cout << "   " << i << "   ";
        color(BLANCO);

        for (int j = 0; j < COLS; j++) {
            color(CYAN);
            cout << "|";

            if (tablero[i][j] == JUGADOR) {
                color(VERDE_FONDO);
                cout << " P  ";
            } else if (tablero[i][j] == CAMINO) {
                color(GRIS);
                cout << " .. ";
            } else {
                // Vidrios (seguros y malos se ven iguales)
                color(AZUL_FONDO);
                cout << " ## ";
            }
        }
        color(CYAN);
        cout << "|" << endl;

        // Linea divisoria
        cout << "       ";
        for (int j = 0; j < COLS; j++) {
            cout << "+----";
        }
        cout << "+" << endl;
        color(BLANCO);
    }

    // Etiqueta META
    color(AMARILLO);
    cout << "         ";
    for (int j = 0; j < COLS; j++) {
        if (j == COLS / 2 - 1) cout << "== META ==";
        else if (j != COLS / 2) cout << "     ";
    }
    cout << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: mostrarTableroPreparacion
// ============================================================
// Muestra el tablero durante la colocacion de trampas,
// revelando los vidrios malos con color rojo para que
// quien prepara el juego vea donde los puso.
void mostrarTableroPreparacion(int tablero[][COLS]) {
    cout << endl;
    color(MAGENTA);
    cout << "  +======================================================+" << endl;
    cout << "  ||";
    color(AMARILLO);
    cout << "     PREPARACION - Colocando trampas              ";
    color(MAGENTA);
    cout << "||" << endl;
    cout << "  +======================================================+" << endl;
    color(BLANCO);
    cout << endl;

    // Numeros de columna
    cout << "         ";
    color(GRIS);
    for (int j = 0; j < COLS; j++) {
        cout << "  " << j << "  ";
    }
    cout << endl;
    color(BLANCO);

    // Linea superior
    cout << "       ";
    color(MAGENTA);
    for (int j = 0; j < COLS; j++) {
        cout << "+----";
    }
    cout << "+" << endl;
    color(BLANCO);

    // Filas
    for (int i = 0; i < FILAS; i++) {
        color(GRIS);
        cout << "   " << i << "   ";

        for (int j = 0; j < COLS; j++) {
            color(MAGENTA);
            cout << "|";

            if (tablero[i][j] == VIDRIO_MALO) {
                color(ROJO_FONDO);
                cout << " XX ";
            } else if (i == 0 && j == 0) {
                color(VERDE_FONDO);
                cout << " S  ";
            } else {
                color(AZUL_FONDO);
                cout << " ## ";
            }
        }
        color(MAGENTA);
        cout << "|" << endl;

        cout << "       ";
        for (int j = 0; j < COLS; j++) {
            cout << "+----";
        }
        cout << "+" << endl;
        color(BLANCO);
    }

    cout << endl;
    color(VERDE);
    cout << "    ## ";
    color(GRIS);
    cout << "= Vidrio seguro   ";
    color(ROJO);
    cout << "XX ";
    color(GRIS);
    cout << "= Vidrio MALO   ";
    color(VERDE);
    cout << "S ";
    color(GRIS);
    cout << "= Inicio" << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: marcarVidriosMalos
// ============================================================
// Pide al usuario las coordenadas (i, j) de los vidrios malos.
// Muestra el tablero actualizado despues de cada colocacion.
void marcarVidriosMalos(int tablero[][COLS]) {
    int cantidad;

    mostrarTableroPreparacion(tablero);

    color(AMARILLO);
    cout << "    Cuantos vidrios malos quieres colocar? ";
    color(BLANCO);
    cin >> cantidad;
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cantidad = 5; }

    int maxTrampas = (FILAS * COLS) - 2;
    if (cantidad < 1 || cantidad > maxTrampas) {
        color(ROJO);
        cout << "    Cantidad no valida. Se usaran 5." << endl;
        color(BLANCO);
        cantidad = 5;
    }

    cout << endl;
    color(CYAN);
    cout << "    Formato: fila,columna (ejemplo: 2,3)" << endl;
    cout << "    Rango: filas [0-" << FILAS - 1 << "], columnas [0-" << COLS - 1 << "]" << endl;
    color(BLANCO);
    cout << endl;

    for (int k = 0; k < cantidad; k++) {
        int fila, col;
        char coma;

        color(AMARILLO);
        cout << "    Trampa #" << (k + 1) << " de " << cantidad << ": ";
        color(BLANCO);
        cin >> fila >> coma >> col;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            color(ROJO);
            cout << "    >> Entrada invalida. Usa numeros: fila,columna" << endl;
            color(BLANCO);
            k--;
            continue;
        }

        if (coma != ',') {
            color(ROJO);
            cout << "    >> Formato incorrecto. Usa: fila,columna" << endl;
            color(BLANCO);
            k--;
            continue;
        }

        if (fila < 0 || fila >= FILAS || col < 0 || col >= COLS) {
            color(ROJO);
            cout << "    >> Posicion fuera del tablero!" << endl;
            color(BLANCO);
            k--;
            continue;
        }

        if (fila == 0 && col == 0) {
            color(ROJO);
            cout << "    >> No puedes poner trampa en el inicio!" << endl;
            color(BLANCO);
            k--;
            continue;
        }

        if (tablero[fila][col] == VIDRIO_MALO) {
            color(ROJO);
            cout << "    >> Ya hay una trampa ahi. Elige otra posicion." << endl;
            color(BLANCO);
            k--;
            continue;
        }

        tablero[fila][col] = VIDRIO_MALO;

        limpiarPantalla();
        mostrarTableroPreparacion(tablero);

        color(VERDE);
        cout << "    Trampa #" << (k + 1) << " colocada en [" << fila << "," << col << "]" << endl;
        color(BLANCO);
    }

    cout << endl;
    color(VERDE);
    cout << "    Todas las trampas han sido colocadas!" << endl;
    color(BLANCO);
}

// ============================================================
// FUNCION: generarVidriosMalosAleatorios
// ============================================================
// Coloca vidrios malos en posiciones aleatorias.
void generarVidriosMalosAleatorios(int tablero[][COLS], int cantidad) {
    srand(time(0));

    int colocados = 0;
    while (colocados < cantidad) {
        int fila = rand() % FILAS;
        int col  = rand() % COLS;

        if (fila == 0 && col == 0) continue;
        if (tablero[fila][col] == VIDRIO_MALO) continue;

        tablero[fila][col] = VIDRIO_MALO;
        colocados++;
    }
}

// ============================================================
// FUNCION: esMovimientoValido
// ============================================================
bool esMovimientoValido(int fila, int col) {
    return (fila >= 0 && fila < FILAS && col >= 0 && col < COLS);
}

// ============================================================
// FUNCION: esMovimientoAdyacente
// ============================================================
// Solo permite movimiento a casillas adyacentes (no diagonal).
bool esMovimientoAdyacente(int filaAct, int colAct, int filaDest, int colDest) {
    int difFila = filaAct - filaDest;
    int difCol  = colAct  - colDest;
    if (difFila < 0) difFila = -difFila;
    if (difCol < 0)  difCol  = -difCol;
    return (difFila + difCol == 1);
}

// ============================================================
// FUNCION: verificarVictoria
// ============================================================
bool verificarVictoria(int filaJugador) {
    return (filaJugador == FILAS - 1);
}

// ============================================================
// FUNCION: verificarDerrota
// ============================================================
bool verificarDerrota(int tablero[][COLS], int fila, int col) {
    return (tablero[fila][col] == VIDRIO_MALO);
}

// ============================================================
// FUNCION: procesarSalto
// ============================================================
void procesarSalto(int tablero[][COLS],
                   int &filaActual, int &colActual,
                   int filaNueva, int colNueva) {
    tablero[filaActual][colActual] = CAMINO;
    tablero[filaNueva][colNueva] = JUGADOR;
    filaActual = filaNueva;
    colActual  = colNueva;
}

// ============================================================
// FUNCION: mostrarMensajeCaida
// ============================================================
// Muestra animacion de caida con colores.
void mostrarMensajeCaida(int fila, int col, int vidasRestantes) {
    cout << endl;
    color(ROJO);
    cout << "  +================================================+" << endl;
    cout << "  ||                                              ||" << endl;
    cout << "  ||    * * * C R A A A C K ! ! ! * * *           ||" << endl;
    cout << "  ||                                              ||" << endl;
    cout << "  ||    El vidrio en [" << fila << "," << col << "] se ha roto!          ||" << endl;
    cout << "  ||                                              ||" << endl;

    if (vidasRestantes > 0) {
        color(AMARILLO);
        cout << "  ||    Alguien te atrapo justo a tiempo!        ||" << endl;
        cout << "  ||    Te quedan " << vidasRestantes << " vida(s).                   ||" << endl;
        cout << "  ||    Vuelves a tu posicion anterior.          ||" << endl;
    } else {
        color(ROJO);
        cout << "  ||    No queda nadie para atraparte...         ||" << endl;
        cout << "  ||    Caes al vacio.                           ||" << endl;
    }

    color(ROJO);
    cout << "  ||                                              ||" << endl;
    cout << "  +================================================+" << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: mostrarMensajeDerrota
// ============================================================
void mostrarMensajeDerrota() {
    cout << endl;
    color(ROJO);
    cout << "  +================================================+" << endl;
    cout << "  ||                                              ||" << endl;
    cout << "  ||     ____                                     ||" << endl;
    cout << "  ||    |    |                                    ||" << endl;
    cout << "  ||    |    O    G A M E   O V E R               ||" << endl;
    cout << "  ||    |   /|\\                                   ||" << endl;
    cout << "  ||    |   / \\                                   ||" << endl;
    cout << "  ||    |________                                 ||" << endl;
    cout << "  ||                                              ||" << endl;
    color(AMARILLO);
    cout << "  ||    Has sido E L I M I N A D O               ||" << endl;
    cout << "  ||    del juego del calamar.                    ||" << endl;
    color(ROJO);
    cout << "  ||                                              ||" << endl;
    cout << "  +================================================+" << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: mostrarMensajeVictoria
// ============================================================
void mostrarMensajeVictoria(int vidas, int turnos) {
    int puntos = vidas * 1000 + (50 - turnos) * 10;
    if (puntos < 0) puntos = 0;

    cout << endl;
    color(VERDE);
    cout << "  +================================================+" << endl;
    cout << "  ||                                              ||" << endl;
    cout << "  ||  *  *  *  *  *  *  *  *  *  *  *  *  *  *   ||" << endl;
    cout << "  ||                                              ||" << endl;
    color(AMARILLO);
    cout << "  ||       HAS CRUZADO EL PUENTE!!!               ||" << endl;
    cout << "  ||                                              ||" << endl;
    cout << "  ||       V I C T O R I A                        ||" << endl;
    color(VERDE);
    cout << "  ||                                              ||" << endl;
    cout << "  ||  *  *  *  *  *  *  *  *  *  *  *  *  *  *   ||" << endl;
    cout << "  ||                                              ||" << endl;
    color(CYAN);
    cout << "  ||  Sobreviviste a la prueba del calamar.       ||" << endl;
    cout << "  ||  Vidas restantes: " << vidas << "                          ||" << endl;
    cout << "  ||  Turnos usados:   " << setw(2) << turnos << "                         ||" << endl;
    color(AMARILLO);
    cout << "  ||  PUNTUACION: " << setw(5) << puntos << " pts                    ||" << endl;
    color(VERDE);
    cout << "  ||                                              ||" << endl;
    cout << "  +================================================+" << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: revelarTablero
// ============================================================
// Al final muestra el tablero con trampas reveladas en rojo.
void revelarTablero(int tablero[][COLS]) {
    cout << endl;
    color(AMARILLO);
    cout << "  +======================================================+" << endl;
    cout << "  ||       TABLERO REVELADO                             ||" << endl;
    cout << "  +======================================================+" << endl;
    color(BLANCO);
    cout << endl;

    cout << "         ";
    color(GRIS);
    for (int j = 0; j < COLS; j++) {
        cout << "  " << j << "  ";
    }
    cout << endl;
    color(BLANCO);

    cout << "       ";
    color(AMARILLO);
    for (int j = 0; j < COLS; j++) {
        cout << "+----";
    }
    cout << "+" << endl;
    color(BLANCO);

    for (int i = 0; i < FILAS; i++) {
        color(GRIS);
        cout << "   " << i << "   ";

        for (int j = 0; j < COLS; j++) {
            color(AMARILLO);
            cout << "|";

            if (tablero[i][j] == VIDRIO_MALO) {
                color(ROJO_FONDO);
                cout << " XX ";
            } else if (tablero[i][j] == CAMINO || tablero[i][j] == JUGADOR) {
                color(VERDE_FONDO);
                cout << " ~~ ";
            } else {
                color(AZUL_FONDO);
                cout << " ## ";
            }
        }
        color(AMARILLO);
        cout << "|" << endl;

        cout << "       ";
        for (int j = 0; j < COLS; j++) {
            cout << "+----";
        }
        cout << "+" << endl;
        color(BLANCO);
    }

    cout << endl;
    color(ROJO);
    cout << "    XX ";
    color(GRIS);
    cout << "= Trampa   ";
    color(VERDE);
    cout << "~~ ";
    color(GRIS);
    cout << "= Tu camino   ";
    color(AZUL);
    cout << "## ";
    color(GRIS);
    cout << "= Vidrio seguro" << endl;
    color(BLANCO);
    cout << endl;
}

// ============================================================
// FUNCION: mostrarMenuPrincipal
// ============================================================
int mostrarMenuPrincipal() {
    mostrarBanner();

    color(CYAN);
    cout << "  +----------------------------------------------+" << endl;
    cout << "  |              MENU  PRINCIPAL                  |" << endl;
    cout << "  +----------------------------------------------+" << endl;
    color(BLANCO);
    cout << "  |                                              |" << endl;
    color(VERDE);
    cout << "  |   [1]";
    color(BLANCO);
    cout << "  Dos jugadores (uno pone trampas)     |" << endl;
    color(VERDE);
    cout << "  |   [2]";
    color(BLANCO);
    cout << "  Un jugador (trampas aleatorias)      |" << endl;
    color(ROJO);
    cout << "  |   [3]";
    color(BLANCO);
    cout << "  Salir                                 |" << endl;
    cout << "  |                                              |" << endl;
    color(CYAN);
    cout << "  +----------------------------------------------+" << endl;
    color(BLANCO);
    cout << endl;
    color(AMARILLO);
    cout << "  >> Elige una opcion: ";
    color(BLANCO);

    int opcion;
    cin >> opcion;
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcion = 0; }
    return opcion;
}

// ============================================================
// FUNCION: elegirDificultad
// ============================================================
int elegirDificultad() {
    limpiarPantalla();
    cout << endl;
    color(CYAN);
    cout << "  +----------------------------------------------+" << endl;
    cout << "  |           ELIGE  DIFICULTAD                   |" << endl;
    cout << "  +----------------------------------------------+" << endl;
    color(BLANCO);
    cout << "  |                                              |" << endl;
    color(VERDE);
    cout << "  |   [1]";
    color(BLANCO);
    cout << "  Facil       ( 5 trampas)             |" << endl;
    color(AMARILLO);
    cout << "  |   [2]";
    color(BLANCO);
    cout << "  Normal      ( 8 trampas)             |" << endl;
    color(ROJO);
    cout << "  |   [3]";
    color(BLANCO);
    cout << "  Dificil     (12 trampas)             |" << endl;
    color(MAGENTA);
    cout << "  |   [4]";
    color(BLANCO);
    cout << "  Imposible   (18 trampas)             |" << endl;
    cout << "  |                                              |" << endl;
    color(CYAN);
    cout << "  +----------------------------------------------+" << endl;
    color(BLANCO);
    cout << endl;
    color(AMARILLO);
    cout << "  >> Elige dificultad: ";
    color(BLANCO);

    int opcion;
    cin >> opcion;
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcion = 2; }

    switch (opcion) {
        case 1: return 5;
        case 2: return 8;
        case 3: return 12;
        case 4: return 18;
        default: return 8;
    }
}

// ============================================================
// FUNCION: jugar
// ============================================================
// Bucle principal del juego. Maneja turnos, vidas,
// movimiento y condiciones de victoria/derrota.
void jugar(int tablero[][COLS]) {
    int filaJugador = 0;
    int colJugador  = 0;
    int vidas       = VIDAS_INICIAL;
    int turno       = 0;

    tablero[filaJugador][colJugador] = JUGADOR;

    limpiarPantalla();
    color(CYAN);
    cout << endl;
    cout << "  +================================================+" << endl;
    cout << "  ||                                              ||" << endl;
    color(AMARILLO);
    cout << "  ||        COMIENZA EL JUEGO                     ||" << endl;
    color(GRIS);
    cout << "  ||                                              ||" << endl;
    cout << "  ||  Llega a la fila " << FILAS - 1 << " para sobrevivir.          ||" << endl;
    cout << "  ||  Solo casillas adyacentes (no diagonal).     ||" << endl;
    cout << "  ||  Formato de salto: fila,columna              ||" << endl;
    color(CYAN);
    cout << "  ||                                              ||" << endl;
    cout << "  +================================================+" << endl;
    color(BLANCO);
    cout << endl;
    cout << "  Presiona ENTER para ver el tablero...";
    limpiarBuffer();
    cin.get();

    bool juegoActivo = true;

    while (juegoActivo) {
        limpiarPantalla();
        mostrarTablero(tablero, vidas, turno);

        int filaDest, colDest;
        char coma;

        color(GRIS);
        cout << "    Posicion actual: ";
        color(VERDE);
        cout << "[" << filaJugador << "," << colJugador << "]" << endl;
        color(GRIS);
        cout << "    Puedes ir: arriba, abajo, izquierda, derecha" << endl;
        color(AMARILLO);
        cout << "    >> Tu salto (fila,columna): ";
        color(BLANCO);
        cin >> filaDest >> coma >> colDest;

        // Si cin fallo (el usuario escribio letras u otra cosa invalida),
        // limpiamos el error y pedimos de nuevo. Sin esto el programa crashea.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            color(ROJO);
            cout << "    Entrada invalida. Usa numeros: fila,columna (ej: 2,3)" << endl;
            color(BLANCO);
            pausar();
            continue;
        }

        if (coma != ',') {
            color(ROJO);
            cout << "    Formato incorrecto. Usa: fila,columna (ej: 2,3)" << endl;
            color(BLANCO);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pausar();
            continue;
        }

        if (!esMovimientoValido(filaDest, colDest)) {
            color(ROJO);
            cout << "    Posicion fuera del tablero!" << endl;
            color(BLANCO);
            pausar();
            continue;
        }

        if (filaDest == filaJugador && colDest == colJugador) {
            color(ROJO);
            cout << "    Ya estas ahi! Muevete a otra casilla." << endl;
            color(BLANCO);
            pausar();
            continue;
        }

        if (!esMovimientoAdyacente(filaJugador, colJugador, filaDest, colDest)) {
            color(ROJO);
            cout << "    Solo puedes saltar a una casilla adyacente!" << endl;
            color(BLANCO);
            pausar();
            continue;
        }

        if (tablero[filaDest][colDest] == CAMINO) {
            color(ROJO);
            cout << "    Ese vidrio ya esta roto. No puedes volver ahi." << endl;
            color(BLANCO);
            pausar();
            continue;
        }

        turno++;

        // Verificar si es vidrio malo
        if (verificarDerrota(tablero, filaDest, colDest)) {
            vidas--;
            tablero[filaDest][colDest] = CAMINO;  // Se rompe

            limpiarPantalla();
            mostrarTablero(tablero, vidas, turno);
            mostrarMensajeCaida(filaDest, colDest, vidas);

            if (vidas <= 0) {
                mostrarMensajeDerrota();
                revelarTablero(tablero);
                juegoActivo = false;
            } else {
                color(AMARILLO);
                cout << "    Sigues en [" << filaJugador << "," << colJugador << "]. Elige otro camino!" << endl;
                color(BLANCO);
            }

            pausar();
        }
        // Vidrio seguro
        else {
            procesarSalto(tablero, filaJugador, colJugador,
                          filaDest, colDest);

            if (verificarVictoria(filaJugador)) {
                limpiarPantalla();
                mostrarTablero(tablero, vidas, turno);
                mostrarMensajeVictoria(vidas, turno);
                revelarTablero(tablero);
                juegoActivo = false;

                pausar();
            }
        }
    }
}

// ============================================================
// FUNCION PRINCIPAL: main
// ============================================================
int main() {
    bool salir = false;

    while (!salir) {
        // Declaracion de la matriz bidimensional
        int tablero[FILAS][COLS];
        inicializarTablero(tablero);

        int opcion = mostrarMenuPrincipal();

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                color(MAGENTA);
                cout << endl;
                cout << "  +================================================+" << endl;
                cout << "  ||           USFQ                               ||" << endl;
                cout << "  ||      MODO DOS JUGADORES                      ||" << endl;
                cout << "  ||                                              ||" << endl;
                color(GRIS);
                cout << "  ||  Jugador 1: Coloca los vidrios malos.        ||" << endl;
                cout << "  ||  Jugador 2: Intenta cruzar el puente.        ||" << endl;
                color(MAGENTA);
                cout << "  ||                                              ||" << endl;
                cout << "  +================================================+" << endl;
                color(BLANCO);
                cout << endl;

                marcarVidriosMalos(tablero);

                cout << endl;
                color(AMARILLO);
                cout << "    Pasa el teclado al Jugador 2." << endl;
                color(BLANCO);
                pausar();

                jugar(tablero);
                break;
            }
            case 2: {
                int trampas = elegirDificultad();
                generarVidriosMalosAleatorios(tablero, trampas);

                limpiarPantalla();
                color(CYAN);
                cout << endl;
                cout << "  +================================================+" << endl;
                cout << "  ||                                              ||" << endl;
                color(AMARILLO);
                cout << "  ||     Se han colocado " << setw(2) << trampas << " trampas al azar...    ||" << endl;
                color(ROJO);
                cout << "  ||     Buena suerte... la vas a necesitar.      ||" << endl;
                color(CYAN);
                cout << "  ||                                              ||" << endl;
                cout << "  +================================================+" << endl;
                color(BLANCO);
                cout << endl;
                pausar();

                jugar(tablero);
                break;
            }
            case 3: {
                salir = true;
                limpiarPantalla();
                cout << endl;
                color(CYAN);
                cout << "  Hasta luego! Gracias por jugar." << endl;
                color(BLANCO);
                cout << endl;
                break;
            }
            default: {
                color(ROJO);
                cout << "    Opcion no valida." << endl;
                color(BLANCO);
                break;
            }
        }

        if (!salir) {
            cout << endl;
            color(AMARILLO);
            cout << "    Jugar de nuevo? (1 = Si, 0 = No): ";
            color(BLANCO);
            int respuesta;
            cin >> respuesta;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); respuesta = 0; }
            if (respuesta != 1) {
                salir = true;
                limpiarPantalla();
                cout << endl;
                color(CYAN);
                cout << "  Gracias por jugar! Hasta la proxima." << endl;
                color(BLANCO);
                cout << endl;
            }
        }
    }

    return 0;
}

/*
 * ============================================================
 * EXPLICACION: Como funciona la matriz en este programa
 * ============================================================
 *
 * 1. DECLARACION:
 *    int tablero[6][6];
 *    Esto crea una matriz de 6 filas y 6 columnas en memoria.
 *    En total son 36 elementos (6 x 6 = 36), todos de tipo int.
 *
 * 2. REPRESENTACION EN MEMORIA:
 *    Aunque visualizamos la matriz como una cuadricula 2D,
 *    en memoria los datos se almacenan de forma lineal (row-major):
 *    [fila0col0][fila0col1]...[fila0col5][fila1col0]...[fila5col5]
 *
 * 3. ACCESO A ELEMENTOS:
 *    tablero[i][j] accede al elemento en la fila i, columna j.
 *    - El primer indice (i) selecciona la fila.
 *    - El segundo indice (j) selecciona la columna dentro de esa fila.
 *    - Los indices van de 0 a N-1 (en este caso, de 0 a 5).
 *
 * 4. USO EN EL PROGRAMA:
 *    - tablero[i][j] = 0  ->  Vidrio seguro
 *    - tablero[i][j] = 1  ->  Vidrio malo (trampa)
 *    - tablero[i][j] = 2  ->  Posicion del jugador
 *    - tablero[i][j] = 3  ->  Camino ya recorrido
 *
 * 5. PASO A FUNCIONES:
 *    Cuando pasamos la matriz a una funcion, debemos indicar
 *    el numero de columnas:
 *      void funcion(int tablero[][COLS])
 *    Formula interna: direccion = base + (i * COLS + j) * sizeof(int)
 *
 * 6. RECORRIDO:
 *    Para visitar todos los elementos usamos dos ciclos anidados:
 *      for (int i = 0; i < FILAS; i++)
 *          for (int j = 0; j < COLS; j++)
 *              // usar tablero[i][j]
 *
 * ============================================================
 */
