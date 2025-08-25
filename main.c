#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "grid.h"

unsigned int length,width;
char c;
G *head;
int a;

void print()        /*��ӡ����*/ 
{
	G *p=head;
	int Count=0;
	while(Count<width*length)
	{
		printf("|%c",change(p->cell));
		p=p->next;
		if(Count%length==length-1)
		    printf("|\n");
		Count++;
	}
}

void release()        /*�ͷ�������Ϣ*/ 
{
	G *p1=head;
	G *p2;
	while(p1!=NULL)
	{
	    p2=p1->next;
	   	free(p1);
	   	p1=p2;
    }
    head=0;
}

int main()
{
	printf("��ӭʹ��������Ϸ�������İ棩��\n");
	int i,j;
	head=NULL;
	while(1)
	{
		printf("��������\nA.�½�����\nB.����һ���ݻ�\nC.��ʼ�Զ��ݻ���ֱ������P��ֹͣ\nD.��������\nE.��������\nF.��Ʒ����\nG.��������Ϸ\n");
	    c=getch();
	    if(c=='A'||c=='a')
	    {
	    	release();
	    	initiation();
	    	print();
		}
		else if(c=='B'||c=='b')
		{
			if(head==NULL)
			    printf("\n����δ��������г�ʼ������������޷��ݻ���\n");
			else
			{
				evolution();
			    printf("\n");
			    print();
			}	 	
		}
		else if(c=='C'||c=='c')
		{
			if(head==NULL)
			    printf("\n����δ��������г�ʼ������������޷��ݻ���\n");
			else
			{
				while(1)
			    {
				    evolution();
				    printf("\n");
			        print();
	                char ch;
	                if(kbhit())        /*�ж��Ƿ��û�����*/ 
	                {
	            	    ch=getch();
	            	    if(ch=='P'||ch=='p')        /*�ж��Ƿ�����p��*/ 
	            	        break;
				    }
	                Sleep(1000);        /*��ͣ1���ٽ�����һ���ݻ�*/ 
			    }
			}
		}
		else if(c=='D'||c=='d')
		{
			if(head==NULL)
			    printf("\n����δ��������г�ʼ������������޷����档\n");
			else
			    save_file();
		}
		else if(c=='E'||c=='e')
		{
			release();
			open_file();
		}
		else if(c=='F'||c=='f')
			printf("\nԼ�������� (John Conway) �� 1970 �귢���ġ�������Ϸ��(Game of Life) ��һ������ҡ���Ϸ����Ҳ�Ƿ�ŵ���������Ԫ���Զ���������һ�֡���Ϸ��һ����������Ķ�ά����������ɣ���������е�ÿ�������ס��һ�����ŵĻ����˵�ϸ������Ϸ������ϸ�����һ��һ�������Ĺ��������ݵ�ǰһ��������ϸ����״̬���������һ��ϸ����״̬��������Ϸ����������������ʳ�﹦�ܣ���ѡ�����ʳ��۲���ʳ��Ӱ����ϸ����ͬ���ݻ����̡�\n");
		else if(c=='G'||c=='g')
		{
			release();
			printf("\n��л��ʹ�ñ�����Ϸ��\n");
		    break;
		}
		else
	    	printf("\n�������ѡ����Ϲ淶�����������롣\n"); 
		printf("\n");
	}
	return 0;
}
