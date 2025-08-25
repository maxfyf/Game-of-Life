#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

extern unsigned int length,width;
extern G *head;
extern int a;

G *p;

typedef struct temp        /*创建临时链表存储邻居活细胞个数信息*/ 
{
	int x;
	int y;
	int count;        /*邻居活细胞个数*/ 
	struct temp *next;
}T;

int search(int n)        /*查找一维坐标对应链节代表的细胞，返回其生存情况*/ 
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
    T *head_t=(T*)malloc(sizeof(T));        /*生成临时链表的第一个链节*/ 
    head_t->x=0;
    head_t->y=0;
    head_t->count=0;
    head_t->next=NULL;
    T *t=head_t;
	while(Count<width*length)        /*生成并初始化临时链表*/ 
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
	while(Count<width*length)        /*导入邻居活细胞个数信息*/ 
	{
	    if(Count/length!=0)
        {
        	if(Count%length!=0)        /*左上角*/ 
        		if(search(Count-length-1)==1||search(Count-length-1)==3)
        		    t->count++;
        	if(Count%length!=length-1)        /*右上角*/ 
        	    if(search(Count-length+1)==1||search(Count-length+1)==3)
        	        t->count++;
        	if(search(Count-length)==1||search(Count-length)==3)        /*上边*/ 
        	    t->count++;
		}
		if(Count/length!=width-1)
        {
        	if(Count%length!=0)        /*左下角*/ 
        	    if(search(Count+length-1)==1||search(Count+length-1)==3)
        	        t->count++;
        	if(Count%length!=length-1)        /*右下角*/ 
        	    if(search(Count+length+1)==1||search(Count+length+1)==3)
        	        t->count++; 
        	if(search(Count+length)==1||search(Count+length)==3)        /*下边*/ 
        	    t->count++;
		}
		if(Count%length!=0)        /*左边*/ 
		    if(search(Count-1)==1||search(Count-1)==3)
		        t->count++;
		if(Count%length!=length-1)        /*右边*/ 
		    if(search(Count+1)==1||search(Count+1)==3)
		        t->count++;
	    Count++;
	    t=t->next;
    }
    Count=0;
    p=head;
    t=head_t;
	while(Count<width*length)        /*演化*/ 
	{
    	if(p->cell==1&&(t->count<2||t->count>3))        /*活细胞死去*/ 
    	    p->cell=0;
    	if(p->cell==0&&t->count==3)        /*死细胞复活*/ 
    	    p->cell=1;
    	if(p->cell==2)
    	{
    		if(t->count>0)
    		    p->cell=1;        /*细胞周围有食物则食物格点被细胞占据*/ 
    		else
    		    p->cell-=2;        /*食物消失*/ 
		}
    	if(p->cell==3)        /*已占据食物的细胞消耗食物并存活*/ 
    	    p->cell-=2;        /*食物消失*/ 
    	Count++;
    	p=p->next;
    	t=t->next;
	}
	if(a)
	    locate_food();        /*再次随机生成食物*/ 
	t=head_t;        /*释放临时链表信息*/ 
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
