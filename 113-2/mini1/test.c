#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 256
typedef struct _Register{
    char name[3];
    int occupy;
}Register;
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN,
    LPAREN, RPAREN,
    INCDEC,
    AND,OR,XOR,
    ADDSUB_ASSIGN
} TokenSet;
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;
extern Register reg[8];
// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
//Operation about register
extern int get_addr(char *str);
extern void initReg();
extern Register *unused_reg();
extern Register* codeGen(BTNode *root,int keep);
extern void returnReg(Register *reg);
int isConstant(BTNode *root);
#define TBLSIZE 256

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node


// The symbol table
extern Symbol table[TBLSIZE];

//The count of symbol
extern int sbcount ;

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(void);
extern BTNode *expr_tail(BTNode *left);
extern BTNode *addsub_expr(void);
extern BTNode *addsub_expr_tail(BTNode *left);
extern BTNode *and_expr(void);
extern BTNode *and_expr_tail(BTNode *left);
extern BTNode *or_expr(void);
extern BTNode *or_expr_tail(BTNode *left);
extern BTNode *xor_expr(void);
extern BTNode *xor_expr_tail(BTNode *left);
extern BTNode *assign_expr(void);
extern BTNode *unary_expr(void);
extern void statement(void);

// Print error message and exit the program
extern void err(ErrorType errorNum);




// Token types

// Test if a token matches the current token
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);


Register reg[8];

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

int get_addr(char *str){
    int addr=-1;
    int i=0;
    while(i<sbcount){
        if(strcmp(str,table[i].name)==0){
            addr=4*i;
            break;
        }
        i++;
    }
    if(addr==-1){
        err(NOTFOUND);
    }
    return addr;
}

int isConstant(BTNode *root){
    switch (root->data){
        case ID:
            return 0;
            break;
        case INT:
            return 1;
            break;
        case ADDSUB:
        case MULDIV:
        case AND:
        case OR:
        case XOR:
            if(isConstant(root->left)&&isConstant(root->right)){
                return 1;
            }
            else{
                return 0;
            }
            break;
        default:
            return 0;

    }
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
            case ADDSUB_ASSIGN:
                if(strcmp(root->lexeme,"+=")==0){
                    lv=evaluateTree(root->left);
                    rv=evaluateTree(root->right);
                    retval=setval(root->left->lexeme,rv+lv);

                }
                else if(strcmp(root->lexeme,"-=")==0){
                    lv=evaluateTree(root->left);
                    rv=evaluateTree(root->right);
                    retval=setval(root->left->lexeme,lv-rv);
                }
                break;
            case INCDEC:
                if(strcmp(root->lexeme,"++")==0){
                    lv=evaluateTree(root->left);
                    retval=setval(root->left->lexeme,lv+1);
                }
                else if(strcmp(root->lexeme,"--")==0){
                    rv=evaluateTree(root->left);
                    retval=setval(root->left->lexeme,rv-1);
                }
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
                        if(isConstant(root->right)==1&&rv==0){
                            err(DIVZERO);
                        }
                    if(rv!=0){
                        retval = lv / rv;
                    }
                } else if(strcmp(root->lexeme,"&")==0){
                    retval =lv&rv;
                }else if(strcmp(root->lexeme,"|")==0){
                    retval=lv|rv;
                }else if(strcmp(root->lexeme,"^")==0){
                    retval=lv^rv;
                }
                break;

            default:
                retval = 0;
        }
    }
    return retval;
}

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
                    returnReg(lreg);
                    if(keep==0){
                        returnReg(retreg);
                    }
                }
                else if(strcmp(root->lexeme,"--")==0){
                    retreg=codeGen(root->left,1);
                    addr=get_addr(root->left->lexeme);
                    lreg=unused_reg();
                    printf("MOV %s 1\n",lreg->name);
                    printf("SUB %s %s\n",retreg->name,lreg->name);
                    printf("MOV [%d] %s\n",addr,retreg->name);
                    returnReg(lreg);
                    if(keep==0){
                        returnReg(retreg);
                    }
                }
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
                    printf("DIV %s %s\n",lreg->name,rreg->name);
                } else if(strcmp(root->lexeme,"&")==0){
                    printf("AND %s %s\n",lreg->name,rreg->name);
                }else if(strcmp(root->lexeme,"|")==0){
                    printf("OR %s %s\n",lreg->name,rreg->name);
                }else if(strcmp(root->lexeme,"^")==0){
                    printf("XOR %s %s\n",lreg->name,rreg->name);
                }
                returnReg(rreg);
                retreg = lreg;
                break;

            default:
                break;
        }
    }
    return retreg;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

void returnReg(Register *reg)
{
    reg->occupy = 0;
}


int sbcount = 0;
Symbol table[TBLSIZE];

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    err(NOTFOUND);
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
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
// factor := INT | ADDSUB INT |
//		   	 ID  | ADDSUB ID  |
//		   	 ID ASSIGN expr |
//		   	 LPAREN expr RPAREN |
//		   	 ADDSUB LPAREN expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        //retp->val = getval(getLexeme());
        advance();
    } else if (match(ID)) {
        left = makeNode(ID, getLexeme());
        //left->val = getval(getLexeme());
        advance();
        if (!match(ASSIGN)&&!match(ADDSUB_ASSIGN)) {
            retp = left;
        } else if(match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = or_expr();
        } else if(match(ADDSUB_ASSIGN)){
            retp = makeNode(ADDSUB_ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = or_expr();
        } else{
            retp=left;
        }
    } else if (match(INCDEC)){
        retp=makeNode(INCDEC,getLexeme());
        advance();
        retp->left = makeNode(ID, getLexeme());
        //retp->left->val = getval(getLexeme());
        advance();
    } else if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0");
        //retp->left->val = 0;
        advance();
        if (match(INT)) {
            retp->right = makeNode(INT, getLexeme());
            //retp->right->val = getval(getLexeme());
            advance();
        } else if (match(ID)) {
            retp->right = makeNode(ID, getLexeme());
            //retp->right->val = getval(getLexeme());
            advance();
        } else if (match(LPAREN)) {
            advance();
            retp->right = or_expr();
            if (match(RPAREN))
                advance();
            else
                error(MISPAREN);
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = or_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}

BTNode* unary_expr() {
    BTNode* node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB,getLexeme());
        advance();
        node->left = makeNode(INT,"0");
        node->right = unary_expr();
    }
    else node = factor();
    return node;
}

// term := factor term_tail
BTNode *term(void) {
    BTNode *node = unary_expr();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return term_tail(node);
    } else {
        return left;
    }
}

// expr := term expr_tail
BTNode *addsub_expr(void) {
    BTNode *node = term();
    return addsub_expr_tail(node);
}

// expr_tail := ADDSUB term expr_tail | NiL
BTNode *addsub_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return addsub_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *and_expr(){
    BTNode *node=addsub_expr();
    return and_expr_tail(node);
}

BTNode *and_expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *xor_expr(){
    BTNode *node=and_expr();
    return xor_expr_tail(node);
}

BTNode *xor_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *or_expr(){
    BTNode *node=xor_expr();
    return or_expr_tail(node);
}

BTNode *or_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else {
        return left;
    }
}


// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;
    if (match(ENDFILE)) {
        //[0] [4] [8] to r0 r1 r2
        for (int i = 0; i < 3; i++)
        {
            char c[2];
            c[0] = (char)('x' + i);
            c[1] = '\0';
            printf("MOV %s [%d]\n",reg[i].name,get_addr(c));
            //sbcount++;
        }
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = or_expr();
        if (match(END)) {
            /*printf("%d\n", evaluateTree(retp));
            printf("Prefix traversal: ");
            printPrefix(retp);
            printf("\n");*/
            evaluateTree(retp);
            codeGen(retp,0);
            freeTree(retp);
            //printf(">> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}





static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

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
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c=fgetc(stdin);
        if(c=='='){
            lexeme[1]=c;
            lexeme[2]='\0';
            return ADDSUB_ASSIGN;
        }
        else if(c=='+'||c=='-'){
            lexeme[1]=c;
            lexeme[2]='\0';
            return INCDEC;
        }
        ungetc(c,stdin);
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) ||c=='_' )&& i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else if(c=='&'){
        lexeme[0]=c;
        lexeme[1]='\0';
        return AND;
    } else if(c=='|'){
        lexeme[0]=c;
        lexeme[1]='\0';
        return OR;
    } else if(c=='^'){
        lexeme[0]='^';
        lexeme[1]='\0';
        return XOR;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  |
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    initReg();
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
