#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

extern unsigned int length,width;
extern G *head;
extern int a;

G *p;

typedef struct temp        /*������ʱ����洢�ھӻ�ϸ��������Ϣ*/ 
{
	int x;
	int y;
	int count;        /*�ھӻ�ϸ������*/ 
	struct temp *next;
}T;

int search(int n)        /*����һά�����Ӧ���ڴ����ϸ�����������������*/ 
{
	p=head;
	int Count=0;
	while(Count<n)
	{
		p=p->next;
		Count++;
	}
	return p->cell;
}

void evolution()
{
	int Count=0;
    T *head_t=(T*)malloc(sizeof(T));        /*������ʱ����ĵ�һ������*/ 
    head_t->x=0;
    head_t->y=0;
    head_t->count=0;
    head_t->next=NULL;
    T *t=head_t;
	while(Count<width*length)        /*���ɲ���ʼ����ʱ����*/ 
	{
		Count++;
	    t->next=(T*)malloc(sizeof(T));
	   	t->next->x=Count%length;
	    t->next->y=Count/length;
	    t->next->count=0;
	    t->next->next=NULL;
	    t=t->next;
	}
	t=head_t;
	Count=0;
	while(Count<width*length)        /*�����ھӻ�ϸ��������Ϣ*/ 
	{
	    if(Count/length!=0)
        {
        	if(Count%length!=0)        /*���Ͻ�*/ 
        		if(search(Count-length-1)==1||search(Count-length-1)==3)
        		    t->count++;
        	if(Count%length!=length-1)        /*���Ͻ�*/ 
        	    if(search(Count-length+1)==1||search(Count-length+1)==3)
        	        t->count++;
        	if(search(Count-length)==1||search(Count-length)==3)        /*�ϱ�*/ 
        	    t->count++;
		}
		if(Count/length!=width-1)
        {
        	if(Count%length!=0)        /*���½�*/ 
        	    if(search(Count+length-1)==1||search(Count+length-1)==3)
        	        t->count++;
        	if(Count%length!=length-1)        /*���½�*/ 
        	    if(search(Count+length+1)==1||search(Count+length+1)==3)
        	        t->count++; 
        	if(search(Count+length)==1||search(Count+length)==3)        /*�±�*/ 
        	    t->count++;
		}
		if(Count%length!=0)        /*���*/ 
		    if(search(Count-1)==1||search(Count-1)==3)
		        t->count++;
		if(Count%length!=length-1)        /*�ұ�*/ 
		    if(search(Count+1)==1||search(Count+1)==3)
		        t->count++;
	    Count++;
	    t=t->next;
    }
    Count=0;
    p=head;
    t=head_t;
	while(Count<width*length)        /*�ݻ�*/ 
	{
    	if(p->cell==1&&(t->count<2||t->count>3))        /*��ϸ����ȥ*/ 
    	    p->cell=0;
    	if(p->cell==0&&t->count==3)        /*��ϸ������*/ 
    	    p->cell=1;
    	if(p->cell==2)
    	{
    		if(t->count>0)
    		    p->cell=1;        /*ϸ����Χ��ʳ����ʳ���㱻ϸ��ռ��*/ 
    		else
    		    p->cell-=2;        /*ʳ����ʧ*/ 
		}
    	if(p->cell==3)        /*��ռ��ʳ���ϸ������ʳ�ﲢ���*/ 
    	    p->cell-=2;        /*ʳ����ʧ*/ 
    	Count++;
    	p=p->next;
    	t=t->next;
	}
	if(a)
	    locate_food();        /*�ٴ��������ʳ��*/ 
	t=head_t;        /*�ͷ���ʱ������Ϣ*/ 
	T *t1=NULL;
	if(t!=NULL)
	{
	    while(t->next!=NULL)
	    {
	    	t1=t->next;
	    	free(t);
	    	t=t1;
		}
		free(t->next);
    }
	free(t);
}
