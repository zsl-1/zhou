#include<stdio.h>
#include<stdlib.h>
struct stu{
    int num;
	char name[20];
	char birthday[20];
	char classnum[20];
};
int main() {
	char name[20],classnum[20],birthday[20],b[20],c[20],d[20],e[20];
	int a,n,i,num,j,flag=1,fl;
	struct stu s[10],temp;
	FILE* fp;
	while (1) {
		printf("1.输入学生数据，并保存。\n2.打开学生数据文件，显示学生信息。\n3.退出。\n");
		scanf("%d",&a);
		if(a==1){
			if((fp=fopen("stu.txt", "r+"))==NULL){
				printf("文件打开失败\n");
				exit(0);
			}
			printf("请输入要存入的数据数目\n");
			if(fscanf(fp,"%s    %s     %s     %s",b,c,d,e)!=EOF)flag=0;
			if((fp=fopen("stu.txt","a+"))==NULL){
				printf("文件打开失败\n");
				exit(0);
			}
			if(flag)fprintf(fp,"学号    姓名     出生日期     班级号\n");
			scanf("%d",&n);
			for(i=0;i<n;i++){
				scanf("%d %s %s %s",&s[i].num,s[i].name,s[i].birthday,s[i].classnum);
			}
            for(i=0;i<n;i++){
		        for(j=0;j<n-i-1;j++){
			        if(s[j].num>s[j+1].num){
						temp=s[j];
						s[j]=s[j+1];
						s[j+1]=temp;
					}
				}
			}
			for(i=0;i<n;i++){
				fprintf(fp,"%d %s  %s  %s\n",s[i].num,s[i].name,s[i].birthday,s[i].classnum);
			}
			if (fclose(fp)) {
				printf("文件无法关闭\n");
				exit(0);
			}
		}
		else if(a==2){
			fl=0;
			if((fp=fopen("stu.txt", "r+"))==NULL){
				printf("文件打开失败\n");
				exit(0);
			}
			while (!feof(fp)) {
				if(fl==0&&fscanf(fp,"%s    %s     %s     %s",b,c,d,e)!=EOF){
					printf("%s  %s  %s  %s\n",b,c,d,e);
				}
				if(fscanf(fp,"%d %s %s %s",&num,name,birthday,classnum)!=EOF)
				    printf("%d %s %s %s\n",num,name,birthday,classnum);
				fl=1;
			}
		}
		else break;
	}
	if (fclose(fp)) {
		printf("文件无法关闭\n");
		exit(0);
	}
	return 0;
}
