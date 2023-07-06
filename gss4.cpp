/*#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct segmenttree{
	int l, r;
	ll sum;
	bool tag;
}t[4 * N];
ll a[N];
int n, m, cnt = 1;

inline ll read(){
	register ll x = 0;
	register bool f = 0;
	register char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}

inline void pushup(int p){
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
	if(t[p * 2].tag && t[p * 2 + 1].tag) t[p].tag = true;
	else t[p].tag = false;
}

void build(int p, int l, int r){
	t[p].l = l, t[p].r = r;
	if(l == r){
		t[p].sum = a[l];
		if(a[l] == 0 || a[l] == 1) t[p].tag = true;
		else t[p].tag = false;
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	pushup(p);
}

void change(int p, int l, int r){
	if(t[p].l == t[p].r){
		t[p].sum = sqrt(t[p].sum);
		if(t[p].sum == 0 || t[p].sum == 1) t[p].tag = true;
		return;
	}

	int mid = (t[p].l + t[p].r) / 2;
	if(l <= mid && !t[p * 2].tag) change(p * 2, l, r);
	if(r > mid && !t[p * 2 + 1].tag) change(p * 2 + 1, l, r);
	pushup(p);
}

ll ask(int p, int l, int r){
	if(l <= t[p].l && r >= t[p].r) return t[p].sum;

	int mid = (t[p].l + t[p].r) / 2;
	ll val = 0;
	if(l <= mid) val += ask(p * 2, l, r);
	if(r > mid) val += ask(p * 2 + 1, l, r);
	return val;
}

int main(){
	int _case = 0;
	while(~scanf("%d", &n)){
		printf("Case #%d:\n",++_case);
		memset(a, 0, sizeof(a));
		memset(t, 0, sizeof(t));
		for(int i = 1; i <= n; i ++ ) a[i] = read();
		build(1, 1, n);
		int op;
		m = read();
		while(m --){
			scanf("%d", &op);
			int l, r;
			scanf("%d%d", &l, &r);
			if(l > r) swap(l, r);
			if(op == 0){
				change(1, l, r);
			}
			else{
				printf("%lld\n", ask(1, l, r));
			}		
		}
		
		puts("");
	}
	
	return 0;
}*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct segmenttree{
	int l, r;
	ll sum;
	bool tag;
}t[4 * N];
ll a[N];
int n, m, cnt = 1;

inline ll read(){
	register ll x = 0;
	register bool f = 0;
	register char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}

inline void pushup(int p){
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
	if(t[p * 2].tag && t[p * 2 + 1].tag) t[p].tag = true;
	else t[p].tag = false;
}

void build(int p, int l, int r){
	t[p].l = l, t[p].r = r;
	if(l == r){
		t[p].sum = a[l];
		if(a[l] == 0 || a[l] == 1) t[p].tag = true;
		else t[p].tag = false;
		return;
	}
	int mid = (l + r) / 2;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
	pushup(p);
}

void change(int p, int l, int r){
	if(t[p].l == t[p].r){
		t[p].sum = sqrt(t[p].sum);
		if(t[p].sum == 0 || t[p].sum == 1) t[p].tag = true;
		return;
	}

	int mid = (t[p].l + t[p].r) / 2;
	if(l <= mid && !t[p * 2].tag) change(p * 2, l, r);
	if(r > mid && !t[p * 2 + 1].tag) change(p * 2 + 1, l, r);
	pushup(p);
}

ll ask(int p, int l, int r){
	if(l <= t[p].l && r >= t[p].r) return t[p].sum;

	int mid = (t[p].l + t[p].r) / 2;
	ll val = 0;
	if(l <= mid) val += ask(p * 2, l, r);
	if(r > mid) val += ask(p * 2 + 1, l, r);
	return val;
}

int main(){
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ ) a[i] = read();
	build(1, 1, n);
	int op;
	m = read();
	while(m --){
		scanf("%d", &op);
		int l, r;
		scanf("%d%d", &l, &r);
		if(l > r) swap(l, r);
		if(op == 0){
			change(1, l, r);
		}
		else{
			printf("%lld\n", ask(1, l, r));
		}		
	}
	
	return 0;
}