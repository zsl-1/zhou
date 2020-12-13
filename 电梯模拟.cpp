#include <windows.h>
#include<bits/stdc++.h>
#include<string.h> 
#include<stdio.h> 
#include<stdlib.h>
using  namespace std;

#define UnitTime 0.1        //��λʱ�� 
#define Maxpeople 1000000   //ģ��ʱ���˿����� 
#define MaxTime 10000       //�������ʱ������� 
#define MinTime 500         //�������ʱ������� 
#define Maxfloor 4          //��ߵ�¥�� 
#define MaxPeopleNum 8      //�����ڳ�����Ա��������� 
#define MaxWaitNumInFloor 7	//ÿһ������ȴ�����
#define Basefloor 1         //¥�Ļ��� 

#define FloorHight 3		//¥��߶�
#define LeftElevatorX 6		//��ߵ��ݵ�x��ʼ����
#define LeftElevatorY 12	//��ߵ��ݵ�y��ʼ����
#define RightElevatorX 34	//�ұߵ��ݵ�x��ʼ����
#define RightElevatorY 12	//�ұߵ��ݵ�y��ʼ����
#define Uptime 51           //��������ʱ�� 
#define Downtime 61         //�����½�ʱ�� 
#define UpSlowdown 14       //������������ʱ�� 
#define DownSlowdown 23     //�����½�����ʱ�� 
#define Accelerate 15       //���ݼ���ʱ��  
#define Doortime 20         //���ݹ���ʱ�� 
#define Peopletime 25       //�˽������ʱ�� 
#define Diantitime 40       //���ʱ�����ʱ�� 
#define Backtime 300        //����Ƿ�ص����� 

#define Goingup 1           //����״̬���� 
#define Goingdown -1        //����״̬�½� 
#define Idle 0              //����״̬�Ⱥ� 

int Time,id,Maxtime;
int flagelevator=0;         //���˿��Ƿ�ͬʱ����ȫ������ 
int Exist[Maxpeople]={0};   //�û��Ƿ���ڶ�����
char ElevatorChar[2][40];   //������ʾ 
char PeopleChar6[2][40];    //�����г˿���ʾ     
char PeopleChar7[2][40];    //�����г˿���ʾ 
typedef struct elevatorcanshu Elevatorcanshu;
typedef struct people{
    int Id;                //���û��ı��
    int EnterTime;         //����ʱ��
    int InFloor;           //�����ڵ�¥��
    int OutFloor;          //��Ҫȥ�Ĳ�¥
    int GiveupTime;        //�������̵ĵȺ�ʱ��
    int FlagElevator0;     //ֵΪ0���������������0 
    int FlagElevator1;     //ֵΪ0���������������1 
    struct people* pre;
    struct people* next;
}*People;

typedef struct dianti{
	int Id;
	struct dianti *next; 
}*Dianti;

typedef struct shixu{
	int xianzhitime;
	People person;
	void(*f)(People per,Elevatorcanshu *&Elevatortemp,int temp);
	struct shixu *next;
}*Shixu;

struct elevatorcanshu{
	int PeopleNum;                   //���������� 
	int CallUp[5];                   //���������ϰ�ť
	int CallDown[5];                 //���������°�ť
	int CallDianti[5];               //�����ڰ�ť
	int again;
	int drcl,drcltime,testdoortime; //�����Ų���
	int state;                      //���ݵĵ�ǰ״̬(GoingUp��GoingDOWEl��Idle)
	int prestate;                   //�����²�״̬(GoingUp��GoingDOWEl��Idle)
	int Floor;                      //���ݵĵ�ǰλ��(¥��)
	int d1;                         //ֵΪ0�������������ڽ�����뿪���ݣ�
	int d2;                         //ֵΪ0��������� �Ѿ���ĳ��ͣ��30Ot���ϣ�
	int d3;                         //ֵΪ0�����ǵ��� �������������˱ų����ݣ�
	struct dianti Stack[Maxfloor+1];//�����ڳ˿�
	struct shixu sxjiankong;        //����ʱ����
	int k;
	int backfirsttime; 
};

struct people upqueue[Maxfloor+1];  //�������� 
struct people downqueue[Maxfloor+1];//�½����� 

void InputMaxTime(); 
void ShowTitle();
void init(Elevatorcanshu *&Elevator,int e);
void input(People per,Elevatorcanshu *&Elevator,int e);             //����˿� 
void Addupqueue(People &p,int in);  //������������ 
void Adddownqueue(People &p,int in);//�����½����� 
void Addshixu(int time,People p,void(*fn)(People per,Elevatorcanshu *&Elevatortemp,int temp),Elevatorcanshu *&Elevator,int e);
void GiveupWait(People per,Elevatorcanshu *&Elevator,int e);
void moni();
void Controler(Elevatorcanshu *&Elevator,int e);
void opendoor(People p,Elevatorcanshu *&Elevator,int e);
void peoplein(People p,Elevatorcanshu *&Elevator,int e);
void peopleout(People p,Elevatorcanshu *&Elevator,int e);
void UniformSpeed(People ap,Elevatorcanshu *&Elevator,int e);
void gofirst(People ap,Elevatorcanshu *&Elevator,int e);
void testinout(People p,Elevatorcanshu *&Elevator,int e);
void diantidown(People ap,Elevatorcanshu *&Elevator,int e);
void diantiup(People ap,Elevatorcanshu *&Elevator,int e);
void closedoor(People ap,Elevatorcanshu *&Elevator,int e);
void diantistop(People ap,Elevatorcanshu *&Elevator,int e);
 
int getWhere(Elevatorcanshu *&Elevator,int e);
int GetUp(Elevatorcanshu *&Elevator,int e);
int GetDown(Elevatorcanshu *&Elevator,int e);

void gotoxy(short x, short y); 
void ShowOthers();
void PrintElevatorFrame();
void DisappearEvelatorBody(int x,Elevatorcanshu *&Elevator,int e);
void ShowElevatorBody(int x,Elevatorcanshu *&Elevator,int e);
void ShowWaitingQueue(int i);
void DisappearWaitingQueue(int i);
void PrintfHelp();

int main()
{
//	system("color 0F");
	ShowTitle();
	InputMaxTime();
	system("cls");
	for(int i=0;i<=Maxfloor;i++){
		upqueue[i].next=downqueue[i].next=NULL;
	}
	id=1;
	Time=0;
	ElevatorChar[0][0]='\0';
	ElevatorChar[1][0]='\0';
	PeopleChar6[0][0]='\0';
	PeopleChar6[1][0]='\0';
	PeopleChar7[0][0]='\0';
	PeopleChar7[1][0]='\0';
	moni();
	return 0;
}
//ȷ���ն��й��λ��
void gotoxy(short x, short y)
{
	COORD coord = { x, y };
	/*COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ�䶨��Ϊ��

	typedef struct _COORD {

	SHORT X; // horizontal coordinate

	SHORT Y; // vertical coordinate
	} COORD;*/

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 	
//��ʾ������Ϣ
void ShowOthers()
{
	gotoxy(14,8);
	printf("����0");
	gotoxy(42,8);
	printf("����1"); 
	for (int i = 0; i <= Maxfloor; i++)
	{
		gotoxy(LeftElevatorX-2,LeftElevatorY-1+(4-i)*FloorHight);
		printf("%d",i);	
	}
	gotoxy(3,4);
	printf("%s",ElevatorChar[0]);
	gotoxy(33,4);
	printf("%s",ElevatorChar[1]);
	gotoxy(3,6);
	printf("%s",PeopleChar6[0]);
	gotoxy(33,6);
	printf("%s",PeopleChar6[1]);
	gotoxy(3,7);
	printf("%s",PeopleChar7[0]);
	gotoxy(33,7);
	printf("%s",PeopleChar7[0]);
}
//������ݵ���������
void PrintElevatorFrame()
{
	int j, i, k;
	for (i = 0; i <= 1; i++)
	{
		for (j = Maxfloor+1; j >= 0; j--)
		{
			if (j == Maxfloor)
			{
				gotoxy(6+i*27,9);
				printf("--------------------------");
			}
			gotoxy(6+i*27,9+j* FloorHight);
			printf("--------------------------");
			
		}
		j= Maxfloor + 1;
		for (k = 9; k <= 9 + j * FloorHight; k ++)
		{
			gotoxy(5+i*27,k);
			printf("|");
			gotoxy(5+i*27+26,k);
			printf("|");
		}
	}

}
//������x��ĵ���
void DisappearEvelatorBody(int x,Elevatorcanshu *&Elevator,int e)
{
	int i, j;
	//����������Ϊ������ɫ(��ɫ)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	for (i = LeftElevatorX + Elevator[e].k * 27; i <= LeftElevatorX + Elevator[e].k * 26 + 24; i++)
	{
		gotoxy(i, LeftElevatorY - 1 + (4 - x)*FloorHight);
		printf(" ");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//��x����ʾ����
void ShowElevatorBody(int x,Elevatorcanshu *&Elevator,int e)
{
	int i, j;
	gotoxy(LeftElevatorX+Elevator[e].k*27,LeftElevatorY-1+(4-x)*FloorHight);
	printf("[");
	for (i = 0; i <= Maxfloor; i++)
	{
		Dianti ap=Elevator[e].Stack[i].next;
		while(ap){
			printf(" %d", ap->Id);
			ap=ap->next;
		}	
	}
	gotoxy(LeftElevatorX+Elevator[e].k*26+24,LeftElevatorY - 1 + (4 - x)*FloorHight);
	printf("]");
}
//��ʾ�ȴ����еĳ˿�
void ShowWaitingQueue(int i)
{
	People p;
	p=upqueue[i].next;
	int j=0;
	while (p != NULL)
	{
		gotoxy(RightElevatorX + 26+j*6, RightElevatorY-1 + (4-p->InFloor)*FloorHight);
		printf(" %d", p->Id);
		printf("��");
		printf("%d",p->OutFloor);
		p = p->next;
		j++;
	}
	p=downqueue[i].next;
	while (p != NULL)
	{
		gotoxy(RightElevatorX + 26+j*6, RightElevatorY-1 + (4-p->InFloor)*FloorHight);
		printf(" %d", p->Id);
		printf("��");
		printf("%d",p->OutFloor);
		p = p->next;
		j++;
	}
}
//�������ڵȴ�״̬�ĳ˿�
void DisappearWaitingQueue(int i)
{
	//�����������ɫ���ñ�����ɫ��дһ�������ȥ���� 0�Ǻ�ɫ 7�ǰ�ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	ShowWaitingQueue(i);
	//������������»ָ�������ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//��ʾ˵����Ϣ
void PrintfHelp()
{
	gotoxy(60, 7);
	printf("˵����ǰ������ֱ�ʾ�˿�ID����ͷ��ʾ�ó˿����ϻ���");
	gotoxy(60, 9);
	printf("��������ִ���ó˿͵�Ŀ��¥��");
}
//��ʼ��������Ϣ 
void init(Elevatorcanshu *&Elevator,int e)
{
	int i;
	Elevator[e].Floor=Basefloor;
	printf("%d\n",Elevator[e].Floor);
	printf("%d\n",Elevator[1].Floor);
	Elevator[e].d1=Elevator[e].d2=Elevator[e].d3=0;
	Elevator[e].state=Elevator[e].prestate=Idle;
    Elevator[e].again=0;
    Elevator[e].drcl=0;
    Elevator[e].sxjiankong.f=NULL;
    Elevator[e].sxjiankong.next=NULL;
    Elevator[e].sxjiankong.person=0;
    Elevator[e].sxjiankong.xianzhitime=0;
    for(i=0;i<=Maxfloor;i++){
    	Elevator[e].CallDianti[i]=0;
    	Elevator[e].CallDown[i]=0;
    	Elevator[e].CallUp[i]=0;
    	Elevator[e].Stack[i].next=NULL;
	}
	Elevator[e].PeopleNum=0; 
}
//��ʾ����ģ�����ͷ
void ShowTitle()
{
	printf("\n\n\n");
	printf("\n\t\t*********************************************************");
	printf("\n\t\t_________________________________________________________");
	printf("\n\t\t��������������������ӭ�������ݹ���ϵͳ ������������������\n\n");
	printf("\t\t                ���ε���ģ���ʱ�䵥λΪ%.1f��\n",UnitTime);
	printf("\n\t\t*********************************************************\n");
	
}
//����������ģ������ʱ�� 
void InputMaxTime()
{
	printf("\n\t\t��������ݵ��������ʱ�䣬�ﵽ��ʱ�䣬����ϵͳ�����Զ�ֹͣ\n");
	printf("\t\t                   �������������ʱ��:");
	while (scanf("%d", &Maxtime) != 1 || Maxtime < MinTime || Maxtime > MaxTime)
	{
		printf("\t\t     �����������������루%d<=�������ʱ��<=%d��\n",MinTime,MaxTime);
		while (getchar() != '\n')
			continue;
		printf("\t\t                   �������������ʱ��:");
	}
}
//�����³˿� 
void input(People pt,Elevatorcanshu *&Elevator,int e)
{
	system("cls");
	int InFloor,OutFloor,GiveupTime,EnterTime,FlagElevator0=0,FlagElevator1=0;
	while(1){
	    printf("\t\t*********************************************************\n");
	    printf("\t\t                   ʱ��Ϊ��%d\n",Time);
	    printf("\t\t            ��%dλ�˿��߽������Ⱥ���ݡ�\n",id);
	    while(1){
	    	printf("\t\t            �����Ĳ�¥���ݵ���ǰ:_____\b\b\b");
        	scanf("%d",&InFloor);
        	if(InFloor>=0&&InFloor<=Maxfloor)break;
        	printf("\t\t            �����¥�㳬�����ޣ����������롣\n"); 
		}
		while(1){
			char c;
			printf("\t\t            �Ƿ���е���0�������루Y/N����");
			getchar();
			c=getchar();
			while(c!='Y'&&c!='N'){
				printf("\t\t            �����ʽ��������������,�Ƿ���е���0��Y/N����");
				getchar();
				c=getchar();
			}
			if(c=='Y'){
				FlagElevator0=1;
			} 
			printf("\t\t            �Ƿ���е���1�������루Y/N����");
			getchar();
			scanf("%c",&c);
			while(c!='Y'&&c!='N'){
				printf("\t\t            �����ʽ��������������,�Ƿ���е���1��Y/N����");
				getchar();
				scanf("%c",&c);
			}
			if(c=='Y'){
				FlagElevator1=1;
			}
			if(FlagElevator0||FlagElevator1)break;
			printf("\t\t            ����û�к��е��ݣ�����������Ҫ���еĵ��ݡ�\n");
		}
	    while(1){
	    	printf("\t\t            ��Ҫȥ�Ĳ�¥:_____\b\b\b");
        	scanf("%d",&OutFloor);
        	if(OutFloor>=0&&OutFloor<=Maxfloor)break;
        	printf("\t\t            �����¥�㳬�����ޣ����������롣\n");
		}
        printf("\t\t            �������̵ĵȺ�ʱ��:_____\b\b\b");
        scanf("%d",&GiveupTime);
        printf("\t\t            ��һ���˿ͳ��ֵ�ʱ����:_____\b\b\b");
        scanf("%d",&EnterTime);
        printf("\t\t*********************************************************\n\n");
        if(OutFloor!=InFloor){
        	break;
		}
		printf("\t\t*********************************************************\n");
		printf("\t\t������󣺳˿�Ҫȥ��¥�����䵱ǰ����¥����ͬ������������\n");
		printf("\t\t*********************************************************\n\n");
	}
	People p;
	p=(People)malloc(sizeof(struct people));
	p->EnterTime=Time;
	p->Id=id++;
	p->InFloor=InFloor;
	p->OutFloor=OutFloor;
	p->GiveupTime=GiveupTime;
	p->FlagElevator0=FlagElevator0;
	p->FlagElevator1=FlagElevator1;
	p->next=NULL;
	p->pre=NULL;
	Exist[id-1]=1;
	if(OutFloor>InFloor){
		Addupqueue(p,InFloor);
		if(FlagElevator0){
			Elevator[0].CallUp[InFloor]=1;
		}
		if(FlagElevator1){
			Elevator[1].CallUp[InFloor]=1;
		}
	}else{
		Adddownqueue(p,InFloor);
		if(FlagElevator0){
			Elevator[0].CallDown[InFloor]=1;
		}
		if(FlagElevator1){
			Elevator[1].CallDown[InFloor]=1;
		}

	}
	if(FlagElevator0&&FlagElevator1){
		flagelevator=1;
	}
	if(!FlagElevator0&&FlagElevator1){
		Addshixu(GiveupTime,p,GiveupWait,Elevator,1);
		Addshixu(EnterTime,NULL,input,Elevator,1);
	}
	else{
		Addshixu(GiveupTime,p,GiveupWait,Elevator,0);
		Addshixu(EnterTime,NULL,input,Elevator,0);
	}

	system("cls");
	ShowOthers();
	PrintElevatorFrame();							//������ݿ��
	PrintfHelp();
	ShowElevatorBody(Elevator[0].Floor,Elevator,0);  
	ShowElevatorBody(Elevator[1].Floor,Elevator,1);                         //�����������
	int i;
	for(i=0;i<=Maxfloor;i++){
		ShowWaitingQueue(i);
	}
}
// ������������
void Addupqueue(People &p,int in)
{
	People q=&upqueue[in];
	while (q->next!=NULL){
		q=q->next;
	}
	q->next=p;
	p->pre=q;
}
// �����½����� 
void Adddownqueue(People &p,int in)
{
	People q=&downqueue[in];
	while (q->next!=NULL){
		q=q->next;
	}
	q->next=p;
	p->pre=q;
}
// ��������������һ����ʱ��˳�����еĶ�����
void Addshixu(int t,People p,void(*fn)(People per,Elevatorcanshu *&Elevatortemp,int temp),Elevatorcanshu *&Elevator,int e)
{
	int time1=Time+t;
	Shixu r=&Elevator[e].sxjiankong;
	Shixu q;
	q=(Shixu)malloc(sizeof(struct shixu));
	q->xianzhitime=time1;
	if(p!=NULL){
		q->person=(People)malloc(sizeof(struct people));
		q->person->pre=p->pre;
		q->person->Id=p->Id;
		q->person->InFloor=p->InFloor;
	}
	else {
		q->person=NULL;
	}
	q->f=fn;
	q->next=NULL;
	while(r->next!=NULL){
		if(r->next->xianzhitime>time1)break;
		r=r->next;
	}
	q->next=r->next;
	r->next=q;
}
//�˿ͷ����ȴ����� 
void GiveupWait(People per,Elevatorcanshu *&Elevator,int e)
{
	if(Exist[per->Id]==0){
		return ;
	}
	else if(per->InFloor==Elevator[0].Floor&&Elevator[0].state==Idle&&per->FlagElevator0&&Elevator[0].PeopleNum<MaxPeopleNum)
	    return ;
	else if(per->InFloor==Elevator[1].Floor&&Elevator[1].state==Idle&&per->FlagElevator1&&Elevator[1].PeopleNum<MaxPeopleNum)
	    return ;
	DisappearWaitingQueue(per->InFloor);
	int i,a,num;
	if(per->FlagElevator0)
	{
		gotoxy(3,6);
		printf("                           ");
		gotoxy(3,7);
		printf("                           ");
		gotoxy(3,6);
		printf("�˿�%d�����Ⱥ�,�뿪��",per->Id);
		a=per->Id;
		num=0;
		strcpy(PeopleChar6[0],"�˿�");
		for(i=0;PeopleChar6[0][i]!='\0';i++){
		}
		do{
			num++;
			a=a/10;
		}while(a);
		a=per->Id;
		num--;
		while(num!=0){
			PeopleChar6[0][i]='0'+a/(int)(pow(10,num));
			a=a%(int)(pow(10,num));
			num--;
			i++;
		}
		PeopleChar6[0][i]='0'+a;
		PeopleChar6[0][i+1]='\0';
		strcat(PeopleChar6[0],"�����Ⱥ�,�뿪��");
		strcpy(PeopleChar7[0]," ");
	}
	if(per->FlagElevator1)
	{
		gotoxy(3+30,6);
		printf("                           ");
		gotoxy(3+30,7);
		printf("                           ");
		gotoxy(3+30,6);
		printf("�˿�%d�����Ⱥ�,�뿪��",per->Id);
		a=per->Id;
		num=0;
		strcpy(PeopleChar6[1],"�˿�");
		for(i=0;PeopleChar6[1][i]!='\0';i++){
		}
		do{
			num++;
			a=a/10;
		}while(a);
		a=per->Id;
		num--;
		while(num!=0){
			PeopleChar6[1][i]='0'+a/(int)(pow(10,num));
			a=a%(int)(pow(10,num));
			num--;
			i++;
		}
		PeopleChar6[1][i]='0'+a;
		PeopleChar6[1][i+1]='\0';
		strcat(PeopleChar6[1],"�����Ⱥ�,�뿪��");
		strcpy(PeopleChar7[1]," ");
	}
	int infloor=per->InFloor;
	int outfloor=per->OutFloor;
	Exist[per->Id]=0;
	People q=per->pre,ap=q->next;
	q->next=ap->next;
	if(ap->next!=NULL)ap->next->pre=q;
	ShowWaitingQueue(per->InFloor);
	free(ap);
} 
//����ģ���һ����ʱ�� 
void moni()
{
	Elevatorcanshu *Elevator;
	Elevator=(Elevatorcanshu *)malloc(sizeof(Elevatorcanshu)*2);
	Elevator[0].k=0;
	Elevator[1].k=1;
    init(Elevator,0);
	init(Elevator,1);
    input(NULL,Elevator,0);
	while(Time<=Maxtime){
		if(Elevator[0].sxjiankong.next||flagelevator){
			do{
				Elevator[0].again=0;
				Controler(Elevator,0);
			}while(Elevator[0].again==1);
		}
	    if(Elevator[1].sxjiankong.next||flagelevator){
	    	do{
				Elevator[1].again=0;
				Controler(Elevator,1);
			}while(Elevator[1].again==1);
		}
		Shixu p=Elevator[0].sxjiankong.next;
		Shixu q=Elevator[1].sxjiankong.next;
		if(p==NULL&&q==NULL){
			Time=Maxtime;
		}
		while(p&&p->xianzhitime<=Time){
			Elevator[0].sxjiankong.next=p->next;
			p->f(p->person,Elevator,0);
			free(p);
			p=Elevator[0].sxjiankong.next;
		}
		while(q&&q->xianzhitime<=Time){
			Elevator[1].sxjiankong.next=q->next;
			q->f(q->person,Elevator,1);
			free(q);
			q=Elevator[1].sxjiankong.next;
		}
		Time++;
		gotoxy(20,2);
		printf("ʱ��Ϊ�� %d", Time);
		Sleep(1000*UnitTime);
	}
	gotoxy(60,30);
	printf("��ʾ����������������˳�");
	getchar();
	getchar();
}
// �Ե��ݽ��п���
void Controler(Elevatorcanshu *&Elevator,int e)
{
	int flag,i;
	if(Elevator[e].state==Idle){
		if(Elevator[e].prestate==Idle){
			Elevator[e].prestate=getWhere(Elevator,e);
		}
		if(Elevator[e].d1==0&&Elevator[e].d3==0&&Elevator[e].CallDianti[Elevator[e].Floor]==2){
			Elevator[e].CallDianti[Elevator[e].Floor]=0;
			flag=0;
			for(i=Elevator[e].Floor+1;i<=Maxfloor;i++){
				if(Elevator[e].CallDown[i]||Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]){
					flag=1;
					break;
				}
			}
			for(i=Elevator[e].Floor-1;i>=0;i--){
				if(Elevator[e].CallDown[i]||Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]){
					flag=1;
					break;
				}
			}
			if(flag){
				return;
			}
			gotoxy(3+30*Elevator[e].k,4);
			printf("                        ");
			gotoxy(3+30*Elevator[e].k,4);
			printf("�����������%d",Elevator[e].k);
			if(Elevator[e].k){
				strcpy(ElevatorChar[1],"�����������1");
			}
			else{
				strcpy(ElevatorChar[0],"�����������0");
			}
            return;
		}
		if(!Elevator[e].d1&&!Elevator[e].d3&&Elevator[e].prestate==Goingup&&((Elevator[e].CallUp[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)||Elevator[e].CallDianti[Elevator[e].Floor]))
		{
			Elevator[e].d1=1;Elevator[e].d2=1;
			if(Elevator[e].drcl){
				Elevator[e].drcl=0;
				gotoxy(3+30*Elevator[e].k,4);
				printf("                        ");
				gotoxy(3+30*Elevator[e].k,4);
				printf("����%d����Ϲ���",Elevator[e].k);
				if(Elevator[e].k){
					strcpy(ElevatorChar[1],"����1����Ϲ���");
				}
				else{
					strcpy(ElevatorChar[0],"����0����Ϲ���");
				}
	            Addshixu(Time-Elevator[e].drcltime,NULL,opendoor,Elevator,e);
			}
			else Addshixu(Doortime,NULL,opendoor,Elevator,e);
			return ;		
		}
		else if(!Elevator[e].d1&&!Elevator[e].d3&&Elevator[e].prestate==Goingdown&&((Elevator[e].CallDown[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)||Elevator[e].CallDianti[Elevator[e].Floor]))
		{
            Elevator[e].d1=1;Elevator[e].d2=1;
            if(Elevator[e].drcl){
                Elevator[e].drcl=0;
				gotoxy(3+30*Elevator[e].k,4);
				printf("                        ");
				gotoxy(3+30*Elevator[e].k,4);
				printf("����%d����Ϲ���",Elevator[e].k);
			    if(Elevator[e].k){
					strcpy(ElevatorChar[1],"����1����Ϲ���");
				}
				else{
					strcpy(ElevatorChar[0],"����0����Ϲ���");
				}
                Addshixu(Time-Elevator[e].drcltime,NULL,opendoor,Elevator,e);
            }
            else Addshixu(Doortime,NULL,opendoor,Elevator,e);
            return ;
        }
        else if(Elevator[e].d3==1&&Elevator[e].prestate==Goingup&&(Elevator[e].CallUp[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)){
            Elevator[e].d1=1;
			Elevator[e].d3=0;   //�Ż�û�أ������˽���
            Addshixu(Peopletime,NULL,peoplein,Elevator,e);
        }
        else if(Elevator[e].d3==1&&Elevator[e].prestate==Goingdown&&(Elevator[e].CallDown[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)){
            Elevator[e].d1=1;
			Elevator[e].d3=0;   //�Ż�û�أ������˽���
            Addshixu(Peopletime,NULL,peoplein,Elevator,e);
        }
        else if(Elevator[e].d1==0&&Elevator[e].d3==0&&Elevator[e].drcl==0&&Elevator[e].prestate==Goingup&&!((Elevator[e].CallUp[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)||Elevator[e].CallDianti[Elevator[e].Floor]))
		{
            int temp=GetUp(Elevator,e);
            if(temp==1){
                Elevator[e].state=Goingup;
                Addshixu(Accelerate,NULL,UniformSpeed,Elevator,e);
            }
            else {
                Elevator[e].prestate=Idle;
                Elevator[e].state=Idle;
                Elevator[e].again=1;
            }
        }
        else if(Elevator[e].d1==0&&Elevator[e].d3==0&&Elevator[e].drcl==0&&Elevator[e].prestate==Goingdown&&!((Elevator[e].CallDown[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)||Elevator[e].CallDianti[Elevator[e].Floor]))
		{
            int temp=GetDown(Elevator,e);
            if(temp==1){
                Elevator[e].state=Goingdown;
                Addshixu(Accelerate,NULL,UniformSpeed,Elevator,e);
            }
            else {
                Elevator[e].prestate=Idle;
                Elevator[e].state=Idle;
                Elevator[e].again=1;
            }
        }
        else if(!Elevator[e].d1&&!Elevator[e].d3&&Elevator[e].drcl==0&&Elevator[e].d2){
            Elevator[e].d2=0;
            Elevator[e].backfirsttime=Time;
            Addshixu(Backtime,NULL,gofirst,Elevator,e);
        }
	}
}
//���ݻ�ȡ�²�ָ�� 
int getWhere(Elevatorcanshu *&Elevator,int e)
{
    int timeUp=-1,timeDown=-1;
    if(upqueue[Elevator[e].Floor].next!=NULL&&Elevator[e].CallUp[Elevator[e].Floor]){
        timeUp=upqueue[Elevator[e].Floor].next->EnterTime;
    }
    if(downqueue[Elevator[e].Floor].next!=NULL&&Elevator[e].CallDown[Elevator[e].Floor]){
        timeDown=downqueue[Elevator[e].Floor].next->EnterTime;
    }
    if(timeUp!=-1||timeDown!=-1){
        if(timeUp!=-1&&timeDown!=-1){
            return timeUp<timeDown?Goingup:Goingdown;
        }
        else if(timeUp!=-1){
            return Goingup;
        }
        else if(timeDown!=-1){
            return Goingdown;
        }
    }
    else{
        timeUp=Maxtime+1; timeDown=Maxtime+1;
        for(int i=Elevator[e].Floor+1;i<=Maxfloor;i++){
            if(upqueue[i].next!=NULL&&Elevator[e].CallUp[i]){
                timeUp=min(timeUp,upqueue[i].next->EnterTime);
            }
            if(downqueue[i].next!=NULL&&Elevator[e].CallDown[i]){
                timeUp=min(timeUp,downqueue[i].next->EnterTime);
            }
        }
        for(int i=Elevator[e].Floor-1;i>=0;i--){
            if(upqueue[i].next!=NULL&&Elevator[e].CallUp[i]){
                timeDown=min(timeDown,upqueue[i].next->EnterTime);
            }
            if(downqueue[i].next!=NULL&&Elevator[e].CallDown[i]){
                timeDown=min(timeDown,downqueue[i].next->EnterTime);
            }
        }
        if(timeUp!=Maxtime+1||timeDown!=Maxtime+1){
            if(timeUp!=Maxtime+1&&timeDown!=Maxtime+1){
                return timeUp<timeDown?Goingup:Goingdown;
            }
            else if(timeUp!=Maxtime+1){
                return Goingup;
            }
            else return Goingdown;
        }
        else{
            if(Elevator[e].CallDianti[Basefloor]==2&&Basefloor>Elevator[e].Floor)return Goingup;
            else if(Elevator[e].CallDianti[Basefloor]==2&&Basefloor<Elevator[e].Floor)return Goingdown;
            return Idle;
        }
    }
}
//�򿪵����� 
void opendoor(People p,Elevatorcanshu *&Elevator,int e)
{
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("����%d�ſ���",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"����1�ſ���");
	}
	else{
		strcpy(ElevatorChar[0],"����0�ſ���");
	}
    if(Elevator[e].Stack[Elevator[e].Floor].next){
        Addshixu(Peopletime,NULL,peopleout,Elevator,e);
    }
    else if(Elevator[e].prestate==Goingup&&upqueue[Elevator[e].Floor].next&&Elevator[e].PeopleNum<MaxPeopleNum){
        Addshixu(Peopletime,NULL,peoplein,Elevator,e);
    }
    else if(Elevator[e].prestate==Goingdown&&downqueue[Elevator[e].Floor].next&&Elevator[e].PeopleNum<MaxPeopleNum){
        Addshixu(Peopletime,NULL,peoplein,Elevator,e);
    }
    else {
    	if(Elevator[e].PeopleNum<MaxPeopleNum){
    		Elevator[e].CallUp[Elevator[e].Floor]=0;
		}
        Elevator[e].CallDown[Elevator[e].Floor]=0;
        Elevator[e].CallDianti[Elevator[e].Floor]=0;
        Elevator[e].d1=0; Elevator[e].d3=1;   //û�˽����������ǿ��ŵ�
        Elevator[e].testdoortime=Time;
        Addshixu(Diantitime,NULL,testinout,Elevator,e);
    }
}
//�˿ͽ������ 
void peoplein(People p,Elevatorcanshu *&Elevator,int e)
{
	int a,num,i;
    if(Elevator[e].prestate==Goingup){
        People ap=upqueue[Elevator[e].Floor].next;
        if(ap&&Elevator[e].PeopleNum<MaxPeopleNum){
        	DisappearEvelatorBody(Elevator[e].Floor,Elevator,e);
        	DisappearWaitingQueue(Elevator[e].Floor);
			gotoxy(3+30*Elevator[e].k,6);
			printf("                           ");
			gotoxy(3+30*Elevator[e].k,7);
			printf("                           ");
			gotoxy(3+30*Elevator[e].k,6);
			printf("�˿�%d�ɹ��������%d\n",ap->Id,Elevator[e].k);
			a=ap->Id;
			num=0;
			strcpy(PeopleChar6[Elevator[e].k],"�˿�");
			for(i=0;PeopleChar6[Elevator[e].k][i]!='\0';i++){
			}
			do{
				num++;
				a=a/10;
			}while(a);
			a=ap->Id;
			num--;
			while(num!=0){
				PeopleChar6[Elevator[e].k][i]='0'+a/(int)(pow(10,num));
				a=a%(int)(pow(10,num));
				num--;
				i++;
			}
			PeopleChar6[Elevator[e].k][i]='0'+a;
			PeopleChar6[Elevator[e].k][i+1]='\0';
			if(Elevator[e].k){
				strcat(PeopleChar6[Elevator[e].k],"�ɹ��������1");
			}
			else{
				strcat(PeopleChar6[Elevator[e].k],"�ɹ��������0");
			}
			strcpy(PeopleChar7[Elevator[e].k]," ");
            Elevator[e].PeopleNum++;
            Exist[ap->Id]=0;
            upqueue[Elevator[e].Floor].next=ap->next;
            Dianti pr=(Dianti)malloc(sizeof(struct dianti));
            int i=ap->OutFloor;
            Elevator[e].CallDianti[i]=1;
            pr->next=Elevator[e].Stack[i].next;
            Elevator[e].Stack[i].next=pr;
            pr->Id=ap->Id;
            ShowElevatorBody(Elevator[e].Floor,Elevator,e);
            ShowWaitingQueue(Elevator[e].Floor);
            free(ap);
        }
        if(upqueue[Elevator[e].Floor].next&&Elevator[e].PeopleNum<MaxPeopleNum)
			Addshixu(Peopletime,NULL,peoplein,Elevator,e);
        else {
        	if(upqueue[Elevator[e].Floor].next){	
        		People t=upqueue[Elevator[e].Floor].next;
        		gotoxy(3+30*Elevator[e].k,4);
				printf("                  ");
				gotoxy(3+30*Elevator[e].k,4);
				printf("����%d������",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(ElevatorChar[1],"����1������");
				}
				else{
					strcpy(ElevatorChar[0],"����0������");
				}
        		gotoxy(3+30*Elevator[e].k,6);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,7);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,6);
				while(t){
					printf("�˿�%d��",t->Id);
					a=t->Id;
					num=0;
					strcpy(PeopleChar6[Elevator[e].k],"�˿�");
					for(i=0;PeopleChar6[Elevator[e].k][i]!='\0';i++){
					}
					do{
						num++;
						a=a/10;
					}while(a);
					a=t->Id;
					num--;
					while(num!=0){
						PeopleChar6[Elevator[e].k][i]='0'+a/(int)(pow(10,num));
						a=a%(int)(pow(10,num));
						num--;
						i++;
					}
					PeopleChar6[Elevator[e].k][i]=',';
					PeopleChar6[Elevator[e].k][i+1]='\0';
					t=t->next;
				}
				gotoxy(3+30*Elevator[e].k,7);
				printf("�޷������������%d",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(PeopleChar7[Elevator[e].k],"�޷������������1");
				}
				else{
					strcpy(PeopleChar7[Elevator[e].k],"�޷������������0");
				}
			}
			if(!upqueue[Elevator[e].Floor].next){
				Elevator[e].CallUp[Elevator[e].Floor]=0;	
			}
            Elevator[e].CallDianti[Elevator[e].Floor]=0;
            Elevator[e].d1=0;Elevator[e].d3=1;  //û�˽����������ǿ��ŵ�
            Elevator[e].testdoortime=Time;
            Addshixu(Diantitime,NULL,testinout,Elevator,e);
        }
    }
    else if(Elevator[e].prestate==Goingdown&&Elevator[e].PeopleNum<MaxPeopleNum){
        People ap=downqueue[Elevator[e].Floor].next;
        if(ap&&Elevator[e].PeopleNum<MaxPeopleNum){
        	DisappearEvelatorBody(Elevator[e].Floor,Elevator,e);
        	DisappearWaitingQueue(Elevator[e].Floor);
        	gotoxy(3+30*Elevator[e].k,6);
        	printf("                           ");
			gotoxy(3+30*Elevator[e].k,7);
			printf("                           ");
			gotoxy(3+30*Elevator[e].k,6);
			printf("�˿�%d�ɹ��������%d\n",ap->Id,Elevator[e].k);
			a=ap->Id;
			num=0;
			strcpy(PeopleChar6[Elevator[e].k],"�˿�");
			for(i=0;PeopleChar6[Elevator[e].k][i]!='\0';i++){
			}
			do{
				num++;
				a=a/10;
			}while(a);
			a=ap->Id;
			num--;
			while(num!=0){
				PeopleChar6[Elevator[e].k][i]='0'+a/(int)(pow(10,num));
				a=a%(int)(pow(10,num));
				num--;
				i++;
			}
			PeopleChar6[Elevator[e].k][i]='0'+a;
			PeopleChar6[Elevator[e].k][i+1]='\0';
			if(Elevator[e].k){
				strcat(PeopleChar6[Elevator[e].k],"�ɹ��������1");
			}
			else{
				strcat(PeopleChar6[Elevator[e].k],"�ɹ��������0");
			}
			strcpy(PeopleChar7[Elevator[e].k]," ");
            Elevator[e].PeopleNum++;
            Exist[ap->Id]=0;
            downqueue[Elevator[e].Floor].next=ap->next;
            Dianti pr=(Dianti)malloc(sizeof(struct dianti));
            int i=ap->OutFloor;
            Elevator[e].CallDianti[i]=1;
            pr->next=Elevator[e].Stack[i].next;
            Elevator[e].Stack[i].next=pr;
            pr->Id=ap->Id;
            ShowElevatorBody(Elevator[e].Floor,Elevator,e);
            ShowWaitingQueue(Elevator[e].Floor);
            free(ap);
        }
        if(downqueue[Elevator[e].Floor].next&&Elevator[e].PeopleNum<MaxPeopleNum)
			Addshixu(Peopletime,NULL,peoplein,Elevator,e);
        else {
        	if(downqueue[Elevator[e].Floor].next){
        		People t=downqueue[Elevator[e].Floor].next;
				gotoxy(3+30*Elevator[e].k,4);
				printf("                        ");
				gotoxy(3+30*Elevator[e].k,4);
				printf("����%d������",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(ElevatorChar[1],"����1������");
				}
				else{
					strcpy(ElevatorChar[0],"����0������");
				}
        		gotoxy(3+30*Elevator[e].k,6);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,7);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,6);
				while(t){
					printf("�˿�%d��",t->Id);
					a=t->Id;
					num=0;
					strcpy(PeopleChar6[Elevator[e].k],"�˿�");
					for(i=0;PeopleChar6[Elevator[e].k][i]!='\0';i++){
					}
					do{
						num++;
						a=a/10;
					}while(a);
					a=t->Id;
					num--;
					while(num!=0){
						PeopleChar6[Elevator[e].k][i]='0'+a/(int)(pow(10,num));
						a=a%(int)(pow(10,num));
						num--;
						i++;
					}
					PeopleChar6[Elevator[e].k][i]=',';
					PeopleChar6[Elevator[e].k][i+1]='\0';
					t=t->next;
				}
				printf("�޷������������%d",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(PeopleChar7[Elevator[e].k],"�޷������������1");
				}
				else{
					strcpy(PeopleChar7[Elevator[e].k],"�޷������������0");
				}
			}
			if(!downqueue[Elevator[e].Floor].next){
				Elevator[e].CallDown[Elevator[e].Floor]=0;
			}
            Elevator[e].CallDianti[Elevator[e].Floor]=0;
            Elevator[e].d1=0;Elevator[e].d3=1;  //û�˽����������ǿ��ŵ�
            Elevator[e].testdoortime=Time;
            Addshixu(Diantitime,NULL,testinout,Elevator,e);
        }
    }
}
//�˿��߳����� 
void peopleout(People p,Elevatorcanshu *&Elevator,int e)
{
	int a,num,i;
    if(Elevator[e].Stack[Elevator[e].Floor].next){
    	DisappearEvelatorBody(Elevator[e].Floor,Elevator,e);
        Dianti ap=Elevator[e].Stack[Elevator[e].Floor].next;
        Elevator[e].Stack[Elevator[e].Floor].next=ap->next;
        Elevator[e].PeopleNum--;
		ShowElevatorBody(Elevator[e].Floor,Elevator,e);
		gotoxy(3+30*Elevator[e].k,6);
		printf("                           ");
		gotoxy(3+30*Elevator[e].k,7);
		printf("                           ");
		gotoxy(3+30*Elevator[e].k,6);
		printf("�˿�%d�߳�����%d",ap->Id,Elevator[e].k);
		a=ap->Id;
		num=0;
		strcpy(PeopleChar6[Elevator[e].k],"�˿�");
		for(i=0;PeopleChar6[Elevator[e].k][i]!='\0';i++){
		}
		do{
			num++;
			a=a/10;
		}while(a);
		a=ap->Id;
		num--;
		while(num!=0){
			PeopleChar6[Elevator[e].k][i]='0'+a/(int)(pow(10,num));
			a=a%(int)(pow(10,num));
			num--;
			i++;
		}
		PeopleChar6[Elevator[e].k][i]='0'+a;
		PeopleChar6[Elevator[e].k][i+1]='\0';
		if(Elevator[e].k){
			strcat(PeopleChar6[Elevator[e].k],"�߳�����1");
		}
		else{
			strcat(PeopleChar6[Elevator[e].k],"�߳�����0");
		}
		strcpy(PeopleChar7[Elevator[e].k]," ");	
        free(ap);
    }
    if(Elevator[e].Stack[Elevator[e].Floor].next){
        Addshixu(Peopletime,NULL,peopleout,Elevator,e);
    }
    else if(Elevator[e].prestate==Goingup&&upqueue[Elevator[e].Floor].next){
        Addshixu(Peopletime,NULL,peoplein,Elevator,e);
    }
    else if(Elevator[e].prestate==Goingdown&&downqueue[Elevator[e].Floor].next){
        Addshixu(Peopletime,NULL,peoplein,Elevator,e);
    }
    else {
        if(Elevator[e].prestate==Goingup){
            Elevator[e].CallUp[Elevator[e].Floor]=0;
            int flag=0;
            for(int i=Elevator[e].Floor+1;i<=Maxfloor;i++){
                if(Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]||Elevator[e].CallDown[i]){
                    flag=1;
					break;
                }
            }
            if(flag==0){
                if(downqueue[Elevator[e].Floor].next!=NULL){
                    Elevator[e].prestate=Goingdown;
                    Addshixu(Peopletime,NULL,peoplein,Elevator,e);
					return;
                }
            }
        }
        else if(Elevator[e].prestate==Goingdown){
            Elevator[e].CallDown[Elevator[e].Floor]=0;
            int flag=0;
            for(int i=Elevator[e].Floor-1;i>=0;i--){
                if(Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]||Elevator[e].CallDown[i]){
                    flag=1;
					break;
                }
            }
            if(flag==0){
                if(upqueue[Elevator[e].Floor].next!=NULL){
                    Elevator[e].prestate=Goingup;
                    Addshixu(Peopletime,NULL,peoplein,Elevator,e);
					return;
                }
            }
        }
        Elevator[e].CallDianti[Elevator[e].Floor]=0;
        Elevator[e].d1=0; Elevator[e].d3=1;     ////û�˽����������ǿ��ŵ�
        Elevator[e].testdoortime=Time;
        Addshixu(Diantitime,NULL,testinout,Elevator,e);
    }
}
//�����Ƿ����� 
int GetUp(Elevatorcanshu *&Elevator,int e)
{
    for(int i=Elevator[e].Floor+1;i<=Maxfloor;i++){
        if(Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]||Elevator[e].CallDown[i])
			return 1;
    }
    return 0;
}
//�����Ƿ��½� 
int GetDown(Elevatorcanshu *&Elevator,int e)
{
    for(int i=Elevator[e].Floor-1;i>=0;i--){
        if(Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]||Elevator[e].CallDown[i])
			return 1;
    }
    return 0;
}
//���ݼ�����ɣ������������ٶ� 
void UniformSpeed(People ap,Elevatorcanshu *&Elevator,int e)
{
	if(Elevator[e].state==Goingup){
		gotoxy(3+30*Elevator[e].k,4);
		printf("                        ");
		gotoxy(3+30*Elevator[e].k,4);
		printf("����%d�Ѽ���������",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"����1�Ѽ���������");
		}
		else{
			strcpy(ElevatorChar[0],"����0�Ѽ���������");
		}
		Addshixu(Uptime,NULL,diantiup,Elevator,e);
	}else{
		gotoxy(3+30*Elevator[e].k,4);
		printf("                        ");
		gotoxy(3+30*Elevator[e].k,4);
		printf("����%d�Ѽ����½���",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"����1�Ѽ����½���");
		}
		else{
			strcpy(ElevatorChar[0],"����0�Ѽ����½���");
		}
		Addshixu(Downtime,NULL,diantidown,Elevator,e);
	}
}
//����ȥ����
void gofirst(People ap,Elevatorcanshu *&Elevator,int e)
{
	if(Elevator[e].state!=Idle||Elevator[e].backfirsttime+Backtime!=Time)
		return;
	if(Elevator[e].Floor==Basefloor&&Elevator[e].d2==0){
		Elevator[e].CallDianti[Basefloor]=2;
		return;
	}
	else if(Elevator[e].Floor==Basefloor)
		return;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                         ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("�����������%d!������%d��",Elevator[e].k,Basefloor);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"�����������1!������1��");
	}
	else{
		strcpy(ElevatorChar[0],"�����������0!������1��");
	}
	Elevator[e].CallDianti[Basefloor]=2;
}
// �����˿ͽ��������ڹ���
void testinout(People p,Elevatorcanshu *&Elevator,int e)
{
    if(Elevator[e].prestate==Goingup){
        if((upqueue[Elevator[e].Floor].next&&Elevator[e].PeopleNum<MaxPeopleNum)||Elevator[e].Stack[Elevator[e].Floor].next||Elevator[e].testdoortime+Diantitime!=Time)
			return;
		if(!upqueue[Elevator[e].Floor].next){
			Elevator[e].CallUp[Elevator[e].Floor]=0;
		}
        Elevator[e].CallDianti[Elevator[e].Floor]=0;
        Elevator[e].d1=0;Elevator[e].d3=0;
        Elevator[e].drcl=1; Elevator[e].drcltime=Time;
		gotoxy(3+30*Elevator[e].k,4);
		printf("                        ");
		gotoxy(3+30*Elevator[e].k,4);
		printf("����%d���ڹ���",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"����1���ڹ���");
		}
		else{
			strcpy(ElevatorChar[0],"����0���ڹ���");
		}
        Addshixu(Doortime,NULL,closedoor,Elevator,e);
    }
    else if(Elevator[e].prestate==Goingdown){
        if((downqueue[Elevator[e].Floor].next&&Elevator[e].PeopleNum<MaxPeopleNum)||Elevator[e].Stack[Elevator[e].Floor].next||Elevator[e].testdoortime+Diantitime!=Time)
			return;
		if(!downqueue[Elevator[e].Floor].next){
			Elevator[e].CallDown[Elevator[e].Floor]=0;
		}
        Elevator[e].CallDianti[Elevator[e].Floor]=0;
        Elevator[e].d1=0;Elevator[e].d3=0;
        Elevator[e].drcl=1; Elevator[e].drcltime=Time;
		gotoxy(3+30*Elevator[e].k,4);
		printf("                        ");
		gotoxy(3+30*Elevator[e].k,4);
		printf("����%d���ڹ���",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"����1���ڹ���");
		}
		else{
			strcpy(ElevatorChar[0],"����0���ڹ���");
		}
        Addshixu(Doortime,NULL,closedoor,Elevator,e);
    }
}
//��������
void diantiup(People ap,Elevatorcanshu *&Elevator,int e)
{
	Elevator[e].Floor++;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("����%d��������",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"����1��������");
	}
	else{
		strcpy(ElevatorChar[0],"����0��������");
	}
	DisappearEvelatorBody(Elevator[e].Floor-1,Elevator,e);
	ShowElevatorBody(Elevator[e].Floor,Elevator,e);
	if(Elevator[e].prestate==Goingup&&(Elevator[e].CallUp[Elevator[e].Floor]||Elevator[e].CallDianti[Elevator[e].Floor]||Elevator[e].CallDown[Elevator[e].Floor])){
		if(Elevator[e].CallUp[Elevator[e].Floor]||Elevator[e].CallDianti[Elevator[e].Floor])
			Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
		else{
		    int flag=0;
            for(int i=Elevator[e].Floor+1;i<=Maxfloor;i++){
                if(Elevator[e].CallUp[i]||Elevator[e].CallDianti[i]||Elevator[e].CallDown[i]){
					flag=1;
					break;
				}
            }
            if(flag==0){
				Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
			}
            else{
                Addshixu(Uptime,NULL,diantiup,Elevator,e);
            }
		}
	}
	else if(Elevator[e].prestate==Goingdown&&(Elevator[e].CallUp[Elevator[e].Floor]||Elevator[e].CallDianti[Elevator[e].Floor]||Elevator[e].CallDown[Elevator[e].Floor])){
        if(Elevator[e].CallDown[Elevator[e].Floor]||Elevator[e].CallDianti[Elevator[e].Floor])
			Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
        else{
            int flag=0;
            for(int i=Elevator[e].Floor-1;i>=0;i--){
                if(Elevator[e].CallUp[i]||Elevator[e].CallDianti[i]||Elevator[e].CallDown[i]){
					flag=1;
					break;
				}
            }
            if(flag==0)Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
            else{
                Addshixu(Uptime,NULL,diantiup,Elevator,e);
            }
        }
	}
	else{
		if(Elevator[e].Floor==Maxfloor){
			Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
		}else{
			Addshixu(Uptime,NULL,diantiup,Elevator,e);
		}
	}
}
//�����½� 
void diantidown(People ap,Elevatorcanshu *&Elevator,int e)
{
	Elevator[e].Floor--;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("����%d�����½�",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"����1�����½�");
	}
	else{
		strcpy(ElevatorChar[0],"����0�����½�");
	}
	DisappearEvelatorBody(Elevator[e].Floor+1,Elevator,e);
	ShowElevatorBody(Elevator[e].Floor,Elevator,e);
	if(Elevator[e].prestate==Goingup&&(Elevator[e].CallUp[Elevator[e].Floor]||Elevator[e].CallDianti[Elevator[e].Floor])){
		Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
	}
	else if(Elevator[e].prestate==Goingdown&&(Elevator[e].CallDown[Elevator[e].Floor]||Elevator[e].CallDianti[Elevator[e].Floor])){
        Addshixu(UpSlowdown,NULL,diantistop,Elevator,e);
	}
	else{
		if(Elevator[e].Floor==0){
			Addshixu(DownSlowdown,NULL,diantistop,Elevator,e);
		}else{
			Addshixu(Downtime,NULL,diantidown,Elevator,e);
		}
	}
}
//�����Ź��� 
void closedoor(People ap,Elevatorcanshu *&Elevator,int e)
{
    if(Elevator[e].drcl==0||Time!=Elevator[e].drcltime+Doortime)
		return;
    Elevator[e].drcl=0;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("����%d�Ź���",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"����1�Ź���");
	}
	else{
		strcpy(ElevatorChar[0],"����0�Ź���");
	}
}
//����ͣ�� 
void diantistop(People ap,Elevatorcanshu *&Elevator,int e)
{
    Elevator[e].state=Idle;
    Elevator[e].d1=0;Elevator[e].d3=0;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("����%dͣ�ˣ���ǰ����%d",Elevator[e].k,Elevator[e].Floor);
	int a=Elevator[e].Floor,i;
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"����1ͣ�ˣ���ǰ����");
		for(i=0;ElevatorChar[1][i]!='\0';i++){
		}
		ElevatorChar[1][i]='0'+Elevator[e].Floor;
		ElevatorChar[1][i+1]='\0';
	}
	else{
		strcpy(ElevatorChar[0],"����0ͣ�ˣ���ǰ����");
		for(i=0;ElevatorChar[0][i]!='\0';i++){
		}
		ElevatorChar[0][i]='0'+Elevator[e].Floor;
		ElevatorChar[0][i+1]='\0';
	}
}
