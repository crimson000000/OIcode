#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int h[N], ne[N], e[N], w[N], idx;
int n, k, l1, l2, st, ed;
int ans = 0;
int d[N], fr[N];
bool flag = false;
map<int, bool> mp;

inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0'&&ch<='9'){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}

void write(int x){
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

void add(int a, int b){
	e[idx] = b, w[idx] = 1, ne[idx] = h[a], h[a] = idx ++;
}

int maxdis, maxv;
void dfs(int u, int fa, int d2s){
	if(maxdis <= d2s){
		maxdis = d2s;
		maxv = u;
	}
	
	for(int i = h[u]; i != -1; i = ne[i]){
		int v = e[i], dist = w[i];
		if(v == fa) continue;
		dfs(v, u, d2s + dist);
	}
}

void dfs_for_d(int x, int fa, int tar){
	if(flag) return;
	for(int i = h[x]; i != -1; i = ne[i]){
		int v = e[i];
		if(flag) return;
		if(v == fa) continue;
		if(v == tar){
			fr[x] = v;
			flag = true;
			return;
		}
		
		fr[x] = v;
		dfs_for_d(v, x, tar);
		if(flag) return;
	}
}

void dp(int x, int fa){
	for(int i = h[x]; i != -1; i = ne[i]){
		int j = e[i];
		if(j == fa) continue;
		dp(j, x);
		ans = max(ans, d[x] + d[j] + w[i]);
		d[x] = max(d[x], d[j] + w[i]);
	}
}

int main(){
	n = read(), k =read();
	memset(h, -1, sizeof h);
	
	for(int i = 0; i < n - 1; i ++ ){
		int a, b;
		a = read(), b = read();
		add(a, b); add(b, a);
	}
	
	dfs(1, 0, 0);
	maxdis = 0, st = maxv; 
	dfs(maxv, 0, 0);
	ed = maxv;
	
	l1 = maxdis;
	
	if(k == 1){
		cout << 2 * (n - 1) - l1 + 1;
		return 0;
	}
	
	dfs_for_d(st, 0, ed);
	
	for(int i = st; i != ed; i = fr[i]){
		mp[i] = 1;
	}mp[ed] = 1;
	
	for(int i = 1; i <= n; i ++ ){
		if(mp.count(i) == 1){
			for(int j = h[i]; j != -1; j = ne[j]){
				int ver = e[j];
				if(mp.count(ver) == 1){
					w[j] = -1;
				}
			}
		}
	} 
	
	dp(1, 0);
	
	cout << 2 * n - l1 - ans << endl;
	
	return 0;
}

