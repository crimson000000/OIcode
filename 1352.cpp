#include <bits/stdc++.h>
using namespace std;
const int N = 6e3 + 10;
int h[N], e[N], ne[N], idx;
int happy[N];
int f[N][2];
int in[N];
int n, root;

void dp(int root){
	f[root][1] = happy[root];
	for(int i = h[root]; i != -1; i = ne[i]){
		int j = e[i];
		dp(j);
		
		f[root][0] += max(f[j][0], f[j][1]);
		f[root][1] += f[j][0];
	}
	
}

void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int main(){
	memset(h, -1, sizeof h);
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i ++ ) scanf("%d", &happy[i]);
	
	for(int i = 0; i < n - 1; i ++ ){
		int a, b;
		scanf("%d%d", &a, &b);
		add(b, a);
		in[a] ++;
	}
	
	int root = 1;
	for(int i = 1; i <= n; i ++ ){
		if(!in[i]){
			root = i;
			break;
		}
	}
	
	dp(root);
	
	printf("%d", max(f[root][0], f[root][1]));
	
	return 0;
}
