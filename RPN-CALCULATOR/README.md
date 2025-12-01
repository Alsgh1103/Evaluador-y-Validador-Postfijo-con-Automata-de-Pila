# 🧮 EVALUADOR Y VALIDADOR POSTFIJO

> Una implementación robusta, modular y eficiente de una calculadora de **Notación Polaca Inversa (Reverse Polish Notation)** escrita en **C**.

![Language](https://img.shields.io/badge/Lenguaje-C-00599C?style=flat-square&logo=c&logoColor=white)
![Build](https://img.shields.io/badge/Build-Make-orange?style=flat-square)
![Type](https://img.shields.io/badge/Type-CLI-black?style=flat-square)

---

## 📖 Descripción

Este proyecto consiste en un evaluador de expresiones matemáticas que utiliza una **pila (stack)** estática para procesar operaciones en tiempo real. A diferencia de las calculadoras tradicionales, el formato RPN elimina la necesidad de paréntesis, haciendo el cálculo computacionalmente más eficiente y lógico.

El sistema está diseñado para ser **versátil**, permitiendo al usuario trabajar tanto de forma interactiva (modo consola) como por lotes (modo archivo), generando siempre archivos de trazabilidad que registran cada paso de la evaluación.

### 🔄 Autómata de Pila

El evaluador implementa un **Autómata de Pila Determinista (APD)** con las siguientes características:

* **Estado único:** `q0` (el autómata permanece siempre en este estado)
* **Símbolo inicial de pila:** `Z0` (marcador de fondo de pila)
* **Alfabeto de entrada:** Dígitos (0-9), operadores (+, -, *, /) y símbolo de fin (=)
* **Transiciones del autómata:**
  * `d(q0, ε, Z0) = (q0, Z0)` - Inicialización
  * `d(q0, número, Z0) = (q0, X Z0)` - Primer número apilado
  * `d(q0, número, X) = (q0, XX)` - Apilar números subsecuentes
  * `d(q0, operador, XX) = (q0, X)` - Desapilar 2, operar, apilar resultado
  * `d(q0, ε, X Z0) = (q0, ε)` - Estado de aceptación (un solo resultado)

**Condición de aceptación:** La pila debe contener exactamente un elemento al finalizar (el resultado).

## ✨ Características Principales

* **Arquitectura Modular:** Código separado en lógica de pila (`stack`), utilidades (`utils`) y programa principal (`main`).
* **Doble Modo de Operación:** Modo consola interactivo y modo archivo por lotes.
* **Trazabilidad Completa:** Genera archivos de evolución mostrando el estado de la pila paso a paso con las **transiciones del autómata**.
* **Formato Inteligente:** Muestra decimales solo cuando es necesario (ej: muestra `5` en lugar de `5.000000` y `2.5` si hay decimales).
* **Manejo de Errores Estricto:** Sistema de validación que detecta y reporta:
  * División por cero.
  * Desbordamiento de pila (Stack Overflow - máximo 100 elementos).
  * Símbolos inválidos (ej: letras mezcladas con números).
  * Insuficiencia de operandos.
  * Expresión incompleta (sobran números en la pila).
  * Pila vacía al finalizar.
* **Sistema de Archivos de Salida:** 
  * **`evolucion_<nombre>.txt`**: Trazabilidad completa paso a paso.
  * **`resultado_<nombre>.txt`**: Resultado numérico o descripción detallada del error.

---

## 📂 Estructura del Proyecto

El código sigue una estructura estándar de la industria para facilitar su mantenimiento y escalabilidad:
```text
RPN-CALCULATOR/
├── include/        # Archivos de cabecera (.h)
│   ├── stack.h     # Definiciones de la Pila
│   └── utils.h     # Funciones auxiliares y validaciones
├── src/            # Código fuente (.c)
│   ├── main.c      # Punto de entrada y bucle principal
│   ├── stack.c     # Lógica de las operaciones de la pila
│   └── utils.c     # Implementación de formateo y helpers
├── Makefile        # Script de compilación automatizada
└── README.md       # Documentación del proyecto
```

## ⚙️ Guía de Instalación y Ejecución

Sigue estos pasos para configurar el entorno y ejecutar el proyecto en tu sistema operativo (Windows o Linux).

### 1. Comprobación de Prerrequisitos

Antes de instalar nada, verifica si ya tienes las herramientas necesarias. Abre tu terminal (PowerShell en Windows o Terminal en Linux) y ejecuta:
```bash
gcc --version
make --version
```

* ✅ Si ambos comandos muestran una versión: Salta directamente al paso 3.

* ❌ Si recibes un error como "comando no encontrado" o "not recognized": Sigue las instrucciones de instalación abajo según tu sistema.

### 2. Instalación de Dependencias

#### 🐧 Opción A: Linux (Ubuntu/Debian)

La forma más rápida es instalar el paquete esencial de construcción:
```bash
sudo apt update
sudo apt install build-essential
```

Esto instalará automáticamente `gcc` y `make`.

#### 🪟 Opción B: Windows

Para compilar C en Windows de manera profesional, recomendamos usar **MSYS2** o **MinGW**.

**Método Rápido (vía Chocolatey)**: Si tienes Chocolatey instalado, abre PowerShell como Administrador y ejecuta:
```PowerShell
choco install make mingw
```

**Método Manual (Sin gestores de paquetes):**

1. Descarga el instalador de w64devkit (un kit portable que no requiere instalación compleja) desde [GitHub w64devkit](https://github.com/skeeto/w64devkit/releases).
2. Descarga el archivo `.zip` más reciente (ej. `w64devkit-1.20.0.zip`).
3. Descomprímelo en una carpeta accesible.
4. Ejecuta el archivo `w64devkit.exe` que está dentro. Esto abrirá una terminal donde `gcc` y `make` funcionarán inmediatamente.

### 3. Compilación del proyecto

Una vez que tengas las dependencias, compilar el proyecto es automático gracias al archivo `Makefile`.

Abre la terminal en la carpeta `RPN-CALCULATOR`

Ejecuta el comando de compilación:
```Bash
make
```

#### Nota para Windows: Si instalaste MinGW manualmente y el comando make no funciona, intenta usar mingw32-make

### 4. Ejecución

Una vez compilado, se generará el ejecutable. El programa soporta **dos modos de operación**:

**Modo Consola (Interactivo) - Sin argumentos:**

Ejecuta el programa sin argumentos para el modo interactivo token por token:

**En Linux / Mac / Git Bash:**
```bash
./rpn_calculator
```

**En Windows (CMD / PowerShell):**
```PowerShell
.\rpn_calculator.exe
```

* Permite ingresar tokens uno a uno (números y operadores)
* **NO muestra la pila en pantalla durante la ejecución** (solo genera archivos)
* Genera archivos de trazabilidad automáticamente con ID aleatorio:
  * `evolucion_manual_XXXX.txt`: Traza completa paso a paso con **transiciones del autómata**
  * `resultado_manual_XXXX.txt`: Resultado final o mensaje de error
* Termina la sesión ingresando `=`
* Al finalizar exitosamente, muestra en pantalla la ubicación de los archivos generados

**Modo Archivo (Batch) - Con argumento de archivo:**

Ejecuta el programa con un archivo de entrada:

**En Linux / Mac / Git Bash:**
```bash
./rpn_calculator entrada.txt
```

**En Windows (CMD / PowerShell):**
```PowerShell
.\rpn_calculator.exe entrada.txt
```

* Lee la expresión completa desde el archivo (tokens separados por espacios)
* El archivo debe terminar con el símbolo `=`
* Genera dos archivos de salida:
  * `evolucion_<nombre_archivo>.txt`: Traza paso a paso del procesamiento con **transiciones del autómata**
  * `resultado_<nombre_archivo>.txt`: Resultado final o mensaje de error detallado
* **Modo silencioso**: Solo muestra mensaje de confirmación al finalizar exitosamente

### 5. Limpieza (Opcional)

Para eliminar los archivos objeto (`.o`) y el ejecutable generado:
```Bash
make clean
```

## 🎮 Ejemplo de Sesión

### Modo Consola

Así se ve una interacción real para calcular la operación `(5 + 3) * 2`:
```text
------ MODO CONSOLA ------
Ingrese operacion (ej: 5 3 +) y '=' para terminar.
--------------------------
> 5
> 3
> +
> 2
> *
> =

Exito. Archivos generados:
 -> evolucion_manual_3847.txt
 -> resultado_manual_3847.txt
```

**Contenido de `evolucion_manual_3847.txt`:**
```text
PASO | TRANSICION                          | DESCRIPCION               | PILA
-----|-------------------------------------|---------------------------|------------------
0    | d(q0, e, Z0) = (q0, Z0)             | INICIO                    | Z0 [ vacia ]
1    | d(q0, 5, Z0) = (q0, X Z0)           | 1 PUSH                    | Z0 [ 5 ]
2    | d(q0, 3, X) = (q0, XX)              | 1 PUSH                    | Z0 [ 5 3 ]
3    | d(q0, +, XX) = (q0, X)              | 2 POP Y 1 PUSH            | Z0 [ 8 ]
4    | d(q0, 2, X) = (q0, XX)              | 1 PUSH                    | Z0 [ 8 2 ]
5    | d(q0, *, XX) = (q0, X)              | 2 POP Y 1 PUSH            | Z0 [ 16 ]
6    | d(q0, e, X Z0) = (q0, e)            | ACEPTACION                | Z0 [ 16 ]
```

**Contenido de `resultado_manual_3847.txt`:**
```text
Resultado: 16
```

### Modo Archivo

**Contenido de `expresion.txt`:**
```text
10 5 + 2 * =
```

**Ejecución:**
```bash
./rpn_calculator expresion.txt
```

**Salida en pantalla:**
```text
Exito. Archivos generados:
 -> evolucion_expresion.txt
 -> resultado_expresion.txt
```

**Contenido de `evolucion_expresion.txt`:**
```text
PASO | TRANSICION                          | DESCRIPCION               | PILA
-----|-------------------------------------|---------------------------|------------------
0    | d(q0, e, Z0) = (q0, Z0)             | INICIO                    | Z0 [ vacia ]
1    | d(q0, 10, Z0) = (q0, X Z0)          | 1 PUSH                    | Z0 [ 10 ]
2    | d(q0, 5, X) = (q0, XX)              | 1 PUSH                    | Z0 [ 10 5 ]
3    | d(q0, +, XX) = (q0, X)              | 2 POP Y 1 PUSH            | Z0 [ 15 ]
4    | d(q0, 2, X) = (q0, XX)              | 1 PUSH                    | Z0 [ 15 2 ]
5    | d(q0, *, XX) = (q0, X)              | 2 POP Y 1 PUSH            | Z0 [ 30 ]
6    | d(q0, e, X Z0) = (q0, e)            | ACEPTACION                | Z0 [ 30 ]
```

**Contenido de `resultado_expresion.txt`:**
```text
Resultado: 30
```

### Ejemplo con Error

**Contenido de `error.txt`:**
```text
5 0 / =
```

**Contenido de `evolucion_error.txt`:**
```text
PASO | TRANSICION                          | DESCRIPCION               | PILA
-----|-------------------------------------|---------------------------|------------------
0    | d(q0, e, Z0) = (q0, Z0)             | INICIO                    | Z0 [ vacia ]
1    | d(q0, 5, Z0) = (q0, X Z0)           | 1 PUSH                    | Z0 [ 5 ]
2    | d(q0, 0, X) = (q0, XX)              | 1 PUSH                    | Z0 [ 5 0 ]
3    | d(q0, /, XX) = RECHAZO              | ERROR                     | Z0 [ 5 0 ]
```

**Contenido de `resultado_error.txt`:**
```text
ERROR ARITMETICO: Division por cero
```

## 🛠️ Tecnologías Utilizadas

* **Lenguaje C:** Gestión de memoria estática y manejo de archivos.
* **Make:** Automatización de compilación.
* **Estructuras de Datos:** Implementación manual de Pila estática (LIFO) con array de tamaño fijo.
* **Teoría de Autómatas:** Autómata de Pila Determinista (APD) para validación sintáctica.

## 📋 Detalles de Implementación

### Autómata de Pila (Pushdown Automaton)

El evaluador implementa un autómata de pila con las siguientes características formales:

**Definición:** M = (Q, Σ, Γ, δ, q0, Z0, F)

* **Q** = {q0} - Conjunto de estados (estado único)
* **Σ** = {0-9, +, -, *, /, =} - Alfabeto de entrada
* **Γ** = {Z0, X} - Alfabeto de pila (Z0 = marcador, X = cualquier número)
* **δ** - Función de transición (ver tabla de transiciones)
* **q0** - Estado inicial
* **Z0** - Símbolo inicial de pila
* **F** = {q0 con pila = X Z0} - Estados de aceptación

**Tabla de Transiciones:**

| Transición | Condición | Acción |
|------------|-----------|--------|
| d(q0, ε, Z0) = (q0, Z0) | Inicio | Inicializar pila con Z0 |
| d(q0, número, Z0) = (q0, X Z0) | Pila vacía | Apilar primer número |
| d(q0, número, X) = (q0, XX) | Pila con elementos | Apilar número adicional |
| d(q0, +, XX) = (q0, X) | Operador suma | Desapilar 2, sumar, apilar resultado |
| d(q0, -, XX) = (q0, X) | Operador resta | Desapilar 2, restar, apilar resultado |
| d(q0, *, XX) = (q0, X) | Operador multiplicación | Desapilar 2, multiplicar, apilar resultado |
| d(q0, /, XX) = (q0, X) | Operador división | Desapilar 2, dividir, apilar resultado |
| d(q0, ε, X Z0) = (q0, ε) | Fin de entrada | ACEPTAR (1 elemento) |

### Pila (Stack)
* **Capacidad:** 100 elementos (definida por `MAX_STACK_SIZE`)
* **Tipo:** Array estático de `double`
* **Índice:** Variable `top` inicializada en -1 (indica pila vacía)
* **Operaciones:**
  * `push(value)` - Apilar elemento (O(1))
  * `pop()` - Desapilar elemento (O(1))
  * `get_stack_size()` - Obtener tamaño (O(1))
  * `get_top_value()` - Ver tope sin desapilar (O(1))

### Operadores Soportados
* Suma: `+`
* Resta: `-`
* Multiplicación: `*`
* División: `/` (con validación de división por cero)

### Validaciones Implementadas
1. **Símbolos inválidos:** Verifica que cada token sea un número válido o un operador
2. **Operandos insuficientes:** Verifica que haya al menos 2 números antes de operar (validación de transición XX)
3. **División por cero:** Validación explícita antes de dividir
4. **Desbordamiento de pila:** Verifica límite de 100 elementos
5. **Verificación final:** Debe quedar exactamente 1 elemento en la pila (condición de aceptación X Z0)

### Manejo de Errores

Todos los errores usan el sistema **fail-fast** (`exit(1)`), escribiendo el error en:
* **Archivo de evolución** (`evolucion_<nombre>.txt`): Marca el paso donde ocurrió el error con la transición `RECHAZO`
* **Archivo de resultado** (`resultado_<nombre>.txt`): Detalla el tipo y descripción del error

**Tipos de errores detectados:**
* **ERROR SINTÁCTICO:** Token inválido, operandos insuficientes, expresión incompleta, pila vacía
* **ERROR ARITMÉTICO:** División por cero
* **ERROR FATAL:** Desbordamiento de pila (Stack Overflow)

### Sistema de Archivos de Salida

El programa **siempre** genera dos archivos independientemente del resultado:

#### Archivo de Evolución (`evolucion_<nombre>.txt`)
Documenta cada paso del procesamiento incluyendo:
- Número de paso secuencial
- Transición del autómata aplicada
- Descripción de la operación realizada
- Estado completo de la pila después de la operación

En caso de error, el último paso mostrará la transición `RECHAZO`.

#### Archivo de Resultado (`resultado_<nombre>.txt`)
Contiene:
- **En caso de éxito:** El resultado numérico final precedido por "Resultado: "
- **En caso de error:** El tipo de error (SINTÁCTICO/ARITMÉTICO/FATAL) seguido de la descripción específica

<div align="center">
  🪄 Desarrollado por grupo 2
</div>
