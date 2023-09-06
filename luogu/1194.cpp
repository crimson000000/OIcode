#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
struct edge{
    int a, b, w;
    bool operator < (const edge& W) const {
        return w < W.w;
    }
}edges[N];
int p[N];
int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
int n, m, tot;

int kruskal(){
    int res = 0;
    for(int i = 0; i <= m; i ++ ) p[i] = i;
    sort(edges, edges + tot);
    for(int i = 0; i <= tot; i ++ ){
        auto e = edges[i];
        int a = e.a, b = e.b, w = e.w;
        a = find(a), b = find(b);
        if(a != b){
            p[find(a)] = find(b);
            res += w;
        }
    }
    return res;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i ++ ){
        edges[tot ++] = {0, i, n};
    }
    for(int i = 1; i <= m; i ++ ){
        for(int j = 1; j <= m; j ++ ){
            int w;
            scanf("%d", &w);
            if(w != 0 && i < j) edges[tot ++] = {i, j, w};
        }
    }
    int t = kruskal();
    cout << t << endl;
}