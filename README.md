# 🎯 Evaluador y Validador Postfijo con Autómata de Pila (AP)

Programa en lenguaje C que implementa un **Autómata de Pila (AP)** para la **evaluación y validación de expresiones aritméticas en notación postfija (RPN)**.  

El sistema procesa una cadena de tokens (operandos y operadores `+`, `-`, `*`, `/`) y:

- ✅ Determina si la expresión es **sintácticamente válida**.
- 🧮 **Calcula el resultado numérico** de la expresión si es correcta.
- 📄 **Genera archivos de trazabilidad** que documentan paso a paso el proceso de evaluación.

---

## 🎓 Contexto académico

Este proyecto fue desarrollado como **trabajo final** para el curso de **Teoría de la Computación** en la  
**Facultad de Ingeniería de Sistemas e Informática** de la **Universidad Nacional Mayor de San Marcos (UNMSM)**.

---

## 🤔 ¿Qué es la notación postfija (RPN)?

En notación postfija los operadores van **después** de los operandos.  
Por ejemplo:

- 📝 Infija: `3 + 4 * 2`  
- ✨ Postfija: `3 4 2 * +`

Esta forma no necesita paréntesis ni prioridades y se puede evaluar fácilmente usando una **pila**.

---

## ⚙️ ¿Qué hace este programa?

Dada una expresión postfija, el programa:

1. 📥 Lee la entrada desde un archivo o desde la consola interactiva.
2. 📚 Usa una pila para ir procesando números y operadores.
3. 🔍 Informa si la expresión es válida o no.
4. 📊 **Genera dos archivos de salida:**
   - **`evolucion_<nombre>.txt`**: Describe el paso a paso de la pila mostrando las transiciones del autómata.
   - **`resultado_<nombre>.txt`**: Muestra el resultado numérico final (si es exitoso) o detalla el error específico (aritmético o sintáctico).

---

## 🧠 Modelo teórico

El proyecto se apoya en dos niveles:

1. 🔤 Un **autómata para clasificar tokens** como *operando* u *operador*.
2. 🎰 Un **autómata de pila** que valida y evalúa la expresión postfija completa.

### 1️⃣ Autómata para validar si un token es operando u operador

Este autómata (finito / de pila trivial) decide si cada token leído es:

- 🔢 **Operando** numérico (entero o decimal).
- ➕ **Operador aritmético** (`+`, `-`, `*`, `/`).
- ❌ **Token inválido**.

![Autómata para distinguir operando / operador](IMAGENES/AFD.jpeg)

### 2️⃣ Autómata de Pila para validar la expresión postfija

El segundo autómata modela el comportamiento clásico de la pila en RPN:

- 📥 Por cada **operando** leído → apila un símbolo `X`.
- 🔄 Por cada **operador binario** leído → desapila dos `X` y vuelve a apilar uno (`X`).
- ✅ La expresión es **aceptada** si al consumir toda la entrada queda exactamente un `X` sobre el símbolo inicial `Z` (es decir, un único resultado).

![Autómata de pila que valida expresiones postfijas](IMAGENES/AP.jpeg)

---

## 🔬 Interpretación del proceso

**Objetivo:** calcular el resultado numérico de una expresión postfija (por ejemplo `10 5 +`).

1. 🔢 Si se lee un **número**, se apila (operación *push*).
2. ➕ Si se lee un **operador** (`+`, `-`, `*`, `/`):
   - ⬇️ Se sacan de la pila los dos últimos números (operaciones *pop*).
   - 🧮 Se aplica la operación: `resultado = operando1 operador operando2`.
   - ⬆️ El resultado se vuelve a apilar (*push*).
3. 🏁 Al finalizar la lectura:
   - ✅ Si queda **exactamente un número** en la pila → la expresión es **VÁLIDA** y ese es el resultado.
   - ❌ Si la pila queda vacía o con más de un número → la expresión es **INVÁLIDA**.
   - ⚠️ Si se intenta dividir entre cero → la expresión se marca como **INVÁLIDA** por error aritmético.

---

## 📁 Estructura del repositorio
```text
├── 🖼️ IMAGENES/                  # Diagramas de los autómatas
│   ├── AFD.jpeg                  # Autómata Finito Determinista
│   └── AP.jpeg                   # Autómata de Pila
├── 💻 RPN-CALCULATOR/            # Código fuente del evaluador
│   ├── include/                  # Archivos de cabecera (.h)
│   ├── src/                      # Código fuente (.c)
│   ├── Makefile                  # Script de compilación
│   └── README.md                 # Documentación técnica detallada
├── 📚 docs/                      # Documentación académica
│   ├── AvanceInformeTC.pdf
│   ├── INFORME_FINAL.pdf
│   ├── Informe_SegundoAvance.pdf
│   └── PRESENTACIÓN_DIAPOSITIVAS.pdf
├── 📜 LICENSE                    # Licencia MIT
└── 📖 README.md                  # Este archivo (documentación principal)
```

---

## 📂 Archivos de entrada y salida

### 📥 Entrada

El programa puede recibir la expresión postfija de dos formas:

1. 💬 **Modo consola interactivo**: Ingresando tokens uno por uno hasta escribir `=`.
2. 📄 **Modo archivo**: Leyendo desde un archivo de texto de cualquier nombre que contenga la expresión completa (tokens separados por espacios).

### 📤 Salida

El programa **siempre genera dos archivos**:

#### 📊 1. **`evolucion_<nombre>.txt`**
Describe el paso a paso de la evaluación mostrando:
- 🔢 Número de paso
- 🔄 Transición del autómata aplicada
- 📝 Descripción de la operación
- 📚 Estado actual de la pila

**Ejemplo exitoso:**
```text
PASO | TRANSICION                          | DESCRIPCION               | PILA
-----|-------------------------------------|---------------------------|------------------
0    | d(q0, e, Z0) = (q0, Z0)             | INICIO                    | Z0 [ vacia ]
1    | d(q0, 10, Z0) = (q0, X Z0)          | 1 PUSH                    | Z0 [ 10 ]
2    | d(q0, 5, X) = (q0, XX)              | 1 PUSH                    | Z0 [ 10 5 ]
3    | d(q0, +, XX) = (q0, X)              | 2 POP Y 1 PUSH            | Z0 [ 15 ]
4    | d(q0, e, X Z0) = (q0, e)            | ACEPTACION                | Z0 [ 15 ]
```

**Ejemplo con error:**
```text
PASO | TRANSICION                          | DESCRIPCION               | PILA
-----|-------------------------------------|---------------------------|------------------
0    | d(q0, e, Z0) = (q0, Z0)             | INICIO                    | Z0 [ vacia ]
1    | d(q0, 5, Z0) = (q0, X Z0)           | 1 PUSH                    | Z0 [ 5 ]
2    | d(q0, +, X) = RECHAZO               | ERROR                     | Z0 [ 5 ]
```

#### 🎯 2. **`resultado_<nombre>.txt`**

- ✅ **Si la evaluación es exitosa**: Muestra el resultado numérico final.
```text
  Resultado: 15
```

- ❌ **Si ocurre un error**: Detalla el tipo de error (sintáctico o aritmético).
```text
  ERROR SINTACTICO: Operandos insuficientes para el operador '+'
```
```text
  ERROR ARITMETICO: Division por cero
```

---

## 🚀 Instalación y uso

Para instrucciones detalladas de compilación, instalación de dependencias y ejemplos de uso, consulta el [📘 README técnico del evaluador](RPN-CALCULATOR/README.md).

### ⚡ Compilación rápida:
```bash
cd RPN-CALCULATOR
make
```

### 💬 Ejecución en modo consola:
```bash
./rpn_calculator
```

### 📄 Ejecución en modo archivo:
```bash
./rpn_calculator entrada.txt
```

---

## 🛠️ Herramientas usadas

- 💾 **Lenguaje de programación**: C
- 🧮 **Modelo teórico**: Autómata de Pila (Pushdown Automaton)
- 📚 **Estructura de datos**: Pila estática (LIFO)
- 🔨 **Build system**: Make

---

## 📜 Licencia

Este proyecto se distribuye bajo la **Licencia MIT**.  
Consulta el archivo `LICENSE` para más detalles.

---

<div align="center">

### 👥 Desarrollado por Grupo 2

**Universidad Nacional Mayor de San Marcos** 🎓  
*Facultad de Ingeniería de Sistemas e Informática*

---

⭐ Si te fue útil este proyecto, no olvides darle una estrella ⭐

</div>
