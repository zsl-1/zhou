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
	printf("��ѡ��1.���ļ�<�»��>   2.��ʾ�ļ�����\n        3.������  4.ɾ����   5.������  6.�޸���\n");
	printf("        7.�����ַ���         8.�滻�ַ���\n        9.�����˳�           0.�����༭\n");
	printf("***********************************************\n");
	printf("��ѡ��ѡ�������"); 
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
		printf("��ѡ��1.���ļ�<�»��>   2.��ʾ�ļ�����\n        3.������  4.ɾ����   5.������  6.�޸���\n");
	    printf("        7.�����ַ���         8.�滻�ַ���\n        9.�����˳�           0.�����༭\n");
	    printf("***********************************************\n");
	    printf("��ѡ��ѡ�������"); 
	}out:
	return 0;
 } 
// ���ļ����� 
void openwj()
{
	FILE *fp;
	printf("�������ļ���<�ɰ����̷���·����������19���ַ�>��");
	scanf("%s",ming);
    if((fp=fopen(ming, "a+"))==NULL){
			printf("�ļ���ʧ��\n");
			exit(0);
		}
	if(fclose(fp)){
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}	
 }
// ��ʾ�ļ����ݺ��� 
void xianshi()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ�!!!\n");
		return ;
	}
	FILE *fp;
    char s[NUM];
    int num=1;
    if((fp=fopen(ming, "r+"))==NULL){
			printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
}
//���뺯�� 
void charu()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ�!!!\n");
		return ;
	}
	FILE *fp;
	cont *p,*head=NULL,*t,*q,*head1=NULL,*head2=NULL,*k;
	int n,i,l;
	printf("�ڵ�l��ǰ��n�У�������l n:");
	while(1){
	    scanf("%d%d",&l,&n); 
	    if(l<=0)printf("�����кŲ��ԣ�����������l n��");
	    if(n<=0)return ;
		else{
			break;
		} 
	}
	printf("��˳��������������ݣ�");
	scanf("\n");
	p=(cont *)malloc(sizeof(cont));              //	����Ҫ���������
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
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	q=(cont *)malloc(sizeof(cont));              //	������ǰ���е�����
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){              //	���´�������
		printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
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
//ɾ������ 
void shanchu()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ�!!!\n");
		return ;
	}
	FILE *fp;
	int m,n,i;
	char s[NUM];
	printf("�ӵ�m����ɾ��n�У�������m��n��"); 
	scanf("%d %d",&m,&n);
	cont *head1=NULL,*p,*head2=NULL,*q,*t;
	if((fp=fopen(ming, "r"))==NULL){                //����Ҫ���������� 
		printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){             //���½�����д���ļ� 
		printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
}
//�������� 
void kaobei()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ�!!!\n");
		return ;
	}
	FILE *fp;
	int m,n,o,i;
	char s[NUM];
	cont *head=NULL,*p,*head1=NULL,*q,*head2=NULL,*k,*t;
	printf("�ѵ�m�п�ʼ��n�в���ԭo��֮ǰ��������m n o:");
	scanf("%d%d%d",&m,&n,&o);
	if((fp=fopen(ming, "r"))==NULL){
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	i=0;                                                     
	while (!feof(fp)) {
		i++;
		if(i==m)break; 
		fgets(s,100,fp);
	}
	p=(cont *)malloc(sizeof(cont));                          //������Ҫ����������
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
	if((fp=fopen(ming, "r"))==NULL){
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	q=(cont *)malloc(sizeof(cont));                    //����ԭ������ 
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){                  //����������д���ļ� 
		printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
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
//�޸ĺ��� 
void xiugai()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ�!!!!\n");
		return ;
	}
	FILE *fp;
	int n,i;
	char s[NUM];
	printf("��������Ҫ�޸ĵ��к��ǣ�");
	scanf("%d",&n);
	cont *head1=NULL,*p,*head2=NULL,*q,*t;
	if((fp=fopen(ming, "r+"))==NULL){
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));                    //���벻������� 
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
	if(!feof(fp))fgets(s,100,fp);                     //����Ҫ�޸ĵ��ַ�������s 
	if(s[0]!='\0'){
		printf("%d: %s",n,s);
	    printf("�������µ����ݣ�");
    }else{
    	printf("�����к����󣡣�\n");
		return ; 
	}
	scanf("\n");                                      //д���µ����� 
	gets(s);
	q=(cont *)malloc(sizeof(cont));                   //����֮�󲻱������ 
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	} 
	if((fp=fopen(ming, "w+"))==NULL){                    //����������д���ļ� 
		printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
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
//���Һ��� 
void chazhao()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ���\n");
		return ;
	}
	int i,j,flag=0,k,l=0,num=0,m=0;
	char c;
	FILE *fp;
	char s[NUM];
	cont *head=NULL,*p,*t;
	printf("����������ҵ��ַ�����"); 
	scanf("\n");
	gets(s);
	if((fp=fopen(ming, "r"))==NULL){
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));                    //�����ļ��������� 
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
	for(p=head;p!=NULL;p=p->next){                         //�������� 
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
				printf("��%d��:%s",m,p->a);
				printf("��%d���ַ������ҵ�������������<Y/N>��",l);
				while(1){
					scanf("\n");
					scanf("%c",&c);
					if(c=='N')goto out;
					else if(c=='Y'){
						flag=0;
						break;
					}
					else{
						printf("�����ʽ��������������(Y/N)��"); 
					}
		    	}
			} 
		}
	}out:
	if(flag==0)printf("û�ҵ���\n");
	if(fclose(fp)){
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
	for(p=head;p!=NULL;){
		t=p;
		p=p->next;
		free(t);
	}
	free(p);
}
//�滻���� 
void tihuan()
{
	if(ming[0]=='\0'){
		printf("���ȴ��ļ���\n");
		return ;
	}
	FILE *fp;
	char c;
	int i,j,flag=0,k,l=0,num=0,m=0;
	char zfc[NUM],zfc1[NUM],zfc2[NUM];
	cont *head=NULL,*p,*t;
	printf("��������滻���ַ�����");
	scanf("\n"); 
	gets(zfc);
	printf("�滻Ϊ��");
	scanf("\n");
	gets(zfc1);
	if((fp=fopen(ming, "r"))==NULL){
		printf("�ļ���ʧ��\n");
		exit(0);
	}
	p=(cont *)malloc(sizeof(cont));                 //�����ļ��������� 
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
	for(p=head;p!=NULL;p=p->next){                 //���������ַ��� 
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
				printf("��%d��:%s",m,p->a);
				printf("��%d���ַ������ҵ����Ƿ��滻<Y/N>��",l);
				while(1){
					scanf("\n");
					scanf("%c",&c);
					if(c=='N')break;
					else if(c=='Y'){                               //�滻�ַ��� 
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
						printf("�����ʽ��������������(Y/N)��"); 
					}
		    	}
		    	printf("�����滻��<Y/N>?");
		    	while(1){
					scanf("\n");
					scanf("%c",&c);
					if(c=='N')goto out;
					else if(c=='Y'){
						flag=0;
						break;
					}
					else{
						printf("�����ʽ��������������(Y/N)��"); 
					}
		    	}
			} 
		}
	}out:
	if(fclose(fp)){
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
	if((fp=fopen(ming, "w+"))==NULL){
		printf("�ļ���ʧ��\n");
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
		printf("�ļ��ر�ʧ��\n");
		exit(0); 
	}
}
//���̺��� 
void cunpan()
{
	system("pause");
	ming[0]='\0';
}
