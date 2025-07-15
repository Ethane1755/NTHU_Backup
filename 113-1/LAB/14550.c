#include <stdio.h>

int n, m, q;
int color[100000+10];
int weight[100000+10];
int ans_color[100000+10];
int ans_weight[100000+10];
int now_color;
int now_weight;
int take[7];

int max (int a, int b) {
    return (a > b ? a : b);
}

void dfs (int dot) {
    int r = take[color[dot]];
    int r_color = now_color;
    int r_weight = now_weight;

    if (take[color[dot]] == 0) {
        now_color++;
        take[color[dot]] = weight[dot];
        now_weight += weight[dot];
    } else {
        now_weight = max(now_weight, now_weight - take[color[dot]] + weight[dot]);
        take[color[dot]] = max(take[color[dot]], weight[dot]);
    }

    if (ans_color[dot] < now_color) {
        ans_color[dot] = now_color;
        ans_weight[dot] = now_weight;
    } else if (ans_color[dot] == now_color) {
        ans_weight[dot] = max(now_weight, ans_weight[dot]);
    }

    for (int i = 2; i * dot < n; i++) {
        dfs(i * dot);
    }

    take[color[dot]] = r;
    now_color = r_color;
    now_weight = r_weight;
}

int main(){
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&color[i]);
        color[i]--;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&weight[i]);
    }
    dfs(1);
    for(int i=1;i<=q;i++){
        scanf("%d",&m);
        printf("%d %d\n",ans_color[m],ans_weight[m]);
    }
}