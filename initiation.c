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
	for(i=0;i<food_num;i++)        /*����ʳ�����������ȵ�С�ڸ�������������*/ 
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
	for(i=0;i<food_num;i++)        /*������״̬������Ƿ���ʳ��*/ 
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
	printf("\n����ѡ���½������ܣ�������������ݵĳ�ʼ����\n"); 
	printf("����������50��Ϊ");
	while(1)        /*Ӧ�Գ���³��������*/ 
	{
	    scanf("%s",str);
	    getchar();
	    if(strlen(str)>2||strlen(str)==0||(strlen(str)==2&&(str[0]<'0'||str[0]=='5'&&str[1]!='0'||str[0]>'5'||str[1]<'0'||str[1]>'9'))||strlen(str)==1&&(str[0]<'0'||str[1]>'9'))
	        printf("���볤�Ȳ����Ϲ淶�����������볤�ȣ�");
	    else
	    {
	    	if(strlen(str)==1)
	    	    length=str[0]-'0';
	    	else
	    	    length=(str[0]-'0')*10+(str[1]-'0');
	    	break;
		}
	}
	printf("��������50��Ϊ");
	while(1)        /*Ӧ�Կ��³��������*/ 
	{
	    scanf("%s",str);
	    getchar();
	    if(strlen(str)>2||strlen(str)==0||(strlen(str)==2&&(str[0]<'0'||str[0]=='5'&&str[1]!='0'||str[0]>'5'||str[1]<'0'||str[1]>'9'))||strlen(str)==1&&(str[0]<'0'||str[1]>'9'))
	        printf("�����Ȳ����Ϲ淶�������������ȣ�");
	    else
	    {
	    	if(strlen(str)==1)
	    	    width=str[0]-'0';
	    	else
	    	    width=(str[0]-'0')*10+(str[1]-'0');
	    	break;
		}
	}
	printf("�������ʼÿ������Ϊ���������ĸ��ʣ���С����ʽ���룩��\n����Ϊ");
	while(1)        /*Ӧ�Ը���³��������*/ 
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
	        printf("������ʲ����Ϲ淶��������������ʣ�");
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
	printf("�Ƿ���Ҫʹ�ø��ӹ��ܣ�\nA.��Ҫ  B.����Ҫ\n");
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
		    printf("�������ѡ����Ϲ淶�����������롣\n"); 
	}
	srand((unsigned)time(NULL));
	head=(G*)malloc(sizeof(G));        /*���ɵ�һ������*/ 
	head->x=0;
	head->y=0;
	head->num=length*(head->x)+head->y;
	head->cell=(rand()/(float)RAND_MAX<=chance);
	head->next=NULL;
	G *p=head;
	int Count=0;        /*����ά����һά��*/ 
	while(Count<width*length)        /*��������*/ 
	{
		Count++;
	    p->next=(G*)malloc(sizeof(G));
		p->next->x=Count%length;        /*һ����άת��*/ 
    	p->next->y=Count/length;        /*һ����άת��*/ 
		p->next->num=Count;
    	p->next->cell=(rand()/(float)RAND_MAX<=chance);
    	p->next->next=NULL;
    	p=p->next;
	}
	if(a)
	    locate_food();        /*���ʳ��*/ 
}
