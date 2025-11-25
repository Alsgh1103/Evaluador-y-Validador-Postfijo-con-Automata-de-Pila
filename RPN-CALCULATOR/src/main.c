#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/utils.h"

int main() {
    char token_buffer[50];

    printf("------ POSTFIX EVALUATOR & VALIDATOR ------\n");
    printf("1. Type number and ENTER.\n");
    printf("2. Type operator and ENTER.\n");
    printf("3. Type '=' to finish.\n");
    printf("-------------------------------------------\n");

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
                    printf("FATAL ERROR: Division by zero.\n");
                    return 1;
                }
                push(op1 / op2);
            }
            printf("   Operation '%s' applied.\n", token_buffer);
        }
        else {
            char *endptr;
            double value = strtod(token_buffer, &endptr);

            if (*endptr != '\0') {
                printf("FATAL ERROR: '%s' is invalid.\n", token_buffer);
                return 1;
            }

            push(value);
            printf("   Data entered.\n");
        }

        print_stack();
    }

    printf("\n--- FINAL RESULT ---\n");
    int size = get_stack_size();

    if (size == 1) {
        printf("Result: ");
        print_formatted(get_top_value());
        printf("\n");
    } else if (size == 0) {
        printf("Stack empty.\n");
    } else {
        printf("ERROR: Incomplete (Remaining %d numbers).\n", size);
    }

    return 0;
}
