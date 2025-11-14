#include <stdio.h>    // Para printf y scanf
#include <stdlib.h>   // Para atof (convertir string a double)
#include <string.h>   // Para strcmp (comparar strings)

#define MAX_PILA 100

double pila[MAX_PILA];
int tope = -1;

int error_sintactico = 0;
int error_aritmetico = 0;

void imprimir_pila() {
    printf("    Estado Pila: [ ");
    
    if (tope == -1) {
        printf("(vacia)");
    } else {
        for (int j = 0; j <= tope; j++) {
            printf("%f ", pila[j]);
        }
    }
    
    printf("] <- TOPE\n\n");
}

void push(double valor) {
    if (tope >= MAX_PILA - 1) {
        printf("    ERROR SINTACTICO: Pila llena (demasiados operandos).\n");
        error_sintactico = 1;
        return;
    }
    tope++;
    pila[tope] = valor;
}

double pop() {
    if (tope < 0) {
        printf("    ERROR SINTACTICO: Faltan operandos para el operador.\n");
        error_sintactico = 1;
        return 0.0;
    }
    double valor = pila[tope];
    tope--;
    return valor;
}

int esOperador(char* token) {
    if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
        strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
        return 1;
    }
    return 0;
}


int main() {
    char tokens[100][30];
    int num_tokens = 0;
    int i;

    char buffer_token[30];

    printf("--- EVALUADOR POSTFIJO (AUTOMATA DE PILA) ---\n");
    printf("Ingrese su expresion (separada por espacios, 's' para terminar):\n");

    while (num_tokens < MAX_PILA) {
        
        int resultado_scan = scanf("%29s", buffer_token);

        if (resultado_scan == EOF) {
            break;
        }

        if (strcmp(buffer_token, "s") == 0) {
            break;
        }

        strcpy(tokens[num_tokens], buffer_token);
        num_tokens++;
    }

    if (num_tokens == 0) {
        printf("No se ingresaron tokens.\n");
        return 1;
    }

    printf("\n--- INICIO DE LA SIMULACION (PASO A PASO) ---\n");
    
    printf("Estado Inicial (Pila Vacia):\n");
    imprimir_pila();
    
    for (i = 0; i < num_tokens; i++) {
        char* token_actual = tokens[i];
        
        printf("--- Paso %d ---\n", i + 1);
        printf("Token Leido: '%s'\n", token_actual);

        if (esOperador(token_actual)) {
            printf("  Accion: Operador. Se haran 2 POPs y 1 PUSH.\n");

            double op2 = pop();
            if (error_sintactico) break;

            double op1 = pop();
            if (error_sintactico) break;

            if (strcmp(token_actual, "+") == 0) {
                push(op1 + op2);
            } else if (strcmp(token_actual, "-") == 0) {
                push(op1 - op2);
            } else if (strcmp(token_actual, "*") == 0) {
                push(op1 * op2);
            } else if (strcmp(token_actual, "/") == 0) {
                if (op2 == 0) {
                    printf("    ERROR ARITMETICO: Division por cero.\n");
                    error_aritmetico = 1;
                    break;
                }
                push(op1 / op2);
            }

        } else {
            printf("  Accion: Operando. Se hara 1 PUSH.\n");
            
            double valor = atof(token_actual);
            push(valor);
        }
        
        if (error_sintactico) break;

        imprimir_pila();
    }

    printf("\n--- RESULTADO FINAL DEL AUTOMATA ---\n");

    if (error_sintactico) {
        printf("ESTADO: EXPRESION RECHAZADA (Error Sintactico).\n");
    
    } else if (error_aritmetico) {
        printf("ESTADO: EXPRESION RECHAZADA (Error Aritmetico).\n");
    
    } else {
        if (tope == 0) {
            printf("ESTADO: EXPRESION ACEPTADA.\n");
            printf("Resultado final: %f\n", pila[tope]);
        
        } else if (tope > 0) {
            printf("ESTADO: EXPRESION RECHAZADA (Error Sintactico).\n");
            printf("Causa: Faltaron operadores (quedaron %d valores en la pila).\n", tope + 1);
        } else {
            printf("ESTADO: EXPRESION RECHAZADA (Error Sintactico).\n");
            printf("Causa: La pila quedo vacia (expresion vacia?).\n");
        }
    }

    return 0;
}