#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int p[N];
bool st[N];
int t, n;
pair<int, int> un[N];
unordered_map<int, int> h;
int cnt, tot;

int find(int x){
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
}

int main(){
	scanf("%d", &t);
	
	while(t -- ){
		h.clear();
		cnt = tot = 1;
		scanf("%d", &n);
		bool flag = true;
		
		for(int i = 1; i <= n * 2; i ++ ) p[i] = i;
		
		for(int i = 0; i < n; i ++ ){
			int a, b, e;
			scanf("%d%d%d", &a, &b, &e);
			
			if(h.find(a) == h.end()) h[a] = cnt ++;
			if(h.find(b) == h.end()) h[b] = cnt ++;
			
			int ha = h[a], hb = h[b];
			
			if(e == 1){
				p[find(ha)] = p[find(hb)];
			}
			else{
				un[tot ++] = {ha, hb};
			}	
		}
		
		for(int i = 1; i < tot; i ++ ){
			int x = un[i].first, y = un[i].second;
			
			if(find(x) == find(y)) {
				flag = false;
				break;
			}
		}
		
		if(flag) puts("YES");
		else puts("NO");
	}
	
	return 0;
}
