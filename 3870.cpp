#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct segmenttree{
	int l, r;
	int dat;
	bool invert;
}t[N * 4];
char a[N];
int n, m;

void build(int p, int l, int r){
	t[p].l = l, t[p].r = r;
	if(l == r){
		t[p].dat = 0;
		t[p].invert = false;
		return;
	}
	int mid = l + r >> 1;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	
	t[p].dat = t[p * 2 + 1].dat + t[p * 2].dat;
}

void spread(int p){
	if(t[p].invert){
		t[p * 2].dat = (t[p * 2].r - t[p * 2].l + 1) - t[p * 2].dat;
		t[p * 2 + 1].dat = (t[p * 2 + 1].r - t[p * 2 + 1].l + 1) - t[p * 2 + 1].dat;
		t[p * 2].invert ^= t[p].invert;
		t[p * 2 + 1].invert ^= t[p].invert;
		t[p].invert = false;
	}
}

void change(int p, int l, int r){
	if(t[p].l >= l && t[p].r <= r){
		t[p].invert ^= 1;
		t[p].dat = t[p].r - t[p].l + 1 - t[p].dat;
		return;
	}
	
	spread(p);
	int mid = t[p].l + t[p].r >> 1;
	if(r > mid) change(p * 2 + 1, l, r);
	if(l <= mid) change(p * 2, l, r);
	
	t[p].dat = t[p * 2].dat + t[p * 2 + 1].dat;
}

int ask(int p, int l, int r){
	if(t[p].l >= l && t[p].r <= r) return t[p].dat;
	
	spread(p);
	int mid = t[p].l + t[p].r >> 1;
	int val = 0;
	if(l <= mid) val += ask(p * 2, l, r);
	if(r > mid) val += ask(p * 2 + 1, l, r);
	return val;
}

int main(){
	scanf("%d%d", &n, &m);
	
	build(1, 1, n);
	
	while(m -- ){
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 0){
			change(1, l, r);
		}else{
			cout << ask(1, l, r) << endl;
		}
	}
	
	return 0;
}
