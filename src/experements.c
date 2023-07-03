#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct t_stack {
    char value;
    struct t_stack* next;
} t_stack;


bool isEmpty(t_stack *head) {
    return head == NULL;
}



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


void    push_back(t_stack **head, t_stack *elem)
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

t_stack* create_stack_elem(char value) {
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
    char symbol, topSymbol;

    for (int i = 0; infix[i]; i++) {
        symbol = infix[i];
        
        bool should_continue = true;
        if (symbol == ' ' || symbol == '\t')
            should_continue = false;
        
        if (should_continue) {
            if (isOperator(&symbol, infix, &i)) {
                bool should_stop = true;
                while (!isEmpty(head) && should_stop) {
                    topSymbol = head->value;
                    if (getPriority(topSymbol) >= getPriority(symbol)) {
                        t_stack* tmp = pop(&head);
                        // postfix[j++] = tmp->value;
                        push_back(str, create_stack_elem(tmp->value));
                        free(tmp);
                    } else {
                        should_stop = false;          //break
                    }
                }
                push(&head, create_stack_elem(symbol));
            } else if (symbol == '(') {
                push(&head, create_stack_elem(symbol));
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
                push_back(str, create_stack_elem(symbol));
            }
        }
    }
    while (!isEmpty(head)) {
        t_stack* tmp = pop(&head);
        // postfix[j++] = tmp->value;
        push_back(str, create_stack_elem(tmp->value));
        free(tmp);
    }

    // postfix[j++] = '\0';
}

void ikael(void) {
    //////////
    char *infix = NULL;
    t_stack* postfix = NULL;
    // char *postfix = NULL; 
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

    printf("Выражение в обратной польской нотации: ");
    while (!isEmpty(postfix)) {
        t_stack* tmp = pop(&postfix);
        printf("%c", tmp->value);
        free(tmp);
    }
    printf("\n");

    free(infix);

}

// Функция для тестирования
int main() {

ikael();



}