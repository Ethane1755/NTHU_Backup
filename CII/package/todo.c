#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 最大字串長度
#define MAXLEN 256

// Token 類型定義
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN,
    LPAREN, RPAREN,
    INCDEC, 
    AND,
    OR,
    XOR,
    ADDSUB_ASSIGN
} TokenSet;

// 目前 Token 及字串
TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Token 判斷與取得
int match(TokenSet token);      // 判斷當前 token 是否為指定 token
void advance(void);            // 取得下一個 token
char *getLexeme(void);         // 取得當前 lexeme

// 符號表相關
#define TBLSIZE 64
#define PRINTERR 1

#define error(errorNum) { \
    if (PRINTERR) \
    err(errorNum); \
}

// 錯誤類型
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// 符號表結構
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// 語法樹節點
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

// 符號表及計數
int sbcount = 0;
Symbol table[TBLSIZE];

// 符號表初始化與操作
void initTable(void);          // 初始化符號表
int getval(char *str);         // 取得變數值
int setval(char *str, int val);// 設定變數值

// 語法樹操作
BTNode *makeNode(TokenSet tok, const char *lexe); // 建立新節點
void freeTree(BTNode *root);                      // 釋放語法樹

// 各層級語法分析函式
BTNode *factor(void);
BTNode *term(void);
BTNode *term_tail(BTNode *left);
BTNode *expr(void);
BTNode *expr_tail(BTNode *left);
BTNode *assign_expr(void);
BTNode *or_expr(BTNode *temp);
BTNode *or_expr_tail(BTNode *left);
BTNode *and_expr(BTNode *temp);
BTNode *and_expr_tail(BTNode *left);
BTNode *xor_expr(BTNode *temp);
BTNode *xor_expr_tail(BTNode *left);
BTNode *addsub_expr(BTNode *temp);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *muldiv_expr(BTNode *temp);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *unary_expr(BTNode *temp);

void statement(void);          // 處理一行 statement
void err(ErrorType errorNum);  // 錯誤處理

// 暫存器模擬
int reg[8][2];

// 語法樹求值與前序列印
int evaluateTree(BTNode *root);
void printPrefix(BTNode *root);

/*============================================================================================
lex implementation
============================================================================================*/

// 取得下一個 token
TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    // 跳過空白與 tab
    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    // 整數
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } 
    // +, -, ++, --, +=, -=
    else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if(c == lexeme[0]){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else if(c == '='){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        }
        ungetc(c, stdin);
        lexeme[1] = '\0';
        return ADDSUB;
    } 
    // *, /
    else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } 
    // 換行
    else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } 
    // =
    else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } 
    // &
    else if (c == '&') {
        strcpy(lexeme, "&");
        return AND;
    } 
    // |
    else if (c == '|') {
        strcpy(lexeme, "|");
        return OR;
    } 
    // ^
    else if (c == '^') {
        strcpy(lexeme, "^");
        return XOR;
    } 
    // (
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } 
    // )
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } 
    // 識別字
    else if (isalpha(c)||c=='_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isdigit(c)||c=='_'||isalpha(c))&& i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } 
    // EOF
    else if (c == EOF) {
        return ENDFILE;
    } 
    // 其他未知字元
    else {
        return UNKNOWN;
    }
}

// 取得下一個 token
void advance(void) {
    curToken = getToken();
}

// 判斷當前 token 是否為指定 token
int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

// 取得目前 lexeme
char *getLexeme(void) {
    return lexeme;
}

/*============================================================================================
parser implementation
============================================================================================*/

// 初始化符號表
void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

// 取得變數值
int getval(char *str) {
    int i = 0;
    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;
    error(UNDEFINED);
}

// 設定變數值
int setval(char *str, int val) {
    int i = 0;
    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

// 建立語法樹節點
BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 釋放語法樹
void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor: 處理數字、變數、遞增遞減、括號等
BTNode *factor(void) {
    BTNode *retp = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        retp -> val = atoi(getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if (match(ID)) {
            retp -> left = makeNode(ID, getLexeme());
            retp -> right = NULL;
            advance();
        } else error(NOTNUMID);
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN)) advance();
        else error(MISPAREN);
    } else error(NOTNUMID);

    return retp;
}

// assign_expr: 處理賦值與複合賦值
BTNode *assign_expr(void){
    BTNode *retp, *left = NULL;

    if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (match(ADDSUB_ASSIGN)) {
            retp = makeNode(ADDSUB_ASSIGN, getLexeme());
            advance();
            retp -> left = left;
            retp -> right = assign_expr();
        } else if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp -> left = left;
            retp -> right = assign_expr();
        } 
        else retp = or_expr(left);
    } else retp = or_expr(NULL);
    return retp;
}

// or_expr: 處理 OR 運算
BTNode *or_expr(BTNode *temp) {
    BTNode *node = xor_expr(temp);
    return or_expr_tail(node);
}

// or_expr_tail: 處理多重 OR
BTNode *or_expr_tail(BTNode *left) {
    BTNode *retp = NULL;
    if (match(OR)) {
        retp = makeNode(OR, getLexeme());
        advance();
        retp -> left = left;
        retp -> right = xor_expr(NULL);
        return or_expr_tail(retp);
    } else return left;
}

// xor_expr: 處理 XOR 運算
BTNode *xor_expr(BTNode *temp) {
    BTNode *node = and_expr(temp);
    return xor_expr_tail(node);
}

// xor_expr_tail: 處理多重 XOR
BTNode *xor_expr_tail(BTNode *left) {
    BTNode *retp = NULL;
    if (match(XOR)) {
        retp = makeNode(XOR, getLexeme());
        advance();
        retp -> left = left;
        retp -> right = and_expr(NULL);
        return xor_expr_tail(retp);
    } else return left;
}

// and_expr: 處理 AND 運算
BTNode *and_expr(BTNode *temp) {
    BTNode *node = addsub_expr(temp);
    return and_expr_tail(node);
}

// and_expr_tail: 處理多重 AND
BTNode *and_expr_tail(BTNode *left) {
    BTNode *retp = NULL;
    if (match(AND)) {
        retp = makeNode(AND, getLexeme());
        advance();
        retp -> left = left;
        retp -> right = addsub_expr(NULL);
        return and_expr_tail(retp);
    } else return left;
}

// addsub_expr: 處理加減運算
BTNode *addsub_expr(BTNode *temp) {
    BTNode *node = muldiv_expr(temp);
    return addsub_expr_tail(node);
}

// addsub_expr_tail: 處理多重加減
BTNode *addsub_expr_tail(BTNode *left) {
    BTNode *retp = NULL;

    if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp -> left = left;
        retp -> right = muldiv_expr(NULL);
        return addsub_expr_tail(retp);
    } else return left;
}

// muldiv_expr: 處理乘除運算
BTNode *muldiv_expr(BTNode *temp) {
    BTNode *node = unary_expr(temp);
    return muldiv_expr_tail(node);
}

// muldiv_expr_tail: 處理多重乘除
BTNode *muldiv_expr_tail(BTNode *left) {
    BTNode *retp;
    if (match(MULDIV)) {
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp -> left = left;
        retp -> right = unary_expr(NULL);
        return muldiv_expr_tail(retp);
    } else return left;
}

// unary_expr: 處理單元運算 (如負號)
BTNode *unary_expr(BTNode *temp) {
    BTNode *retp;

    if (temp) return temp;
    if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp -> left = makeNode(INT, "0");
        retp -> right = unary_expr(NULL);
        return retp;
    } else return factor();
}

// statement: 處理一行輸入
void statement(void) {
    BTNode *retp;

    if(match(ENDFILE)) {
        printf("MOV r0 [0]\n");
        printf("MOV r1 [4]\n");
        printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        advance();
    } else {
        for (int i = 0; i < 8; i++) {
            reg[i][0] = reg[i][1] = 0;
        }
        retp = assign_expr();
        if (match(END)) {
            evaluateTree(retp);
            freeTree(retp);
            advance();
        } else error(SYNTAXERR);
    }
} 

// 錯誤處理
void err(ErrorType errorNum) {
   printf("EXIT 1\n");
    exit(0);
}

/*============================================================================================
codeGen implementation
============================================================================================*/

// 暫存器與記憶體模擬
int lend = 0;
int prev[8][2];

// 尋找可用暫存器
int find_new_reg(){
    int i;
    for (i = 0; i < 8; i++) {
        if (reg[i][1] == 0) return i;
    }
    printf("MOV [%d] r%d\n", 252 - 4 * lend, lend);
    prev[lend][0] = reg[lend][0];
    prev[lend][1] = 1;
    lend++;
    return lend - 1;
}

// 取得變數對應的記憶體位址
int address(char *str){
    for (int i = 0; i < TBLSIZE; i++) {
        if (strcmp(table[i].name, str) == 0) return i * 4;
    }
    error(NOTFOUND);
}

// 檢查語法樹是否有 ID 節點
int have_ID(BTNode *root){
    if (root -> data == ID) return 1;
    if (root -> left != NULL) {
        if (have_ID(root -> left)) return 1;
    }
    if (root -> right != NULL) {
        if (have_ID(root -> right)) return 1;
    }
    return 0;
}

// 遞迴計算語法樹並產生組合語言
int evaluateTree(BTNode *root) {
    int retval, rv, lv = 0;
    int nu = 0;
    
    if (root != NULL) {
        switch(root -> data) {
            case ID:
                nu = find_new_reg();
                printf("MOV r%d [%d]\n", nu, address(root -> lexeme));
                reg[nu][0] = getval(root -> lexeme);
                reg[nu][1] = 1;
                return nu;
            case INT:
                nu = find_new_reg();
                printf("MOV r%d %d\n", nu, atoi(root -> lexeme));
                reg[nu][0] = atoi(root -> lexeme);
                reg[nu][1] = 1;
                return nu;
            case ASSIGN:
                rv = evaluateTree(root -> right);
                if (root -> left -> data != ID) error(NOTLVAL);
                setval(root -> left -> lexeme, reg[rv][0]);
                printf("MOV [%d] r%d\n", address(root -> left -> lexeme), rv);
                return rv;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root -> left);
                rv = evaluateTree(root -> right);
                if (strcmp(root -> lexeme, "+") == 0) {
                    printf("ADD r%d r%d\n", lv, rv);
                    reg[lv][0] += reg[rv][0];
                } else if (strcmp(root -> lexeme, "-") == 0) {
                    printf("SUB r%d r%d\n", lv, rv);
                    reg[lv][0] -= reg[rv][0];
                } else if (strcmp(root -> lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n", lv, rv);
                    reg[lv][0] *= reg[rv][0];
                } else if (strcmp(root -> lexeme, "/") == 0) {
                    if (reg[rv][0] == 0) {
                        if (have_ID(root -> right)) reg[rv][0] = 1;
                        else error(DIVZERO);
                    }
                    printf("DIV r%d r%d\n", lv, rv);
                    reg[lv][0] /= reg[rv][0];
                } 
                if (prev[rv][1]) {
                    //printf("MOV r%d [%d]\n", rv, 252 - rv * 4);
                    lend--;
                    reg[rv][0] = prev[rv][0];
                    prev[rv][1] = 0;
                } else {
                    reg[rv][0] = 0;
                    reg[rv][1] = 0;
                }
                return lv;
            case INCDEC:
                lv = evaluateTree(root -> left);
                nu = find_new_reg();
                if (root -> left -> data != ID) error(SYNTAXERR);
                if (root -> lexeme[0] == '+') {
                    printf("MOV r%d 1\n", nu);
                    reg[nu][0] = 1;
                    reg[nu][1] = 1;
                    printf("ADD r%d r%d\n", lv, nu);
                    reg[lv][0] += reg[nu][0];
                    printf("MOV [%d] r%d\n", address(root->left->lexeme), lv);
                    setval(root->left->lexeme, reg[lv][0]);
                    if (prev[nu][1]) {
                        //printf("MOV r%d [%d]\n", nu, 252- nu * 4);
                        lend--;
                        reg[nu][0] = prev[nu][0];
                        prev[nu][1] = 0;
                    } else {
                        reg[nu][0] = 0;
                        reg[nu][1] = 0;
                    }
                    return lv;
                } else if (root -> lexeme[0] == '-') {
                    printf("MOV r%d 1\n", nu);
                    reg[nu][0] = 1;
                    reg[nu][1] = 1;
                    printf("SUB r%d r%d\n", lv, nu);
                    reg[lv][0] -= reg[nu][0];
                    if (prev[nu][1]) {
                        //printf("MOV r%d [%d]\n", nu, 252- nu * 4);
                        lend--;
                        reg[nu][0] = prev[nu][0];
                        prev[nu][1] = 0;
                    } else {
                        reg[nu][0] = 0;
                        reg[nu][1] = 0;
                    }
                    printf("MOV [%d] r%d\n", address(root->left->lexeme), lv);
                    setval(root->left->lexeme, reg[lv][0]);
                    return lv;
                }
                break;
            case AND:
                lv = evaluateTree(root -> left);
                rv = evaluateTree(root -> right);
                printf("AND r%d r%d\n", lv, rv);
                reg[lv][0] = reg[lv][0] & reg[rv][0];
                if (prev[rv][1]) {
                    //printf("MOV r%d [%d]\n", rv, 252 - 4 * rv);
                    lend--;
                    reg[rv][0] = prev[rv][0];
                    prev[rv][1] = 0;
                } else {
                    reg[rv][0] = 0;
                    reg[rv][1] = 0;
                }
                return lv;
            case OR:
                lv = evaluateTree(root -> left);
                rv = evaluateTree(root -> right);
                printf("OR r%d r%d\n", lv, rv);
                reg[lv][0] = reg[lv][0] | reg[rv][0];
                if (prev[rv][1]) {
                    //printf("MOV r%d [%d]\n", rv, 252 - 4 * rv);
                    lend--;
                    reg[rv][0] = prev[rv][0];
                    prev[rv][1] = 0;
                } else {
                    reg[rv][0] = 0;
                    reg[rv][1] = 0;
                }
                return lv;
            case XOR:
                lv = evaluateTree(root -> left);
                rv = evaluateTree(root -> right);
                printf("XOR r%d r%d\n", lv, rv);
                reg[lv][0] = reg[lv][0] ^ reg[rv][0];
                if (prev[rv][1]) {
                    //printf("MOV r%d [%d]\n", rv, 252 - 4 * rv);
                    lend--;
                    reg[rv][0] = prev[rv][0];
                    prev[rv][1] = 0;
                } else {
                    reg[rv][0] = 0;
                    reg[rv][1] = 0;
                }
                return lv;
            case ADDSUB_ASSIGN:
                lv = evaluateTree(root -> left);
                rv = evaluateTree(root -> right);
                if (root -> lexeme[0] == '+') {
                    printf("ADD r%d r%d\n", lv, rv);
                    reg[lv][0] += reg[rv][0];
                } else if (root -> lexeme[0] == '-') {
                    printf("SUB r%d r%d\n", lv, rv);
                    reg[lv][0] -= reg[rv][0];
                }
                printf("MOV [%d] r%d\n", address(root->left->lexeme), lv);
                setval(root->left->lexeme, reg[lv][0]);
                if (prev[rv][1]) {
                    lend--;
                    reg[rv][0] = prev[rv][0];
                    prev[rv][1] = 0;
                } else {
                    reg[rv][0] = 0;
                    reg[rv][1] = 0;
                }
                return lv;
            default:
                retval = 0;
        }
    }
    return retval;
}

// 前序列印語法樹
void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/*============================================================================================
main
============================================================================================*/

// 主程式: 反覆讀取並處理每一行
int main() {
    initTable();
    while (1) {
        statement();
    }
    return 0;
}
