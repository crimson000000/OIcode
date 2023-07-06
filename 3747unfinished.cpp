#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct segmenttree{
	int l, r;
	ll sum;
}t[4 * N];
int n, m, p, c;

ll qmi(ll a, ll b, ll p){
	ll ans = 1;
	while(b){
		if(b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}

void build(int p, int l, int r){
	t[p].l = l, t[p].r = r;
	if(l == r){
		ll h;
		scanf("%lld", &h);
		t[p].sum = h;
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
}

void change(int p, int l, int r){
	if(l == r){
		t[p].sum = qmi(c, t[p].sum, p);
		return;
	}
	spread(p);
	int mid = (t[p].l + t[p].r) / 2;
	if(l <= mid) change(p * 2, l, r);
	if(r > mid)	change(p * 2 + 1, l, r);
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
}

ll ask(int p, int l, int r){
	if(l <= t[p].l && r >= t[p].r) return t[p].sum;
	
	spread(p);
	int mid = (t[p].l + t[p].r) / 2;
	ll val = 0;
	if(l <= mid) val += ask(p * 2, l, r);
	if(r > mid) val += ask(p * 2 + 1, l, r);
	return val;
}

int main(){
	scanf("%d%d%d%d", &n, &m, &p, &c);
	
	build(1, 1, n);
	
	while(m -- ){
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(l > r) swap(l, r);
		if(op == 1){
			change(1, l, r); 
		}
		else{
			
		}
	}
}
