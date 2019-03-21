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
//********************************
double Times()
{
	SYSTEMTIME ti;
	GetLocalTime(&ti);
	return ti.wMilliseconds;
}
//********************************
void ShellInsert(SqList &l,int dk)
{
	int i,j;
	for(i=dk;i<l.length;i++)
	if(l.elem[i]<l.elem[i-dk])
	{
		int t=l.elem[i];
		for(j=i-dk;j>=0 && t<l.elem[j];j-=dk)
		l.elem[j+dk]=l.elem[j];
		l.elem[j+dk]=t;
	}
}
//********************************
void ShellSort(SqList &l)
{
	int k=5;
	double t1,t2;
	t1=Times();
	for(;k>0;k-=2)
	ShellInsert(l,k);
	t2=Times();
	cout<<"共用时"<<t2-t1<<"毫秒"<<endl;
}
//********************************
int main()
{
	int e;
	SqList l;
	InitList(l);
	fstream f;
	f.open("测试数据.txt",ios::in);
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
	
	ShellSort(l);
	
	f.close();
	DestoryList(l);
	return 0;
}
