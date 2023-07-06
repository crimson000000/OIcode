#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;

int q[N];//序列 

int rev[N];//用来存储翻转的序列 

int find(int l,int r,int x){
	while(l<r){
		int mid=l+r+1>>1;
		if(q[mid]<x) l=mid;
		else r=mid-1;
	}
	return l;
} 

int main(){
	int m;
	cin>>m;
	for(int i=0;i<m;i++) scanf("%d",&q[i]);
	
	cout<<find(0,m-1,5);
	return 0; 
}
