#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/stack.h"
#include "../include/utils.h"

void modo_archivo(char *nombre_entrada) {
    char nombre_res[300];
    char nombre_evo[300];

    sprintf(nombre_res, "resultado_%s", nombre_entrada);
    sprintf(nombre_evo, "evolucion_%s", nombre_entrada);

    FILE *f_entrada = fopen(nombre_entrada, "r");
    FILE *f_res = fopen(nombre_res, "w");
    FILE *f_evo = fopen(nombre_evo, "w");

    if (f_entrada == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s\n", nombre_entrada);
        exit(1);
    }

    fprintf(f_evo, "ENTRADA    =>   ESTADO DE LA PILA\n");
    fprintf(f_evo, "---------------------------------\n");
    fprintf(f_evo, "(Inicio)   =>   ");
    print_stack_file(f_evo);
    fprintf(f_evo, "\n");

    char token[50];

    while (fscanf(f_entrada, "%49s", token) == 1) {
        if (strcmp(token, "=") == 0) break;

        if (is_operator(token)) {
            if (get_stack_size() < 2) {
                fprintf(f_res, "ERROR: Faltan operandos para operar '%s'.", token);
                fprintf(f_evo, "%-10s =>   [RECHAZADO: Faltan operandos]\n", token);
                exit(1);
            }
            double op2 = pop();
            double op1 = pop();
            double res = 0;

            if (strcmp(token, "+") == 0) res = op1 + op2;
            else if (strcmp(token, "-") == 0) res = op1 - op2;
            else if (strcmp(token, "*") == 0) res = op1 * op2;
            else if (strcmp(token, "/") == 0) {
                if (op2 == 0) {
                    fprintf(f_res, "ERROR: Division por cero.");
                    fprintf(f_evo, "%-10s =>   [RECHAZADO: Division por 0]\n", token);
                    exit(1);
                }
                res = op1 / op2;
            }
            push(res);
            
            fprintf(f_evo, "%-10s =>   ", token);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        } 
        else {
            char *endptr;
            double value = strtod(token, &endptr);
            if (*endptr != '\0') {
                fprintf(f_res, "ERROR: Simbolo invalido.");
                fprintf(f_evo, "%-10s =>   [RECHAZADO: Simbolo invalido]\n", token);
                exit(1);
            }
            push(value);
            
            fprintf(f_evo, "%-10s =>   ", token);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        }
    }

    int size = get_stack_size();
    if (size == 1) {
        printf("Exito. Archivos generados: %s y %s\n", nombre_res, nombre_evo);
        fprintf(f_res, "Resultado: ");
        print_formatted_file(f_res, get_top_value());
        fprintf(f_res, "\n");
        fprintf(f_evo, "(Fin)      =>   [ACEPTADO]\n");
    } else if (size == 0) {
        fprintf(f_res, "ERROR: Pila vacia.");
        fprintf(f_evo, "(Fin)      =>   [RECHAZADO: Pila vacia]\n");
        exit(1);
    } else {
        fprintf(f_res, "ERROR: Expresion incompleta (Sobran %d numeros).", size);
        fprintf(f_evo, "(Fin)      =>   [RECHAZADO: Sobran numeros]\n");
        exit(1);
    }

    fclose(f_entrada);
    fclose(f_res);
    fclose(f_evo);
}

void modo_consola() {
    srand(time(NULL)); 
    int id = rand() % 10000; 

    char nombre_res[100];
    char nombre_evo[100];
    sprintf(nombre_res, "resultado_manual_%d.txt", id);
    sprintf(nombre_evo, "evolucion_manual_%d.txt", id);

    FILE *f_res = fopen(nombre_res, "w");
    FILE *f_evo = fopen(nombre_evo, "w");

    printf("------ MODO CONSOLA ------\n");
    printf("Ingrese operacion y presione ENTER.\n");
    printf("Escribe '=' para terminar.\n");
    printf("--------------------------\n");

    fprintf(f_evo, "ENTRADA    =>   ESTADO DE LA PILA\n");
    fprintf(f_evo, "---------------------------------\n");
    fprintf(f_evo, "(Inicio)   =>   ");
    print_stack_file(f_evo);
    fprintf(f_evo, "\n");

    char token[50];

    while (1) {
        printf("> ");
        if (scanf("%49s", token) == EOF) break;
        if (strcmp(token, "=") == 0) break;

        if (is_operator(token)) {
            if (get_stack_size() < 2) {
                // Solo guardamos en archivo y salimos
                fprintf(f_res, "ERROR: Faltan operandos.");
                fprintf(f_evo, "%-10s =>   [RECHAZADO: Faltan operandos]\n", token);
                exit(1);
            }
            double op2 = pop();
            double op1 = pop();
            double res = 0;

            if (strcmp(token, "+") == 0) res = op1 + op2;
            else if (strcmp(token, "-") == 0) res = op1 - op2;
            else if (strcmp(token, "*") == 0) res = op1 * op2;
            else if (strcmp(token, "/") == 0) {
                if (op2 == 0) {
                    fprintf(f_res, "ERROR: Division por cero.");
                    fprintf(f_evo, "%-10s =>   [RECHAZADO: Division por 0]\n", token);
                    exit(1);
                }
                res = op1 / op2;
            }
            push(res);
            
            fprintf(f_evo, "%-10s =>   ", token);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        } 
        else {
            char *endptr;
            double value = strtod(token, &endptr);
            if (*endptr != '\0') {
                fprintf(f_res, "ERROR: Simbolo invalido.");
                fprintf(f_evo, "%-10s =>   [RECHAZADO: Simbolo invalido]\n", token);
                exit(1);
            }
            push(value);

            fprintf(f_evo, "%-10s =>   ", token);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        }
    }

    int size = get_stack_size();
    if (size == 1) {
        printf("\nExito. Archivos generados:\n -> %s\n -> %s\n", nombre_res, nombre_evo);

        fprintf(f_res, "Resultado: ");
        print_formatted_file(f_res, get_top_value());
        fprintf(f_res, "\n");
        fprintf(f_evo, "(Fin)      =>   [ACEPTADO]\n");
    } else if (size == 0) {
        fprintf(f_res, "ERROR: Pila vacia.");
        fprintf(f_evo, "(Fin)      =>   [RECHAZADO: Pila vacia]\n");
        exit(1);
    } else {
        fprintf(f_res, "ERROR: Expresion incompleta.");
        fprintf(f_evo, "(Fin)      =>   [RECHAZADO: Sobran numeros]\n");
        exit(1);
    }

    fclose(f_res);
    fclose(f_evo);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        modo_archivo(argv[1]);
    } 
    else if (argc == 1) {
        modo_consola();
    } 
    else {
        printf("Error: Uso incorrecto.\n");
        return 1;
    }
    return 0;
}