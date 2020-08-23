#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#include<windows.h>
#include<time.h>
using namespace std;
vector<int>ve[200];
int W[105][105][105],n;
int Lx[105],Ly[105];
int Left[1005],lea[11],leanow[20][105],e;
bool S[1005],T[1005],zz[100];
string nam[70];
int xh[70][70],blosz[20],nblo,ngrp,bl[105],tot[100];
int cantchoose[20][105],nzznow[105];
void sc(string s){
	int ls=s.length();
	for(int i=0;i<ls;i++)cout<<s[i],Sleep(30);
}
bool match(int i,int k) {
	S[i]=1;
	for(int j=1; j<=blosz[k]; j++) {
//	cout<<i<<"I "<<j<<"J "<<Lx[i]+Ly[j]<<" "<<W[i][j]<<endl;
		if(Lx[i]+Ly[j]==W[k][i][j]&&!T[j]) {
			T[j]=1;

			if(!Left[j]||match(Left[j],k)) {

//				cout<<j<<"j "<<Left[j]<<" ";
//				cout<<i<<"i\n";

				Left[j]=i;
				return 1;
			}

		}
	}
	return 0;
}
void update(int k) {
	int a=inf;
	for(int i=1; i<=blosz[k]; i++)
		if(S[i])
			for(int j=1; j<=blosz[k]; j++)
				if(!T[j]) {
					a=min(a,Lx[i]+Ly[j]-W[k][i][j]);
				}
	for(int i=1; i<=blosz[k]; i++) {
		if(S[i])Lx[i]-=a;
		if(T[i])Ly[i]+=a;
	}
}
void KM(int k) {

	for(int i=1; i<=blosz[k]; i++) {
		Left[i]=Lx[i]=Ly[i]=0;
		for(int j=1; j<=blosz[k]; j++)
			Lx[i]=max(Lx[i],W[k][i][j]);
	}

	for(int i=1; i<=blosz[k]; i++) {
		for(;;) {
			for(int j=1; j<=n; j++)S[j]=T[j]=0;
			if(match(i,k))break;
			else update(k);
		}
	}
}
void initgrp() {
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=ngrp; j++) {
			if(!zz[xh[i][j]])blosz[i]++;
			else bl[xh[i][j]]=i;
		}
	for(int i=1; i<=ngrp; i++)cantchoose[bl[i]][i]=1;
}
void initW(int k) {
	int sum=0;
	for(int i=1; i<=nblo; i++)if(bl[lea[k]]!=i) {
			int p=++nzznow[i],l=0;
			leanow[i][p]=lea[k];
//			cout<<i<<"i "<<p<<"p "<<k<<"k "<<lea[k]<<endl;; 
			for(int j=1; j<=ngrp; j++) {
				if(!zz[xh[i][j]])cin>>W[i][p][++l],sum++;
				
			}
	}
//	cout<<sum<<"sum\n";
}

void pb(int k) {
//	int tot=0;
	int l=0;
//	cout<<"test\n";
	for(int i=1; i<=ngrp; i++) {
		if(zz[xh[k][i]])continue;
		ve[leanow[k][Left[++l]]].push_back(xh[k][i]);
		tot[leanow[k][Left[l]]]+=W[k][Left[l]][l];
		//tot+=W[k][Left[l]][l]; 
//		cout<<leanow[k][Left[l]]<<endl;
//		cout<<nam[leanow[k][Left[l]]]<<" "<<nam[xh[k][i]]<<endl;
	}
//	cout<<tot<<endl;
}
void clr() {
	for(int i=1; i<=n; i++)S[i]=T[i]=0,Left[i]=0;
}
int main() {
	sc("请输入班级人数（包括假人）\n");
	cin>>n;
	sc("请输入小组个数\n"); 
	cin>>ngrp,nblo=n/ngrp;
	sc("请输入每位同学的姓名（按学号升序排列）\n"); 
	for(int i=1; i<=n; i++)cin>>nam[i];
	sc("请输入组长们的学号（可不按顺序排列）\n"); 
	for(int i=1; i<=ngrp; i++)cin>>lea[i],zz[lea[i]]=1;
	sc("请输入每位组长与待选组员们之间的学习效率值\n"); 
	for(int i=1; i<=nblo; i++)
		for(int j=1; j<=ngrp; j++) {
			cin>>xh[i][j];
		}
/*		for(int i=1; i<=nblo; i++)
		for(int j=1; j<=ngrp; j++)cout<<xh[i][j]<<endl;
*/	initgrp();
	for(int i=1; i<=ngrp; i++) {
//	cout<<i<<"III\n";
		initW(i);
		
	}
	for(int i=1; i<=nblo; i++)
		KM(i),pb(i),clr();
	freopen("分组.out","w",stdout);
	for(int i=1;i<=ngrp;i++){
		cout<<"第"<<i<<"组：   ";
		cout<<"组长:"<<nam[lea[i]]<<" 组员： ";
//		cout<<ve[lea[i]].size()<<"sz\n";
//	cout<<nam[ve[lea[i]][4]];
		for(int j=0;j<ve[lea[i]].size();j++)cout<<nam[ve[lea[i]][j]]<<" ";
		cout<<endl;
	}
	int likenum=0;
/*	for(int i=1;i<=ngrp;i++){
		cout<<tot[lea[i]]<<endl;
		likenum+=tot[lea[i]];
	}
	cout<<likenum;*/
}
