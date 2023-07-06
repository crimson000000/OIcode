#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int h[N * 2], ne[N * 2], e[N * 2], idx;
int f[N][21], d[N];
int n, m, s, t;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

queue<int> q;
void bfs(){
    q.push(s); d[s] = 1;
    while(!q.empty()){
        auto ver = q.front();
        q.pop();
        for(int i = h[ver]; i != -1; i = ne[i]){
            int j = e[i];
            if(d[j]) return;
            d[j] = d[ver] + 1;
            f[j][0] = ver;
            for(int k = 1; k <= t; k ++ ) f[j][k] = f[f[j][k - 1]][k - 1];
            q.push(j);
        }
    }
}

void dfs(int now, int fath) {
	f[now][0] = fath; d[now] = d[fath] + 1;
	for(int i = 1; i <= t; ++i)
		f[now][i] = f[f[now][i-1]][i-1];
	for(int i = h[now]; i != -1; i = ne[i])
		if(e[i] != fath) dfs(e[i], now);
}

int lca(int x, int y){
    if(d[x] > d[y]) swap(x, y);
    for(int i = t; i >= 0; i -- ){
        if(d[f[y][i]] >= d[x]) y = f[y][i];
    }
    if(x == y) return x;
    for(int i = t; i >= 0; i -- )
        if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

int main(){
    scanf("%d%d%d", &n, &m, &s);
    memset(h, -1, sizeof h);
    for(int i = 0; i < n - 1; i ++ ){
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    t = log(n) / log(2) + 1;
    dfs(s, 0);

    while(m -- ){
        int x, y;
        scanf("%d%d", &x, &y);
        cout << lca(x, y) << endl;
    }
}