#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Ahmed Hussein 2025
//this struct represents a stack that can grow as needed
struct stack {
    char *items;  
    int top;      
    int capacity;   
};

//this creates a new empty stack
struct stack* create_stack() {
    struct stack *s = malloc(sizeof(struct stack));
    s->capacity = 64;  // start with capacity for 64 elements
    s->top = -1;       
    s->items = malloc(s->capacity * sizeof(char));
    return s;
}

//this frees memory used by the stack
void free_stack(struct stack *s) {
    free(s->items);
    free(s);
}

//this adds an element to the top of the stack
void push(struct stack *s, char c) {
    if (s->top == s->capacity - 1) {
        s->capacity *= 2;
        s->items = realloc(s->items, s->capacity * sizeof(char));
    }
    s->items[++(s->top)] = c;
}

//this removes and returns the top element from the stack
char pop(struct stack *s) {
    if (s->top < 0) {
        printf("error: stack is empty\n");
        exit(1);
    }
    return s->items[(s->top)--];
}


bool is_empty(struct stack *s) {
    return s->top == -1;
}


bool is_opening(char c) {
    return c == '(' || c == '[' || c == '{';
}


bool is_closing(char c) {
    return c == ')' || c == ']' || c == '}';
}

//this checks if two brackets form a valid pair with nesting rules
bool is_valid_pair(char open, char close) {  // Fixed
    if (open == '(' && close == ')') return true;
    if (open == '[' && close == ']') return true;
    if (open == '{' && close == '}') return true;
    if (open == '(' && close != ')') return false;
    if (open == '[' && (close == '{' || close == '}')) return false;
    return false;
}

//this checks if an expression has balanced parentheses
bool is_balanced(const char *expr) {
    struct stack *s = create_stack();
    
    for (int i = 0; expr[i] != '\0'; i++) {
        if (is_opening(expr[i])) {
            push(s, expr[i]);
        }
        else if (is_closing(expr[i])) {
            if (is_empty(s)) {
                free_stack(s);
                return false;
            }
            
            char popped = pop(s);
            if (!is_valid_pair(popped, expr[i])) {
                free_stack(s);
                return false;
            }
        }
    }
    
    bool balanced = is_empty(s);
    free_stack(s);
    return balanced;
}

int main() {
    char expr[1000];
    
    printf("enter an expression to check: ");
    fgets(expr, sizeof(expr), stdin);
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '\n') {
            expr[i] = '\0';
            break;
        }
    }
    if (is_balanced(expr)) {
        printf("valid expression\n");
    } else {
        printf("invalid expression\n");
    }
    return 0;
}