#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

typedef struct t_stack {
    char* value;
    struct t_stack* next;
} t_stack;


bool isEmpty(t_stack *head) {
    return head == NULL;
}




void print_all_stack(t_stack* head) {
    printf("Stack: ");
    // Проход по всем элементам стека
    t_stack* current = head;
    while (current != NULL) {
        // Вывод значения текущего элемента стека
        printf("%s |", current->value);
        // Переход к следующему элементу стека
        current = current->next;
    }
    printf("\n");
}




t_stack* create_stack_elem(char* value) {
    t_stack* new_elem = malloc(sizeof(t_stack));
    if (new_elem) {
        new_elem->value = malloc((strlen(value) + 1) * sizeof(char));
        if (new_elem->value) {
            strcpy(new_elem->value, value);
            new_elem->next = NULL;
        } else {
            // Обработка ошибки выделения памяти
            fprintf(stderr, "Ошибка выделения памяти\n");
            free(new_elem);
            new_elem = NULL;
        }
    } else {
        // Обработка ошибки выделения памяти
        fprintf(stderr, "Ошибка выделения памяти\n");
    }
    return new_elem;
}










int isOperator(char *symbol, char *str, int *i) {
    bool result = false;

    if (strncmp(str + *i, "cos", 3) == 0) {
    *symbol = 'c';
    result = true;
    (*i) += 2;
  } else if (strncmp(str + *i, "sin", 3) == 0) {
    *symbol = 's';
    result = true;
    (*i) += 2;
  } else if (strncmp(str + *i, "tan", 3) == 0) {
    *symbol = 't';
    result = true;
    (*i) += 2;
  } else if (strncmp(str + *i, "acos", 4) == 0) {
    *symbol = 'a';
    result = true;
    (*i) += 3;
  } else if (strncmp(str + *i, "asin", 4) == 0) {
    *symbol = 'i';
    result = true;
    (*i) += 3;
  } else if (strncmp(str + *i, "atan", 4) == 0) {
    *symbol = 'n';
    result = true;
    (*i) += 3;
  } else if (strncmp(str + *i, "sqrt", 4) == 0) {
    *symbol = 'q';
    result = true;
    (*i) += 3;
  } else if (strncmp(str + *i, "ln", 2) == 0) {
    *symbol = 'l';
    result = true;
    (*i) += 1;
  } else if (strncmp(str + *i, "log", 3) == 0) {
    *symbol = 'g';
    result = true;
    (*i) += 2;
    } else if (symbol[0] == '+' || symbol[0] == '-' || symbol[0] == '*' || 
    symbol[0] == '/' || symbol[0] == '^' || symbol[0] == '%') {
        result = true;
    };
    return result;
}

// Получение приоритета оператора
int getPriority(char* symbol) {
    int res = -1;
    
    switch (*symbol) {
        case '+':
        case '-':
            res = 1;
            break;
        case '*':
        case '%':
        case '/':
            res = 2;
            break;
        case '^':
            res = 3;
            break;
        case 'c':
        case 's':
        case 't':
        case 'a':
        case 'i':
        case 'n':
        case 'q':
        case 'l':
        case 'g':
            res = 4;
            break;
    }
    return res;
}
// Размещение элемента в стеке
void push_front(t_stack** head, t_stack* elem) {
    if (head && elem) {
        elem->next = *head;
        *head = elem;
    }
}

char* get_top_elem(t_stack* head) {
    return head->value;
}


bool check_trigon(char* substr) {
    const char *str = "cstainqlg";
    bool flag = false;
    char *result = strstr(str, substr);
    if (result != NULL)
        flag = true;
    else
        flag = false;
    return flag;
}



void push_back(t_stack **head, t_stack *elem)
{
	if (head == NULL && elem == NULL) return;
	
    if (*head == NULL)
		*head = elem;
	else {
        t_stack* temp = *head;
	    while (temp->next)
            temp = temp->next;
        temp->next = elem;
    }
}


t_stack* pop(t_stack** head) {
    t_stack* temp = NULL;
    if (!isEmpty(*head)) {
        temp = *head;
        *head = (*head)->next;
    }
    return temp; 
}

// t_stack* pop_back(t_stack** head) {
//     t_stack* tmp = NULL;
//         t_stack* cur = *head;
//         while (cur->next->next != NULL) {
//             cur = cur->next;
//         }
//     tmp = cur->next;
//     cur->next = NULL;
//     return tmp;
// }

// t_stack* tmp = *head;
// while (tmp->next->next != NULL) {
//     tmp = tmp->next;
// }
// t_stack* popped = tmp->next;
// tmp->next = NULL;
// free(popped);



char* get_last_elem(t_stack* head) {
    t_stack* tmp = head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    return tmp->value;
}

//  pop_back(t_stack** head) {
//     t_stack* tmp = *head;
//     while (tmp->next != NULL)

// }

t_stack* pop_back(t_stack** head) {
    t_stack* temp = NULL;
    if (*head == NULL) {
        return NULL;  // Стек пустой
    } else if ((*head)->next == NULL) {
        // В стеке только один элемент
        temp = *head;
        *head = NULL;
    } else {
        // Более одного элемента в стеке
        t_stack* current = *head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        temp = current->next;
        current->next = NULL;
    }
    return temp;
}






// isdigit(infix[i]) {}
int get_number(char * infix, int pos, t_stack **head) {
    size_t number_size = 0;
    while (isdigit(infix[pos]) || infix[pos] == '.') {
        pos++;
        number_size++;
    }
    pos--;
    char* number = malloc((number_size + 1) * sizeof(char));
    if (number == NULL)
        pos = -1;
    else {
        memcpy(number, &infix[pos - number_size + 1], number_size);
        number[number_size] = '\0';
        t_stack* tmp = create_stack_elem(number);
        // printf("%s\n", number);
        if (tmp != NULL) {
            push_back(head, tmp);
        } else {
            pos = -1;
            free(number);
        }
    }
    return pos;
}




void double_to_str(double x, t_stack **head) {
    int length = snprintf(NULL, 0, "%0.15f", x);
    char* result = malloc((length + 1) * sizeof(char)); // Выделение памяти для строки результатов
    snprintf(result, length + 1, "%0.15f", x);
    push_front(head, create_stack_elem(result));
    free(result);
}





// strncat(number, &infix[pos - number_size + 1], 1);

// Преобразование инфиксной нотации в обратную польскую нотацию
void infixToPostfix(char* infix, t_stack** numbers) {
    t_stack* operators = NULL;   //head -> operators
    char* symbol = malloc(2 * sizeof(char));
    char* top_symbol = malloc(2 * sizeof(char));

    
    for (int i = 0; infix[i]; i++) {

        symbol[0] = infix[i];
        symbol[1] = '\0';
        bool should_continue = true;
        if (symbol[0] == ' ' || symbol[0] == '\t')
            should_continue = false;
        
        if (should_continue) {
            if (isOperator(symbol, infix, &i)) {
                bool should_stop = true;
                while (!isEmpty(operators) && should_stop) {
                    top_symbol = operators->value;
                    if (getPriority(top_symbol) >= getPriority(symbol)) {
                        t_stack* tmp = pop(&operators);
                        // push_back(str, create_stack_elem(tmp->value));
                        push_back(numbers, create_stack_elem(tmp->value));
                        free(tmp);
                    } else {
                        should_stop = false;
                    }
                }
                push_front(&operators, create_stack_elem(symbol));
            } else if (symbol[0] == '(') {
                push_front(&operators, create_stack_elem(symbol));
            } else if (symbol[0] == ')') {
                bool should_stop = true;
                while (!isEmpty(operators) && should_stop) {
                    t_stack* tmp = pop(&operators);
                    top_symbol = tmp->value;
                    free(tmp);

                    if (top_symbol[0] == '(')
                        should_stop = false;
                    if (should_stop)
                        push_back(numbers, create_stack_elem(top_symbol));
                }
            } else {
                i = get_number(infix, i, numbers);
            }
        }
    }
    while (!isEmpty(operators)) {
        t_stack* tmp = pop(&operators);
        push_back(numbers, create_stack_elem(tmp->value));
        free(tmp);
    }
    free(symbol);
    free(top_symbol);
}



t_stack* evaluatePostfix(t_stack** postfix) {
    t_stack* head = NULL;
    // print_all_stack(*postfix);
    while (!isEmpty(*postfix)) {
            char* str = get_top_elem(*postfix);  // Получаем строку из стека
            double num = strtod(str, NULL);  // Преобразуем строку в число
        if (num != 0.0) {
            t_stack* tmp = pop(postfix);
            push_front(&head, create_stack_elem(tmp->value));
            // printf("===========%s\n", tmp->value);
            free(tmp);
        } else if (check_trigon(str)) {
            printf("--------------------\n");
            print_all_stack(*postfix);
            print_all_stack(head);
            printf("--------------------\n");
            t_stack* inter = pop(&head);
            t_stack* tmp = pop(postfix);
            // print_all_stack(*postfix);
            // print_all_stack(head);
            char* d = tmp->value;
            free(tmp);
            double x = atof(inter->value);
            switch (*d) {
                case 'c':
                    x = cos(x);
                    double_to_str(x, &head);
                    break;
                case 's':
                    x = sin(x);
                    double_to_str(x, &head);
                    printf("%f\n", x);
                    break;
                case 't':
                    x = tan(x);
                    double_to_str(x, &head);
                    break;
                case 'a':
                    x = acos(x);
                    double_to_str(x, &head);
                    break;
                case 'i':
                    x = asin(x);
                    double_to_str(x, &head);
                    break;
                case 'n':
                    x = atan(x);
                    double_to_str(x, &head);
                    break;
                case 'q':
                    x = sqrt(x);
                    double_to_str(x, &head);
                    break;
                case 'l':
                    x = log(x);
                    double_to_str(x, &head);
                    break;
                case 'g':
                    x = log10(x);
                    double_to_str(x, &head);
                    break;
            }
        } else {
            double a = 0;
            double b = 0;
            double x = 0;
            // print_all_stack(head);
            t_stack* inter2 = pop(&head);
            t_stack* inter1 = pop(&head);
            // print_all_stack(head);
            t_stack* tmp = pop(postfix);
            char* d = tmp->value;
            free(tmp);
            b = atof(inter2->value);
            a = atof(inter1->value);
            printf("%f\n", b);
            printf("%f\n", a);
            // printf("%s\n", d);
            switch (*d) {
                case '+':
                     x = a + b;
                    double_to_str(x, &head);
                    break;
                case '-':
                    x = a - b;
                    double_to_str(x, &head);
                    break;
                case '*':
                    x = a * b;
                    double_to_str(x, &head);
                    break;
                case '/':
                    x = a / b;
                    double_to_str(x, &head);
                    break;
                default:
                    printf("Error: Invalid operator\n");
                    exit(1);
            }
        }
    }
    return pop(&head);
}













// Функция для тестирования
int main() {
    char *infix = NULL;
    t_stack* postfix = NULL;
    int len = 0;
    int bufsize = 0;
    char c;
    printf("Введите строку: ");
    while ((c = getchar()) != '\n') {
            if (len >= bufsize - 1) {
                bufsize += 32;
                infix = realloc(infix, bufsize);
                if (!infix) {
                    printf("Ошибка: не удалось выделить память\n");
                    exit(1);
                }
            }
            infix[len++] = c;
        }

    infix[len] = '\0';


    infixToPostfix(infix, &postfix);
    t_stack* tmp = evaluatePostfix(&postfix);
    double val = atof(tmp->value);
    printf("%lf\n", val);
    free(tmp);
    // printf("Выражение в обратной польской нотации: \n");
    // while (!isEmpty(postfix)) {
    //     t_stack* tmp = pop(&postfix);
    //     printf("%s", tmp->value);
    //     free(tmp);
    // }
    // printf("\n");

    free(infix);
    free(postfix);

    return 0;
}














// void ikael(void) {
//     char *infix = NULL;
//     t_stack* postfix = NULL;
//     int len = 0;
//     int bufsize = 0;
//     char c;
//     printf("Введите строку: ");
//     while ((c = getchar()) != '\n') {
//             if (len >= bufsize - 1) {
//                 bufsize += 32;
//                 infix = realloc(infix, bufsize);
//                 if (!infix) {
//                     printf("Ошибка: не удалось выделить память\n");
//                     exit(1);
//                 }
//             }
//             infix[len++] = c;
//         }

//     infix[len] = '\0';


//     infixToPostfix(infix, &postfix);
//     printf("Выражение  = %с", evaluatePostfix(&postfix));    
//     printf("Выражение в обратной польской нотации: ");
//     while (!isEmpty(postfix)) {
//         t_stack* tmp = pop(&postfix);
//         printf("%c", tmp->value);
//         free(tmp);
//     }
//     printf("\n");

//     free(infix);


// }