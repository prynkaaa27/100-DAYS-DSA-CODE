/*
 * ============================================================
 *  Deque (Double-Ended Queue) — Full Implementation in C
 * ============================================================
 *
 *  A Deque allows insertion and deletion at BOTH ends.
 *  Implemented using a doubly-linked list for O(1) operations
 *  on push/pop at front and back.
 *
 *  Time Complexity:
 *    push_front, push_back, pop_front, pop_back,
 *    front, back, empty, size              → O(1)
 *    clear, erase, resize, assign, reverse → O(n)
 *    sort                                  → O(n log n)
 * ============================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ──────────── Node & Deque Structures ──────────── */
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;
typedef struct Deque {
    Node *head;   // front of the deque
    Node *tail;   // rear  of the deque
    int   count;  // number of elements
} Deque;
/* ──────────── Helper: Create a new node ──────────── */
Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}
/* ──────────── Initialise an empty deque ──────────── */
void initDeque(Deque *dq) {
    dq->head  = NULL;
    dq->tail  = NULL;
    dq->count = 0;
}
/* ════════════════════════════════════════════════════
 *  CORE OPERATIONS
 * ════════════════════════════════════════════════════ */
/* 1. push_front — Insert at the front   O(1) */
void push_front(Deque *dq, int value) {
    Node *node = createNode(value);
    if (dq->head == NULL) {
        dq->head = dq->tail = node;
    } else {
        node->next     = dq->head;
        dq->head->prev = node;
        dq->head       = node;
    }
    dq->count++;
    printf("  push_front(%d)  →  size = %d\n", value, dq->count);
}
/* 2. push_back — Insert at the rear   O(1) */
void push_back(Deque *dq, int value) {
    Node *node = createNode(value);
    if (dq->tail == NULL) {
        dq->head = dq->tail = node;
    } else {
        node->prev     = dq->tail;
        dq->tail->next = node;
        dq->tail       = node;
    }
    dq->count++;
    printf("  push_back(%d)   →  size = %d\n", value, dq->count);
}
/* 3. pop_front — Remove from the front   O(1) */
int pop_front(Deque *dq) {
    if (dq->head == NULL) {
        printf("  pop_front()  →  Deque is EMPTY!\n");
        return -1;
    }
    Node *temp = dq->head;
    int   val  = temp->data;
    dq->head = dq->head->next;
    if (dq->head)
        dq->head->prev = NULL;
    else
        dq->tail = NULL;   // deque became empty
    free(temp);
    dq->count--;
    printf("  pop_front()  →  removed %d, size = %d\n", val, dq->count);
    return val;
}
/* 4. pop_back — Remove from the rear   O(1) */
int pop_back(Deque *dq) {
    if (dq->tail == NULL) {
        printf("  pop_back()   →  Deque is EMPTY!\n");
        return -1;
    }
    Node *temp = dq->tail;
    int   val  = temp->data;
    dq->tail = dq->tail->prev;
    if (dq->tail)
        dq->tail->next = NULL;
    else
        dq->head = NULL;   // deque became empty
    free(temp);
    dq->count--;
    printf("  pop_back()   →  removed %d, size = %d\n", val, dq->count);
    return val;
}
/* 5. front — Return the front element   O(1) */
int front(Deque *dq) {
    if (dq->head == NULL) {
        printf("  front()      →  Deque is EMPTY!\n");
        return -1;
    }
    printf("  front()      →  %d\n", dq->head->data);
    return dq->head->data;
}
/* 6. back — Return the rear element   O(1) */
int back(Deque *dq) {
    if (dq->tail == NULL) {
        printf("  back()       →  Deque is EMPTY!\n");
        return -1;
    }
    printf("  back()       →  %d\n", dq->tail->data);
    return dq->tail->data;
}
/* 7. empty — Check if the deque is empty   O(1) */
int empty(Deque *dq) {
    int e = (dq->count == 0);
    printf("  empty()      →  %s\n", e ? "true" : "false");
    return e;
}
/* 8. size — Return the number of elements   O(1) */
int size(Deque *dq) {
    printf("  size()       →  %d\n", dq->count);
    return dq->count;
}
/* ════════════════════════════════════════════════════
 *  ADDITIONAL OPERATIONS
 * ════════════════════════════════════════════════════ */
/* 9. clear — Remove all elements   O(n) */
void clear(Deque *dq) {
    Node *cur = dq->head;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    dq->head = dq->tail = NULL;
    dq->count = 0;
    printf("  clear()      →  deque cleared, size = 0\n");
}
/* 10. erase — Remove element at a given 0-based index   O(n) */
int erase(Deque *dq, int index) {
    if (index < 0 || index >= dq->count) {
        printf("  erase(%d)    →  Index out of bounds!\n", index);
        return -1;
    }
    Node *cur = dq->head;
    for (int i = 0; i < index; i++)
        cur = cur->next;
    int val = cur->data;
    if (cur->prev) cur->prev->next = cur->next;
    else           dq->head = cur->next;
    if (cur->next) cur->next->prev = cur->prev;
    else           dq->tail = cur->prev;
    free(cur);
    dq->count--;
    printf("  erase(%d)    →  removed %d, size = %d\n", index, val, dq->count);
    return val;
}
/* 11. swap — Swap contents of two deques   O(1) */
void swap(Deque *a, Deque *b) {
    Node *tmpH  = a->head;  a->head  = b->head;  b->head  = tmpH;
    Node *tmpT  = a->tail;  a->tail  = b->tail;  b->tail  = tmpT;
    int   tmpC  = a->count; a->count = b->count;  b->count = tmpC;
    printf("  swap()       →  deques swapped\n");
}
/* 12. emplace_front — Same as push_front (C has no move semantics) */
void emplace_front(Deque *dq, int value) {
    push_front(dq, value);
}
/* 13. emplace_back — Same as push_back (C has no move semantics) */
void emplace_back(Deque *dq, int value) {
    push_back(dq, value);
}
/* 14. resize — Change the size of the deque   O(n) */
void resize(Deque *dq, int newSize, int fillValue) {
    if (newSize < 0) {
        printf("  resize()     →  Invalid size!\n");
        return;
    }
    while (dq->count > newSize)
        pop_back(dq);
    while (dq->count < newSize)
        push_back(dq, fillValue);
    printf("  resize(%d)   →  size = %d\n", newSize, dq->count);
}
/* 15. assign — Replace all elements with n copies of a value   O(n) */
void assign(Deque *dq, int n, int value) {
    clear(dq);
    for (int i = 0; i < n; i++)
        push_back(dq, value);
    printf("  assign(%d, %d) →  size = %d\n", n, value, dq->count);
}
/* 16. reverse — Reverse the order of elements   O(n) */
void reverseDeque(Deque *dq) {
    Node *cur = dq->head;
    while (cur) {
        Node *tmp  = cur->prev;
        cur->prev  = cur->next;
        cur->next  = tmp;
        cur        = cur->prev;   // move forward (prev is now next)
    }
    // swap head and tail pointers
    Node *tmp = dq->head;
    dq->head  = dq->tail;
    dq->tail  = tmp;
    printf("  reverse()    →  deque reversed\n");
}
/* 17. sort — Merge-sort the deque   O(n log n) */
// Helper: split the list into two halves
static void splitList(Node *source, Node **front, Node **back) {
    Node *slow = source;
    Node *fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back  = slow->next;
    slow->next = NULL;
    if (*back) (*back)->prev = NULL;
}
// Helper: merge two sorted lists
static Node *merge(Node *a, Node *b) {
    if (!a) return b;
    if (!b) return a;
    Node *result;
    if (a->data <= b->data) {
        result = a;
        result->next = merge(a->next, b);
        if (result->next) result->next->prev = result;
        result->prev = NULL;
    } else {
        result = b;
        result->next = merge(a, b->next);
        if (result->next) result->next->prev = result;
        result->prev = NULL;
    }
    return result;
}
// Helper: merge sort on doubly-linked list
static void mergeSort(Node **headRef) {
    Node *head = *headRef;
    if (!head || !head->next) return;
    Node *a, *b;
    splitList(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headRef = merge(a, b);
}
void sortDeque(Deque *dq) {
    if (dq->count <= 1) return;
    mergeSort(&dq->head);
    // fix tail pointer
    Node *cur = dq->head;
    while (cur->next) cur = cur->next;
    dq->tail = cur;
    printf("  sort()       →  deque sorted in ascending order\n");
}
/* ════════════════════════════════════════════════════
 *  UTILITY: Print the deque
 * ════════════════════════════════════════════════════ */
void printDeque(Deque *dq) {
    printf("  Deque [%d]:   ", dq->count);
    if (dq->count == 0) {
        printf("(empty)\n");
        return;
    }
    Node *cur = dq->head;
    printf("FRONT ↔ ");
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) printf(" ↔ ");
        cur = cur->next;
    }
    printf(" ↔ REAR\n");
}
/* ════════════════════════════════════════════════════
 *  DEMO / MAIN
 * ════════════════════════════════════════════════════ */
int main() {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║   Deque (Double-Ended Queue) — C Demo    ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    Deque dq;
    initDeque(&dq);
    /* ── Core operations ── */
    printf("── Core Operations ─────────────────────────\n");
    push_back(&dq, 10);
    push_back(&dq, 20);
    push_back(&dq, 30);
    push_front(&dq, 5);
    push_front(&dq, 1);
    printDeque(&dq);            // 1 ↔ 5 ↔ 10 ↔ 20 ↔ 30
    printf("\n");
    front(&dq);                 // 1
    back(&dq);                  // 30
    size(&dq);                  // 5
    empty(&dq);                 // false
    printf("\n");
    pop_front(&dq);             // removes 1
    pop_back(&dq);              // removes 30
    printDeque(&dq);            // 5 ↔ 10 ↔ 20
    /* ── Additional operations ── */
    printf("\n── Additional Operations ───────────────────\n");
    // erase index 1
    erase(&dq, 1);
    printDeque(&dq);            // 5 ↔ 20
    // reverse
    push_back(&dq, 40);
    push_back(&dq, 50);
    printDeque(&dq);            // 5 ↔ 20 ↔ 40 ↔ 50
    reverseDeque(&dq);
    printDeque(&dq);            // 50 ↔ 40 ↔ 20 ↔ 5
    // sort
    printf("\n");
    sortDeque(&dq);
    printDeque(&dq);            // 5 ↔ 20 ↔ 40 ↔ 50
    // resize
    printf("\n");
    resize(&dq, 6, 0);
    printDeque(&dq);            // 5 ↔ 20 ↔ 40 ↔ 50 ↔ 0 ↔ 0
    // assign
    printf("\n");
    assign(&dq, 3, 7);
    printDeque(&dq);            // 7 ↔ 7 ↔ 7
    /* ── Swap demo ── */
    printf("\n── Swap Demo ───────────────────────────────\n");
    Deque dq2;
    initDeque(&dq2);
    push_back(&dq2, 100);
    push_back(&dq2, 200);
    printf("  Before swap:\n");
    printf("    dq1: "); printDeque(&dq);
    printf("    dq2: "); printDeque(&dq2);
    swap(&dq, &dq2);
    printf("  After  swap:\n");
    printf("    dq1: "); printDeque(&dq);
    printf("    dq2: "); printDeque(&dq2);
    /* ── Clean up ── */
    printf("\n── Cleanup ─────────────────────────────────\n");
    clear(&dq);
    clear(&dq2);
    printDeque(&dq);
    printf("\n✓ All operations executed successfully.\n");
    return 0;
}
