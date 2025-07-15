#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256
#define TBLSIZE 64
#define MAX_REG 8
int allow_undeclared_id = 0;  // 預設不允許未宣告 ID

typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ASSIGN, ADDSUB_ASSIGN, INCDEC,
    OR, XOR, AND,
    ADDSUB, MULDIV,
    LPAREN, RPAREN
} TokenSet;

typedef enum {
    MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

typedef struct _BTNode {
    TokenSet data;
    char lexeme[MAXLEN];
    struct _BTNode *left, *right;
} BTNode;

typedef struct {
    char name[MAXLEN];
    int val;
    int defined; // 1:已定義(左值), 0:未定義
} Symbol;

typedef struct
{
    char name[3]; // r0, r1, r2...
    int val;
    int unknown_val;
    int occupy;
} Register;
Register reg[MAX_REG];

Symbol table[TBLSIZE];
int sbcount = 0;

TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

void err(ErrorType errorNum) {
    printf("EXIT 1\n");
    exit(0);
}

void initReg()
{
    for(int i=0;i<8;i++){
        reg[i].occupy=0;
        reg[i].name[0]='r';
        reg[i].name[1]=i+'0';
        reg[i].name[2]='\0';
    }
}

Register *unused_reg(){
    Register *cur=NULL;
    for(int i=0;i<8;i++){
        if(reg[i].occupy==0){
            cur=&(reg[i]);
            cur->occupy=1;
            break;
        }
    }
    if(cur==NULL){
        err(RUNOUT);
    }
    return cur;
}

void returnReg(Register *reg)
{
    reg->occupy = 0;
}



void initTable(void) {
    strcpy(table[0].name, "x"); table[0].val = 0; table[0].defined = 1;
    strcpy(table[1].name, "y"); table[1].val = 0; table[1].defined = 1;
    strcpy(table[2].name, "z"); table[2].val = 0; table[2].defined = 1;
    sbcount = 3;
}

int lookup(char *str) {
    for (int i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return i;
    return -1;
}

int get_addr(char *str){
    int addr=0;
    int i=0;
    while(i<sbcount){
        if(strcmp(str,table[i].name)==0){
            addr=4*i;
            break;
        }
        i++;
    }
    //err(NOTFOUND);
    return addr;
}

void addVar(char *str) {
    if (lookup(str) == -1) {
        strcpy(table[sbcount].name, str);
        table[sbcount].val = 0;
        table[sbcount].defined = 1;
        sbcount++;
    }
}

TokenSet getToken(void) {
    int i = 0;
    char c = '\0';
    while ((c = fgetc(stdin)) == ' ' || c == '\t');
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (isalpha(c) || c == '_') {
        i = 0;
        while ((isalnum(c) || c == '_') && i < MAXLEN - 1) {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == '+') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '+') { lexeme[1] = c; lexeme[2] = '\0'; return INCDEC; }
        else if (c == '=') { lexeme[1] = c; lexeme[2] = '\0'; return ADDSUB_ASSIGN; }
        else { ungetc(c, stdin); lexeme[1] = '\0'; return ADDSUB; }
    } else if (c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '-') { lexeme[1] = c; lexeme[2] = '\0'; return INCDEC; }
        else if (c == '=') { lexeme[1] = c; lexeme[2] = '\0'; return ADDSUB_ASSIGN; }
        else { ungetc(c, stdin); lexeme[1] = '\0'; return ADDSUB; }
    } else if (c == '*') { lexeme[0] = c; lexeme[1] = '\0'; return MULDIV; }
    else if (c == '/') { lexeme[0] = c; lexeme[1] = '\0'; return MULDIV; }
    else if (c == '&') { lexeme[0] = c; lexeme[1] = '\0'; return AND; }
    else if (c == '|') { lexeme[0] = c; lexeme[1] = '\0'; return OR; }
    else if (c == '^') { lexeme[0] = c; lexeme[1] = '\0'; return XOR; }
    else if (c == '=') { lexeme[0] = c; lexeme[1] = '\0'; return ASSIGN; }
    else if (c == '(') { lexeme[0] = c; lexeme[1] = '\0'; return LPAREN; }
    else if (c == ')') { lexeme[0] = c; lexeme[1] = '\0'; return RPAREN; }
    else if (c == '\n') { lexeme[0] = '\0'; return END; }
    else if (c == EOF) { return ENDFILE; }
    else { return UNKNOWN; }
}

void advance(void) { curToken = getToken(); }
int match(TokenSet token) { if (curToken == UNKNOWN) advance(); return token == curToken; }
char *getLexeme(void) { return lexeme; }

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->left = node->right = NULL;
    return node;
}
void freeTree(BTNode *root) {
    if (root) { freeTree(root->left); freeTree(root->right); free(root); }
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
// --- Parser 分層 ---
BTNode *assign_expr(void);
BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *);
BTNode *addsub_expr(void);
BTNode *addsub_expr_tail(BTNode *);
BTNode *muldiv_expr(void);
BTNode *muldiv_expr_tail(BTNode *);
BTNode *unary_expr(void);
BTNode *factor(void);

BTNode *assign_expr(void) {
    BTNode *node;
    
    allow_undeclared_id = 1;  // 允許新的 ID，因為左邊可能是新變數
    node = or_expr();
    allow_undeclared_id = 0;  // 之後恢復原狀
    if (node->data == ID ) {
        if (match(ASSIGN)) {
            char id[MAXLEN];
            strcpy(id, node->lexeme); // 儲存變數名稱
            //printf("%s\n", id);
            free(node); // 先釋放掉舊的節點
            advance();
            addVar(id); // 宣告變數
            BTNode *assignNode = makeNode(ASSIGN, "=");
            assignNode->left = makeNode(ID, id);
            assignNode->right = assign_expr(); // 注意是 assign_expr (右結合)
            return assignNode;
        }
    
        if (match(ADDSUB_ASSIGN)) {
            char id[MAXLEN];
            strcpy(id, node->lexeme);
            free(node);
            char op[MAXLEN];
            strcpy(op, getLexeme());
            advance();
            if (lookup(id) == -1) err(NOTFOUND);
            BTNode *assignNode = makeNode(ADDSUB_ASSIGN, op);
            assignNode->left = makeNode(ID, id);
            assignNode->right = assign_expr(); // += 是右邊只吃表達式
            return assignNode;
        }
    }
    return node;
}

BTNode *or_expr(void) {
    BTNode *node = xor_expr();
    return or_expr_tail(node);
}
BTNode *or_expr_tail(BTNode *left) {
    if (match(OR)) {
        BTNode *node = makeNode(OR, getLexeme()); advance();
        node->left = left; node->right = xor_expr();
        return or_expr_tail(node);
    }
    return left;
}
BTNode *xor_expr(void) {
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}
BTNode *xor_expr_tail(BTNode *left) {
    if (match(XOR)) {
        BTNode *node = makeNode(XOR, getLexeme()); advance();
        node->left = left; node->right = and_expr();
        return xor_expr_tail(node);
    }
    return left;
}
BTNode *and_expr(void) {
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}
BTNode *and_expr_tail(BTNode *left) {
    if (match(AND)) {
        BTNode *node = makeNode(AND, getLexeme()); advance();
        node->left = left; node->right = addsub_expr();
        return and_expr_tail(node);
    }
    return left;
}
BTNode *addsub_expr(void) {
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}
BTNode *addsub_expr_tail(BTNode *left) {
    if (match(ADDSUB)) { // 處理加減運算
        BTNode *node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    }
    return left;
}
BTNode *muldiv_expr(void) {
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}
BTNode *muldiv_expr_tail(BTNode *left) {
    if (match(MULDIV)) {
        BTNode *node = makeNode(MULDIV, getLexeme()); 
        advance();
        node->left = left; 
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    }
    return left;
}
BTNode *unary_expr(void) {
    if (match(ADDSUB)) {
        char op[MAXLEN]; 
        strcpy(op, getLexeme());
        advance();
        if (match(LPAREN)) { 
            //printf("asd\n");
            advance();
            BTNode *node = or_expr();
            if (!match(RPAREN)) err(MISPAREN);
            advance();
            BTNode *unaryNode = makeNode(ADDSUB, op);
            unaryNode->left = makeNode(INT, "0");
            unaryNode->right = node;
            return unaryNode;
        } else { // 處理一般一元運算
            //printf("asd\n");
            BTNode *node = makeNode(ADDSUB, op);
            node->left = makeNode(INT, "0");
            node->right = unary_expr();
            return node;
        }
    }  else if (match(INCDEC)) {
        char op[MAXLEN]; strcpy(op, getLexeme());
        advance();
        if (!match(ID)) err(NOTNUMID);
        if (lookup(getLexeme()) == -1) err(NOTFOUND);
        BTNode *node = makeNode(INCDEC, op);
        node->left = makeNode(ID, getLexeme());
        advance();
        return node;
    }
    return factor();
}
BTNode *factor(void) {
    if (match(INT)) {
        BTNode *node = makeNode(INT, getLexeme());
        advance();
        return node;
    } else if (match(ID)) {
        char id[MAXLEN];
        strcpy(id, getLexeme());
        if (lookup(id) == -1) {
            if (allow_undeclared_id) {
                addVar(id);  // 如果允許，就幫他加進 symbol table
            } else {
                err(NOTFOUND);
            }
        }
        advance();
        return makeNode(ID, id);
    } else if (match(LPAREN)) {
        advance();
        BTNode *node = assign_expr();
        if (!match(RPAREN)) err(MISPAREN);
        advance();
        return node;
    }
    err(NOTNUMID);
    return NULL;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        err(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        err(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                break;
            case ADDSUB:
            case MULDIV:
            case AND:
            case OR:
            case XOR:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0) retval = 1;
                    else retval = lv / rv;
                } else if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                } else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                }
                break;
            case INCDEC:
                lv = evaluateTree(root->left);
                if (strcmp(root->lexeme, "++") == 0) {
                    retval = setval(root -> left -> lexeme, lv + 1);
                } else {
                    retval = setval(root -> left -> lexeme, lv - 1);
                }
                break;
            case ADDSUB_ASSIGN:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+=") == 0) {
                    retval = setval(root->left->lexeme, lv += rv);
                } else {
                    retval = setval(root->left->lexeme, lv -= rv);
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}
int containsVariable(BTNode *root) {
    if (root == NULL) {
        return 0; 
    }
    if (root->data == ID) {
        return 1; 
    }
    return containsVariable(root->left) || containsVariable(root->right);
}

// --- Codegen ---
int regCount = 0;
int getReg() { return regCount++; }

Register *codeGen(BTNode *root,int keep){
    Register *retreg=NULL,*lreg=NULL,*rreg=NULL;
    int addr=0;
    if (root != NULL) {
        switch (root->data) {
            case ID:
                addr=get_addr(root->lexeme);
                retreg=unused_reg();
                printf("MOV %s [%d]\n",retreg->name,addr);
                break;
            case INT:
                retreg=unused_reg();
                printf("MOV %s %d\n",retreg->name,atoi(root->lexeme));
                break;
            case ASSIGN:
                addr=get_addr(root->left->lexeme);
                rreg=codeGen(root->right,1);
                printf("MOV [%d] %s\n", addr, rreg->name);
                returnReg(rreg);
                retreg=rreg;
                break;
            case ADDSUB_ASSIGN:
                if(strcmp(root->lexeme,"+=")==0){
                    lreg=codeGen(root->left,1);//x的register
                    rreg=codeGen(root->right,1);//expr的register
                    addr=get_addr(root->left->lexeme);
                    printf("ADD %s %s\n",lreg->name,rreg->name);
                    printf("MOV [%d] %s\n",addr,lreg->name);
                    returnReg(rreg);
                    returnReg(lreg);
                    retreg=lreg;

                }
                else if(strcmp(root->lexeme,"-=")==0){
                    lreg=codeGen(root->left,1);//x的register
                    rreg=codeGen(root->right,1);//expr的register
                    addr=get_addr(root->left->lexeme);
                    printf("SUB %s %s\n",lreg->name,rreg->name);
                    printf("MOV [%d] %s\n",addr,lreg->name);
                    returnReg(rreg);
                    returnReg(lreg);
                    retreg=lreg;
                }
                break;
             case INCDEC:
                if(strcmp(root->lexeme,"++")==0){
                    retreg=codeGen(root->left,1);
                    addr=get_addr(root->left->lexeme);
                    lreg=unused_reg();
                    printf("MOV %s 1\n",lreg->name);
                    printf("ADD %s %s\n",retreg->name,lreg->name);
                    printf("MOV [%d] %s\n",addr,retreg->name);
                    if(keep==0){
                        returnReg(retreg);
                    }
                    returnReg(lreg);
                }
                else if(strcmp(root->lexeme,"--")==0){
                    retreg=codeGen(root->left,1);
                    addr=get_addr(root->left->lexeme);
                    lreg=unused_reg();
                    printf("MOV %s 1\n",lreg->name);
                    printf("SUB %s %s\n",retreg->name,lreg->name);
                    printf("MOV [%d] %s\n",addr,retreg->name);
                    if(keep==0){
                        returnReg(retreg);
                    }
                    returnReg(lreg);
                }
                break;
                break;
            case ADDSUB:
            case MULDIV:
            case AND:
            case OR:
            case XOR:
                lreg=codeGen(root->left,1);
                rreg=codeGen(root->right,1);
                if (strcmp(root->lexeme, "+") == 0) {
                    printf("ADD %s %s\n",lreg->name,rreg->name);
                } else if (strcmp(root->lexeme, "-") == 0) {
                    printf("SUB %s %s\n",lreg->name,rreg->name);
                } else if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL %s %s\n",lreg->name,rreg->name);
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (!containsVariable(root->right)&& evaluateTree(root->right) == 0){
                        err(DIVZERO);
                    } 
                    printf("DIV %s %s\n",lreg->name,rreg->name);
                } else if(strcmp(root->lexeme,"&")==0){
                    printf("AND %s %s\n",lreg->name,rreg->name);
                }else if(strcmp(root->lexeme,"|")==0){
                    printf("OR %s %s\n",lreg->name,rreg->name);
                }else if(strcmp(root->lexeme,"^")==0){
                    printf("XOR %s %s\n",lreg->name,rreg->name);
                }
                //returnReg(rreg);
                retreg = lreg;
                break;

            default:
                break;
        }
    }
    return retreg;
}

int r0, r1, r2 = 0;
void store_xyz() {
    // x, y, z 分別存到 r0, r1, r2
    printf("MOV r0 [0]\n");
    printf("MOV r1 [4]\n");
    printf("MOV r2 [8]\n");
    r0 = table[0].val; // x
    r1 = table[1].val; // y
    r2 = table[2].val; // z
    //printf("x:%d y:%d z:%d\n", r0, r1, r2);
    /*for (int i = 0; i < sbcount - 1; i++) {
        printf("%s: %d, ", table[i].name, table[i].val);
    }
    printf("%s: %d\n", table[sbcount-1].name, table[sbcount-1].val);*/
}

int main() {
    //freopen("input.txt", "w", stdout);
    initTable();
    initReg();
    advance();
    BTNode *root;
    regCount = 0;
    while (!match(ENDFILE)) {
        for(int i = 0; i < 8; i++) {
            reg[i].occupy = 0;
        }
        if (match(END)) { advance(); continue; }
        root = assign_expr();
        if (!match(END) && !match(ENDFILE)) err(SYNTAXERR);
        codeGen(root, 1);
        evaluateTree(root);
        /*printf("Prefix traversal: ");
        printPrefix(root);
        printf("\n");
        for (int i = 0; i < sbcount - 1; i++) {
            printf("%s: %d, ", table[i].name, table[i].val);
        }
        printf("%s: %d\n", table[sbcount-1].name, table[sbcount-1].val);
        */
        freeTree(root);
        advance();
    }
    store_xyz();
    printf("EXIT 0\n");
    return 0;
}