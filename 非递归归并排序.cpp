#include<iostream>
#include<fstream>
#include<ctime> 
#include<Windows.h>
#include<stdlib.h>
using namespace std;

double Times()
{
	SYSTEMTIME ti;
	GetLocalTime(&ti);
	return ti.wMilliseconds;
}

void sort(int *arr3,int *arr1,int begin,int m,int end)
{
    int i=begin,j=m+1,k,h;
    for(k=i;i<=m && j<=end;k++)
	{
        if(arr3[i]<arr3[j])
            arr1[k]=arr3[i++];
        else
            arr1[k]=arr3[j++];
    }
    if(i<=m)
        for(h=0; h<=m-i;h++)
            arr1[k+h]=arr3[i+h];
	else
        for(h=0;h<=end-j;h++)
            arr1[k+h]=arr3[j+h];
}

void Merge(int *arr1,int *temp,int k,int length){
    int i=0,j;
    while(i <= length-2*k)
	{
        sort(arr1,temp,i,i+k-1,i+2*k-1);
        i+=2*k;
    }
    if(i < length-k+1)
        sort(arr1,temp,i,i+k-1,length-1);
    else
        for(j=i;j<length;j++)
            temp[j]=arr1[j];
    for(i=0;i<length;i++){
        arr1[i]=temp[i];
    }
}

void MergeSort(int *arr,int length){
    int *temp =new int[length];
    int i = 1;
    while(i<length){
        Merge(arr,temp,i,length);
        i *= 2;
    }
}

int main()
{
    int a[20000],i;
	fstream f;
	f.open("测试数据.txt",ios::in);
	if(!f)
	{
		cout<<"open error"<<endl;
		exit(0);
	}
	for(int i=0;i<20000;i++)
		f>>a[i];
	f.close();
	
	double t1,t2;
	t1=Times();
	MergeSort(a,20000);
	t2=Times();
	cout<<"共用时"<<t2-t1<<"毫秒"<<endl;
	
	return 0;
}

