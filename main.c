#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "grid.h"

unsigned int length,width;
char c;
G *head;
int a;

void print()        /*打印链表*/ 
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

void release()        /*释放链表信息*/ 
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
	printf("欢迎使用生命游戏程序（中文版）！\n");
	int i,j;
	head=NULL;
	while(1)
	{
		printf("工具栏：\nA.新建网格\nB.进行一次演化\nC.开始自动演化，直至输入P键停止\nD.保存网格\nE.加载网格\nF.产品介绍\nG.结束该游戏\n");
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
			    printf("\n您尚未对网格进行初始化或加载网格，无法演化。\n");
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
			    printf("\n您尚未对网格进行初始化或加载网格，无法演化。\n");
			else
			{
				while(1)
			    {
				    evolution();
				    printf("\n");
			        print();
	                char ch;
	                if(kbhit())        /*判断是否敲击键盘*/ 
	                {
	            	    ch=getch();
	            	    if(ch=='P'||ch=='p')        /*判断是否敲入p键*/ 
	            	        break;
				    }
	                Sleep(1000);        /*暂停1秒再进行下一次演化*/ 
			    }
			}
		}
		else if(c=='D'||c=='d')
		{
			if(head==NULL)
			    printf("\n您尚未对网格进行初始化或加载网格，无法保存。\n");
			else
			    save_file();
		}
		else if(c=='E'||c=='e')
		{
			release();
			open_file();
		}
		else if(c=='F'||c=='f')
			printf("\n约翰·康威 (John Conway) 于 1970 年发明的“生命游戏”(Game of Life) 是一个零玩家“游戏”，也是冯诺依曼提出的元胞自动机的其中一种。游戏由一个无限延伸的二维矩形世界组成，这个世界中的每个方格居住着一个活着的或死了的细胞。游戏描述了细胞如何一代一代进化的规则，它根据当前一代中相邻细胞的状态，计算出下一代细胞的状态。本款游戏额外添加了随机生成食物功能，可选择添加食物观察在食物影响下细胞不同的演化过程。\n");
		else if(c=='G'||c=='g')
		{
			release();
			printf("\n感谢您使用本款游戏！\n");
		    break;
		}
		else
	    	printf("\n您输入的选项不符合规范，请重新输入。\n"); 
		printf("\n");
	}
	return 0;
}
