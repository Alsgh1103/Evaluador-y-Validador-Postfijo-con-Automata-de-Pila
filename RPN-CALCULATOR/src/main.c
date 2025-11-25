#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/utils.h"

int main() {
    char token_buffer[50];

    printf("------ EVALUADOR Y VALIDADOR POSTFIJO ------\n");
    printf("1. Escribe numero y ENTER.\n");
    printf("2. Escribe operador y ENTER.\n");
    printf("3. Escribe '=' para terminar.\n");
    printf("---------------------------------------------\n");

    while (1) {
        printf("> ");

        if (scanf("%49s", token_buffer) == EOF) break;

        if (strcmp(token_buffer, "=") == 0) {
            break;
        }

        if (is_operator(token_buffer)) {
            double op2 = pop();
            double op1 = pop();

            if (strcmp(token_buffer, "+") == 0) push(op1 + op2);
            else if (strcmp(token_buffer, "-") == 0) push(op1 - op2);
            else if (strcmp(token_buffer, "*") == 0) push(op1 * op2);
            else if (strcmp(token_buffer, "/") == 0) {
                if (op2 == 0) {
                    printf("ERROR FATAL: Division por cero.\n");
                    return 1;
                }
                push(op1 / op2);
            }
            printf("   Operacion '%s' aplicada.\n", token_buffer);
        }
        else {
            char *endptr;
            double value = strtod(token_buffer, &endptr);

            if (*endptr != '\0') {
                printf("ERROR FATAL: '%s' no es valido.\n", token_buffer);
                return 1;
            }

            push(value);
            printf("   Dato ingresado.\n");
        }

        print_stack();
    }

    printf("\n--- RESULTADO FINAL ---\n");
    int size = get_stack_size();

    if (size == 1) {
        printf("Resultado: ");
        print_formatted(get_top_value());
        printf("\n");
    } else if (size == 0) {
        printf("Pila vacia.\n");
    } else {
        printf("ERROR: Incompleto (Sobran %d numeros).\n", size);
    }

    return 0;
}
