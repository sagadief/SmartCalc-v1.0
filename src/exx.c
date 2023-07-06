#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct t_stack {
    char value;
    char* number;
    int flag;
    struct t_stack* next;
} t_stack;


bool isEmpty(t_stack *head) {
    return head == NULL;
}

////////////////////





void print_all_stack(t_stack* head) {
    printf("Stack: ");
    // Проход по всем элементам стека
    t_stack* current = head;
    while (current != NULL) {
        // Вывод значения текущего элемента стека
        printf("%c ", current->value);
        // Переход к следующему элементу стека
        current = current->next;
    }
    printf("\n");
}





///////////////////





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
    *symbol = 't';
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
    } else if (*symbol == '+' || *symbol == '-' || *symbol == '*' || 
    *symbol == '/' || *symbol == '^' || *symbol == '%') {
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

// isdigit(infix[i]) {}
int get_number(char * infix, int pos, t_stack **str) {
    int number_size = 0;
    while (isdigit(infix[pos]) || infix[pos] == '.') {
        number_size++;
        pos++;
    }
    char* number = malloc(number_size * sizeof(char));
    if (number == NULL)
        pos = -1;
    else {
        strncpy(number, infix, number_size);
        t_stack* tmp = create_stack_elem(number);
        if (tmp != NULL)
            push_front(&str, create_stack_elem(number));
        else pos = -1;
    }
    return pos;
}







t_stack* create_stack_elem(char* value) {
    t_stack* new_elem = malloc(sizeof(t_stack));
    if (new_elem) {
        new_elem->value = value;
        new_elem->next = NULL;
    }

    return new_elem;
    // возвращает NULL если память не выделилась
}


// Преобразование инфиксной нотации в обратную польскую нотацию
void infixToPostfix(char* infix, t_stack** str) {
    t_stack* head = NULL;
    char symbol;
    char* topSymbol;

    for (int i = 0; infix[i]; i++) {
        while(infix[i] == ' ' || infix[i] == '\t')
            i++;

        symbol = infix[i];

        if (isOperator(&symbol, infix, &i)) {
            bool should_stop = true;
            while (!isEmpty(head) && should_stop) {
                topSymbol = head->value;
                if (getPriority(topSymbol) >= getPriority(symbol)) {
                    t_stack* tmp = pop(&head);
                    push_back(str, create_stack_elem(tmp->value));
                    free(tmp);
                } else {
                    should_stop = false;          //break
                }
            }
            push_front(&head, create_stack_elem(symbol));
        } else if (symbol == '(') {
            push_front(&head, create_stack_elem(symbol));
        } else if (symbol == ')') {
            bool should_stop = true;
            while (!isEmpty(head) && should_stop) {
                t_stack* tmp = pop(&head);
                topSymbol = tmp->value;
                free(tmp);

                if (topSymbol == '(')
                    should_stop = false;
                if (should_stop)
                    push_back(str, create_stack_elem(topSymbol));
            }
        } else {
            printf("%s", infix + i);
            push_back(str, create_stack_elem(symbol));
        }
    }
    while (!isEmpty(head)) {
        t_stack* tmp = pop(&head);
        push_back(str, create_stack_elem(tmp->value));
        free(tmp);
    }
}



t_stack* evaluatePostfix(t_stack** postfix) {
// void evaluatePostfix(t_stack** postfix) {
    // str = postfix
    // head = stack
    t_stack* head = NULL;
    
    // int i = 0;
    // print_all_stack(*postfix);
    while (!isEmpty(*postfix)) {
        // if (isdigit(get_top_elem(*postfix))) {
        //     t_stack* tmp = pop(postfix);
        //     push_front(&head, create_stack_elem(tmp->value));  // - '0'
        //     free(tmp);
        // while (!isEmpty(*postfix)) {
        //     // printf("%d\n", get_top_elem(*postfix));
        //     if (get_top_elem(*postfix) >= '0' && get_top_elem(*postfix) <= '9') {
        //         // printf("%d\n", get_top_elem(*postfix));
        //         }
        //     t_stack* tmp = pop(postfix);
        //     int g = tmp->value - '0';
        //     printf("%d\n", g);
        //     push_front(&head, create_stack_elem(tmp->value));
        //     free(tmp);
        // }
        ////
        // if (get_top_elem(*postfix) >= '0' && get_top_elem(*postfix) <= '9') {
            // print_all_stack(*postfix);
            if (isdigit(get_top_elem(*postfix))) {
            // printf("========= %c", get_top_elem(*postfix));
            t_stack* tmp = pop(postfix);
            push_front(&head, create_stack_elem(tmp->value));
            // printf("===============\n");
            // print_all_stack(head);
            // printf("======%c\n", tmp->value);
            free(tmp);
        // }
        // printf("$$$$$$$$$$$$$$$");
        } else {
            double a = 0;
            double b = 0;
            double x = 0;
            char result;
            // char arr[255] = {};
            // head = pop(&head);
            print_all_stack(head);
            t_stack* inter2 = pop(&head);
            // b = inter2->value;
            print_all_stack(head);
            t_stack* inter1 = pop(&head);
            // a = inter1->value;
            print_all_stack(head);
            // head = pop(&head);
        //     // print_all_stack(&head);
        //     // for (int i = 0; !isEmpty(head); i++) {
        //     //     printf("Элемент номер %d = %c\n", head->value);
        //     //     head = pop(&head);
        //     // }
            // t_stack* operand2 = pop(&head);
            // t_stack* operand1 = pop(&head);
            // printf("===2==== %c\n", inter2->value);
            // printf("===1==== %c\n", inter1->value);
        //     // printf("\n");
        //     // printf("#########%c\n",get_top_elem(*postfix));
            t_stack* tmp = pop(postfix);
            char d = tmp->value;
            free(tmp);
            b = atof(inter2->value);
            a = atof(inter1->value);
            switch (d) {
                case '+':
                     x = a + b;
                    result = (char)x;
                    push_back(&head, create_stack_elem(result));
                    // printf("+\n");
                    // print_all_stack(&head);
                    break;
                case '-':
                    x = a - b;
                    result = (char)x;
                    push_back(&head, create_stack_elem(result));
                    // print_all_stack(&head);
                    break;
                case '*':
                    x = a * b;
                    result = (char)x;
                    push_back(&head, create_stack_elem(result));
                    // print_all_stack(&head);
                    break;
                case '/':
                    x = a / b;
                    result = (char)x;
                    push_back(&head, create_stack_elem(result));
                    break;
                default:
                    printf("Error: Invalid operator\n");
                    exit(1);
            }
        }
    }
    // printf("\n******************** %c\n", get_top_elem(head));
    // print_all_stack(head);
    return pop(&head);
}



int calculate_postfix(t_stack* postfix) {

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
    // evaluatePostfix(&postfix);
    // t_stack* tmp = evaluatePostfix(&postfix);
    // printf("%d\n", tmp->value);
    // free(tmp);
    // printf("Выражение  = %d\n", evaluatePostfix(&postfix));
    printf("Выражение в обратной польской нотации: ");
    while (!isEmpty(postfix)) {
        t_stack* tmp = pop(&postfix);
        printf("%c\n", tmp->value);
        free(tmp);
    }
    printf("\n");

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