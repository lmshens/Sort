#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<ctime>
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
	
	int i,t,*sort;
	sort=new int[SORTSIZE];

	fstream f;
	f.open("测试数据逆.txt",ios::in);
	if(!f)
	{
		cout<<"open error"<<endl;
		exit(0);
	}
	for(i=0;i<SORTSIZE;i++)
		f>>sort[i];
	for(int j=0;j<SORTSIZE-1;j++)
	{
		for(i=0;i<SORTSIZE-j+1;i++)
		{
			if(sort[i]>sort[i+1])
			{
				t=sort[i];sort[i]=sort[i+1];sort[i+1]=t;
			}
		}
	}
//	for(i=0;i<SORTSIZE;i++)
//	cout<<sort[i]<<" ";
	delete []sort;
	f.close();
	t2=Times();
	cout<<"共用时"<<t2-t1<<"毫秒"<<endl;
	return 0;
}
