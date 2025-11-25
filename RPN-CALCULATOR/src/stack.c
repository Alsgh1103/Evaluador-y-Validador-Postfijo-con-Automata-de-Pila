#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"
#include "../include/utils.h"

#define MAX_STACK_SIZE 100

static double stack[MAX_STACK_SIZE];
static int top = -1;

void push(double value) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("FATAL ERROR: Stack overflow.\n");
        exit(1);
    }
    top++;
    stack[top] = value;
}

double pop() {
    if (top < 0) {
        printf("FATAL ERROR: Missing operands in stack.\n");
        exit(1);
    }
    double value = stack[top];
    top--;
    return value;
}

void print_stack() {
    printf("   [ Stack: ");
    if (top == -1) {
        printf("empty ");
    } else {
        for (int j = 0; j <= top; j++) {
            print_formatted(stack[j]);
            printf(" ");
        }
    }
    printf("] <\n");
}

int get_stack_size() {
    return top + 1;
}

double get_top_value() {
    if (top >= 0) return stack[top];
    return 0.0;
}
