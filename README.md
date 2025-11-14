# Evaluador y Validador Postfijo con Autómata de Pila (AP)

Programa hecho en Lenguaje C, el cual implementa un **Autómata de Pila (AP)** para la **evaluación y validación de expresiones aritméticas en Notación Postfija**.
El sistema procesa una cadena de tokens (operandos y operadores `+`, `-`, `*`, `/`) y:
-  Determina si la expresión es **sintácticamente válida**.  
-  **Calcula el resultado numérico** de la expresión.

## Contexto Académico

Este proyecto fue desarrollado como **trabajo final** para el curso de **Teoría de la Computación** en la  
**Facultad de Ingeniería de Sistemas e Informática** de la  
**Universidad Nacional Mayor de San Marcos (UNMSM)**.

---

### Interpretación del Proceso
Objetivo: Calcular el resultado numérico de una expresión postfija (ej. 10 5 +).

- **Proceso (token por token):**

- Si se lee un NÚMERO: Se apila (hace push) directamente en la pila.

- Si se lee un OPERADOR (+, -, *, /):

- Se sacan (hacen pop) los dos últimos números de la pila (Operando 2, luego Operando 1).

- Se realiza la operación matemática (ej. Operando1 + Operando2).

- Se apila (hace push) el resultado de esa operación de nuevo en la pila.

- **Finalización:**

- Si al terminar de leer la entrada queda exactamente un número en la pila → La expresión es VÁLIDA y ese es el resultado.

- Si la pila queda vacía o con más de un número → La expresión es INVÁLIDA (Error de sintaxis).

- Si ocurre una división por cero → La expresión es INVÁLIDA (Error aritmético).

---

### Características

- El programa en C simula el autómata de pila para ver si una expresión postfija está bien escrita y, si lo está, la halla.
- Se crearon 4 funciones (Push,Pop,esOperador e imprimir_pila), las cuales son el motor de nuestro programa.
- En la zona principal, se solicita todos los valores y operandos (+,-,/,*) y los coloca en orden:
  - si tenemos un operando, llama a push y los coloca en la cima de la pila
  - si tenemos un operador llama a pop y extrae los dos últimos operandos
  - halla el valor encontrado y lo coloca con un push de nuevo sobre la cima de la pila.
  - Al final si quedó solo un valor sobre la cima de la pila (el resultado de toda la operación), el procedimiento es correcto

---

### Herramientas Usadas

- Lógica Principal fue desarrollado en lenguaje C
- Modelo teórico utilizado, un autómata de pila

---

### Ejecución

