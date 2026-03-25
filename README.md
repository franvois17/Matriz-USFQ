# Matriz-USFQ
juego del calamar
# Juego del Calamar - Prueba de los Vidrios

Programa en C++ que simula la prueba de los vidrios del Juego del Calamar. Creado con fines didacticos para aprender **arreglos bidimensionales (matrices)** en C++.

## Que es el juego?

El jugador debe cruzar un tablero de 6x6 saltando sobre vidrios. Algunos vidrios son seguros y otros son falsos. Si pisas un vidrio falso, pierdes una vida. Si llegas al otro extremo del tablero, ganas.

### Caracteristicas

- Tablero visual con colores en consola (Windows)
- Sistema de 3 vidas
- Movimiento adyacente (arriba, abajo, izquierda, derecha)
- **Modo 2 jugadores**: uno coloca las trampas, otro cruza el puente
- **Modo 1 jugador**: trampas aleatorias con 4 niveles de dificultad (Facil, Normal, Dificil, Imposible)
- Sistema de puntuacion
- Tablero revelado al final mostrando todas las trampas

## Requisitos

- **Sistema operativo**: Windows (usa `windows.h` para colores en consola)
- **Compilador C++**: MinGW (g++) o Visual Studio (cl)

### Instalar MinGW (g++) con winget

```bash
winget install --id BrechtSanders.WinLibs.POSIX.UCRT
```

Si ya tienes Visual Studio instalado, tambien puedes usar su compilador `cl`.

## Como compilar

### Opcion 1: Con g++ (MinGW)

```bash
g++ -o juego_vidrios.exe juego_vidrios.cpp -std=c++17
```

### Opcion 2: Con Visual Studio (cl)

Abre la **Developer Command Prompt** de Visual Studio y ejecuta:

```bash
cl /EHsc /Fe:juego_vidrios.exe juego_vidrios.cpp
```

## Como ejecutar

Despues de compilar, simplemente ejecuta:

```bash
./juego_vidrios.exe
```

O haz doble clic en `juego_vidrios.exe` desde el explorador de archivos.

## Como jugar

1. Elige un modo de juego en el menu principal
2. **Modo 2 jugadores**: El jugador 1 coloca los vidrios malos ingresando coordenadas `fila,columna`. Luego pasa el teclado al jugador 2
3. **Modo 1 jugador**: Elige la dificultad y las trampas se colocan solas
4. En cada turno, ingresa la coordenada `fila,columna` a donde quieres saltar
5. Solo puedes moverte a casillas adyacentes (no en diagonal)
6. Si caes en un vidrio malo, pierdes una vida. Si pierdes las 3 vidas, pierdes el juego
7. Llega a la fila 5 (ultima fila) para ganar

### Ejemplo de entrada

```
Tu salto (fila,columna): 1,0
```

## Conceptos de matrices que se aplican

Este programa usa los siguientes conceptos de arreglos bidimensionales:

| Concepto | Donde se usa en el codigo |
|---|---|
| Declaracion `int tablero[FILAS][COLS]` | Estructura central del juego |
| Acceso `tablero[i][j]` | Leer/modificar cada vidrio |
| Ciclos anidados `for i, for j` | Mostrar e inicializar el tablero |
| Paso a funciones `tablero[][COLS]` | Todas las funciones reciben la matriz |
| Modificacion por referencia | Las funciones modifican el tablero directamente |
| Constantes para dimensiones | `const int FILAS = 6, COLS = 6` |

## Estructura del codigo

```
juego_vidrios.cpp
|
|-- inicializarTablero()     -> Llena la matriz con ceros
|-- mostrarTablero()         -> Imprime el tablero con colores
|-- mostrarTableroPreparacion() -> Muestra trampas al colocarlas
|-- marcarVidriosMalos()     -> El usuario coloca trampas
|-- generarVidriosMalosAleatorios() -> Trampas aleatorias
|-- esMovimientoValido()     -> Valida indices dentro de la matriz
|-- esMovimientoAdyacente()  -> Solo permite saltos de 1 casilla
|-- verificarVictoria()      -> Checa si llego a la ultima fila
|-- verificarDerrota()       -> Checa si piso vidrio malo
|-- procesarSalto()          -> Mueve al jugador en la matriz
|-- revelarTablero()         -> Muestra todas las trampas al final
|-- jugar()                  -> Bucle principal del juego
|-- main()                   -> Menu y control general
```
