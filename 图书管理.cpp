#include <stdio.h>
void ruku(int a);
int jieyue(int a);
void guihuan(int a);
void qingchu(int a);
void chaxun(int e);
int main()
{
    int n,a,b,c,d,e;
    printf("(1)采编入库\n(2)借阅\n(3)归还\n(4)清除库存\n(5)查询功能\n(0)退出程序\n");
    scanf("%d",&n);
    while(n!=0){
    if(n==1){
    	scanf("%d",&a);
    	ruku(a);
    		while(1){
    			if(a>0&&a<10000)break;
    			scanf("%d",&a);
    			ruku(a);
			}
		
	}
	else if(n==2){
		scanf("%d",&b);
		if(jieyue(b))printf("借阅成功,书号：%d\n",b);
		else {printf("输入超过三次，借阅失败\n"); }
	}
	else if(n==3){
		scanf("%d",&c);
		guihuan(c);
		while(1){
			if(c>0&&c<10000)break;
			scanf("%d",&c);
			guihuan(c);
		}
	}
	else if(n==4){
		scanf("%d",&d);
		qingchu(d);
		while(1){
			if(d>0&&d<10000)break;
			scanf("%d",&d);
			qingchu(d);
		}
	}
	else if(n==5){
		printf("(1)按照书名查询\n(2)按照作者名\n(3)按照ISBN查询\n");
		scanf("%d",&e);
		chaxun(e);
	}
	printf("(1)采编入库\n(2)借阅\n(3)归还\n(4)清除库存\n(5)查询功能\n(0)退出程序\n");
	scanf("%d",&n);}
	printf("(1)采编入库\n(2)借阅\n(3)归还\n(4)清除库存\n(5)查询功能\n(0)退出程序\n");
    return 0;
}
void ruku(int a)
{
	if(a>0&&a<10000){
		printf("入库成功,书号：%d\n",a);
	}
	else{
		printf("输入书号错误，请重新输入入库书号：");
	}
 } 
 int jieyue(int a)
 {
 	int b;
 	static int d=0;
 	if(a>0&&a<10000){
 		return 1;  
	 }
	 else{
	 	if(d<2){
	 	printf("请重新输入借书书号：");
	 	scanf("%d",&b);
	 	d++;
	 	jieyue(b);
		}
		else{
			return 0;
		}
	 }
 }
 void guihuan(int a)
{
	if(a>0&&a<10000){
		printf("归还成功,书号：%d\n",a);
	}
	else{
		printf("输入书号错误，请重新输入入库书号：");
	}
 }
 void qingchu(int a)
{
	if(a>0&&a<10000){
		printf("注销成功,书号：%d\n",a);
	}
	else{
		printf("输入书号错误，请重新输入入库书号：");
	}
 }
 void chaxun(int e)
 {
 	char a[1000];
 	if(e==1){
 		printf("请输入书名：");
		scanf("%s",a);
		printf("查询图书书名：%s\n",a);
	 }
	 else if(e==2){
	 	printf("请输入作者：");
	 	scanf("%s",a);
		printf("查询图书作者：%s\n",a);
	 }
	 else if(e==3){
	 	printf("请输入ISBN:");
		 scanf("%s",a) ;
		 printf("查询图书ISBN：%s\n",a);
	 }
 }
 
