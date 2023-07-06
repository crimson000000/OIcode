#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) x & -x
typedef long long ll;
const int N = 1e5 + 10;
ll a[N], b[N], c[N];
int n, m;

void print(ll a[]){
	for(int i = 1; i <= n; i ++ ) cout << a[i] << " ";
	
	puts("-------");
}

void add(ll a[], int x, ll val){
	for(int i = x; i <= n; i += lowbit(i)){
		a[i] += val;
	}
}

ll ask(ll a[], ll x){
	auto ans = 0;
	
	for(; x; x -= lowbit(x)){
		ans += a[x];
	}
	
	return ans;
}

void exadd(int l, int r, ll val){
	add(b, l, val); add(b, r + 1, -val);
	add(c, l, val * (l - 1)); add(c, r + 1, - val * r); 
}

ll exask(int l, int r){
	return (r * ask(b, r) - (l - 1) * ask(b, l - 1)) - (ask(c, r) - ask(c,l - 1));
}

int main(){
	scanf("%d%d", &n, &m);
	
	for(int i = 1; i <= n; i ++ ){
		scanf("%lld", &a[i]);
		add(b, i, a[i] - a[i - 1]);
		add(c, i, (a[i] - a[i - 1]) * (i - 1));
	}
//	print(b), print(c);
		
	while(m -- ){
		int op, l, r, k;
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d%d", &l, &r, &k);
			
			exadd(l, r, k);
//			print(b), print(c);
		}
		else if(op == 2){
			scanf("%d%d", &l, &r);
			
			cout << exask(l, r) << endl;
		}
	}
}
