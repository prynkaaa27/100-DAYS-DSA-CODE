#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

int main() {
    int n, i, value;
    struct node *head = NULL, *temp = NULL, *newnode = NULL;

    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        scanf("%d", &value);

        newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = value;
        newnode->next = NULL;
        newnode->prev = NULL;

        if(head == NULL) {
            head = newnode;
            temp = newnode;
        } else {
            temp->next = newnode;     // forward link
            newnode->prev = temp;     // backward link
            temp = newnode;           // move temp
        }
    }

    // Forward Traversal
    temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return 0;
}