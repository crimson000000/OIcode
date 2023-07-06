#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100010];
ll n, m, p, t;

ll qmi(ll a, ll k, ll p){
	ll res = 1;
	while(k){
		if(k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}

ll C(ll n, ll m){
	if(m > n) return 0;
	return ((a[n] * qmi(a[m], p - 2, p)) % p * qmi(a[n - m], p - 2, p) % p);
}

ll lucas(ll n, ll m){
	if(!m) return 1;
	return C(n % p, m % p) * lucas(n / p, m / p) % p;
}

int main(){
	cin >> t;
	
	while(t -- ){
		cin >> n >> m >> p;
		a[0] = 1;
		for(int i = 1; i <= p; i ++ ) a[i] = a[i - 1] * i % p;
		cout << lucas(n + m, n) << endl;
	}
}
