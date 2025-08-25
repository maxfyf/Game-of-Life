typedef struct grid        /*定义结构体代表网格供所有文件调用*/ 
{
	int x;
	int y;
	int num;
	int cell;
	struct grid *next;
}G; 
