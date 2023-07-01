//
// Created by Thrace Bebe on 4/18/23.
//

#ifndef C7_SMARTCALC_V1_0_1_HEADER_H_
#define C7_SMARTCALC_V1_0_1_HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

# define SIZE 260


typedef struct trigon {
    int cos, sin, tan, acos, asin, atan, sqrt, ln, log;
} trigon_n;

typedef struct symbol {
    int plus, minus, multiply, division, interest, bracket, unbracket, degree, dot;
} symbol_n;

typedef struct t_stack {
    char value;
    int priority;
    struct t_stack* next;
} t_stack;

typedef struct queue {
    int value;
    struct queue* next;
} queue;



//for stack
t_stack* create_stack_elem(char value);
void print_all_stack(t_stack** head);
void print_one_elem_from_stack(t_stack** head);
void add_elem_to_stack(t_stack** head, t_stack* elem);
void delete_elem_from_stack(t_stack** head);
int check_trigon(char *bukva, int *dot, trigon_n *tr);
int check_symbol(char *bukva, int dot, symbol_n *sy);
int get_priority(char symbol);
//for queue
// void enqueue(int);
// void dequeue();
// void show();






#endif //C7_SMARTCALC_V1_0_1_HEADER_H_










// Высший приоритет:

// ( и ): скобки для управления порядком операций
// Средний приоритет:

// ^: возведение в степень
// Низший приоритет:

// * и /: умножение и деление
// %: остаток от деления

1 2 + 1 3 * 3 / - 3 3 / 1 2 - * +












