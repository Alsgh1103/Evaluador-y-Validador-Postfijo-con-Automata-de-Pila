#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

void print_formatted(double value) {
    char buffer[100];

    sprintf(buffer, "%.10f", value);

    int len = strlen(buffer);
    while (len > 0 && buffer[len-1] == '0') {
        buffer[len-1] = '\0';
        len--;
    }

    if (len > 0 && buffer[len-1] == '.') {
        buffer[len-1] = '\0';
    }

    printf("%s", buffer);
}

int is_operator(char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0);
}
