#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int q[N];//���� 

void qsort(int q[],int l,int r){
	if(l>=r) return;//�ݹ��յ� 
	int s=q[l+r>>1],i=l-1,j=r+1;//sΪ��׼ֵ��iΪ��ָ�룬jΪ��ָ�� 
	while(i<j){
		do i++;while(q[i]<s);
		do j--;while(q[j]>s);
		if(i<j) swap(q[i],q[j]);//�������򣬽��� 
	}
	qsort(q,l,j);qsort(q,j+1,r);//�ݹ鴦���������� 
} 

int main(){
	int m;
	cin>>m;
	for(int i=0;i<m;i++) scanf("%d",&q[i]);
	qsort(q,0,m-1);
	for(int i=0;i<m;i++) printf("%d ",q[i]);
	return 0; 
}
