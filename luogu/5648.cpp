#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
ll a[N], lastans = 0;
ll f[N][21];
int n, m;

void ST_pre() {
	int t = log(n) / log(2) + 1;

	for (register int j = 1; j < t; j ++)
		for (register int i = 1; i <= n - (1 << j) + 1; i ++)
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

ll query(int l, int r) {
	int k = log(r - l + 1) / log(2);
	return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main(){
	scanf("%d%d", &n, &m);
	
	for(int i = 1; i <= n; i ++ ) scanf("%lld", &a[i]);
	
	for(int i = 1; i <= n; i ++ ) f[i][0] = a[i];
	
	ST_pre();
	
	while(m --){
		int u, v;
		scanf("%d%d", &u, &v);
		int l = 1 + (u ^ lastans) % n, q = (v ^ (lastans + 1)) % (n - l + 1);
		int r = l + q - 1;
		
		ll ans = 0;
		for(int i = l; i <= r; i ++ ){
			ans += query(l, i);
		}
		
		lastans = ans;
		cout << ans << endl;
	}
	
	return 0;
}
