#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/stack.h"
#include "../include/utils.h"

void modo_archivo(char *nombre_entrada) {
    char nombre_res[300];
    char nombre_evo[300];
    char transicion[300];
    char descripcion[300];
    int paso = 0;

    sprintf(nombre_res, "resultado_%s", nombre_entrada);
    sprintf(nombre_evo, "evolucion_%s", nombre_entrada);

    FILE *f_entrada = fopen(nombre_entrada, "r");
    FILE *f_res = fopen(nombre_res, "w");
    FILE *f_evo = fopen(nombre_evo, "w");

    if (f_entrada == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s\n", nombre_entrada);
        exit(1);
    }

    fprintf(f_evo, "%-4s | %-35s | %-25s | %s\n", "PASO", "TRANSICION", "DESCRIPCION", "PILA");
    fprintf(f_evo, "-----|-------------------------------------|---------------------------|------------------\n");
    
    fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, "d(q0, e, Z0) = (q0, Z0)", "INICIO");
    print_stack_file(f_evo);
    fprintf(f_evo, "\n");

    char token[50];

    while (fscanf(f_entrada, "%49s", token) == 1) {
        if (strcmp(token, "=") == 0) break;
        
        paso++;
        
        if (is_operator(token)) {
            if (get_stack_size() < 2) {
                fprintf(f_evo, "%-4d | %-35s | %-25s | ERROR: Stack Underflow\n", paso, "ERROR", "Faltan operandos");
                fprintf(f_res, "ERROR SINTACTICO: Faltan operandos para operar '%s'.", token);
                fclose(f_entrada); fclose(f_res); fclose(f_evo);
                exit(1);
            }
            double op2 = pop();
            double op1 = pop();
            double res = 0;

            if (strcmp(token, "+") == 0) {
                res = op1 + op2;
                sprintf(transicion, "d(q0, +, XX) = (q0, X)");
            }
            else if (strcmp(token, "-") == 0) {
                res = op1 - op2;
                sprintf(transicion, "d(q0, -, XX) = (q0, X)");
            }
            else if (strcmp(token, "*") == 0) {
                res = op1 * op2;
                sprintf(transicion, "d(q0, *, XX) = (q0, X)");
            }
            else if (strcmp(token, "/") == 0) {
                if (op2 == 0) {
                    fprintf(f_evo, "%-4d | %-35s | %-25s | ERROR: Division por 0\n", paso, "ERROR", "Division por cero.");
                    fprintf(f_res, "ERROR ARITMETICO: Division por cero.");
                    fclose(f_entrada); fclose(f_res); fclose(f_evo);
                    exit(1);
                }
                res = op1 / op2;
                sprintf(transicion, "d(q0, /, XX) = (q0, X)");
            }

            sprintf(descripcion, "2 POP Y 1 PUSH");
            push(res);
            
            fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, transicion, descripcion);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        } 
        else {
            char *endptr;
            double value = strtod(token, &endptr);
            if (*endptr != '\0') {
                fprintf(f_evo, "%-4d | %-35s | %-25s | ERROR: Token invalido\n", paso, "ERROR", "Simbolo no reconocido");
                fprintf(f_res, "ERROR SINTACTICO: Simbolo invalido '%s'.", token);
                fclose(f_entrada); fclose(f_res); fclose(f_evo);
                exit(1);
            }
            
            if (get_stack_size() == 0) {
                sprintf(transicion, "d(q0, %s, Z0) = (q0, X Z0)", token);
            } else {
                sprintf(transicion, "d(q0, %s, X) = (q0, XX)", token);
            }

            sprintf(descripcion, "1 PUSH");
            push(value);
            
            fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, transicion, descripcion);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        }
    }

    paso++;
    int size = get_stack_size();
    if (size == 1) {
        printf("Exito. Archivos generados:\n -> %s\n -> %s\n", nombre_res, nombre_evo);
        fprintf(f_res, "Resultado: ");
        print_formatted_file(f_res, get_top_value());
        
        fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, "d(q0, e, X Z0) = (q0, e)", "ACEPTACION");
        print_stack_file(f_evo);
        fprintf(f_evo, "\n");

    } else if (size == 0) {
        fprintf(f_res, "ERROR SINTACTICO: Pila vacia.");
        fprintf(f_evo, "%-4d | %-35s | %-25s | RECHAZO: Pila vacia\n", paso, "RECHAZO", "Falta Z0");
        exit(1);
    } else {
        fprintf(f_res, "ERROR SINTACTICO: Expresion incompleta (Sobran %d numeros).", size);
        fprintf(f_evo, "%-4d | %-35s | %-25s | RECHAZO: Sobran datos\n", paso, "RECHAZO", "Pila sucia");
        exit(1);
    }

    fclose(f_entrada);
    fclose(f_res);
    fclose(f_evo);
}

void modo_consola() {
    srand(time(NULL)); 
    int id = rand() % 10000; 
    
    char transicion[300];
    char descripcion[300];
    int paso = 0;

    char nombre_res[100];
    char nombre_evo[100];
    sprintf(nombre_res, "resultado_manual_%d.txt", id);
    sprintf(nombre_evo, "evolucion_manual_%d.txt", id);

    FILE *f_res = fopen(nombre_res, "w");
    FILE *f_evo = fopen(nombre_evo, "w");

    printf("------ MODO CONSOLA ------\n");
    printf("Ingrese operacion (ej: 5 3 +) y '=' para terminar.\n");
    printf("--------------------------\n");

    fprintf(f_evo, "%-4s | %-35s | %-25s | %s\n", "PASO", "TRANSICION", "DESCRIPCION", "PILA");
    fprintf(f_evo, "-----|-------------------------------------|---------------------------|------------------\n");
    
    fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, "d(q0, e, Z0) = (q0, Z0)", "INICIO");
    print_stack_file(f_evo);
    fprintf(f_evo, "\n");

    char token[50];

    while (1) {
        printf("> ");
        if (scanf("%49s", token) == EOF) break;
        if (strcmp(token, "=") == 0) break;
        
        paso++;
        
        if (is_operator(token)) {
            if (get_stack_size() < 2) {
                fprintf(f_evo, "%-4d | %-35s | %-25s | ERROR: Stack Underflow\n", paso, "ERROR", "Faltan operandos");
                fprintf(f_res, "ERROR SINTACTICO: Faltan operandos para operar '%s'.", token);
                fclose(f_res); fclose(f_evo);
                exit(1);
            }
            double op2 = pop();
            double op1 = pop();
            double res = 0;

            if (strcmp(token, "+") == 0) {
                res = op1 + op2;
                sprintf(transicion, "d(q0, +, XX) = (q0, X)");
            }
            else if (strcmp(token, "-") == 0) {
                res = op1 - op2;
                sprintf(transicion, "d(q0, -, XX) = (q0, X)");
            }
            else if (strcmp(token, "*") == 0) {
                res = op1 * op2;
                sprintf(transicion, "d(q0, *, XX) = (q0, X)");
            }
            else if (strcmp(token, "/") == 0) {
                if (op2 == 0) {
                    fprintf(f_evo, "%-4d | %-35s | %-25s | ERROR: Division por 0\n", paso, "ERROR", "Division por cero.");
                    fprintf(f_res, "ERROR ARITMETICO: Division por cero.");
                    fclose(f_res); fclose(f_evo);
                    exit(1);
                }
                res = op1 / op2;
                sprintf(transicion, "d(q0, /, XX) = (q0, X)");
            }

            sprintf(descripcion, "2 POP Y 1 PUSH");
            push(res);
            
            fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, transicion, descripcion);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        } 
        else {
            char *endptr;
            double value = strtod(token, &endptr);
            if (*endptr != '\0') {
                fprintf(f_evo, "%-4d | %-35s | %-25s | ERROR: Token invalido\n", paso, "ERROR", "Simbolo no reconocido");
                fprintf(f_res, "ERROR SINTACTICO: Simbolo invalido '%s'.", token);
                fclose(f_res); fclose(f_evo);
                exit(1);
            }
            
            if (get_stack_size() == 0) {
                sprintf(transicion, "d(q0, %s, Z0) = (q0, X Z0)", token);
            } else {
                sprintf(transicion, "d(q0, %s, X) = (q0, XX)", token);
            }

            sprintf(descripcion, "1 PUSH");
            push(value);

            fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, transicion, descripcion);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        }
    }

    paso++;
    int size = get_stack_size();
    if (size == 1) {
        printf("\nExito. Archivos generados:\n -> %s\n -> %s\n", nombre_res, nombre_evo);

        fprintf(f_res, "Resultado: ");
        print_formatted_file(f_res, get_top_value());
        
        fprintf(f_evo, "%-4d | %-35s | %-25s | Z0 ", paso, "d(q0, e, X Z0) = (q0, e)", "ACEPTACION");
        print_stack_file(f_evo);
        fprintf(f_evo, "\n");

    } else if (size == 0) {
        fprintf(f_res, "ERROR SINTACTICO: Pila vacia.");
        fprintf(f_evo, "%-4d | %-35s | %-25s | RECHAZO: Pila vacia\n", paso, "RECHAZO", "Falta Z0");
        exit(1);
    } else {
        fprintf(f_res, "ERROR SINTACTICO: Expresion incompleta (Sobran %d numeros).", size);
        fprintf(f_evo, "%-4d | %-35s | %-25s | RECHAZO: Sobran numeros\n", paso, "RECHAZO", "Pila sucia");
        exit(1);
    }
    
    fclose(f_res);
    fclose(f_evo);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        modo_archivo(argv[1]);
    } else {
        modo_consola();
    }
    return 0;
}