#include<bits/stdc++.h>
using namespace std;
const int N = 20010, M = 1e5 + 10;
int fa[N], b[N];
int n, m;

struct fight{
	int x;
	int y;
	int z;
	bool operator < (const fight& w){
		return z < w.z;
	}
}f[M];

int find(int x){
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}

bool check(int x, int y){
	x = find(x), y = find(y);
	return x == y;
}

int main(){
	scanf("%d%d", &n, &m);
	
	for(int i = 0; i < m; i ++ ){
		scanf("%d%d%d", &f[i].x, &f[i].y, &f[i].z);
	}
	
	for(int i = 1; i <= n; i ++ ) fa[i] = i;
	
	sort(f, f + m);
	
	for(int i = m - 1; i >= 0; i -- ){
		if(check(f[i].x, f[i].y)){
			cout << f[i].z << endl;
			return 0;
		} 
		int x = f[i].x, y = f[i].y;
		if(!b[x]) b[x] = y;
		else fa[find(y)] = find(b[x]);
		if(!b[y]) b[y] = x;
		else fa[find(x)] = find(b[y]);
	}
	
	cout << 0 << endl;
	return 0;
} 
