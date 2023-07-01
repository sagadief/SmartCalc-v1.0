#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// Проверка, является ли стек пустым
int isEmpty(Stack* stack) {
    return stack->top == -1;
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
void push(Stack* stack, char symbol) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = symbol;
    } else {
        printf("Ошибка: стек переполнен\n");
        exit(1);
    }
}

// Удаление элемента из стека и возврат его значения
char pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    } else {
        printf("Ошибка: попытка извлечения из пустого стека\n");
        exit(1);
    }
}

// Структура стека


// Инициализация стека
void init(Stack* stack) {
    stack->top = -1;
}





//============================================================================

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
    Stack stack;
    init(&stack);

    int i = 0, j = 0;
    char symbol, topSymbol;


    for (i; infix[i] != '\0'; i++) {
        symbol = infix[i];

        if (symbol == ' ' || symbol == '\t') {
            continue;
        }
        if (isOperator(&symbol, infix, &i)) {
            while (!isEmpty(&stack)) {
                topSymbol = stack.data[stack.top];
                if (getPriority(topSymbol) >= getPriority(symbol)) {
                    postfix[j++] = pop(&stack);
                    // delete_elem_from_stack(&stack);
                } else {
                    break;
                }
            }
            push(&stack, symbol);
        } else if (symbol == '(') {
            push(&stack, symbol);
        } else if (symbol == ')') {
            while (!isEmpty(&stack)) {
                topSymbol = pop(&stack);
                if (topSymbol == '(') {
                    break;
                }
                postfix[j++] = topSymbol;
            }
        } else {
            postfix[j++] = symbol;
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j++] = '\0';
}

// Функция для тестирования
int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Введите выражение в инфиксной нотации: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0';

    infixToPostfix(infix, postfix);

    printf("Выражение в обратной польской нотации: %s\n", postfix);

    return 0;
}





























