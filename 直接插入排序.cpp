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
void InsertSort(SqList &l)
{
	int i,j;
	double t1,t2;
	t1=Times();
	for(i=1;i<l.length;i++)
	if(l.elem[i]<l.elem[i-1])
	{
		int t=l.elem[i];
		l.elem[i]=l.elem[i-1];
		for(j=i-2;j>=0 && t<l.elem[j];j--)
			l.elem[j+1]=l.elem[j];
		l.elem[j+1]=t;
	}
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
	
	InsertSort(l);
	
	f.close();
	DestoryList(l);
	return 0;
}
