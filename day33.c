#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char x){
    stack[++top] = x;
}

char pop(){
    return stack[top--];
}

int precedence(char x){
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    if(x == '^')
        return 3;
    return 0;
}

int main(){
    char infix[MAX], postfix[MAX];
    int i = 0, j = 0;

    scanf("%s", infix);

    while(infix[i] != '\0'){
        
        // Operand
        if(isalnum(infix[i])){
            postfix[j++] = infix[i];
        }

        // Opening bracket
        else if(infix[i] == '('){
            push(infix[i]);
        }

        // Closing bracket
        else if(infix[i] == ')'){
            while(stack[top] != '('){
                postfix[j++] = pop();
            }
            pop();
        }

        // Operator
        else{
            while(top != -1 && precedence(stack[top]) >= precedence(infix[i])){
                postfix[j++] = pop();
            }
            push(infix[i]);
        }

        i++;
    }

    while(top != -1){
        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("%s", postfix);

    return 0;
}