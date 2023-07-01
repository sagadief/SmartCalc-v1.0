//
// Created by Thrace Bebe on 4/18/23.
//

#include "header.h"
// int main () {
//     trigon_n trig;
//     int a = check_trigon("sin(30)", 0, &trig);
//     printf("%d\n", a);
// }
int main() {
    char *line = NULL;
    char c;
    int len = 0;
    int bufsize = 0;

    printf("Введите строку: ");

//  поставить вместо реалока каллок --------------
    while ((c = getchar()) != '\n') {
        if (len >= bufsize - 1) {
            bufsize += 32;
            line = realloc(line, bufsize);
            if (!line) {
                printf("Ошибка: не удалось выделить память\n");
                exit(1);
            }
        }
        line[len++] = c;
    }

    line[len] = '\0';

    printf("Вы ввели первый раз %s\n", line);

    t_stack* head = NULL;
    trigon_n tr = {0};
    symbol_n sy = {0};
    // char specialChars[] = { '+', '-', '*', '/', '%' };
    // int numSpecialChars = sizeof(specialChars) / sizeof(char);
    // check_trigon(line, 0, &tr);
    for (int i; i< len; i++) {
        // int b = check_trigon(line, i, &tr);
        if (isdigit(line[i])) {
            printf("Цифра найдена! = :%c\n", line[i]);
            add_elem_to_stack(&head, create_stack_elem(line[i]));
        }
        else if (isspace(line[i])) {
            // i = i + 1;
            printf("PROBEL!");
         }else if (check_trigon(line, &i, &tr)) {
            // printf("Вывод тригонометрии = %d\n", check_trigon(line, i));
            if (tr.cos == 1) {
            printf("Найдена функция cos\n");
            add_elem_to_stack(&head, create_stack_elem('c'));
            } 
            if (tr.sin == 1) {
            printf("Найдена функция sin\n");
            add_elem_to_stack(&head, create_stack_elem('s'));
            }
            if (tr.tan == 1) {
            printf("Найдена функция tan\n");
            add_elem_to_stack(&head, create_stack_elem('t'));
            }
            if (tr.acos == 1) {
            printf("Найдена функция acos\n");
            add_elem_to_stack(&head, create_stack_elem('o'));
            }
            if (tr.asin == 1) {
            printf("Найдена функция asin\n");
            add_elem_to_stack(&head, create_stack_elem('i'));
            }
            if (tr.atan == 1) {
            printf("Найдена функция atan\n");
            add_elem_to_stack(&head, create_stack_elem('n'));
            }
            if (tr.sqrt == 1) {
            printf("Найдена функция sqrt\n");
            add_elem_to_stack(&head, create_stack_elem('q'));
            }
            if (tr.ln == 1) {
            printf("Найдена функция sin\n");
            add_elem_to_stack(&head, create_stack_elem('l'));
            }
            if (tr.log == 1) {
            printf("Найдена функция log\n");
            add_elem_to_stack(&head, create_stack_elem('g'));
            }
        } else if (check_symbol(line, i, &sy)) {
            // printf("Вывод тригонометрии = %d\n", check_trigon(line, i));
            if (sy.plus == 1) {
            printf("символ найден! = : + \n");
            add_elem_to_stack(&head, create_stack_elem('+'));
            } 
            if (sy.minus == 1) {
            printf("символ найден! = : - \n");
            add_elem_to_stack(&head, create_stack_elem('-'));
            }
            if (sy.multiply == 1) {
            printf("символ найден! = : * \n");
            add_elem_to_stack(&head, create_stack_elem('*'));
            }
            if (sy.division == 1) {
            printf("символ найден! = : / \n");
            add_elem_to_stack(&head, create_stack_elem('/'));
            }
            if (sy.interest == 1) {
            printf("символ найден! = : % \n");
            add_elem_to_stack(&head, create_stack_elem('%'));
            }
            if (sy.bracket == 1) {
            printf("символ найден! = : ( \n");
            add_elem_to_stack(&head, create_stack_elem('('));
            }
            if (sy.unbracket == 1) {
            printf("символ найден! = : ) \n");
            add_elem_to_stack(&head, create_stack_elem(')'));
            }
            if (sy.degree == 1) {
            printf("символ найден! = : ^ \n");
            add_elem_to_stack(&head, create_stack_elem('^'));
            }
            if (sy.dot == 1) {
            printf("символ найден! = : . \n");
            add_elem_to_stack(&head, create_stack_elem('.'));
            }
        }
    }

    // add_elem_to_stack(&head, create_stack_elem(line)); // 1 аргумент - куда заносим, 2 аргумент - что заносим
    print_all_stack(&head);              //      Stack: 
    delete_elem_from_stack(&head);       //      delete
    print_all_stack(&head);              //      Stack: 


    free(line);
    return 0;
}

int check_trigon(char *bukva, int *dot, trigon_n *tr) {
        int status = 0;
        char trigon_chars[] = {'c', 's', 't', 'a', 'l'};
        int num_trigon_chars = sizeof(trigon_chars) / sizeof(char);
        for (int i = 0; i < num_trigon_chars; i++) {
            // printf("%c\n", trigon_chars[i]);
            if (bukva[*dot] == trigon_chars[i]) {
                // printf("Тригонометрический символ найден! = :%c\n", trigon_chars[i]);
                if (bukva[*dot] == 'c' && bukva[*dot+1] == 'o' && bukva[*dot+2] == 's') {
                    tr->cos = 1;
                    *dot = *dot + 2;
                    status = 1;
                } else if (bukva[*dot] == 's') {
                    if (bukva[*dot + 1] == 'i' && bukva[*dot + 2] == 'n') {
                        tr->sin = 1;
                        *dot = *dot + 2;
                        status = 1;
                    } else if (bukva[*dot + 1] == 'q' && bukva[*dot + 2] == 'r' && bukva[*dot + 3] == 't') {
                        tr->sqrt = 1;
                        *dot = *dot + 3;
                        status = 1;
                    } else {
                        status = 0;
                    }
                } else if (bukva[*dot] == 't' && bukva[*dot + 1] == 'a' && bukva[*dot + 2] == 'n') {
                    tr->tan = 1;
                    *dot = *dot + 2;
                    status = 1;
                } else if (bukva[*dot] == 'a') {
                    if (bukva[*dot + 1] == 'c' && bukva[*dot + 2] == 'o' && bukva[*dot + 3] == 's') {
                        tr->acos = 1;
                        *dot = *dot + 3;
                        status = 1;
                    } else if (bukva[*dot + 1] == 's' && bukva[*dot + 2] == 'i' && bukva[*dot + 3] == 'n') {
                        tr->asin = 1;
                        *dot = *dot + 3;
                        status = 1;
                    } else if (bukva[*dot + 1] == 't' && bukva[*dot + 2] == 'a' && bukva[*dot + 3] == 'n') {
                        tr->atan = 1;
                        *dot = *dot + 3;
                        status = 1;
                    } else {
                        status = 0;
                    }
                } else if (bukva[*dot] == 'l') {
                    if (bukva[*dot + 1] == 'n') {
                        tr->ln = 1;
                        *dot = *dot + 1;
                        status = 1;
                    } else if (bukva[*dot + 1] == 'o' && bukva[*dot + 2] == 'g') {
                        tr->log = 1;
                        *dot = *dot + 2;
                        status = 1;
                    } else {
                        status = 0;
                    }
                } else {
                    status = 0;
                }
            } 
        }
        return status;
    }


int check_symbol(char *bukva, int dot, symbol_n *sy) {
    int status = 0;
    char specialChars[] = { '+', '-', '*', '/', '%', '(', ')', '^', '.' };
        // char trigon_chars[] = {'c', 's', 't', 'a', 'l'};
    int len = sizeof(specialChars) / sizeof(specialChars[0]);
    for (int i = 0; i < len; i++) {
        // printf("%c\n", trigon_chars[i]);
        if (bukva[dot] == '+') {
                sy->plus = 1;
                status = 1;
        }
        if (bukva[dot] == '-') {
                sy->minus = 1;
                status = 1;
        }
        if (bukva[dot] == '*') {
                sy->multiply = 1;
                status = 1;
        }
        if (bukva[dot] == '/') {
                sy->division = 1;
                status = 1;
        }        
        if (bukva[dot] == '%') {
                sy->interest = 1;
                status = 1;
        }
        if (bukva[dot] == '(') {
                sy->bracket = 1;
                status = 1;
        }
        if (bukva[dot] == ')') {
                sy->unbracket = 1;
                status = 1;
        }
        if (bukva[dot] == '^') {
                sy->degree = 1;
                status = 1;
        }
        if (bukva[dot] == '.') {
                sy->dot = 1;
                status = 1;
        }
    }
    return 1;
}



int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}



int getPriority(char symbol, trigon_n *tr) {
    int priory = -1;
    switch (symbol) {
        case '+':
            priory = 1;
        case '-':
            priory = 1;
        case '*':
            priory = 2;
        case '/':
            priory = 2;
        case '^':
            priory = 3;
        case '^':
            priory = 3;
        case '^':
            priory = 3;
        default:
            return 0;
    }
}

if (c == '+' || c == '-' || c == 'm')
    pr = 1;
  else if (c == '*' || c == '/')
    pr = 2;
  else if (c == '^' || c == '|' || c == '~')
    pr = 3;
  else if (c == 'c' || c == 's' || c == 't' || c == 'a' || c == 'l' ||
           c == 'o' || c == 'i' || c == 'n' || c == 'q' || c == 'g')
    pr = 4;

  return pr;
}


//------------------------------------------------------------
t_stack* create_stack_elem(char value) {
    t_stack* new_elem;
    new_elem  = malloc(sizeof(t_stack));
    if (new_elem) {
        new_elem->value = value;
        new_elem->next = NULL;
    }

    return new_elem;
    // возвращает NULL если память не выделилась
}
//------------------------------------------------------------
void print_one_elem_from_stack(t_stack** head) {
    // printf("1_elem: ");
    t_stack* curent = *head;
    // printf("%с \n", curent->value);
}
// вывод всех элементов стека---------------------------------
void print_all_stack(t_stack** head) {
    printf("Stack: ");
    // Проход по всем элементам стека
    t_stack* current = *head;
    while (current != NULL) {
        // Вывод значения текущего элемента стека
        printf("%c ", current->value);
        // Переход к следующему элементу стека
        current = current->next;
    }
    printf("\n");
}
//------------------------------------------------------------
void add_elem_to_stack(t_stack** head, t_stack* elem) {
    if (head && elem) {
        elem->next = *head;
        *head = elem;
    }
}
//------------------------------------------------------------
void delete_elem_from_stack(t_stack** head) {
    if (*head != NULL) {
        t_stack* temp = *head;
        *head = (*head)->next;
//        free(temp->value); //не нужно потому что память статическая
        free(temp);
    }
}


//добавление и проверка триг. на коррекцию
int validateFunc(const char *str, int *i, char *res) {
  int result = SUCCSESS;

  if (strncmp(str + *i, "cos", 3) == 0) {
    *res = 'c';
    (*i) += 2;
  } else if (!strncmp(str + *i, "sin", 3) == 0) {
    *res = 's';
    (*i) += 2;
  } else if (!strncmp(str + *i, "tan", 3) == 0) {
    *res = 't';
    (*i) += 2;
  } else if (!strncmp(str + *i, "acos", 4) == 0) {
    *res = 'a';
    (*i) += 3;
  } else if (!strncmp(str + *i, "asin", 4) == 0) {
    *res = 'i';
    (*i) += 3;
  } else if (!strncmp(str + *i, "atan", 4) == 0) {
    *res = 't';
    (*i) += 3;
  } else if (!strncmp(str + *i, "sqrt", 4) == 0) {
    *res = 'q';
    (*i) += 3;
  } else if (!strncmp(str + *i, "ln", 2) == 0) {
    *res = 'l';
    (*i) += 1;
  } else if (!strncmp(str + *i, "log", 3) == 0) {
    *res = 'g';
    (*i) += 2;
  } else {
    result = FAILTURE;
  }

  return result;
}






//strcmp - функция для проверки строки на cos, sin, mod и тд
// сначала проверяем сроку на тригонометрию - если есть, меняем на 1 чаровский символ
// после изменений заносим в стек
// после стека работаем по алгоритму дейкстры


