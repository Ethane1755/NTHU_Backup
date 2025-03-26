#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BTNode {
    char c;
    struct BTNode* left;
    struct BTNode* right;
} BTNode;

// 修正 createNode()，避免 switch 覆蓋
BTNode* createNode(char input) {
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    newNode->c = input;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 修正 parseExpression，避免無窮遞迴
BTNode* parseExpression(const char** expr) {
    if (**expr == '\0') return NULL;  // 避免超出字串範圍
    char c = **expr;
    (*expr)++;  // 推進指標，確保不會無窮迴圈

    BTNode* node = createNode(c);
    if (c == '|' || c == '&') {
        node->left = parseExpression(expr);
        node->right = parseExpression(expr);
    }
    return node;
}

// 修正 eval()，確保變數正確對應
int evaluate(BTNode* root, int A, int B, int C, int D) {
    if (!root) return 0;
    switch (root->c) {
        case 'A': return A;
        case 'B': return B;
        case 'C': return C;
        case 'D': return D;
        case '&': return evaluate(root->left, A, B, C, D) & evaluate(root->right, A, B, C, D);
        case '|': return evaluate(root->left, A, B, C, D) | evaluate(root->right, A, B, C, D);
        default: return 0;
    }
}

// 修正 freeTree()，避免對 NULL 記憶體釋放
void freeTree(BTNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char expr[30];

    // **使用 fgets() 確保輸入讀取正確**
    while (fgets(expr, sizeof(expr), stdin)) {
        expr[strcspn(expr, "\n")] = '\0';  // **去除換行符號**
        if (expr[0] == '\0') break;  // **避免空輸入**

        const char* p = expr;  // **用 `const char*` 確保 `parseExpression()` 正確解析**
        BTNode* root = parseExpression(&p);

        printf("A B C D output\n");
        for (int A = 0; A < 2; A++) {
            for (int B = 0; B < 2; B++) {
                for (int C = 0; C < 2; C++) {
                    for (int D = 0; D < 2; D++) {
                        int result = evaluate(root, A, B, C, D);
                        printf("%d %d %d %d %d\n", A, B, C, D, result);
                    }
                }
            }
        }

        freeTree(root);  // **釋放記憶體**
    }

    printf("Program finished.\n");  // **確認程式正常結束**
    return 0;
}