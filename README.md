# Evaluador y Validador Postfijo con Autómata de Pila (AP)

Programa en lenguaje C que implementa un **Autómata de Pila (AP)** para la **evaluación y validación de expresiones aritméticas en notación postfija (RPN)**.  
El sistema procesa una cadena de tokens (operandos y operadores `+`, `-`, `*`, `/`) y:

- Determina si la expresión es **sintácticamente válida**.
- **Calcula el resultado numérico** de la expresión si es correcta.

---

## Contexto académico

Este proyecto fue desarrollado como **trabajo final** para el curso de **Teoría de la Computación** en la  
**Facultad de Ingeniería de Sistemas e Informática** de la **Universidad Nacional Mayor de San Marcos (UNMSM)**.

---

## ¿Qué es la notación postfija (RPN)?

En notación postfija los operadores van **después** de los operandos.  
Por ejemplo:

- Infija: `3 + 4 * 2`  
- Postfija: `3 4 2 * +`

Esta forma no necesita paréntesis ni prioridades y se puede evaluar fácilmente usando una **pila**.

---

## ¿Qué hace este programa?

Dada una expresión postfija, el programa:

1. Lee la entrada como una secuencia de tokens separados por espacios.
2. Usa una pila para ir procesando números y operadores.
3. Informa si la expresión es válida o no.
4. Muestra el **resultado numérico** cuando la expresión es correcta.
5. Reporta errores como:
   - Falta de operandos.
   - División entre cero.
   - Resultado no único en la pila al final.

---

## Interpretación del proceso

Objetivo: calcular el resultado numérico de una expresión postfija (por ejemplo `10 5 +`).

1. Si se lee un **número**, se apila (operación *push*).
2. Si se lee un **operador** (`+`, `-`, `*`, `/`):
   - Se sacan de la pila los dos últimos números (operaciones *pop*).
   - Se aplica la operación: `resultado = operando1 operador operando2`.
   - El resultado se vuelve a apilar (*push*).
3. Al finalizar la lectura:
   - Si queda **exactamente un número** en la pila → la expresión es **VÁLIDA** y ese es el resultado.
   - Si la pila queda vacía o con más de un número → la expresión es **INVÁLIDA**.
   - Si se intenta dividir entre cero → la expresión se marca como **INVÁLIDA** por error aritmético.

---

## Estructura del repositorio

```text
AP_postfijo.c   → Código fuente en C
LICENSE         → Licencia del proyecto
README.md       → Documentación principal
```
## Requisitos
- Compilador de C (por ejemplo, `gcc`)
    - En Linux: suele venir en el paquete `build-essential`.
    - En Windows: se puede usar MinGW o WSL.
- Consola o terminal para compilar y ejecutar el programa.

## Compilación y ejecución
1. Compilar:
   ``` bash
   gcc AP_postfijo.c -o ap_postfijo
   ```
2. Ejecutar:
    ``` bash
   ./ap_postfijo
   ```
3. Ingresar la expresión postfija cuando el programa lo solicite, separando cada token con un espacio:
   ``` bash
   Ingrese la expresión postfija:
    3 4 + 2 *
   ```
## Ejemplos de uso
- **Ejemplo 1: expresión válida simple**
Entrada:
 ``` bash
   2 3 +
   ```
Salida esperada: 
 ``` bash
   Resultado: 5
   ```
