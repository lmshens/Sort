#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<ctime>
#include<Windows.h>
using namespace std;
#define LIST_INIT_SIZE 20000
#define LISTINCREMENT 10
typedef struct{
	int *elem;
	int length;
	int listsize;
}SqList;
//************************************************
bool CreateList(SqList &L,int e)
{
	if (!L.elem)
	{
		cout << "线性表不存在！" << endl;
		exit(0);
	}
	L.length++;
	int *l=L.elem;
	*(l+L.length-1)=e;
	return true;	
}
//************************************************
bool InitList(SqList &L)
{
	L.elem = new int[LIST_INIT_SIZE];
	if (!L.elem)
	{
		cout << "分配空间失败" << endl;
		exit(0);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return true;
}
//************************************************
bool DestoryList(SqList &L)
{
	if (!L.elem)
	{
		cout << "该表不存在" << endl;
		return false;
	}
	L.length = 0;
	L.listsize = 0;
	delete(L.elem);
	return true;
}
//*******************************************
bool ListTraverse(const SqList &L)
{
	if (!L.elem)
	{
		cout << "该表不存在" << endl;
		return false;
	}
	int *l = L.elem;
	cout<<"该表内容如下："<<endl; 
	for(int i=0;i<L.length;i++)
	{
		cout << *l << " ";
		l += 1;
	}
	return true;
}
//*************************************************
double Times()
{
	SYSTEMTIME ti;
	GetLocalTime(&ti);
	return ti.wMilliseconds;
}
//********************************
void HeadAdjust(SqList &l,int s,int m)
{
	int rc=l.elem[s];
	for(int j=2*s;j<=m;j*=2)
	{
		if(j<m && l.elem[j]<l.elem[j+1]) j++;
		if(rc>=l.elem[j]) break;
		l.elem[s]=l.elem[j];
		s=j;
	}
	l.elem[s]=rc;
} 
//*************************************************
void HeadSort(SqList &l)
{
	int t,i;
	for(i=l.length/2;i>=0;i--)
	HeadAdjust(l,i,l.length-1);
	for(i=l.length-1;i>0;i--)
	{
		t=l.elem[0];
		l.elem[0]=l.elem[i];
		l.elem[i]=t;
		HeadAdjust(l,0,i-1);
	}
}
//*************************************************

int main()
{
	int e;
	SqList l;
	InitList(l);
	fstream f;
	f.open("测试数据正.txt",ios::in);
	if(!f)
	{
		cout<<"open error"<<endl;
		exit(0);
	}
	for(int i=0;i<20000;i++)
	{
		f>>e;
		CreateList(l,e);
	}
	
	double t1,t2;
	t1=Times();
	HeadSort(l);
	t2=Times();
	cout<<"共用时"<<t2-t1<<"毫秒"<<endl; 
	
	f.close();
	DestoryList(l);
	return 0;
 } 
