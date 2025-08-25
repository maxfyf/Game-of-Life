#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "grid.h"

extern unsigned int length,width;
extern G *head;
extern int a;

char change(int cell)        /*��0��1��2��3��Ӧת��Ϊ' '��'*'��'$'��'#' */ 
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

void print_grid(FILE *fp)        /*��ӡ�ļ��еĸ��*/ 
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
	printf("\n����ѡ����������ܡ����������ı�Ϊ׼��\n���������������ļ�·��������:");
	scanf("%s",filename); 
	getchar();
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
		printf("�������ļ������ڡ�\n");
	else
	{
		int det=0;
		char temp=fgetc(fp);
		while(temp!='\n')        /*�ҵ�����ͷ*/
		    temp=fgetc(fp);
		temp=fgetc(fp);
	    head=(G*)malloc(sizeof(G));        /*���ɵ�һ�����*/ 
	    head->x=0;
    	head->y=0;
	    head->num=0;
	    head->cell=temp-'0';
    	head->next=NULL;
	    G *p=head;
    	length=1;
		temp=fgetc(fp);
    	int times=1;
	    while(temp==','&&times%2!=0||temp=='0'&&times%2==0||temp=='1'&&times%2==0||temp=='2'&&times%2==0||temp=='3'&&times%2==0)        /*���ɵ�һ�У�ȷ������*/ 
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
	    }        /*���ݵ�һ�з���Ҫ�󲿷�ȷ�����񳤶�*/ 
	    width=1;
	    if(temp=='\n'&&times%2==0)
    	        det=1;
	    else;
	    if(det==1)        /*����ʣ����*/ 
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
				    break;        /*�������һ���Ժ󲻷���Ҫ�󲿷�ȷ��������*/ 
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
		printf("�����ļ�������Ϊ��\n");
		print();        /*��ӡ����*/ 
	}
	fclose(fp);
}

void save_file()
{
	char filename[100];
	int i,j;
	printf("\n����ѡ�񱣴������ܡ�\n�������������ļ�·�������ƣ����ļ����ڣ���ֱ�ӱ��棻���ļ������ڣ����½��ļ�����\n");
	scanf("%s",filename);
	getchar();
	if(access(filename,F_OK)!=0)
	{
	    printf("��·���µĸ��ļ������ڣ����½��ļ���\n");
	    FILE *fp=fopen(filename,"w+");        /*ֱ��д��*/ 
	    print_grid(fp);
	    fclose(fp);
	}
	else
	{
		printf("��·���µĸ��ļ����ڣ��Ƿ�Ҫ����ļ����������ݣ�\nA.��   B.��\n");
    	char c;
    	c=getch();
    	while(1)
    	{
    		if(c=='a'||c=='A')
    		{
		        FILE *fp=fopen(filename,"w+");        /*ֱ��д��*/ 
		        print_grid(fp);
		        fclose(fp);
	            break;
			}
    		else if(c=='b'||c=='B')
    		{
    			FILE *fp=fopen(filename,"a+");        /*����ļ����������ݺ���д��*/ 
			    print_grid(fp);
			    fclose(fp);
	            break;
			}
			else
			{
			    printf("\n�������ѡ����Ϲ淶�����������롣\nA.��   B.��\n"); 
			    c=getch();
		    }
		}
	}
	printf("\n�������ѳɹ������ڸ��ļ��С�\n");
}
