#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_VAR = 3000;    // 最大變數數量
const int MAX_GATE = 40000;  // 最大閘數量
char Variable[MAX_VAR][20];  // 儲存所有變數名稱
int numVar = 0;              // 目前已登記的變數數量
int occupied[MAX_GATE];      // 儲存每個變數的值


// 定義閘的結構
struct Gate {
    char operand[10];  // 閘的型態 (如 and, or, not...)
    char in1[20], in2[20]; // 兩個輸入變數名稱
    char out[20];          // 輸出變數名稱
};

// 取得變數的索引，若不存在則新增
int getVar (const char *s) {
    for (int i = 0; i < numVar; i++) {
        if (strcmp(Variable[i], s) == 0) return i;
    }
    strcpy(Variable[numVar], s);
    return numVar++;
}

// 計算閘的輸出值
int evalGate(const char *operand, int a, int b) {
    if (strcmp(operand, "buf") == 0) return a;
    else if (strcmp(operand, "not") == 0) return !a;
    else if (strcmp(operand, "and") == 0) return a & b;
    else if (strcmp(operand, "nand") == 0) return !(a & b);
    else if (strcmp(operand, "or") == 0) return a | b;
    else if (strcmp(operand, "nor") == 0) return !(a | b);
    else if (strcmp(operand, "xor") == 0) return a ^ b;
    else if (strcmp(operand, "xnor") == 0) return !(a ^ b);
    else return 0;
}

int main (int argc, char *argv[]) {
    // 檢查參數數量
    if (argc < 4) {
        cerr << "Please use circuit.txt, pattern.txt, output.txt" << "\n";
        return 1;
    }

    // 開啟檔案
    ifstream fin(argv[1]);
    ifstream fpat(argv[2]);
    ofstream fout(argv[3]);

    int NI, NO, NG; // 輸入數、輸出數、閘數
    char Input[MAX_VAR][20], Output[MAX_VAR][20];
    fin >> NI >> NO >> NG; // 讀取電路資訊

    // 讀取所有輸入變數名稱
    for (int i = 0; i < NI; i++) {
        fin >> Input[i];
        getVar(Input[i]);
    }
    // 讀取所有輸出變數名稱
    for (int i = 0; i < NO; i++) {
        fin >> Output[i];
        getVar(Output[i]);
    }

    Gate gate[MAX_GATE]; // 儲存所有閘的資訊
    // 讀取每個閘的資訊
    for (int i = 0; i < NG; i++) {
        fin >> gate[i].operand >> gate[i].in1;
        // 單輸入閘
        if (strcmp(gate[i].operand, "buf") == 0 || strcmp(gate[i].operand, "not") == 0) {
            strcpy(gate[i].in2, "ouo"); // 用 "ouo" 當作無效輸入
            fin >> gate[i].out;
        } else { // 雙輸入閘
            fin >> gate[i].in2 >> gate[i].out;
        }
        getVar(gate[i].out); // 註冊輸出變數
    }

    int deg[MAX_VAR] = {0}; // 記錄每個閘的入度
    int inp1[MAX_GATE], inp2[MAX_GATE], out[MAX_GATE]; // 儲存每個閘的輸入/輸出變數索引
    for (int i = 0; i < NG; i++) {
        inp1[i] = getVar(gate[i].in1);
        out[i] = getVar(gate[i].out);
        if (!strcmp(gate[i].in2, "ouo")) inp2[i] = -1; // 單輸入閘
        else inp2[i] = getVar(gate[i].in2);
    }

    // 計算每個閘的入度（拓撲排序用）
    for (int i = 0; i < NG; i++) {
        for (int j = 0; j < NG; j++) {
            if (out[i] == inp1[j] || out[i] == inp2[j]) {
                deg[j]++;
            } 
        }
    }

    int done[MAX_GATE] = {0}; // 記錄閘是否已排序
    int order[MAX_GATE];      // 儲存拓撲排序後的閘順序
    int len = 0;              // 已排序的閘數

    // 拓撲排序，決定閘的運算順序
    while (len < NG) {
        for (int i = 0; i < NG; i++) {
            if (!done[i] && deg[i] == 0) {
                done[i] = 1;
                order[len++] = i;
                for (int j = 0; j < NG; j++) {
                    if (!done[j] && (out[i] == inp1[j] || out[i] == inp2[j])) {
                        deg[j]--;
                    }
                }
            }
        }
    }

    string stream;
    // 讀取每一組輸入測資
    while (getline(fpat, stream)) {
        if (stream.empty()) continue;
        // 設定輸入變數的值
        for (int i = 0; i < NI; i++) {
            occupied[getVar(Input[i])] = stream[i] - '0';
        }

        // 依照拓撲順序計算每個閘的輸出
        for (int i = 0; i < len; i++) {
            int id = order[i];
            int a = occupied[inp1[id]];
            int b;
            if (inp2[id] == -1) b = 0; // 單輸入閘
            else b = occupied[inp2[id]];
            occupied[out[id]] = evalGate(gate[id].operand, a, b);
        }

        // 輸出結果
        for (int i = 0; i < NO; i++) {
            fout << occupied[getVar(Output[i])];
        }
        fout << "\n";
    }
    return 0;
}