#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef pair<int, int> PII;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int n, p, k;

inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

void add(int a, int b, int c){
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void bidirect(int a, int b, int c){
	add(a, b, c), add(b, a, c);
}

void dijkstra(int s){
	memset(dist, 0x3f, sizeof dist);
	priority_queue<PII, vector<PII>, greater<PII>> heap;
	dist[s] = 0;
	heap.push({0, s});
	while(heap.size()){
		auto t = heap.top();
		heap.pop();
		int ver = t.second;
		
		if(st[ver]) continue;
		st[ver] = true;
		for(int i = h[ver]; i != -1; i = ne[i]){
			int j = e[i];
			if(dist[j] > max(dist[ver], w[i])){
				dist[j] = max(dist[ver], w[i]);
				if(!st[j]){
					heap.push({dist[j], j});
				}
			}
		}
	}
}

int main(){
	memset(h, -1, sizeof h);
	n = read(), p = read(), k = read();
	
	for(int i = 0; i < p ; i ++ ){
		int a = read(), b = read(), c = read();
		bidirect(a, b, c);
		for(int j = 1; j <= k; j ++ ){
			add(a + (j - 1) * n, b + j * n, 0);
			add(b + (j - 1) * n, a + j * n, 0);
			bidirect(a + j * n, b + j * n, c);
		}
	}
	
	int st = 1, ed = n;
	dijkstra(1);
	
	if(dist[ed + k * n] < 1000000) cout << dist[ed + k * n] << endl;
	else cout << -1 << endl;
	return 0;
}
