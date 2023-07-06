#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct segmenttree{
	int l, r;
	ll sum, add;
}t[4 * N];
int n, m;

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

void spread(int p){
	if(t[p].add){
		t[p * 2].sum += t[p].add * (t[p * 2].r - t[p * 2].l + 1);
		t[p * 2 + 1].sum += t[p].add * (t[p * 2 + 1].r - t[p * 2 + 1].l + 1);
		t[p * 2].add += t[p].add;
		t[p * 2 + 1].add += t[p].add;
		t[p].add = 0;
	}
}

void change(int p, int l, int r, ll val){
	if(l <= t[p].l && r >= t[p].r){
		t[p].sum += val * (t[p].r - t[p].l + 1);
		t[p].add += val;
		return;
	}
	spread(p);
	int mid = (t[p].l + t[p].r) / 2;
	if(l <= mid) change(p * 2, l, r, val);
	if(r > mid)	change(p * 2 + 1, l, r, val);
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
	scanf("%d%d", &n, &m);
	
	build(1, 1, n);
	
	while(m -- ){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int a, b;
			ll k;
			scanf("%d%d%lld", &a, &b, &k);
			change(1, a, b, k);
		}
		else{
			int a, b;
			scanf("%d%d", &a, &b);
			cout << ask(1, a, b) << endl;
		}	
	}
	
	return 0;
}
