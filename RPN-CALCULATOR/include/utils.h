#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void print_formatted(double value);
void print_formatted_file(FILE *f, double value);
int is_operator(char* token);

#endif