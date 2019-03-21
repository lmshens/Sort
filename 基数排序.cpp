#include<fstream> 
#include<stdlib.h>
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

typedef struct QNode{
	int data;
	QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
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
bool InitQueue(LinkQueue &q)
{
	q.front=new QNode;
	if(!q.front)
	{
		cout<<"初始化失败！"<<endl;
		return false;
	}
	q.rear=q.front;
	q.rear->next=NULL;
}
//*************************************
bool DestoryQueue(LinkQueue &q)
{
	if(!q.front)
	{
		cout<<"该队列不存在！"<<endl;
		return false;
	}
	QNode *p;
	p=q.front;
	while(p)
	{
		p=q.front->next;
		delete q.front;
		q.front=p;
	}
	return true;
}
//*************************************
bool EnQueue(LinkQueue &q,int e)
{
	if(!q.front)
	{
		cout<<"该队列不存在！"<<endl;
		return false;
	}
	QNode *p=new QNode;
	if(!p)
	{
		cout<<"插入失败！"<<endl;
		return false;
	}
	p->data=e;
	p->next=NULL;
	(q.rear)->next=p;
	q.rear=p;
	return true;
}
//*************************************
bool DeQueue(LinkQueue &q,int &e)
{
	QNode *p=(q.front)->next;
	e=p->data;
	(q.front)->next=p->next;
	if(p->next==NULL)
	q.rear=q.front;
	delete p;
	return true;
}
//*************************************
double Times()
{
	SYSTEMTIME ti;
	GetLocalTime(&ti);
	return ti.wMilliseconds;
}
//********************************
void RadixSort(SqList &l)
{
	double t1,t2;
	t1=Times();
	int num=0,i=0,j=0,k,t=1;
	LinkQueue q[10];
	for(num=0;num<2;num++)
	{
		for(k=0;k<10;k++)
		InitQueue(q[k]);
		
		for(j=0;j<l.length;j++)
		{
			k=(l.elem[j]%(t*10)-l.elem[j]%t)/t;
			EnQueue(q[k],l.elem[j]);
		}
		
		j=0;i=0;
		while(j<l.length)
		{
			while(q[i].front!=q[i].rear)
			{
				DeQueue(q[i],l.elem[j]);
				j++;
			}
			i++;
		}
		
		t*=10;
	}
	for(i=0;i<10;i++)
	DestoryQueue(q[i]);
	t2=Times();
	cout<<"共用时"<<t2-t1<<"毫秒"<<endl; 
}
//*************************************
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
	
	RadixSort(l);
	
	f.close();
	DestoryList(l);
	return 0;
}
