#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
struct edge{
    int a, b, w;
    bool operator < (const edge& W) const {
        return w < W.w;
    }
}edges[N];
int p[N];
int n, k, sum;

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int kruskal(){
    int res = 0, cnt = 0;
    for(int i = 1; i <= n; i ++ ) p[i] = i;
    sort(edges, edges + k);
    for(int i = 0; i < k; i ++ ){
        auto e = edges[i];
        int a = e.a, b = e.b, w = e.w;
        a = find(a), b = find(b);
        if(a != b){
            p[find(a)] = find(b);
            res += w;
            cnt ++;
        }
    }
    return res;
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 0; i < k; i ++ ){
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[i] = {a, b, w};
        sum += w;
    }
    int t = kruskal();
    cout << sum - t << endl;
}