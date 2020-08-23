#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int W[1005][1005],n;
int Lx[1005],Ly[1005];
int Left[1005],lea[11],lea6[11],e;
bool S[1005],T[1005],zy[100],zz[100];
string nam[70];
int grpnum,xh[70];
bool match(int i) {
	S[i]=1;
	for(int j=1; j<=grpnum; j++) {
//	cout<<i<<"I "<<j<<"J "<<Lx[i]+Ly[j]<<" "<<W[i][j]<<endl;
		if(Lx[i]+Ly[j]==W[i][j]&&!T[j]) {  
			T[j]=1;

			if(!Left[j]||match(Left[j])) {

//				cout<<j<<"j "<<Left[j]<<" ";
//				cout<<i<<"i\n";

				Left[j]=i;
				return 1;
			}
			
		}
	}return 0;
}
void update() {
	int a=inf;
	for(int i=1; i<=grpnum; i++)
		if(S[i])
			for(int j=1; j<=grpnum; j++)
				if(!T[j]) {
					a=min(a,Lx[i]+Ly[j]-W[i][j]);
				}
	for(int i=1; i<=grpnum; i++) {
		if(S[i])Lx[i]-=a;
		if(T[i])Ly[i]+=a;
	}
}
void KM() {

	for(int i=1; i<=grpnum; i++) {
		Left[i]=Lx[i]=Ly[i]=0;

		for(int j=1; j<=grpnum; j++)
			Lx[i]=max(Lx[i],W[i][j]);
	}
	for(int i=1; i<=grpnum; i++) {
		for(;;) {
			for(int j=1; j<=n; j++)S[j]=T[j]=0;
			if(match(i))break;
			else update();
		}
	}
}
void init() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>nam[i];
	}
	for(int i=1; i<=10; i++) {
		cin>>lea[i];
		zz[lea[i]]=1;
	}
	cin>>grpnum;
	for(int j=1; j<=10; j++)cin>>xh[j],zy[xh[j]]=1;
	for(int i=1; i<=10; i++)if(!zy[lea[i]])lea6[++e]=lea[i];
//	cout<<e<<"e\n";
	for(int i=1; i<=e; i++) {
		for(int j=1; j<=grpnum; j++)cin>>W[i][j];
	}
}
void out() {
	int l=0;
	for(int i=1; i<=10; i++) {
		if(zz[xh[i]])continue;
		cout<<endl;
		l++;
		cout<<nam[lea6[Left[l]]]<<" "<<nam[xh[i]]<<endl;
	}
}
int main() {
	init();
	KM();
	out();
}
/*
60
Ð»Íò³Ç
Ã·ÐñÓî
ÑîË¼º­
ãÉÎÄèº
ÌïË¼Óê
ÑÏ¼ÑÂ×
ÕÅÓðÏè
¹ùÈÊ½Ü
ÍõÈðç÷
¸µÀÖö©
×ÞîÚç÷
³Âê»È»
Îâ¿ÉÍû
¹¶ìÓìÓ
Ô¬×Ó¾û
ÃÏÔÆÀÖ
ÕÔÓî°º
³ÂÏèÓî
È«×Ïâù
¹ËÐÄâù
Ðíî£ÐÇ
ÍõÏÈÖ¾
ÎâÓîÏü
ÑîºÆ¶¬
Ïò½ø
³Â¾ýºÀ
ËïÎÄÐÀ
ÑÏãÉÐÀ
ÁúÔ¬½¿
ÖÜË¼âù
ÕÂµÂÔª
Í¯Ö¾³É
Àî¼ÑÞ±
ÕÔ¿ÉÜ°
ÕÔÖ¾½Ü
ºú³½Óê
²ÌÃÈ
ÁõêÊ³½
ËïÖÙÓñ
Àî¼Òçâ
ÍõºãÓî
ÇÇ´ººÀ
ÁõÓê
ÄôÀöæÃ
ÃÏÖ®ÖÛ
Ì·»ã
ÖÜÎ¨ÒÕ
Áõ¿¬Óú
ÕÅÃÎæÃ
Ñî¾°Ë¬
À×ÀÚ
ÀîÔÆê»
ËÕº­
ÌÆÖ¾³Ð
ÎÂ¿¡ÒÝ
Àî×ÔÏè
Íõ­Zãü
ÎâÐÂÖÞ
Â³¿­Íþ
¼ÙÈË
7
12
6
54
52
15
18
30
23
58

6
4
1
2
5
7
12
10
3
6
54

4 
7 
3 
2 
10 
9 


10 
2 
7 
6 
1 
8 


10 
5 
3 
9 
1 
6 


2 
4 
9 
6 
3 
8 


2 
1 
9 
5 
10 
6 


7 
6 
4 
3 
9 
2 


*/
/*
60
Ð»Íò³Ç
Ã·ÐñÓî
ÑîË¼º­
ãÉÎÄèº
ÌïË¼Óê
ÑÏ¼ÑÂ×
ÕÅÓðÏè
¹ùÈÊ½Ü
ÍõÈðç÷
¸µÀÖö©
×ÞîÚç÷
³Âê»È»
Îâ¿ÉÍû
¹¶ìÓìÓ
Ô¬×Ó¾û
ÃÏÔÆÀÖ
ÕÔÓî°º
³ÂÏèÓî
È«×Ïâù
¹ËÐÄâù
Ðíî£ÐÇ
ÍõÏÈÖ¾
ÎâÓîÏü
ÑîºÆ¶¬
Ïò½ø
³Â¾ýºÀ
ËïÎÄÐÀ
ÑÏãÉÐÀ
ÁúÔ¬½¿
ÖÜË¼âù
ÕÂµÂÔª
Í¯Ö¾³É
Àî¼ÑÞ±
ÕÔ¿ÉÜ°
ÕÔÖ¾½Ü
ºú³½Óê
²ÌÃÈ
ÁõêÊ³½
ËïÖÙÓñ
Àî¼Òçâ
ÍõºãÓî
ÇÇ´ººÀ
ÁõÓê
ÄôÀöæÃ
ÃÏÖ®ÖÛ
Ì·»ã
ÖÜÎ¨ÒÕ
Áõ¿¬Óú
ÕÅÃÎæÃ
Ñî¾°Ë¬
À×ÀÚ
ÀîÔÆê»
ËÕº­
ÌÆÖ¾³Ð
ÎÂ¿¡ÒÝ
Àî×ÔÏè
Íõ­Zãü
ÎâÐÂÖÞ
Â³¿­Íþ
¼ÙÈË
7
12
6
54
52
15
18
30
23
58

8
52
26
11
20
9
39
15
14
16
21


10 
2 
4 
6 
9 

5 
3 
7 




2 
3 
6 
4 
9 

8 
1 
10 



3 
1 
6 
7 
10 

8 
5 
4 




2 
1 
6 
10 
3 

8 
4 
7 




1 
7 
9 
3 
4 

8 
6 
10 




5 
2 
1 
10 
9 

3 
7 
6 




8 
7 
6 
3 
4 

10 
9 
5 




8 
9 
3 
2 
1 

7 
4 
5 
*/
