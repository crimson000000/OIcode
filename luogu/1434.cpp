#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int h[N][N];
int f[N][N];
int n, m;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int dp(int x, int y){
	if(f[x][y] != -1) return f[x][y];
	
	f[x][y] = 1;
	
	for(int i = 0; i < 4; i ++ ){
		int a = x + dx[i], b = y + dy[i];
		
		if(a >= 1 && a <= n && b >= 1 && b <= m && h[a][b] < h[x][y]){
			f[x][y] = max(f[x][y], dp(a, b) + 1);
		}
	}
	return f[x][y];
}

int main(){
	scanf("%d%d", &n, &m);
	memset(f, -1, sizeof f);
	for(int i = 1; i <= n; i ++ ){
		for(int j = 1; j <= m; j ++ ){
			scanf("%d", &h[i][j]);
		}
	}
	
	int res = 0;
	for(int i = 1; i <= n; i ++ ){
		for(int j = 1; j <= m; j ++ ){
			res = max(res, dp(i, j));
		}
	}
	
	cout << res << endl;
	return 0;
}
