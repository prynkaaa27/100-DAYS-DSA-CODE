#include <stdio.h>
#define MAX 100

struct Stack {
    int arr[MAX];
    int top;
};

void push(struct Stack *s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        s->top++;
        s->arr[s->top] = value;
    }
}

void pop(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
    } else {
        printf("%d\n", s->arr[s->top]);
        s->top--;
    }
}

void display(struct Stack s) {
    if (s.top == -1) {
        return;
    }
    for (int i = s.top; i >= 0; i--) {
        printf("%d ", s.arr[i]);
    }
    printf("\n");
}

int main() {
    int n, type, value;
    struct Stack s;
    s.top = -1;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &value);
            push(&s, value);
        } 
        else if (type == 2) {
            pop(&s);
        } 
        else if (type == 3) {
            display(s);
        }
    }

    return 0;
}