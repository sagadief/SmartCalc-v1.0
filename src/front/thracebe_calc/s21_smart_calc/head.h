//
// Created by Thrace Bebe on 4/18/23.
//

#ifndef C7_SMARTCALC_V1_0_1_HEAD_H_
#define C7_SMARTCALC_V1_0_1_HEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// # define SIZE 260

typedef struct t_stack{
    char* value;
    struct t_stack* next;
} t_stack;



bool is_empty(t_stack *head);
void print_all_stack(t_stack* head);
t_stack* create_stack_elem(char* value);
bool is_operator(char *symbol, char *str, int *i);
int getPriority(char* symbol);
void push_front(t_stack** head, t_stack* elem);
char* get_top_elem(t_stack* head);
bool check_trigon(char* substr);
void push_back(t_stack **head, t_stack *elem);
t_stack* pop(t_stack** head);
bool is_unary_operator(const char* op);
char* get_last_elem(t_stack* head);
t_stack* pop_back(t_stack** head);
int get_number(char * infix, int pos, t_stack **head);
void double_to_str(double x, t_stack **head);
void double_to_str_trig(double x, t_stack **head);
void infixToPostfix(char* infix,  double x, t_stack** numbers);
double evaluatePostfix(t_stack** postfix,  double x);
bool valide_str(char*infix);


#endif //C7_SMARTCALC_V1_0_1_HEAD_H_

