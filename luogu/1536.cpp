#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int p[N];
bool vis[N];
int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
int n, m;

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

int main(){
    while(n = read()){
        m = read();
        int res = n;
        for(int i = 1; i <= n; i ++ ) p[i] = i;
        for(int i = 0; i < m; i ++ ){
            int a = read(), b = read();
            
            a = find(a), b = find(b);
            if(a != b){
                res --;
                p[find(a)] = find(b);
            }
        }
        cout << res - 1 << endl;
    }
}