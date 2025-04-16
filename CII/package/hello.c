#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256
#define TBLSIZE 64

// === Token and AST Definitions ===
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV, ANDORXOR,
    ASSIGN, ADDSUB_ASSIGN, INCDEC,
    LPAREN, RPAREN
} TokenSet;

typedef enum {
    MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

#define PRINTERR 1

typedef struct _BTNode {
    TokenSet data;
    char lexeme[MAXLEN];
    int val;
    struct _BTNode *left, *right;
} BTNode;

// === Symbol Table ===
typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;

Symbol table[TBLSIZE];
int sbcount = 0;

// === Lexer ===
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

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
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == '=') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        } else if (c == '+' || c == '-') {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '&' || c == '|' || c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ANDORXOR;
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
        i = 0;
        while ((isalnum(c) || c == '_') && i < MAXLEN - 1) {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN) advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}

// === Error Handling ===
void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN: fprintf(stderr, "mismatched parenthesis\n"); break;
            case NOTNUMID: fprintf(stderr, "number or identifier expected\n"); break;
            case NOTFOUND: fprintf(stderr, "variable not defined\n"); break;
            case RUNOUT: fprintf(stderr, "out of memory\n"); break;
            case NOTLVAL: fprintf(stderr, "lvalue required as an operand\n"); break;
            case DIVZERO: fprintf(stderr, "divide by constant zero\n"); break;
            case SYNTAXERR: fprintf(stderr, "syntax error\n"); break;
            default: fprintf(stderr, "undefined error\n"); break;
        }
    }
    exit(0);
}

// === Symbol Table ===
void initTable(void) {
    strcpy(table[0].name, "x"); table[0].val = 0;
    strcpy(table[1].name, "y"); table[1].val = 0;
    strcpy(table[2].name, "z"); table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    for (int i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;
    if (sbcount >= TBLSIZE) err(RUNOUT);
    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    for (int i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }
    if (sbcount >= TBLSIZE) err(RUNOUT);
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

// === AST Operations ===
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
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    if (!root) return 0;

    switch (root->data) {
        case ID: retval = getval(root->lexeme); break;
        case INT: retval = atoi(root->lexeme); break;
        case ASSIGN:
            rv = evaluateTree(root->right);
            retval = setval(root->left->lexeme, rv);
            break;
        case ADDSUB:
        case MULDIV:
        case ANDORXOR:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);
            if (!strcmp(root->lexeme, "+")) retval = lv + rv;
            else if (!strcmp(root->lexeme, "-")) retval = lv - rv;
            else if (!strcmp(root->lexeme, "*")) retval = lv * rv;
            else if (!strcmp(root->lexeme, "/")) {
                if (rv == 0) err(DIVZERO);
                retval = lv / rv;
            } else if (!strcmp(root->lexeme, "&")) retval = lv & rv;
            else if (!strcmp(root->lexeme, "|")) retval = lv | rv;
            else if (!strcmp(root->lexeme, "^")) retval = lv ^ rv;
            break;
        default: retval = 0;
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

// === Parser ===
BTNode *expr(void);
BTNode *term(void);
BTNode *factor(void);
BTNode *term_tail(BTNode *);
BTNode *expr_tail(BTNode *);

BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme()); advance();
            retp->left = left; retp->right = expr();
        } else if (match(ADDSUB_ASSIGN)) {
            // x += expr --> x = x + expr
            retp = makeNode(ASSIGN, "=");
            retp->left = left;
            // 避免 lexeme 是 += 而不是 +
            char op_char = getLexeme()[0]; // '+' or '-'
            BTNode *op = makeNode(ADDSUB, op_char == '+' ? "+" : "-");
            advance();
            op->left = makeNode(ID, left->lexeme); // copy of x
            op->right = expr();
            retp->right = op;
        } else if (match(INCDEC)) {
            retp = makeNode(ASSIGN, "="); retp->left = left;
            BTNode *op = makeNode(ADDSUB, getLexeme()[0] == '+' ? "+" : "-"); advance();
            op->left = makeNode(ID, left->lexeme);
            op->right = makeNode(INT, "1");
            retp->right = op;
        } else {
            retp = left;
        }
    } else if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme()); retp->left = makeNode(INT, "0"); advance();
        if (match(INT)) {
            retp->right = makeNode(INT, getLexeme()); advance();
        } else if (match(ID)) {
            retp->right = makeNode(ID, getLexeme()); advance();
        } else if (match(LPAREN)) {
            advance(); retp->right = expr(); if (match(RPAREN)) advance(); else err(MISPAREN);
        } else err(NOTNUMID);
    } else if (match(LPAREN)) {
        advance(); retp = expr(); if (match(RPAREN)) advance(); else err(MISPAREN);
    } else err(NOTNUMID);

    return retp;
}

BTNode *term(void) {
    return term_tail(factor());
}

BTNode *term_tail(BTNode *left) {
    BTNode *node;
    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme()); advance();
        node->left = left; node->right = factor();
        return term_tail(node);
    }
    return left;
}

BTNode *expr(void) {
    return expr_tail(term());
}

BTNode *expr_tail(BTNode *left) {
    BTNode *node;
    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme()); advance();
        node->left = left; node->right = term();
        return expr_tail(node);
    } else if (match(ANDORXOR)) {
        node = makeNode(ANDORXOR, getLexeme()); advance();
        node->left = left; node->right = term();
        return expr_tail(node);
    }
    return left;
}

void statement(void) {
    BTNode *retp;
    if (match(ENDFILE)) exit(0);
    else if (match(END)) {
        printf(">> "); advance();
    } else {
        retp = expr();
        if (match(END)) {
            printf("%d\n", evaluateTree(retp));
            printf("Prefix traversal: "); printPrefix(retp); printf("\n");
            freeTree(retp);
            printf(">> "); advance();
        } else err(SYNTAXERR);
    }
}

int main() {
    initTable();
    printf(">> ");
    while (1) statement();
    return 0;
}
