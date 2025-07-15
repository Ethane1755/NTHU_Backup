#include <stdlib.h>
#include <stdio.h>
typedef struct _Node {
    char val;
    struct _Node* next;
} Node;

//list[i]'s head node
Node *head[100005] = {};
//list[i]'s tail node
Node *tail[100005] = {};

void swap(int a, int b) {
    Node *tmp;
    tmp = head[a];
    head[a] = head[b];
    head[b] = tmp;
    tmp = tail[a];
    tail[a] = tail[b];
    tail[b] = tmp;
}

void append(int a, int b) {
    if (head[a] == NULL) return;
    if (head[b] == NULL) {
        swap(a, b);
        return;
    }
    tail[b]->next = head[a];
    tail[b] = tail[a];
    head[a] = NULL;
    tail[a] = NULL;
}

void move_to_front(int a, int b) {
    if (head[a] == NULL) return;
    if (head[b] == NULL) {
        swap(a, b);
        return;
    }
    tail[a]->next = head[b];
    head[b] = head[a];
    tail[a] = NULL;
    head[a] = NULL;
}

int main () {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int sz;
        scanf("%d", &sz);
        if (sz == 0) {
            head[i] = NULL;
            tail[i] = NULL;
            continue;
        }
        char buf[1000005];
        scanf("%s", buf);
        Node *prev = NULL;
        for (int j = 0; j < sz; j++) {
            Node *node = (Node*)malloc(sizeof(Node));
            node->val = buf[j];
            node->next = NULL;
            if (prev == NULL) {
                head[i] = node;
            } else {
                prev->next = node;
            }
            prev = node;
        }
        tail[i] = prev;
    }

    int Q;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int type, a, b;
        scanf("%d %d %d", &type, &a, &b);
        if (type == 1) {
            move_to_front(a, b);
        } else if (type == 2) {
            append(a, b);
        } else if (type == 3) {
            swap(a, b);
        }
    }

    for (int i = 1; i <= n; i++) {
        Node *cur = head[i];
        while (cur) {
            putchar(cur->val);
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        putchar('\n');
    }
    return 0;
}