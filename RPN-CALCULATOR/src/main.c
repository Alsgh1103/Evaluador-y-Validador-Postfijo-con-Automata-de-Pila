#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/utils.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Uso ./rpn_calculator archivo.txt\n");
        return 1;
    }

    char nombre_entrada[200];
    char nombre_res[300];
    char nombre_evo[300];

    strcpy(nombre_entrada, argv[1]);

    sprintf(nombre_res, "resultado_%s", nombre_entrada);
    sprintf(nombre_evo, "evolucion_%s", nombre_entrada);

    FILE *f_entrada = fopen(nombre_entrada, "r");
    FILE *f_res = fopen(nombre_res, "w");
    FILE *f_evo = fopen(nombre_evo, "w");

    if (f_entrada == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s\n", nombre_entrada);
        return 1;
    }

    fprintf(f_evo, "ENTRADA    =>   ESTADO DE LA PILA\n");
    fprintf(f_evo, "---------------------------------\n");
    
    fprintf(f_evo, "(Inicio)   =>   ");
    print_stack_file(f_evo);
    fprintf(f_evo, "\n");

    char token_buffer[50];

    while (1) {
        if (fscanf(f_entrada, "%49s", token_buffer) == EOF) break;

        if (strcmp(token_buffer, "=") == 0) break;

        if (is_operator(token_buffer)) {
            if (get_stack_size() < 2) {
                fprintf(f_res, "ERROR: Faltan operandos para operar '%s'.", token_buffer);
                exit(1);
            }

            double op2 = pop();
            double op1 = pop();

            if (strcmp(token_buffer, "+") == 0) push(op1 + op2);
            else if (strcmp(token_buffer, "-") == 0) push(op1 - op2);
            else if (strcmp(token_buffer, "*") == 0) push(op1 * op2);
            else if (strcmp(token_buffer, "/") == 0) {
                if (op2 == 0) {
                    fprintf(f_res, "ERROR: Division por cero.");
                    exit(1);
                }
                push(op1 / op2);
            }
            
            fprintf(f_evo, "%-10s =>   ", token_buffer);
            print_stack_file(f_evo);
            fprintf(f_evo, "\n");
        }
        else {
            char *endptr;
            double value = strtod(token_buffer, &endptr);

            if (*endptr != '\0') {
                fprintf(f_res, "ERROR: Simbolo invalido.");
                exit(1);
            }

            push(value);
            
            fprintf(f_evo, "%-10s =>   ", token_buffer);
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
    } else if (size == 0) {
        fprintf(f_res, "ERROR: Pila vacia (No hay resultado).");
        exit(1);
    } else {
        fprintf(f_res, "ERROR: Expresion incompleta (Sobran %d numeros).", size);
        exit(1);
    }

    fclose(f_entrada);
    fclose(f_res);
    fclose(f_evo);

    return 0;
}