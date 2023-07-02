#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//old
#define MAX_SIZE 100

// typedef struct {
//     char data[MAX_SIZE];
//     int top;
// } Stack;


///////////////
typedef struct t_stack {
    char value;
    struct t_stack* next;
} t_stack;
///////////////






// Проверка, является ли стек пустым
bool isEmpty(t_stack *head) {
    return head == NULL;
}



// Проверка, является ли символ оператором
int isOperator(char *symbol, char *str, int *i) {
    int result = 0;

    if (strncmp(str + *i, "cos", 3) == 0) {
    *symbol = 'c';
    result = 1;
    (*i) += 2;
  } else if (strncmp(str + *i, "sin", 3) == 0) {
    *symbol = 's';
    result = 1;
    (*i) += 2;
  } else if (strncmp(str + *i, "tan", 3) == 0) {
    *symbol = 't';
    result = 1;
    (*i) += 2;
  } else if (strncmp(str + *i, "acos", 4) == 0) {
    *symbol = 'a';
    result = 1;
    (*i) += 3;
  } else if (strncmp(str + *i, "asin", 4) == 0) {
    *symbol = 'i';
    result = 1;
    (*i) += 3;
  } else if (strncmp(str + *i, "atan", 4) == 0) {
    *symbol = 't';
    result = 1;
    (*i) += 3;
  } else if (strncmp(str + *i, "sqrt", 4) == 0) {
    *symbol = 'q';
    result = 1;
    (*i) += 3;
  } else if (strncmp(str + *i, "ln", 2) == 0) {
    *symbol = 'l';
    result = 1;
    (*i) += 1;
  } else if (strncmp(str + *i, "log", 3) == 0) {
    *symbol = 'g';
    result = 1;
    (*i) += 2;
    } else if (*symbol == '+' || *symbol == '-' || *symbol == '*' || 
    *symbol == '/' || *symbol == '^' || *symbol == '%') {
        result = 1;
    };
    return result;
}

// Получение приоритета оператора
int getPriority(char symbol) {
    int res = -1;
    switch (symbol) {
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
        case 'q':
        case 'l':
        case 'g':
            res = 4;
            break;
    }
    return res;
}
// Размещение элемента в стеке

// void push(t_stack** head, t_stack* elem) {
void push(t_stack** head, t_stack* elem) {
    if (head && elem) {
        elem->next = *head;
        *head = elem;
    }
}

// Удаление элемента из стека и возврат его значения
// char pop(Stack* stack) {
//     if (!isEmpty(stack)) {
//         return stack->data[stack->top--];
//     } else {
//         printf("Ошибка: попытка извлечения из пустого стека\n");
//         exit(1);
//     }
// }

t_stack* pop(t_stack** head) {
    t_stack* temp = NULL;
    if (!isEmpty(*head)) {
        temp = *head;
        *head = (*head)->next;   
    }
    return temp; 
}

t_stack* create_stack_elem(char value) {
    t_stack* new_elem = malloc(sizeof(t_stack));
    if (new_elem) {
        new_elem->value = value;
        new_elem->next = NULL;
    }

    return new_elem;
    // возвращает NULL если память не выделилась
}




// Структура стека


// Инициализация стека
// void init(t_stack** head) {
//     stack->top = -1;
// }





//============================================================================

// t_stack* create_stack_elem(char value) {
//     t_stack* new_elem;
//     new_elem  = malloc(sizeof(t_stack));
//     if (new_elem) {
//         new_elem->value = value;
//         new_elem->next = NULL;
//     }

//     return new_elem;
//     // возвращает NULL если память не выделилась
// }



// char print_one_elem_from_stack(t_stack** head) {
//     t_stack* current = *head;
//     return current->value;
// }

// поменять Stack на t_stack
// typedef struct t_stack {
//     char value;
//     struct t_stack* next;
// } t_stack;


// void delete_elem_from_stack(Stack* stack) {
//     if (*head != NULL) {
//         t_stack* temp = *head;
//         *head = (*head)->next;
// //        free(temp->value); //не нужно потому что память статическая
//         free(temp);
//     }
// }

// void add_elem_to_stack(Stack* stack, Stack* elem) {
//     if (stack && elem) {
//         elem->next = stack;
//         stack = elem;
//     }
// }


//================================================================================

// Преобразование инфиксной нотации в обратную польскую нотацию
void infixToPostfix(char* infix, char* postfix) {
    t_stack* head = NULL;

    int i = 0, j = 0;
    char symbol, topSymbol;

    for (i; infix[i] != '\0'; i++) {
        symbol = infix[i];
        int cont = 1;
        if (symbol == ' ' || symbol == '\t') {
            cont = 0;                                        //continue;
        }
        if (cont) {
            if (isOperator(&symbol, infix, &i)) {
                int stop = 1;
                while (!isEmpty(head) && stop) {
                    topSymbol = head->value;
                    if (getPriority(topSymbol) >= getPriority(symbol)) {
                        t_stack* tmp = pop(&head);
                        postfix[j++] = tmp->value;
                        free(tmp);
                    } else {
                        stop = 0;          //break
                    }
                }
                push(&head, create_stack_elem(symbol));
            } else if (symbol == '(') {
                push(&head, create_stack_elem(symbol));
            } else if (symbol == ')') {
                int stop = 1;
                while (!isEmpty(head) && stop) {
                    t_stack* tmp = pop(&head);
                    topSymbol = tmp->value;
                    free(tmp);
                    if (topSymbol == '(') {
                        stop = 0;
                    }
                    if (stop) {postfix[j++] = topSymbol;}
                }
            } else {
                postfix[j++] = symbol;
            }
        }
    }
    while (!isEmpty(head)) {
        t_stack* tmp = pop(&head);
        postfix[j++] = tmp->value;
        free(tmp);
    }

    postfix[j++] = '\0';
}

// Функция для тестирования
int main() {


//////////
    char *infix = NULL; 
    char *postfix = NULL; 
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
//////////

    char postfix[MAX_SIZE];
    // char *postfix = NULL;



    infixToPostfix(infix, postfix);

    printf("Выражение в обратной польской нотации: %s\n", postfix);

    return 0;
}





























