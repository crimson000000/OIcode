#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,P=131;
typedef unsigned long long ULL;
ULL p[N];
string s[N];
ULL gethash(string a){
	int l=a.size();
//	cout<<l<<endl;
	ULL h=0;
	for(int i=0;i<l;i++){
		h=h*P+a[i];
//		cout<<h<<endl;
	}
	return h;
}
int m;
vector<ULL> cnt;
int main(){
	p[0]=1;
	cin>>m;
	for(int i=1;i<=2000;i++) p[i]=p[i-1]*P;
//	for(int i=1;i<=2000;i++) cout<<p[i]<<endl;;
	for(int i=0;i<m;i++){
		cin>>s[i];
		cnt.push_back(gethash(s[i]));
	}
	sort(cnt.begin(),cnt.end());
	cnt.erase(unique(cnt.begin(),cnt.end()),cnt.end());
	cout<<cnt.size()<<endl;
	return 0;
}
