#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "grid.h"

extern unsigned int length,width;
float chance;
extern G *head;
extern int a;

int count(int x,int y)
{
	int n=x*length+y; 
    return n;
}

void locate_food()
{
	int i,j;
	int d=1;
	int l[25];
	int food_num=(length+width)/4;
	G *p;
	srand((unsigned)time(NULL));
	for(i=0;i<food_num;i++)        /*生成食物个数个不相等的小于格点总数的随机数*/ 
	    while(1)
	    {
		    l[i]=rand()%(length*width);
		    for(j=0;j<i;j++)
		    {
			    if(l[i]==l[j])
			    {
			    	d=0;
			    	break;
				}
				else;
			}
			if(!d)
				d=1;
			else
			    break;
		}
	for(i=0;i<food_num;i++)        /*在生存状态处标记是否有食物*/ 
	{
	    j=0;
		p=head;
	    while(j<l[i])
	    {
	    	p=p->next;
	    	j++;
		}
		p->cell+=2;
	}
}

void initiation()
{
	char c;
	char str[100];
	float chance=0;
	printf("\n您已选择新建网格功能，请完成网格数据的初始化。\n"); 
	printf("长（不超过50）为");
	while(1)        /*应对长度鲁棒性输入*/ 
	{
	    scanf("%s",str);
	    getchar();
	    if(strlen(str)>2||strlen(str)==0||(strlen(str)==2&&(str[0]<'0'||str[0]=='5'&&str[1]!='0'||str[0]>'5'||str[1]<'0'||str[1]>'9'))||strlen(str)==1&&(str[0]<'0'||str[1]>'9'))
	        printf("输入长度不符合规范，请重新输入长度：");
	    else
	    {
	    	if(strlen(str)==1)
	    	    length=str[0]-'0';
	    	else
	    	    length=(str[0]-'0')*10+(str[1]-'0');
	    	break;
		}
	}
	printf("宽（不超过50）为");
	while(1)        /*应对宽度鲁棒性输入*/ 
	{
	    scanf("%s",str);
	    getchar();
	    if(strlen(str)>2||strlen(str)==0||(strlen(str)==2&&(str[0]<'0'||str[0]=='5'&&str[1]!='0'||str[0]>'5'||str[1]<'0'||str[1]>'9'))||strlen(str)==1&&(str[0]<'0'||str[1]>'9'))
	        printf("输入宽度不符合规范，请重新输入宽度：");
	    else
	    {
	    	if(strlen(str)==1)
	    	    width=str[0]-'0';
	    	else
	    	    width=(str[0]-'0')*10+(str[1]-'0');
	    	break;
		}
	}
	printf("请输入初始每个格子为有生命格点的概率（用小数形式输入）。\n概率为");
	while(1)        /*应对概率鲁棒性输入*/ 
	{
	    scanf("%s",str);
	    getchar();
	    int q=1;
	    int l=strlen(str);
	    int i;
	    if(l<2)
	        q=0;
	    else
	    {
	        if(str[0]!='0'&&str[0]!='.')
	            q=0;
	        else
	        {
	    	    if(str[0]=='0')
	    	    {
	    	    	if(l<3)
	    	    	    q=0;
	    	    	else if(str[1]!='.')
	    	    	    q=0;
	    	    	else
	    	    	{
	    	    		for(i=2;i<l;i++)
	    	    		    if(str[i]<'0'||str[i]>'9')
	    	    		    {
	    	    		    	q=0;
	    	    		    	break;
							}
					}
				}
				else
				{
					for(i=1;i<l;i++)
						if(str[i]<'0'||str[i]>'9')
						{
							q=0;
							break;
						}
				}
		    }
		}
	    if(!q)
	        printf("输入概率不符合规范，请重新输入概率：");
	    else
	    {
	    	if(str[0]=='.')
	    		for(i=1;i<l;i++)
	    		    chance+=pow(10,-i)*(float)(str[i]-'0');
			else
				for(i=2;i<l;i++)
				    chance+=pow(10,-i+1)*(float)(str[i]-'0');
			break;
		}
	}
	printf("是否需要使用附加功能？\nA.需要  B.不需要\n");
	while(1)
	{
		c=getch();
		if(c=='A'||c=='a')
		{
		    a=1;
		    break;
		}
		else if(c=='B'||c=='b')
		{
		    a=0;
		    break;
		}
		else
		    printf("您输入的选项不符合规范，请重新输入。\n"); 
	}
	srand((unsigned)time(NULL));
	head=(G*)malloc(sizeof(G));        /*生成第一个链节*/ 
	head->x=0;
	head->y=0;
	head->num=length*(head->x)+head->y;
	head->cell=(rand()/(float)RAND_MAX<=chance);
	head->next=NULL;
	G *p=head;
	int Count=0;        /*将二维坐标一维化*/ 
	while(Count<width*length)        /*生成链表*/ 
	{
		Count++;
	    p->next=(G*)malloc(sizeof(G));
		p->next->x=Count%length;        /*一、二维转换*/ 
    	p->next->y=Count/length;        /*一、二维转换*/ 
		p->next->num=Count;
    	p->next->cell=(rand()/(float)RAND_MAX<=chance);
    	p->next->next=NULL;
    	p=p->next;
	}
	if(a)
	    locate_food();        /*添加食物*/ 
}
