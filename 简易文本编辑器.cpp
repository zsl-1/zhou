#include<stdio.h>
#include<stdlib.h>
#define NUM 100
typedef struct content{
	char a[NUM];
	struct content *next; 
}cont;

void openwj(); 
void xianshi();
void charu();
void shanchu();
void kaobei();
void xiugai();
void chazhao();
void tihuan();
void cunpan();

char ming[20]="";
int main ()
{
	int a;
	printf("***********************************************\n");
	printf("请选择：1.打开文件<新或旧>   2.显示文件内容\n        3.插入行  4.删除行   5.拷贝行  6.修改行\n");
	printf("        7.查找字符串         8.替换字符串\n        9.存盘退出           0.放弃编辑\n");
	printf("***********************************************\n");
	printf("请选择选项操作："); 
	while(1){
		scanf("%d",&a);
		switch(a){
			case 1:
				openwj();
				break;
		    case 2:
		    	xianshi();
		    	break;
		    case 3:
		    	charu();
		    	break;
		    case 4:
		    	shanchu();
		    	break;
		    case 5:
		    	kaobei();
		    	break;
		    case 6:
		    	xiugai();
		    	break;
		    case 7:
		    	chazhao();
		    	break;
		    case 8:
		    	tihuan();
		    	break;
		    case 9:
		    	cunpan();
		    	break;
		    default: goto out;
		}
		printf("***********************************************\n");
		printf("请选择：1.打开文件<新或旧>   2.显示文件内容\n        3.插入行  4.删除行   5.拷贝行  6.修改行\n");
	    printf("        7.查找字符串         8.替换字符串\n        9.存盘退出           0.放弃编辑\n");
	    printf("***********************************************\n");
	    printf("请选择选项操作："); 
	}out:
	return 0;
 } 
// 打开文件函数 
void openwj()
{
	FILE *fp;
	printf("请输入文件名<可包括盘符，路径，不超过19个字符>：");
	scanf("%s",ming);
    if((fp=fopen(ming, "a+"))==NULL){
			printf("文件打开失败\n");
			exit(0);
		}
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}	
 }
// 显示文件内容函数 
void xianshi()
{
	if(ming[0]=='\0'){
		printf("请先打开文件!!!\n");
		return ;
	}
	FILE *fp;
    char s[NUM];
    int num=1;
    if((fp=fopen(ming, "r+"))==NULL){
			printf("文件打开失败\n");
			exit(0);
		}
    while (!feof(fp)) {
	    fgets(s,100,fp);
		if(!feof(fp)){
		    printf("%d: ",num++);
		    printf("%s",s);
		}
	} 
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
}
//插入函数 
void charu()
{
	if(ming[0]=='\0'){
		printf("请先打开文件!!!\n");
		return ;
	}
	FILE *fp;
	cont *p,*head=NULL,*t,*q,*head1=NULL,*head2=NULL,*k;
	int n,i,l;
	printf("在第l行前插n行，请输入l n:");
	while(1){
	    scanf("%d%d",&l,&n); 
	    if(l<=0)printf("插入行号不对，请重新输入l n：");
	    if(n<=0)return ;
		else{
			break;
		} 
	}
	printf("请顺序输入待插入内容：");
	scanf("\n");
	p=(cont *)malloc(sizeof(cont));              //	存入要插入的内容
	t=p;
	for(i=0;i<n;i++){
		p->next=(cont *)malloc(sizeof(cont));
	    gets(p->a);
		if(head==NULL){
			head=p;
		}
		t=p;
		p=p->next;	
	}
	t->next=NULL;
	if((fp=fopen(ming, "r"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	q=(cont *)malloc(sizeof(cont));              //	存入先前本有的内容
	i=0;
	t=q;
	while (!feof(fp)) {
		if(l>1){
			fgets(q->a,100,fp);
			i++;
			if(feof(fp))break;
			q->next=(cont *)malloc(sizeof(cont));
			if(head1==NULL)head1=q;
			t=q;
			q=q->next; 
			if(i==l-1)break;
		}
		else{
			break;
		}
	}
	t->next=NULL;
	k=(cont *)malloc(sizeof(cont));
	t=k;
	while (!feof(fp)) {
		k->next=(cont *)malloc(sizeof(cont));
		fgets(k->a,100,fp);
		if(feof(fp))break;
		if(head2==NULL)head2=k;
		t=k;
		k=k->next; 
	}
	t->next=NULL;
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){              //	重新存入内容
		printf("文件打开失败\n");
		exit(0);
	}
    for(p=head1;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
	}
	for(p=head;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
		fprintf(fp,"\n");
	}
	for(p=head2;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
	}
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	for(p=head;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	for(p=head1;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	for(p=head2;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
}
//删除函数 
void shanchu()
{
	if(ming[0]=='\0'){
		printf("请先打开文件!!!\n");
		return ;
	}
	FILE *fp;
	int m,n,i;
	char s[NUM];
	printf("从第m行起删除n行，请输入m，n："); 
	scanf("%d %d",&m,&n);
	cont *head1=NULL,*p,*head2=NULL,*q,*t;
	if((fp=fopen(ming, "r"))==NULL){                //存入要保留的数据 
		printf("文件打开失败\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));
	t=p;
	for(i=1;i<m&&!feof(fp);i++){
		p->next=(cont *)malloc(sizeof(cont));
	    fgets(p->a,100,fp);
	    if(feof(fp))break;
		if(head1==NULL){
			head1=p;
		}
		t=p;
		p=p->next;	
	}
	t->next=NULL;
	i=0;
	while (!feof(fp)) {
		fgets(s,100,fp);
		i++;
		if(i==n)break; 
	}
	q=(cont *)malloc(sizeof(cont));
	t=q;
	while(!feof(fp)){
		q->next=(cont *)malloc(sizeof(cont));
	    fgets(q->a,100,fp);
	    if(feof(fp))break;
		if(head2==NULL){
			head2=q;
		}
		t=q;
		q=q->next;	
	}
	t->next=NULL;
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){             //重新将数据写入文件 
		printf("文件打开失败\n");
		exit(0);
	}
	for(p=head1;p!=NULL;p=p->next){
		fputs(p->a,fp);
	}
	for(p=head2;p!=NULL;p=p->next){
		fputs(p->a,fp);
	}
	for(p=head1;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	for(p=head2;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
}
//拷贝函数 
void kaobei()
{
	if(ming[0]=='\0'){
		printf("请先打开文件!!!\n");
		return ;
	}
	FILE *fp;
	int m,n,o,i;
	char s[NUM];
	cont *head=NULL,*p,*head1=NULL,*q,*head2=NULL,*k,*t;
	printf("把第m行开始的n行插在原o行之前，请输入m n o:");
	scanf("%d%d%d",&m,&n,&o);
	if((fp=fopen(ming, "r"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	i=0;                                                     
	while (!feof(fp)) {
		i++;
		if(i==m)break; 
		fgets(s,100,fp);
	}
	p=(cont *)malloc(sizeof(cont));                          //存入需要拷贝的数据
	t=p;
	i=0;
	while(!feof(fp)){
		p->next=(cont *)malloc(sizeof(cont));
	    fgets(p->a,100,fp);
	    i++;
	    if(feof(fp))break;
		if(head==NULL){
			head=p;
		}
		t=p;
		p=p->next;
		if(i==n)break;	
	}
	t->next=NULL;
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	if((fp=fopen(ming, "r"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	q=(cont *)malloc(sizeof(cont));                    //存入原有数据 
	i=0;
	t=q;
	while (!feof(fp)) {
		if(o>1){
			fgets(q->a,100,fp);
			i++;
			if(feof(fp))break;
			q->next=(cont *)malloc(sizeof(cont));
			if(head1==NULL)head1=q;
			t=q;
			q=q->next; 
			if(i==o-1)break;
		}
		else{
			break;
		}
	}
	t->next=NULL;
	k=(cont *)malloc(sizeof(cont));
	t=k;
	while (!feof(fp)) {
		k->next=(cont *)malloc(sizeof(cont));
		fgets(k->a,100,fp);
		if(feof(fp))break;
		if(head2==NULL)head2=k;
		t=k;
		k=k->next; 
	}
	t->next=NULL;
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){                  //将数据重新写入文件 
		printf("文件打开失败\n");
		exit(0);
	}
    for(p=head1;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
	}
	for(p=head;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
	}
	for(p=head2;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
	}
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	for(p=head;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	for(p=head1;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	for(p=head2;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
}
//修改函数 
void xiugai()
{
	if(ming[0]=='\0'){
		printf("请先打开文件!!!!\n");
		return ;
	}
	FILE *fp;
	int n,i;
	char s[NUM];
	printf("请输入需要修改的行号是：");
	scanf("%d",&n);
	cont *head1=NULL,*p,*head2=NULL,*q,*t;
	if((fp=fopen(ming, "r+"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));                    //存入不变的数据 
	t=p;
	i=0;
	while(!feof(fp)){
		p->next=(cont *)malloc(sizeof(cont));
	    fgets(p->a,100,fp);
	    i++;
	    if(feof(fp))break;
		if(head1==NULL){
			head1=p;
		}
		t=p;
		p=p->next;
		if(i==n-1)break;	
	}
	t->next=NULL;
	if(!feof(fp))fgets(s,100,fp);                     //将需要修改的字符串存入s 
	if(s[0]!='\0'){
		printf("%d: %s",n,s);
	    printf("请输入新的内容：");
    }else{
    	printf("所输行号有误！！\n");
		return ; 
	}
	scanf("\n");                                      //写入新的内容 
	gets(s);
	q=(cont *)malloc(sizeof(cont));                   //存入之后不变的数据 
	t=q;
	while (!feof(fp)) {
		q->next=(cont *)malloc(sizeof(cont));
		fgets(q->a,100,fp);
		if(feof(fp))break;
		if(head2==NULL)head2=q;
		t=q;
		q=q->next; 
	}
	t->next=NULL;
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	} 
	if((fp=fopen(ming, "w+"))==NULL){                    //将数据重新写入文件 
		printf("文件打开失败\n");
		exit(0);
	}
	for(p=head1;p!=NULL;p=p->next){
		fputs(p->a,fp);
	}
	fputs(s,fp);
	fprintf(fp,"\n");
	for(p=head2;p!=NULL;p=p->next){
		fputs(p->a,fp);
	}
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	for(p=head1;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	for(p=head2;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
}
//查找函数 
void chazhao()
{
	if(ming[0]=='\0'){
		printf("请先打开文件。\n");
		return ;
	}
	int i,j,flag=0,k,l=0,num=0,m=0;
	char c;
	FILE *fp;
	char s[NUM];
	cont *head=NULL,*p,*t;
	printf("请输入待查找的字符串："); 
	scanf("\n");
	gets(s);
	if((fp=fopen(ming, "r"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));                    //存入文件所有数据 
	t=p;
	while (!feof(fp)) {
		p->next=(cont *)malloc(sizeof(cont));
		fgets(p->a,100,fp);
		if(feof(fp))break;
		if(head==NULL)head=p;
		t=p;
		p=p->next; 
	}
	t->next=NULL;
	for(p=head;p!=NULL;p=p->next){                         //遍历查找 
		m++;
		for(i=0;p->a[i]!='\0';i++){
			j=0;
			k=i;
			if(p->a[k]==s[j]){
				for(k++,j++;s[j]!='\0';k++,j++){
					if(s[j]!=p->a[k])break;
				}
			}
			if(s[j]=='\0'){
				flag=1;
				l++; 
				printf("第%d行:%s",m,p->a);
				printf("第%d个字符串处找到。继续查找吗<Y/N>？",l);
				while(1){
					scanf("\n");
					scanf("%c",&c);
					if(c=='N')goto out;
					else if(c=='Y'){
						flag=0;
						break;
					}
					else{
						printf("输入格式错误，请重新输入(Y/N)："); 
					}
		    	}
			} 
		}
	}out:
	if(flag==0)printf("没找到。\n");
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	for(p=head;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
}
//替换函数 
void tihuan()
{
	if(ming[0]=='\0'){
		printf("请先打开文件。\n");
		return ;
	}
	FILE *fp;
	char c;
	int i,j,flag=0,k,l=0,num=0,m=0;
	char zfc[NUM],zfc1[NUM],zfc2[NUM];
	cont *head=NULL,*p,*t;
	printf("请输入代替换的字符串：");
	scanf("\n"); 
	gets(zfc);
	printf("替换为：");
	scanf("\n");
	gets(zfc1);
	if((fp=fopen(ming, "r"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));                 //存入文件所有数据 
	t=p;
	while (!feof(fp)) {
		p->next=(cont *)malloc(sizeof(cont));
		fgets(p->a,100,fp);
		if(feof(fp))break;
		if(head==NULL)head=p;
		t=p;
		p=p->next; 
	}
	t->next=NULL;
	for(p=head;p!=NULL;p=p->next){                 //遍历查找字符串 
		m++;
		for(i=0;p->a[i]!='\0';i++){
			j=0;
			k=i;
			if(p->a[k]==zfc[j]){
				for(k++,j++;zfc[j]!='\0';k++,j++){
					if(zfc[j]!=p->a[k])break;
				}
			}
			if(zfc[j]=='\0'){
				flag=1;
				l++; 
				printf("第%d行:%s",m,p->a);
				printf("第%d个字符串处找到。是否替换<Y/N>？",l);
				while(1){
					scanf("\n");
					scanf("%c",&c);
					if(c=='N')break;
					else if(c=='Y'){                               //替换字符串 
						for(j=0;p->a[k]!='\0';k++,j++){           
							zfc2[j]=p->a[k];
						}
						zfc2[j]='\0';
						for(k=i,j=0;zfc1[j]!='\0';k++,j++){
					        p->a[k]=zfc1[j];
				        }
				        for(j=0;zfc2[j]!='\0';k++,j++){
					        p->a[k]=zfc2[j];
				        }
				        p->a[k]='\0';
						break;
					}
					else{
						printf("输入格式错误，请重新输入(Y/N)："); 
					}
		    	}
		    	printf("继续替换吗<Y/N>?");
		    	while(1){
					scanf("\n");
					scanf("%c",&c);
					if(c=='N')goto out;
					else if(c=='Y'){
						flag=0;
						break;
					}
					else{
						printf("输入格式错误，请重新输入(Y/N)："); 
					}
		    	}
			} 
		}
	}out:
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){
		printf("文件打开失败\n");
		exit(0);
	}
	for(p=head;p!=NULL;){
		fputs(p->a,fp);
		p=p->next;
	}
	for(p=head;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
	if(fclose(fp)){
		printf("文件关闭失败\n");
		exit(0); 
	}
}
//存盘函数 
void cunpan()
{
	system("pause");
	ming[0]='\0';
}
