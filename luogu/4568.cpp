#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int N = 2e6 + 10;
int h[110005], ne[N], w[N], e[N], idx;
/*struct Edge
{
    int to,next,cost;
}edge[2500001];
int cnt,head[110005];

void add(int u,int v,int c=0)
{
    edge[++cnt]=(Edge){v,head[u],c};
    head[u]=cnt;
}*/
int n, m, k, s, t;
bool st[N];
int dist[N];

inline int read(){
    int x = 0;
	char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
    return x;
}

inline void add(int a, int b, int c = 0){
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dijkstra(int s){
	memset(dist, 0x3f, sizeof dist);
	dist[s] = 0;
	priority_queue<PII, vector<PII>, greater<PII> > heap;
	heap.push({0, s});
	while(!heap.empty()){
		auto t = heap.top();
		heap.pop();
		int distance = t.first, ver = t.second;
		
		if(st[ver]) continue;
		st[ver] = true;
		
		for(register int i = h[ver]; i != -1; i = ne[i]){
			int j = e[i];
			if(distance + w[i]  <= dist[j]){
				dist[j] = distance + w[i];
				heap.push({dist[j], j});
			}
		}
	}
}

int main(){
	memset(h, -1, sizeof h);
	n = read(), m = read(), k = read(), s = read(), t = read();
	int a, b, c;
	for(register int i = 0; i < m; i ++ ){
		a = read(), b = read(), c = read();
		add(a, b, c);
		add(b, a, c);
		for(register int j = 1; j <= k; j ++ ){
			add(a + (j - 1) * n, b + j * n);
			add(b + (j - 1) * n, a + j * n);
			add(a + j * n, b + j * n, c);
			add(b + j * n, a + j * n, c);
		}
	}
	
	for(register int i = 1; i <= k; i ++ ){
		add(t + (i - 1) * n, t + i * n);
	}
	
	dijkstra(s);
	printf("%d", dist[t + k * n]);
	return 0;
}
