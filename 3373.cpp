#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct segmenttree{
	int l, r;
	ll sum, add;
	ll mul;
}t[4 * N];
ll a[N];
int n, m, M;

void build(int p, int l, int r){
	t[p].l = l, t[p].r = r, t[p].mul = 1;
	if(l == r){
		t[p].sum = a[l] % M;
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
	t[p].sum %= M;
}

void spread(int p){
	t[p * 2].sum = (t[p].mul * t[p * 2].sum + (t[p * 2].r - t[p * 2].l + 1) * t[p].add) % M;
	t[p * 2 + 1].sum = (t[p].mul * t[p * 2 + 1].sum + (t[p * 2 + 1].r - t[p * 2 + 1].l + 1) * t[p].add) % M;
	
	t[p * 2].mul = t[p * 2].mul * t[p].mul % M;
	t[p * 2 + 1].mul = t[p * 2 + 1].mul * t[p].mul % M;
	
	t[p * 2].add = (t[p * 2].add * t[p].mul + t[p].add) % M;
	t[p * 2 + 1].add = (t[p * 2 + 1].add * t[p].mul + t[p].add) % M;
	
	t[p].add = 0, t[p].mul = 1;
}

void change_add(int p, int l, int r, ll val){
	if(l <= t[p].l && r >= t[p].r){
		t[p].sum += val * (t[p].r - t[p].l + 1);
		t[p].add += val;
		t[p].sum %= M, t[p].add %= M;
		return;
	}
	spread(p);
	int mid = (t[p].l + t[p].r) / 2;
	if(l <= mid) change_add(p * 2, l, r, val);
	if(r > mid)	change_add(p * 2 + 1, l, r, val);
	t[p].sum = (t[p * 2].sum + t[p * 2 + 1].sum) % M;
}

void change_mul(int p, int l, int r, ll val){
	if(l <= t[p].l && r >= t[p].r){
		t[p].sum = t[p].sum * val % M;
		t[p].add = t[p].add * val % M;
		t[p].mul = t[p].mul * val % M;
		return;
	}
	spread(p);
	int mid = (t[p].l + t[p].r) / 2;
	if(l <= mid) change_mul(p * 2, l, r, val);
	if(r > mid) change_mul(p * 2 + 1, l, r, val);
	t[p].sum = (t[p * 2].sum + t[p * 2 + 1].sum) % M;
}

ll ask(int p, int l, int r){
	if(l <= t[p].l && r >= t[p].r) return t[p].sum;
	
	spread(p);
	int mid = (t[p].l + t[p].r) / 2;
	ll val = 0;
	if(l <= mid) val += ask(p * 2, l, r);
	if(r > mid) val += ask(p * 2 + 1, l, r);
	val %= M;
	return val;
}

int main(){
	scanf("%d%d%d", &n, &m, &M);
	
	for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	
	build(1, 1, n);
	
	while(m -- ){
		int op, a, b;
		ll k;
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d%lld", &a, &b, &k);
			change_mul(1, a, b, k);
		}
		else if(op == 2){
			scanf("%d%d%lld", &a, &b, &k);
			change_add(1, a, b, k);
		}else{
			scanf("%d%d", &a, &b);
			if(a > b) swap(a, b);
			cout << ask(1, a, b) % M << endl;
		}
	}
	
	return 0;
}
