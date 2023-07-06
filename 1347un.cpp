#include <bits/stdc++.h>
using namespace std;
const int N = 30;
int n, m;
int d[N];
int h[N], e[N], ne[N], idx;
int q[100], hh, tt = -1;

void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int topsort(){
	int temp = 0, f = 0;
	for(int i = 0; i < n; i ++ ){
		if(d[i] == 0) q[++ tt] = i;
		temp ++;
	}
	if(temp > 1) f = 1;
	while(tt <= hh){
		for(int i = h[q[hh ++ ]]; i != -1; i = ne[i]){
			d[e[i]] --;
			if(d[e[i]] == 0){
				q[++ tt] = e[i];
				temp ++;
			}
			
		}
		if(temp > 1) f = 1;
	}
	if(tt != n - 1) return -1;
	else if(f == 1) return 0;
	else return 1;
}

int main(){
	memset(h, -1,sizeof h);
	cin >> n >> m;
	
	for(int i = 0; i < m; i ++ ){
		char op[5];
		scanf("%s", op);
		int first = op[0]-'0', second = op[2]-'0';
		add(first, second);
		d[first] ++;
	}
	
}
