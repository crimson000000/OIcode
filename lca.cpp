/*#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int h[N], ne[N], e[N], idx;
int f[N][21], d[N], lg[N];
int n, m, s, t;

void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

queue<int> p;
/*void dfs(int now, int fath) {
	f[now][0] = fath; d[now] = d[fath] + 1;
	for(int i = 1; i <= t; ++i)
		f[now][i] = f[f[now][i-1]][i-1];
	for(int i = h[now]; i != -1; i = ne[i])
		if(e[i] != fath) dfs(e[i], now);
}

int lca(int x, int y){
	if(d[x] > d[y]) swap(x, y);
	for(int i = t; i >= 0; i -- ){
		if(d[x] <= d[f[y][i]]) y = f[y][i];
	}
	if(x == y) return x;
	for(int i = t - 1; i >= 0; i -- ){
		if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	}
	return f[x][0];
}
void bfs() {
	p.push(s); d[s] = 1;
	while (p.size()) {
		int x = p.front(); p.pop();
		for (int i = h[x]; i != -1; i = ne[i]) {
			int y = e[i];
			if (d[y]) continue;
			d[y] = d[x] + 1;
			f[y][0] = x;
			for (int j = 1; j <= t; j++)
				f[y][j] = f[f[y][j - 1]][j - 1];
			p.push(y);
		}
	}
}

int lca(int x, int y) {
	if (d[x] > d[y]) swap(x, y);
	for (int i = t; i >= 0; i--)
		if (d[f[y][i]] >= d[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = t; i >= 0; i--)
		if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

int main(){
	memset(h, -1, sizeof h);
	scanf("%d%d%d", &n, &m, &s);
	int t = log(n) / log(2) + 1;
	for(int i = 0; i < n - 1; i ++ ){
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	
	bfs();
	while(m -- ){
		int x, y;
		scanf("%d%d", &x, &y);
		cout << lca(x, y) << endl;
	}
	return 0;
}*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct zzz {
    int t, nex;
}e[500010 << 1]; int head[500010], tot;
void add(int x, int y) {
	e[++tot].t = y;
	e[tot].nex = head[x];
	head[x] = tot;
}
int depth[500001], fa[500001][22], lg[500001];
void dfs(int now, int fath) {
	fa[now][0] = fath; depth[now] = depth[fath] + 1;
	for(int i = 1; i <= lg[depth[now]]; ++i)
		fa[now][i] = fa[fa[now][i-1]][i-1];
	for(int i = head[now]; i; i = e[i].nex)
		if(e[i].t != fath) dfs(e[i].t, now);
}
int LCA(int x, int y) {
	if(depth[x] < depth[y]) swap(x, y);
	while(depth[x] > depth[y])
		x = fa[x][lg[depth[x]-depth[y]] - 1];
	if(x == y) return x;
	for(int k = lg[depth[x]] - 1; k >= 0; --k)
		if(fa[x][k] != fa[y][k])
			x = fa[x][k], y = fa[y][k];
	return fa[x][0];
}
int main() {
	int n, m, s; scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= n-1; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	for(int i = 1; i <= n; ++i)
		lg[i] = lg[i-1] + (1 << lg[i-1] == i);
	dfs(s, 0);
	for(int i = 1; i <= m; ++i) {
		int x, y; scanf("%d%d",&x, &y);
		printf("%d\n", LCA(x, y));
	}
	return 0;
}
