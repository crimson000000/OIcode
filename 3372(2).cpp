#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
ll n, m;
int pos[N], l[N], r[N];
ll sum[N], add[N], a[N];

inline ll read(){
	ll x = 0, f = 1;
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

void change(int x, int y, ll val){
	int p = pos[x], q = pos[y];
	if(p == q){
		for(int i = x; i <= y; i ++ ) a[i] += val;
		sum[p] += (y - x + 1) * val;
	}
	else{
		for(int i = p + 1; i < q; i ++ ) add[i] += val;
		for(int i = x; i <= r[p]; i ++ ) a[i] += val;
		sum[p] += val * (r[p] - x + 1);
		for(int i = l[q]; i <= y; i ++ ) a[i] += val;
		sum[q] += val * (y - l[q] + 1);
	}
}

ll ask(int x, int y){
	int p = pos[x], q = pos[y];
	ll s = 0;
	if(p == q){
		for(auto i = x; i <= y; i ++ ) s += a[i];
		return s;
	}
	else{
		for(int i = p + 1; i < q; i ++ ) s += sum[i] + add[i] * (r[i] - l[i] + 1);
		for(int i = x; i <= r[p]; i ++ ) s += a[i];
		s += add[p] * (r[p] - x + 1);
		for(int i = l[q]; i <= y; i ++ ) s += a[i];
		s += add[q] * (y - l[q] + 1);
	}
	return s;
}

int main(){
	n = read(), m = read();
	
	int t = sqrt(n);
	for(int i = 1; i <= n; i ++ ) {
		a[i] = read();
	}
	
	for(int i = 1; i <= t; i ++ ){
		l[i] = (i - 1) * t + 1;
		r[i] = i * t;
	}
	
	if(r[t] < n) t ++, r[t] = n, l[t] = r[t - 1] + 1; 
	for(int i = 1; i <= t; i ++ ){
		for(int j = l[i]; j <= r[i]; j ++ ){
			pos[j] = i;
			sum[i] += a[j];
		}
	}
	
	while(m -- ){
		ll op = read(), x, y, k;
		if(op == 1){
			x = read();
			y = read();
			k = read();
			change(x, y, k);
		}
		else{
			x = read();
			y = read();
			cout << ask(x, y) << endl;
		}
	}
	
	return 0;
}
