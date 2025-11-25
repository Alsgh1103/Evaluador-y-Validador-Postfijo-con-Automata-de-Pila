# 🧮 EVALUADOR Y VALIDADOR POSTFIJO
> Una implementación robusta, modular y eficiente de una calculadora de **Notación Polaca Inversa (Reverse Polish Notation)** escrita en **C**.

![Language](https://img.shields.io/badge/Lenguaje-C-00599C?style=flat-square&logo=c&logoColor=white)
![Build](https://img.shields.io/badge/Build-Make-orange?style=flat-square)
![Type](https://img.shields.io/badge/Type-CLI-black?style=flat-square)

---

## 📖 Descripción

Este proyecto consiste en un evaluador de expresiones matemáticas que utiliza una **pila (stack)** dinámica para procesar operaciones en tiempo real. A diferencia de las calculadoras tradicionales, el formato RPN elimina la necesidad de paréntesis, haciendo el cálculo computacionalmente más eficiente y lógico.

El sistema está diseñado para ser **interactivo**, permitiendo al usuario visualizar el estado de la memoria (la pila) después de cada ingreso de datos.

## ✨ Características Principales

* **Arquitectura Modular:** Código separado en lógica de pila (`stack`), utilidades (`utils`) y programa principal (`main`).
* **Visualización en Tiempo Real:** Muestra el contenido de la pila paso a paso.
* **Formato Inteligente:** Muestra decimales solo cuando es necesario (ej: muestra `5` en lugar de `5.000000` y `2.5` si hay decimales).
* **Manejo de Errores:** Sistema de "Muerte Súbita" que detecta y reporta:
    * División por cero.
    * Desbordamiento de pila (Stack Overflow).
    * Sintaxis inválida (ej: letras mezcladas con números).
    * Insuficiencia de operandos.

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
- ✅ Si ambos comandos muestran una versión: Salta directamente al paso 3.
- ❌ Si recibes un error como "comando no encontrado" o "not recognized": Sigue las instrucciones de instalación abajo según tu sistema.
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
   #### Nota para Windows: Si instalaste MinGW manualmente y el comando make no funciona, intenta usar mingw32-make.

### 4. Ejecución
Una vez compilado, se generará el ejecutable. Inícialo con el comando correspondiente a tu sistema:
**En Linux / Mac / Git Bash:**
```
Bash
./rpn_calculator
```
**En Windows (CMD / PowerShell):**
```PowerShell
.\rpn_calculator.exe
```

### 5. Limpieza (Opcional)
Para eliminar los archivos objeto (`.o`) y el ejecutable generado:
```Bash
make clean
```
### ¿Por qué esta estructura es mejor?

1.  **Paso 0 (Validación):** Evita que el usuario instale cosas si ya las tiene (muy común en Linux).
2.  **Windows es complicado:** En Windows, `make` no viene instalado por defecto. He dado una solución **"Método Manual" (w64devkit)** que es infalible porque es portable (bajar, descomprimir y ejecutar), eliminando los problemas de configurar variables de entorno (PATH) que suelen confundir a los principiantes.
3.  **Diferenciación de Ejecución:** Muchos tutoriales dicen `./programa` y eso falla en el CMD de Windows. Aquí especifico claramente `.\` para Windows y `./` para Linux.

## 🎮 Ejemplo de Sesión
Así se ve una interacción real para calcular la operación `(5 + 3) * 2`:
```C
------ EVALUADOR Y VALIDADOR POSTFIJO ------
1. Escribe numero y ENTER.
2. Escribe operador y ENTER.
3. Escribe '=' para terminar.
---------------------------------------------
> 5 3 +
   Dato ingresado.
   [ Pila: 5 ] <
>    Dato ingresado.
   [ Pila: 5 3 ] <
>    Operacion '+' aplicada.
   [ Pila: 8 ] <
> 2 *
   Dato ingresado.
   [ Pila: 8 2 ] <
>    Operacion '*' aplicada.
   [ Pila: 16 ] <
> =

--- RESULTADO FINAL ---
Resultado: 16
```
## 🛠️ Tecnologías Utilizadas
- Lenguaje C: Gestión de memoria y punteros.
- Make: Automatización de compilación.
- Estructuras de Datos: Implementación manual de Pilas (LIFO).
<div align="center">
  🪄 Desarrollado por grupo 2
</div>
