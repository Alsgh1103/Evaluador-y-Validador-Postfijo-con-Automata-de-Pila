# Evaluador y Validador Postfijo con Autómata de Pila (AP)

Programa hecho en Lenguaje C, el cual implementa un **Autómata de Pila (AP)** para la **evaluación y validación de expresiones aritméticas en Notación Postfija**.
El sistema procesa una cadena de tokens (operandos y operadores `+`, `-`, `*`, `/`) y:
-  Determina si la expresión es **sintácticamente válida**.  
-  **Calcula el resultado numérico** de la expresión.

## Contexto Académico

Este proyecto fue desarrollado como **trabajo final** para el curso de **Teoría de la Computación** en la  
**Facultad de Ingeniería de Sistemas e Informática** de la  
**Universidad Nacional Mayor de San Marcos (UNMSM)**.

## Modelo Matemático del Autómata de Pila (AP)

El evaluador se basa en un **Autómata de Pila**, definido mediante la séptupla:

**M = (Q, Σ, Γ, δ, q₀, Z₀, F)**

### Definiciones de la Séptupla

| Símbolo | Nombre | Descripción |
|--------|--------|-------------|
| **Q = { q₁ }** | Conjunto de estados | El autómata trabaja con un único estado |
| **Σ = { V, +, -, *, / }** | Alfabeto de entrada | `V` representa cualquier **operando numérico** |
| **Γ = { X, Z₀ }** | Alfabeto de la pila | `X` representa un operando almacenado en la pila |
| **q₀ = q₁** | Estado inicial | El autómata comienza en `q₁` |
| **Z₀** | Símbolo inicial de pila | Marca la base de la pila |
| **F = ∅** | Conjunto de aceptación | La aceptación se da cuando la **pila queda vacía** |

---

### Interpretación del Proceso
Objetivo: Calcular el resultado numérico de una expresión postfija (ej. 10 5 +).

Proceso (token por token):

- Si se lee un NÚMERO: Se apila (hace push) directamente en la pila.

- Si se lee un OPERADOR (+, -, *, /):

- Se sacan (hacen pop) los dos últimos números de la pila (Operando 2, luego Operando 1).

- Se realiza la operación matemática (ej. Operando1 + Operando2).

- Se apila (hace push) el resultado de esa operación de nuevo en la pila.

Finalización:

Si al terminar de leer la entrada queda exactamente un número en la pila → La expresión es VÁLIDA y ese es el resultado.

Si la pila queda vacía o con más de un número → La expresión es INVÁLIDA (Error de sintaxis).

Si ocurre una división por cero → La expresión es INVÁLIDA (Error aritmético).
