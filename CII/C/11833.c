#include <stdio.h>
#include <stdlib.h>

int N = 0;
int in_index[200001];
int pre_inx = 0;

typedef struct _node {
    int value;
    struct _node *left;
    struct _node *right;
} Node;

Node *create_node(int value) {
    Node *NewNode = (Node*)malloc(sizeof(Node));
    NewNode -> value = value;
    NewNode -> right = NewNode -> left = NULL;
    return NewNode;
}
void postorder(Node *root){
    if(!root) return;
    postorder(root -> left);
    postorder(root -> right);
    printf("%d ", root -> value);
}
void destroy(Node* root) {
    if(!root) return;
    destroy(root -> left);
    destroy(root -> right);
    free(root);
}

Node *build(int *inorder, int *preorder, int inorder_start, int inorder_end) {
    if (inorder_start > inorder_end) return NULL;

    int root_v = preorder[pre_inx++];
    Node *root = create_node(root_v);

    int root_pos = in_index[root_v];
    root -> left = build(inorder, preorder, inorder_start, root_pos - 1);
    root -> right = build(inorder, preorder, root_pos + 1, inorder_end);

    return root;
}

int main () {
    scanf("%d", &N);
    int *inorder = (int*)malloc(N * sizeof(int));
    int *preorder = (int*)malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &inorder[i]);
        in_index[inorder[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &preorder[i]);
    }
    Node *root = build(inorder, preorder, 0, N - 1);
    postorder(root);
    printf("\n");
    destroy(root);
    free(inorder);
    free(preorder);

    return 0;
}