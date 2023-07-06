#include <bits/stdc++.h>
using namespace std;
const int N= 5e5 + 10;
struct SegmentTree{
	int l, r;
	int lmax, rmax;
	int dat, sum;
}t[4 * N];
int n, q, h;

void build(int p, int l, int r){
	t[p].l = l, t[p].r = r;
	if(l == r){
		scanf("%d", &h);
		t[p].lmax = t[p].rmax = t[p].sum = t[p].dat = h;
		return;
	}
	
	int mid = (l + r) >> 1;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
	t[p].lmax = max(t[p * 2].lmax, t[p * 2].sum + t[p * 2 + 1].lmax);
	t[p].rmax = max(t[p * 2 + 1].rmax, t[p * 2].rmax + t[p * 2 + 1].sum);
	t[p].dat = max(max(t[p * 2].dat, t[p * 2 + 1].dat), t[p * 2].rmax + t[p * 2 + 1].lmax);
}

void change(int p, int x, int val){
	if(t[p].l == x && t[p].r == x){
		t[p].lmax = t[p].rmax = t[p].sum = t[p].dat= val;
		return;
	}
	
	int mid = (t[p].l + t[p].r) >> 1;
	if(x <= mid) change(p * 2, x, val);
	else change(p * 2 + 1, x, val);
	
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
	t[p].lmax = max(t[p * 2].lmax, t[p * 2].sum + t[p * 2 + 1].lmax);
	t[p].rmax = max(t[p * 2 + 1].rmax, t[p * 2].rmax + t[p * 2 + 1].sum);
	t[p].dat = max(max(t[p * 2].dat, t[p * 2 + 1].dat), t[p * 2].rmax + t[p * 2 + 1].lmax);
}

SegmentTree ask(int p, int l, int r){
	if(l <= t[p].l && r >= t[p].r) {
		return t[p];
	}
	
	int mid = (t[p].l + t[p].r) >> 1;
	if(r <= mid) return ask(p * 2, l, r);
	else if(l > mid) return ask(p * 2 + 1, l, r);
	
	SegmentTree a, b, ans;
	a = ask(p * 2, l, r), b = ask(p * 2 + 1, l, r);
	ans.dat = max(max(a.dat, b.dat), a.rmax + b.lmax);
	ans.lmax = max(a.lmax, a.sum + b.lmax);
	ans.rmax = max(b.rmax, b.sum + a.rmax); 
	
	return ans;
}

int main(){
	scanf("%d", &n);
	
	build(1, 1, n);
	
	scanf("%d", &q);
	while(q -- ){
		int l, r;
		scanf("%d%d", &l, &r);
		if(l > r) swap(l, r);
		SegmentTree ans = ask(1, l, r);
		cout << ans.dat << endl;
	}
	return 0;
}
