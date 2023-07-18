#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "head.h"
// typedef struct t_stack {
//     char* value;
//     struct t_stack* next;
// } t_stack;


bool is_empty(t_stack *head) {
    return head == NULL;
}




void print_all_stack(t_stack* head) {
    printf("Stack: ");
    // Проход по всем элементам стека
    t_stack* current = head;
    while (current != NULL) {
        // Вывод значения текущего элемента стека
        printf("%s | ", current->value);
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










bool is_operator(char *symbol, char *str, int *i) {
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
    if (!is_empty(*head)) {
        temp = *head;
        *head = (*head)->next;
    }
    return temp; 
}


bool is_unary_operator(const char* operator) {
    return strcmp(operator, "-") == 0 || strcmp(operator, "+") == 0;
}


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
        }
        free(number);
    }
    return pos;
}




void double_to_str(double x, t_stack **head) {
    int length = snprintf(NULL, 0, "%0.15f", x);
    char* result = malloc((length + 1) * sizeof(char)); // Выделение памяти для строки результатов
    snprintf(result, length + 1, "%0.15f", x);
    // push_front(head, create_stack_elem(result));
    push_back(head, create_stack_elem(result));
    free(result);
}

void double_to_str_trig(double x, t_stack **head) {
    int length = snprintf(NULL, 0, "%0.15f", x);
    char* result = malloc((length + 1) * sizeof(char)); // Выделение памяти для строки результатов
    snprintf(result, length + 1, "%0.15f", x);
    // push_front(head, create_stack_elem(result));
    push_front(head, create_stack_elem(result));
    free(result);
}





// void check_bracket();


// Преобразование инфиксной нотации в обратную польскую нотацию
void infixToPostfix(char* infix, t_stack** numbers) {
    t_stack* operators = NULL;
    printf("**********************\n");
    char* symbol = malloc(2 * sizeof(char));
    char* top_symbol = malloc(2 * sizeof(char));
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    int i = 0;


    if (infix[i] == '-') {
        symbol[0] = '-';
        symbol[1] = '\0';

        t_stack* tmp = create_stack_elem(symbol);
        if (tmp != NULL) {
            push_back(&operators, tmp);
            // print_all_stack(operators);
            i++;
        } else {
            printf("BAD\n");
        }
    }

    for (i; infix[i]; i++) {

        symbol[0] = infix[i];
        symbol[1] = '\0';
        bool should_continue = true;
        if (symbol[0] == ' ' || symbol[0] == '\t')
            should_continue = false;
        
        if (should_continue) {
            if (is_operator(symbol, infix, &i)) {
                bool should_stop = true;
                while (!is_empty(operators) && should_stop) {
                    top_symbol = operators->value;
                    // print_all_stack(operators);
                    // printf("===%s\n", top_symbol);
                    // printf("===%s\n", symbol);
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
                int j = i + 1 ;
                int count = -1;
                int flag = 1;
                while (flag) {
                    if (infix[j] == '(')
                        flag++;
                    if (infix[j] == ')')
                        flag--;
                    count++;
                    j++;
                }
                char* sub_str = malloc(count * sizeof(char));
                sub_str[count] = '\0';
                strncpy(sub_str, infix + i + 1, count);
                t_stack* in_brackets = NULL;
                infixToPostfix(sub_str, &in_brackets);
                double num = evaluatePostfix(&in_brackets);
//                printf("===========================%f\n", num);
                i = i + count;
                double_to_str(num, numbers);
                print_all_stack(*numbers);
                // printf("Выражение в обратной польской нотации: \n");
                // while (!is_empty(*numbers)) {
                //     t_stack* tmp = pop(numbers);
                //     printf("%s", tmp->value);
                //     free(tmp);
                // }
                // printf("\n");
                
            } else if (symbol[0] == ')') {
                bool should_stop = true;
                while (!is_empty(operators) && should_stop) {
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
    while (!is_empty(operators)) {
        t_stack* tmp = pop(&operators);
        push_back(numbers, create_stack_elem(tmp->value));
        free(tmp);
    }
    free(symbol);
    free(top_symbol);
}



double evaluatePostfix(t_stack** postfix) {
    t_stack* head = NULL;
    while (!is_empty(*postfix)) {
    //    printf("============\n");
    //    print_all_stack(head);
            char* str = get_top_elem(*postfix);  // Получаем строку из стека
            // double num = strtod(str, NULL);  // Преобразуем строку в число
            char* endPtr;
            strtod(str, &endPtr);
        if (!(endPtr == str)) {
            t_stack* tmp = pop(postfix);
            // push_front(&head, create_stack_elem(tmp->value)); //push_front(&head, tmp);
            push_back(&head, create_stack_elem(tmp->value));
            free(tmp);                                         //убираем
        } else if (check_trigon(str)) {
            t_stack* inter = pop_back(&head);
            t_stack* tmp = pop(postfix);
            char* d = tmp->value;
            free(tmp);
            double x = atof(inter->value);
            // printf("@@@@@@@@@@@@@@@@@@@@%f\n", x);
            switch (*d) {
                case 'c':
                    x = cos(x);
                    // printf("%f\n", x);
                    double_to_str(x, &head);
                    break;
                case 's':
                    x = sin(x);
                    double_to_str(x, &head);
                    // printf("==========%f\n", x);
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
            t_stack* inter2 = pop_back(&head);
            t_stack* inter1 = pop_back(&head);
            t_stack* tmp = pop(postfix);
            char* d = tmp->value;
            b = atof(inter2->value);
            if (inter1 == NULL) {
                if (tmp->value[0] == '-' ) {
                    a = -1;
                } else if (tmp->value[0] == '+') {
                    a = 1;
                }
                d[0] = '*';
            } else {
                a = atof(inter1->value);
            }

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
                case '%':
                    x = fmod(a, b);
                    double_to_str(x, &head);
                    break;
                case '^':
                    x = pow(a, b);
                    double_to_str(x, &head);
                    break;
                // default:
                //     printf("Error: Invalid operator\n");
                //     exit(1);
            }
        }
    }
        // return pop(&head);
    // t_stack* tmp = pop(&head);
    // double val = atof(tmp->value);
    // printf("%.10f\n", val);
    // free(tmp);
    t_stack* tmp = pop(&head);
    double val = atof(tmp->value);
    free(tmp);
    return val;
}











// 5 10 - -

// Функция для тестирования
int main() {
    // char *infix = {"5+)\0"};
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
    // print_all_stack(postfix);
    // printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("%0.10f\n", evaluatePostfix(&postfix));
    // printf("Выражение в обратной польской нотации: \n");
    // while (!is_empty(postfix)) {
    //     t_stack* tmp = pop(&postfix);
    //     printf("%s", tmp->value);
    //     free(tmp);
    // }
    // printf("\n");

    // free(infix);
    // free(postfix);

    return 0;
}
