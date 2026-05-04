#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Linked list node for stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack using linked list
typedef struct Stack {
    Node* top;
} Stack;

// Initialize stack
Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

// Check if stack is empty
int isEmpty(Stack* s) {
    return s->top == NULL;
}

// Push onto stack (dynamic allocation)
void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// Pop from stack (free memory)
int pop(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    Node* temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);   // Dynamic memory freed
    return val;
}

// Free entire stack
void freeStack(Stack* s) {
    while (!isEmpty(s)) pop(s);
    free(s);
}

// Evaluate postfix expression
int evaluatePostfix(char* expr) {
    Stack* s = createStack();
    char* token = strtok(expr, " ");

    while (token != NULL) {
        // If token is a number, push it
        if (isdigit(token[0]) || (token[0] == '-' && strlen(token) > 1)) {
            push(s, atoi(token));
        } else {
            // It's an operator — pop two operands
            int b = pop(s);
            int a = pop(s);
            switch (token[0]) {
                case '+': push(s, a + b); break;
                case '-': push(s, a - b); break;
                case '*': push(s, a * b); break;
                case '/':
                    if (b == 0) { fprintf(stderr, "Division by zero\n"); exit(1); }
                    push(s, a / b);
                    break;
                default:
                    fprintf(stderr, "Unknown operator: %c\n", token[0]);
                    exit(1);
            }
        }
        token = strtok(NULL, " ");
    }

    int result = pop(s);
    freeStack(s);
    return result;
}

int main() {
    char expr[256];
    fgets(expr, sizeof(expr), stdin);
    // Remove trailing newline
    expr[strcspn(expr, "\n")] = '\0';

    printf("%d\n", evaluatePostfix(expr));
    return 0;
}