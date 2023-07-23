#include "head.h"
#include <unistd.h>

bool is_empty(t_stack *head) {
    return head == NULL;
}




void print_all_stack(t_stack* head) {
    printf("Stack: ");
    t_stack* current = head;
    while (current != NULL) {
        printf("%s | ", current->value);
        current = current->next;
    }
    printf("\n");
}



t_stack* create_stack_elem(char* value) {
    t_stack* new_elem = ( t_stack*)malloc(sizeof(t_stack));
    if (new_elem) {
        new_elem->value = (char*)malloc((strlen(value) + 1) * sizeof(char));
        if (new_elem->value) {
            strcpy(new_elem->value, value);
            new_elem->next = NULL;
        } else {
            free(new_elem);
            new_elem = NULL;
        }
    } else {
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
  } else if (strncmp(str + *i, "mod", 3) == 0) {
    *symbol = 'm';
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
        case 'm':
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
    char *result = (char*)strstr(str, substr);
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



bool is_unary_operator(const char* op) {
    return strcmp(op, "-") == 0 || strcmp(op, "+") == 0;
}


char* get_last_elem(t_stack* head) {
    t_stack* tmp = head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    return tmp->value;
}


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


int get_number(char * infix, int pos, t_stack **head) {
    size_t number_size = 0;
    bool flag = false;
    if (infix[pos] == 'x')
        flag = true;
    while (isdigit(infix[pos]) || infix[pos] == '.' || flag) {
        pos++;
        number_size++;
        flag = false;
    }
    pos--;
    char* number = (char*)malloc((number_size + 1) * sizeof(char));
    if (number == NULL)
        pos = -1;
    else {
        memcpy(number, &infix[pos - number_size + 1], number_size);
        number[number_size] = '\0';
        t_stack* tmp = create_stack_elem(number);
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
    char* result = (char*)malloc((length + 1) * sizeof(char));
    snprintf(result, length + 1, "%0.15f", x);
    push_back(head, create_stack_elem(result));
    free(result);
}


bool valide_str(char* infix) {
    bool flag = true, one_digit = false;
    int i = 0, brack = 0;
    if (infix[0] == '*' || infix[0] == '/' || infix[0] == '^')
        flag = false;
    while (infix[i] != '\0') {
        if (infix[i] == '(')
            brack++;
        else if (infix[i] == ')')
            brack--;
        if (isdigit(infix[i]) || infix[i] == 'x')
            one_digit = true;            
        i++;
        if (infix[i] == 'e') {
            flag = false;
        }
    }

    if (brack != 0)
        flag = false;
    if (!one_digit)
        flag = false;

    return flag;
}








// Преобразование инфиксной нотации в обратную польскую
void infixToPostfix(char* infix, double x, t_stack** numbers) {

    t_stack* operators = NULL;
    char* symbol = (char*)malloc(2 * sizeof(char));
    // char* top_symbol =(char*) malloc(2 * sizeof(char));
    char* top_symbol = NULL;
    int i = 0;

    if (infix[i] == '-') {
        symbol[0] = '-';
        symbol[1] = '\0';

        t_stack* tmp = create_stack_elem(symbol);
        push_back(&operators, tmp);
        i++;
    }

    for (; infix[i]; i++) {

        symbol[0] = infix[i]; 
        symbol[1] = '\0';
        bool should_continue = true;
        if (symbol[0] == ' ' || symbol[0] == '\t')
            should_continue = false;

        if (should_continue) {
            if (is_operator(symbol, infix, &i)) {  //good
                bool should_stop = true;
                while (!is_empty(operators) && should_stop) {
                    top_symbol = operators->value;
                    if (getPriority(top_symbol) >= getPriority(symbol)) {
                        t_stack* tmp = pop(&operators);
                        push_back(numbers, create_stack_elem(tmp->value));
                        free(tmp->value);
                        free(tmp);
                    } else {
                        should_stop = false;
                    }
                }
                push_front(&operators, create_stack_elem(symbol));
            } else if (symbol[0] == '(') {
                push_front(&operators, create_stack_elem(symbol));
                int j = i + 1;
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
                char* sub_str = (char*)malloc(count * sizeof(char));
                sub_str[count] = '\0';
                strncpy(sub_str, infix + i + 1, count);
                t_stack* in_brackets = NULL;
                infixToPostfix(sub_str, x, &in_brackets);
                free(sub_str);
                double num = evaluatePostfix(&in_brackets, x);
                i = i + count;
                double_to_str(num, numbers);

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
                        // free(tmp->value);
                    free(top_symbol);
                }
            } else {        
                i = get_number(infix, i, numbers);
            }
            // free(symbol);
            // free(top_symbol);
        }
    }
    while (!is_empty(operators)) {
        t_stack* tmp = pop(&operators);
        push_back(numbers, create_stack_elem(tmp->value));
        free(tmp->value);
        free(tmp);
    }
    free(symbol);
    free(top_symbol);
}



double evaluatePostfix(t_stack** postfix, double x) {
    t_stack* head = NULL;
    while (!is_empty(*postfix)) {
            char* str = get_top_elem(*postfix);  // Получаем строку из стека
            char* endPtr;
            double gg = 0;
            gg = strtod(str, &endPtr);
            if (!(gg == 0 && endPtr == str) || (strcmp(str, "x") == 0)) {            // проверка на число
            t_stack* tmp = pop(postfix);
            // printf("$$$$$$$$$$$$$$$$%s\n", tmp->value);
            push_back(&head, create_stack_elem(tmp->value));
            free(tmp);
        } else if (check_trigon(str)) {
            t_stack* inter = pop_back(&head);
            t_stack* tmp = pop(postfix);
            char* d = tmp->value;
            free(tmp);
            double dob = atof(inter->value);
            switch (*d) {
                case 'c':
                    dob = cos(dob);
                    double_to_str(dob, &head);
                    break;
                case 's':
                    dob = sin(dob);
                    double_to_str(dob, &head);
                    break;
                case 't':
                    dob = tan(dob);
                    double_to_str(dob, &head);
                    break;
                case 'a':
                    dob = acos(dob);
                    double_to_str(dob, &head);
                    break;
                case 'i':
                    dob = asin(dob);
                    double_to_str(dob, &head);
                    break;
                case 'n':
                    dob = atan(dob);
                    double_to_str(dob, &head);
                    break;
                case 'q':
                    dob = sqrt(dob);
                    double_to_str(dob, &head);
                    break;
                case 'l':
                    dob = log(dob);
                    double_to_str(dob, &head);
                    break;
                case 'g':
                    dob = log10(dob);
                    double_to_str(dob, &head);
                    break;
            }
        } else {
            double a = 0;
            double b = 0;
            double dob = 0;
            t_stack* inter2 = pop_back(&head);
            t_stack* inter1 = pop_back(&head);
            if (strcmp(inter2->value, "x") == 0)
                b = x;
            else
                b = atof(inter2->value);
            // printf("inter2 = %s\n", inter2->value);
            // printf("inter1 = %s\n", inter1->value);
            t_stack* tmp = pop(postfix);
            char* d = tmp->value;
            if (inter1 == NULL) {
                if (tmp->value[0] == '-' ) {
                    a = -1;
                } else if (tmp->value[0] == '+') {
                    a = 1;
                }
                d[0] = '*';
            } else {
                if (strcmp(inter1->value, "x") == 0)
                    a = x;
                else
                    a = atof(inter1->value);
            }

            switch (*d) {
                case '+':
                     dob = a + b;
                    double_to_str(dob, &head);
                    break;
                case '-':
                    dob = a - b;
                    double_to_str(dob, &head);
                    break;
                case '*':
                    dob = a * b;
                    double_to_str(dob, &head);
                    break;
                case '/':
                    dob = a / b;
                    double_to_str(dob, &head);
                    break;
                case 'm':
                    dob = fmod(a, b);
                    double_to_str(dob, &head);
                    break;
                case '^':
                    dob = pow(a, b);
                    double_to_str(dob, &head);
                    break;
            }
        }
    }
    t_stack* tmp = pop(&head);
    double val = atof(tmp->value);
    free(tmp);
    return val;
}











// 5 10 - -

// Функция для тестирования
int main() {
  // char *infix = {"5+)\0"};
  double y = 21.00;
  char *infix = NULL;
  t_stack* postfix = NULL;
  int len = 0;
  int bufsize = 0;
  char c;
  printf("Введите строку: ");
  while ((c = getchar()) != '\n') {
          if (len >= bufsize - 1) {
              bufsize += 32;
              infix = (char*)realloc(infix, bufsize);
              if (!infix) {
                  printf("Ошибка: не удалось выделить память\n");
                  exit(1);
              }
          }
          infix[len++] = c;
      }

  infix[len] = '\0';


    if (valide_str(infix)) {
    infixToPostfix(infix, y,&postfix);
    print_all_stack(postfix);
    printf("%0.10f\n", evaluatePostfix(&postfix, y));
//    printf("Выражение в обратной польской нотации: \n");
//    while (!is_empty(postfix)) {
//        t_stack* tmp = pop(&postfix);
//        printf("%s", tmp->value);
//        free(tmp);
//    }
//    printf("\n");

    free(infix);
    free(postfix);
    } else {
        printf("ERROR\n");
    }
  return 0;
}
