#include<iostream>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
#define SORTSIZE 20000
using namespace std;

double Times()
{
	SYSTEMTIME ti;
	GetLocalTime(&ti);
	return ti.wMilliseconds;
}

int main()
{
	double t1,t2;
	t1=Times();
	
	int i,max,t,*sort;
	sort=new int[SORTSIZE];
	
	fstream f;
	f.open("测试数据正.txt",ios::in);
	if(!f)
	{
		cout<<"open error"<<endl;
		exit(0);
	}
	for(i=0;i<SORTSIZE;i++)
	f>>sort[i];
	for(int j=0;j<SORTSIZE;j++)
	{
		max=sort[0];
		for(i=0;i<SORTSIZE-j;i++)
			if(sort[i]>=max)
			{
				max=sort[i];
				t=i;
			}
		sort[t]=sort[i-1];
		sort[i-1]=max;	
	}
//	for(i=0;i<SORTSIZE;i++)
//	cout<<sort[i]<<" ";
	delete []sort; 
	f.close();
	t2=Times();
	cout<<"共用时"<<t2-t1<<"毫秒"<<endl;
	return 0;
}
