#include <stdio.h>
void ruku(int a);
int jieyue(int a);
void guihuan(int a);
void qingchu(int a);
void chaxun(int e);
int main()
{
    int n,a,b,c,d,e;
    printf("(1)�ɱ����\n(2)����\n(3)�黹\n(4)������\n(5)��ѯ����\n(0)�˳�����\n");
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
		if(jieyue(b))printf("���ĳɹ�,��ţ�%d\n",b);
		else {printf("���볬�����Σ�����ʧ��\n"); }
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
		printf("(1)����������ѯ\n(2)����������\n(3)����ISBN��ѯ\n");
		scanf("%d",&e);
		chaxun(e);
	}
	printf("(1)�ɱ����\n(2)����\n(3)�黹\n(4)������\n(5)��ѯ����\n(0)�˳�����\n");
	scanf("%d",&n);}
	printf("(1)�ɱ����\n(2)����\n(3)�黹\n(4)������\n(5)��ѯ����\n(0)�˳�����\n");
    return 0;
}
void ruku(int a)
{
	if(a>0&&a<10000){
		printf("���ɹ�,��ţ�%d\n",a);
	}
	else{
		printf("������Ŵ������������������ţ�");
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
	 	printf("���������������ţ�");
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
		printf("�黹�ɹ�,��ţ�%d\n",a);
	}
	else{
		printf("������Ŵ������������������ţ�");
	}
 }
 void qingchu(int a)
{
	if(a>0&&a<10000){
		printf("ע���ɹ�,��ţ�%d\n",a);
	}
	else{
		printf("������Ŵ������������������ţ�");
	}
 }
 void chaxun(int e)
 {
 	char a[1000];
 	if(e==1){
 		printf("������������");
		scanf("%s",a);
		printf("��ѯͼ��������%s\n",a);
	 }
	 else if(e==2){
	 	printf("���������ߣ�");
	 	scanf("%s",a);
		printf("��ѯͼ�����ߣ�%s\n",a);
	 }
	 else if(e==3){
	 	printf("������ISBN:");
		 scanf("%s",a) ;
		 printf("��ѯͼ��ISBN��%s\n",a);
	 }
 }
 
