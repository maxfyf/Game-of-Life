#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "grid.h"

extern unsigned int length,width;
extern G *head;
extern int a;

char change(int cell)        /*将0、1、2、3对应转换为' '、'*'、'$'、'#' */ 
{
	if(cell==0)
	    return ' ';
	else if(cell==1)
	    return '*';
	else if(cell==2)
	    return '$';
	else
	    return '#';
}

void print_grid(FILE *fp)        /*打印文件中的格点*/ 
{
	if(width<10)
	    fputc(width+'0',fp);
	else
	{
		fputc(width/10+'0',fp);
		fputc(width%10+'0',fp);
	}
	fputc(',',fp);
	if(length<10)
	    fputc(length+'0',fp);
	else
	{
		fputc(length/10+'0',fp);
		fputc(length%10+'0',fp);
	}
	fputc('\n',fp);
	G *p=head;
	int Count=0;
	while(Count<width*length)
	{
		fputc(p->cell+'0',fp);
		p=p->next;
		if(Count%length==length-1)
		{
        	fputc(',',fp);
		    fputc('\n',fp);
		}
		else
		    fputc(',',fp);
		Count++;
    }
    fputc('\n',fp);
}

void open_file()
{
	char filename[100];
	printf("\n您已选择加载网格功能。（以正文文本为准）\n请输入网格所在文件路径与名称:");
	scanf("%s",filename); 
	getchar();
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
		printf("您所找文件不存在。\n");
	else
	{
		int det=0;
		char temp=fgetc(fp);
		while(temp!='\n')        /*找到网格开头*/
		    temp=fgetc(fp);
		temp=fgetc(fp);
	    head=(G*)malloc(sizeof(G));        /*生成第一个格点*/ 
	    head->x=0;
    	head->y=0;
	    head->num=0;
	    head->cell=temp-'0';
    	head->next=NULL;
	    G *p=head;
    	length=1;
		temp=fgetc(fp);
    	int times=1;
	    while(temp==','&&times%2!=0||temp=='0'&&times%2==0||temp=='1'&&times%2==0||temp=='2'&&times%2==0||temp=='3'&&times%2==0)        /*生成第一行，确定长度*/ 
	    {
	    	if(times%2==0)
	    	{
	            p->next=(G*)malloc(sizeof(G));
		        p->next->x=length;
    	        p->next->y=0; 
		        p->next->num=length;
        	    p->next->cell=temp-'0';
    	        p->next->next=NULL;
    	        p=p->next;
	    		length++;
			}
			else;
			times++;
			temp=fgetc(fp);
	    }        /*根据第一行符合要求部分确定网格长度*/ 
	    width=1;
	    if(temp=='\n'&&times%2==0)
    	        det=1;
	    else;
	    if(det==1)        /*生成剩余行*/ 
	    {
	    	while(1)
	    	{
	            int Count=0;
	    		times=0;
	    		temp=fgetc(fp);
	    		while(temp==','&&times%2!=0||temp=='0'&&times%2==0||temp=='1'&&times%2==0||temp=='2'&&times%2==0||temp=='3'&&times%2==0)
	    		{
					if(temp!=',')
					{
						Count++;
                        p->next=(G*)malloc(sizeof(G));
	                    p->next->x=Count;
   	                    p->next->y=width; 
	                    p->next->num=width*length+Count;
       	                p->next->cell=temp-'0';
   	                    p->next->next=NULL;
   	                    p=p->next;
   	                }
   	                else;
  				    times++;
				    temp=fgetc(fp);
					if(Count==length)
					    break;
					else;
				}
				if(Count!=length)
				    break;        /*根据最后一行以后不符合要求部分确定网格宽度*/ 
				else
				{
					width++;
					if(temp!=','&fgetc(fp)!='\n')
	    				break;
				}
			}
		}
		p=head;
		while(p)
		{
			if(p->cell>1)
			{
				a=1;
				break;
			}
			p=p->next;
			if(!p)
			    a=0;
		}
		printf("加载文件中网格为：\n");
		print();        /*打印网格*/ 
	}
	fclose(fp);
}

void save_file()
{
	char filename[100];
	int i,j;
	printf("\n您已选择保存网格功能。\n请输入所保存文件路径与名称（如文件存在，则直接保存；如文件不存在，则新建文件）：\n");
	scanf("%s",filename);
	getchar();
	if(access(filename,F_OK)!=0)
	{
	    printf("该路径下的该文件不存在，已新建文件。\n");
	    FILE *fp=fopen(filename,"w+");        /*直接写入*/ 
	    print_grid(fp);
	    fclose(fp);
	}
	else
	{
		printf("该路径下的该文件存在，是否要替代文件中已有内容？\nA.是   B.否\n");
    	char c;
    	c=getch();
    	while(1)
    	{
    		if(c=='a'||c=='A')
    		{
		        FILE *fp=fopen(filename,"w+");        /*直接写入*/ 
		        print_grid(fp);
		        fclose(fp);
	            break;
			}
    		else if(c=='b'||c=='B')
    		{
    			FILE *fp=fopen(filename,"a+");        /*清空文件中已有内容后再写入*/ 
			    print_grid(fp);
			    fclose(fp);
	            break;
			}
			else
			{
			    printf("\n您输入的选项不符合规范，请重新输入。\nA.是   B.否\n"); 
			    c=getch();
		    }
		}
	}
	printf("\n此网格已成功保存在该文件中。\n");
}
