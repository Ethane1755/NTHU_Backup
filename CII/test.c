#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_VARS 100

typedef struct {
    char name[20];
    int addr;
    int defined;
} Variable;

Variable vars[MAX_VARS];
int varCount = 3; // 預設 x, y, z 已存在
int nextAddr = 12; // 新變數從 [12] 開始
int hasError = 0;

void emit(const char *format, ...) {
    if (hasError) return; // 若已出錯則不再產生指令
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int getVarAddress(const char *name, int defineIfNotFound) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].addr;
        }
    }
    if (defineIfNotFound) {
        strcpy(vars[varCount].name, name);
        vars[varCount].addr = nextAddr;
        vars[varCount].defined = 0;
        nextAddr += 4;
        return vars[varCount++].addr;
    }
    return -1;
}

void defineVar(const char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].defined = 1;
            return;
        }
    }
}

// 解析並產生組合語言 (簡化版)
void processAssignment(char *line) {
    char var[20], expr[100];
    if (sscanf(line, "%s = %[^\n]", var, expr) != 2) {
        hasError = 1;
        return;
    }
    
    int addr = getVarAddress(var, 1);
    char *token = strtok(expr, " ");
    
    if (!token) {
        hasError = 1;
        return;
    }

    int r = 0; // 使用 r0
    if (isdigit(token[0])) {
        emit("MOV r%d %s\n", r, token);
    } else {
        int rhsAddr = getVarAddress(token, 0);
        if (rhsAddr == -1) {
            hasError = 1;
            return;
        }
        emit("MOV r%d [%d]\n", r, rhsAddr);
    }

    while ((token = strtok(NULL, " "))) {
        char op = token[0];
        char *next = strtok(NULL, " ");
        if (!next) {
            hasError = 1;
            return;
        }

        int r2 = 1;
        if (isdigit(next[0])) {
            emit("MOV r%d %s\n", r2, next);
        } else {
            int rhsAddr = getVarAddress(next, 0);
            if (rhsAddr == -1) {
                hasError = 1;
                return;
            }
            emit("MOV r%d [%d]\n", r2, rhsAddr);
        }

        switch (op) {
            case '+': emit("ADD r%d r%d\n", r, r2); break;
            case '-': emit("SUB r%d r%d\n", r, r2); break;
            case '*': emit("MUL r%d r%d\n", r, r2); break;
            case '/': emit("DIV r%d r%d\n", r, r2); break;
            case '&': emit("AND r%d r%d\n", r, r2); break;
            case '|': emit("OR r%d r%d\n", r, r2); break;
            case '^': emit("XOR r%d r%d\n", r, r2); break;
            default: hasError = 1; return;
        }
    }

    emit("MOV [%d] r%d\n", addr, r);
    defineVar(var);
}

int main() {
    strcpy(vars[0].name, "x"); vars[0].addr = 0; vars[0].defined = 1;
    strcpy(vars[1].name, "y"); vars[1].addr = 4; vars[1].defined = 1;
    strcpy(vars[2].name, "z"); vars[2].addr = 8; vars[2].defined = 1;

    char line[100];
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "END\n") == 0 || strcmp(line, "ENDFILE\n") == 0) break;
        processAssignment(line);
        if (hasError) {
            printf("EXIT 1\n");
            return 0;
        }
    }

    emit("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\nEXIT 0\n");
    return 0;
}