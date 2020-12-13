#include <windows.h>
#include<bits/stdc++.h>
#include<string.h> 
#include<stdio.h> 
#include<stdlib.h>
using  namespace std;

#define UnitTime 0.1        //单位时间 
#define Maxpeople 1000000   //模拟时最大乘客数量 
#define MaxTime 10000       //最大运行时间的上限 
#define MinTime 500         //最大运行时间的下限 
#define Maxfloor 4          //最高的楼层 
#define MaxPeopleNum 8      //电梯内乘坐人员的最大数量 
#define MaxWaitNumInFloor 7	//每一层的最大等待人数
#define Basefloor 1         //楼的基层 

#define FloorHight 3		//楼层高度
#define LeftElevatorX 6		//左边电梯的x起始坐标
#define LeftElevatorY 12	//左边电梯的y起始坐标
#define RightElevatorX 34	//右边电梯的x起始坐标
#define RightElevatorY 12	//右边电梯的y起始坐标
#define Uptime 51           //电梯上升时间 
#define Downtime 61         //电梯下降时间 
#define UpSlowdown 14       //电梯上升减速时间 
#define DownSlowdown 23     //电梯下降减速时间 
#define Accelerate 15       //电梯加速时间  
#define Doortime 20         //电梯关门时间 
#define Peopletime 25       //人进入电梯时间 
#define Diantitime 40       //检查时否关门时间 
#define Backtime 300        //检查是否回到基层 

#define Goingup 1           //电梯状态上升 
#define Goingdown -1        //电梯状态下降 
#define Idle 0              //电梯状态等候 

int Time,id,Maxtime;
int flagelevator=0;         //检查乘客是否同时呼叫全部电梯 
int Exist[Maxpeople]={0};   //用户是否存在队列中
char ElevatorChar[2][40];   //电梯提示 
char PeopleChar6[2][40];    //第六行乘客提示     
char PeopleChar7[2][40];    //第七行乘客提示 
typedef struct elevatorcanshu Elevatorcanshu;
typedef struct people{
    int Id;                //该用户的编号
    int EnterTime;         //进入时间
    int InFloor;           //他所在的楼层
    int OutFloor;          //他要去哪层楼
    int GiveupTime;        //他能容忍的等候时间
    int FlagElevator0;     //值为0，除非有请求电梯0 
    int FlagElevator1;     //值为0，除非有请求电梯1 
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
	int PeopleNum;                   //电梯内人数 
	int CallUp[5];                   //电梯外向上按钮
	int CallDown[5];                 //电梯外向下按钮
	int CallDianti[5];               //电梯内按钮
	int again;
	int drcl,drcltime,testdoortime; //电梯门参量
	int state;                      //电梯的当前状态(GoingUp，GoingDOWEl，Idle)
	int prestate;                   //电梯下步状态(GoingUp，GoingDOWEl，Idle)
	int Floor;                      //电梯的当前位置(楼层)
	int d1;                         //值为0，除非人们正在进入和离开电梯；
	int d2;                         //值为0，如果电梯 已经在某层停候30Ot以上；
	int d3;                         //值为0，除非电梯 门正开着又无人迸出电梯；
	struct dianti Stack[Maxfloor+1];//电梯内乘客
	struct shixu sxjiankong;        //电梯时序监控
	int k;
	int backfirsttime; 
};

struct people upqueue[Maxfloor+1];  //上升队列 
struct people downqueue[Maxfloor+1];//下降队列 

void InputMaxTime(); 
void ShowTitle();
void init(Elevatorcanshu *&Elevator,int e);
void input(People per,Elevatorcanshu *&Elevator,int e);             //加入乘客 
void Addupqueue(People &p,int in);  //加入上升队列 
void Adddownqueue(People &p,int in);//加入下降队列 
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
//确定终端中光标位置
void gotoxy(short x, short y)
{
	COORD coord = { x, y };
	/*COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。其定义为：

	typedef struct _COORD {

	SHORT X; // horizontal coordinate

	SHORT Y; // vertical coordinate
	} COORD;*/

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 	
//显示其余信息
void ShowOthers()
{
	gotoxy(14,8);
	printf("电梯0");
	gotoxy(42,8);
	printf("电梯1"); 
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
//输出电梯的整体轮廓
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
//隐藏在x层的电梯
void DisappearEvelatorBody(int x,Elevatorcanshu *&Elevator,int e)
{
	int i, j;
	//先设置字体为背景颜色(黑色)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	for (i = LeftElevatorX + Elevator[e].k * 27; i <= LeftElevatorX + Elevator[e].k * 26 + 24; i++)
	{
		gotoxy(i, LeftElevatorY - 1 + (4 - x)*FloorHight);
		printf(" ");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//在x层显示电梯
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
//显示等待队列的乘客
void ShowWaitingQueue(int i)
{
	People p;
	p=upqueue[i].next;
	int j=0;
	while (p != NULL)
	{
		gotoxy(RightElevatorX + 26+j*6, RightElevatorY-1 + (4-p->InFloor)*FloorHight);
		printf(" %d", p->Id);
		printf("↑");
		printf("%d",p->OutFloor);
		p = p->next;
		j++;
	}
	p=downqueue[i].next;
	while (p != NULL)
	{
		gotoxy(RightElevatorX + 26+j*6, RightElevatorY-1 + (4-p->InFloor)*FloorHight);
		printf(" %d", p->Id);
		printf("↓");
		printf("%d",p->OutFloor);
		p = p->next;
		j++;
	}
}
//消隐处于等待状态的乘客
void DisappearWaitingQueue(int i)
{
	//设置字体的颜色，用背景颜色再写一遍就能消去字体 0是黑色 7是白色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	ShowWaitingQueue(i);
	//消隐完后再重新恢复字体颜色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//显示说明信息
void PrintfHelp()
{
	gotoxy(60, 7);
	printf("说明：前面的数字表示乘客ID，箭头表示该乘客向上或下");
	gotoxy(60, 9);
	printf("后面的数字代表该乘客的目标楼层");
}
//初始化电梯信息 
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
//显示电梯模拟界面头
void ShowTitle()
{
	printf("\n\n\n");
	printf("\n\t\t*********************************************************");
	printf("\n\t\t_________________________________________________________");
	printf("\n\t\t〓〓〓〓〓〓〓〓〓欢迎来到电梯管理系统 〓〓〓〓〓〓〓〓〓\n\n");
	printf("\t\t                本次电梯模拟的时间单位为%.1f秒\n",UnitTime);
	printf("\n\t\t*********************************************************\n");
	
}
//输入最大电梯模拟运行时间 
void InputMaxTime()
{
	printf("\n\t\t请输入电梯的最大运行时间，达到该时间，电梯系统将会自动停止\n");
	printf("\t\t                   请输入最大运行时间:");
	while (scanf("%d", &Maxtime) != 1 || Maxtime < MinTime || Maxtime > MaxTime)
	{
		printf("\t\t     输入有误，需重新输入（%d<=最大运行时间<=%d）\n",MinTime,MaxTime);
		while (getchar() != '\n')
			continue;
		printf("\t\t                   请输入最大运行时间:");
	}
}
//加入新乘客 
void input(People pt,Elevatorcanshu *&Elevator,int e)
{
	system("cls");
	int InFloor,OutFloor,GiveupTime,EnterTime,FlagElevator0=0,FlagElevator1=0;
	while(1){
	    printf("\t\t*********************************************************\n");
	    printf("\t\t                   时间为：%d\n",Time);
	    printf("\t\t            第%d位乘客走进来，等候电梯。\n",id);
	    while(1){
	    	printf("\t\t            他在哪层楼电梯的门前:_____\b\b\b");
        	scanf("%d",&InFloor);
        	if(InFloor>=0&&InFloor<=Maxfloor)break;
        	printf("\t\t            输入的楼层超出界限，请重新输入。\n"); 
		}
		while(1){
			char c;
			printf("\t\t            是否呼叫电梯0，请输入（Y/N）：");
			getchar();
			c=getchar();
			while(c!='Y'&&c!='N'){
				printf("\t\t            输入格式错误，请重新输入,是否呼叫电梯0（Y/N）：");
				getchar();
				c=getchar();
			}
			if(c=='Y'){
				FlagElevator0=1;
			} 
			printf("\t\t            是否呼叫电梯1，请输入（Y/N）：");
			getchar();
			scanf("%c",&c);
			while(c!='Y'&&c!='N'){
				printf("\t\t            输入格式错误，请重新输入,是否呼叫电梯1（Y/N）：");
				getchar();
				scanf("%c",&c);
			}
			if(c=='Y'){
				FlagElevator1=1;
			}
			if(FlagElevator0||FlagElevator1)break;
			printf("\t\t            您都没有呼叫电梯，请重新输入要呼叫的电梯。\n");
		}
	    while(1){
	    	printf("\t\t            他要去哪层楼:_____\b\b\b");
        	scanf("%d",&OutFloor);
        	if(OutFloor>=0&&OutFloor<=Maxfloor)break;
        	printf("\t\t            输入的楼层超出界限，请重新输入。\n");
		}
        printf("\t\t            他能容忍的等候时间:_____\b\b\b");
        scanf("%d",&GiveupTime);
        printf("\t\t            下一个乘客出现的时间间隔:_____\b\b\b");
        scanf("%d",&EnterTime);
        printf("\t\t*********************************************************\n\n");
        if(OutFloor!=InFloor){
        	break;
		}
		printf("\t\t*********************************************************\n");
		printf("\t\t输入错误：乘客要去的楼层与其当前所在楼层相同，请重新输入\n");
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
	PrintElevatorFrame();							//输出电梯框架
	PrintfHelp();
	ShowElevatorBody(Elevator[0].Floor,Elevator,0);  
	ShowElevatorBody(Elevator[1].Floor,Elevator,1);                         //输出电梯主体
	int i;
	for(i=0;i<=Maxfloor;i++){
		ShowWaitingQueue(i);
	}
}
// 加入上升队列
void Addupqueue(People &p,int in)
{
	People q=&upqueue[in];
	while (q->next!=NULL){
		q=q->next;
	}
	q->next=p;
	p->pre=q;
}
// 加入下降队列 
void Adddownqueue(People &p,int in)
{
	People q=&downqueue[in];
	while (q->next!=NULL){
		q=q->next;
	}
	q->next=p;
	p->pre=q;
}
// 将各个操作加入一个按时间顺序排列的队列中
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
//乘客放弃等待电梯 
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
		printf("乘客%d放弃等候,离开了",per->Id);
		a=per->Id;
		num=0;
		strcpy(PeopleChar6[0],"乘客");
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
		strcat(PeopleChar6[0],"放弃等候,离开了");
		strcpy(PeopleChar7[0]," ");
	}
	if(per->FlagElevator1)
	{
		gotoxy(3+30,6);
		printf("                           ");
		gotoxy(3+30,7);
		printf("                           ");
		gotoxy(3+30,6);
		printf("乘客%d放弃等候,离开了",per->Id);
		a=per->Id;
		num=0;
		strcpy(PeopleChar6[1],"乘客");
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
		strcat(PeopleChar6[1],"放弃等候,离开了");
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
//电梯模拟的一个计时器 
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
		printf("时间为： %d", Time);
		Sleep(1000*UnitTime);
	}
	gotoxy(60,30);
	printf("演示结束，按下任意键退出");
	getchar();
	getchar();
}
// 对电梯进行控制
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
			printf("无人请求电梯%d",Elevator[e].k);
			if(Elevator[e].k){
				strcpy(ElevatorChar[1],"无人请求电梯1");
			}
			else{
				strcpy(ElevatorChar[0],"无人请求电梯0");
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
				printf("电梯%d被打断关门",Elevator[e].k);
				if(Elevator[e].k){
					strcpy(ElevatorChar[1],"电梯1被打断关门");
				}
				else{
					strcpy(ElevatorChar[0],"电梯0被打断关门");
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
				printf("电梯%d被打断关门",Elevator[e].k);
			    if(Elevator[e].k){
					strcpy(ElevatorChar[1],"电梯1被打断关门");
				}
				else{
					strcpy(ElevatorChar[0],"电梯0被打断关门");
				}
                Addshixu(Time-Elevator[e].drcltime,NULL,opendoor,Elevator,e);
            }
            else Addshixu(Doortime,NULL,opendoor,Elevator,e);
            return ;
        }
        else if(Elevator[e].d3==1&&Elevator[e].prestate==Goingup&&(Elevator[e].CallUp[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)){
            Elevator[e].d1=1;
			Elevator[e].d3=0;   //门还没关，又有人进来
            Addshixu(Peopletime,NULL,peoplein,Elevator,e);
        }
        else if(Elevator[e].d3==1&&Elevator[e].prestate==Goingdown&&(Elevator[e].CallDown[Elevator[e].Floor]&&Elevator[e].PeopleNum<MaxPeopleNum)){
            Elevator[e].d1=1;
			Elevator[e].d3=0;   //门还没关，又有人进来
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
//电梯获取下步指令 
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
//打开电梯门 
void opendoor(People p,Elevatorcanshu *&Elevator,int e)
{
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("电梯%d门开了",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"电梯1门开了");
	}
	else{
		strcpy(ElevatorChar[0],"电梯0门开了");
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
        Elevator[e].d1=0; Elevator[e].d3=1;   //没人进出，但门是开着的
        Elevator[e].testdoortime=Time;
        Addshixu(Diantitime,NULL,testinout,Elevator,e);
    }
}
//乘客进入电梯 
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
			printf("乘客%d成功进入电梯%d\n",ap->Id,Elevator[e].k);
			a=ap->Id;
			num=0;
			strcpy(PeopleChar6[Elevator[e].k],"乘客");
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
				strcat(PeopleChar6[Elevator[e].k],"成功进入电梯1");
			}
			else{
				strcat(PeopleChar6[Elevator[e].k],"成功进入电梯0");
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
				printf("电梯%d已满载",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(ElevatorChar[1],"电梯1已满载");
				}
				else{
					strcpy(ElevatorChar[0],"电梯0已满载");
				}
        		gotoxy(3+30*Elevator[e].k,6);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,7);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,6);
				while(t){
					printf("乘客%d，",t->Id);
					a=t->Id;
					num=0;
					strcpy(PeopleChar6[Elevator[e].k],"乘客");
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
				printf("无法继续进入电梯%d",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(PeopleChar7[Elevator[e].k],"无法继续进入电梯1");
				}
				else{
					strcpy(PeopleChar7[Elevator[e].k],"无法继续进入电梯0");
				}
			}
			if(!upqueue[Elevator[e].Floor].next){
				Elevator[e].CallUp[Elevator[e].Floor]=0;	
			}
            Elevator[e].CallDianti[Elevator[e].Floor]=0;
            Elevator[e].d1=0;Elevator[e].d3=1;  //没人进出，但门是开着的
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
			printf("乘客%d成功进入电梯%d\n",ap->Id,Elevator[e].k);
			a=ap->Id;
			num=0;
			strcpy(PeopleChar6[Elevator[e].k],"乘客");
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
				strcat(PeopleChar6[Elevator[e].k],"成功进入电梯1");
			}
			else{
				strcat(PeopleChar6[Elevator[e].k],"成功进入电梯0");
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
				printf("电梯%d已满载",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(ElevatorChar[1],"电梯1已满载");
				}
				else{
					strcpy(ElevatorChar[0],"电梯0已满载");
				}
        		gotoxy(3+30*Elevator[e].k,6);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,7);
				printf("                           ");
				gotoxy(3+30*Elevator[e].k,6);
				while(t){
					printf("乘客%d，",t->Id);
					a=t->Id;
					num=0;
					strcpy(PeopleChar6[Elevator[e].k],"乘客");
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
				printf("无法继续进入电梯%d",Elevator[e].k); 
				if(Elevator[e].k){
					strcpy(PeopleChar7[Elevator[e].k],"无法继续进入电梯1");
				}
				else{
					strcpy(PeopleChar7[Elevator[e].k],"无法继续进入电梯0");
				}
			}
			if(!downqueue[Elevator[e].Floor].next){
				Elevator[e].CallDown[Elevator[e].Floor]=0;
			}
            Elevator[e].CallDianti[Elevator[e].Floor]=0;
            Elevator[e].d1=0;Elevator[e].d3=1;  //没人进出，但门是开着的
            Elevator[e].testdoortime=Time;
            Addshixu(Diantitime,NULL,testinout,Elevator,e);
        }
    }
}
//乘客走出电梯 
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
		printf("乘客%d走出电梯%d",ap->Id,Elevator[e].k);
		a=ap->Id;
		num=0;
		strcpy(PeopleChar6[Elevator[e].k],"乘客");
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
			strcat(PeopleChar6[Elevator[e].k],"走出电梯1");
		}
		else{
			strcat(PeopleChar6[Elevator[e].k],"走出电梯0");
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
        Elevator[e].d1=0; Elevator[e].d3=1;     ////没人进出，但门是开着的
        Elevator[e].testdoortime=Time;
        Addshixu(Diantitime,NULL,testinout,Elevator,e);
    }
}
//电梯是否上升 
int GetUp(Elevatorcanshu *&Elevator,int e)
{
    for(int i=Elevator[e].Floor+1;i<=Maxfloor;i++){
        if(Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]||Elevator[e].CallDown[i])
			return 1;
    }
    return 0;
}
//电梯是否下降 
int GetDown(Elevatorcanshu *&Elevator,int e)
{
    for(int i=Elevator[e].Floor-1;i>=0;i--){
        if(Elevator[e].CallDianti[i]||Elevator[e].CallUp[i]||Elevator[e].CallDown[i])
			return 1;
    }
    return 0;
}
//电梯加速完成，将进入正常速度 
void UniformSpeed(People ap,Elevatorcanshu *&Elevator,int e)
{
	if(Elevator[e].state==Goingup){
		gotoxy(3+30*Elevator[e].k,4);
		printf("                        ");
		gotoxy(3+30*Elevator[e].k,4);
		printf("电梯%d已加速上升！",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"电梯1已加速上升！");
		}
		else{
			strcpy(ElevatorChar[0],"电梯0已加速上升！");
		}
		Addshixu(Uptime,NULL,diantiup,Elevator,e);
	}else{
		gotoxy(3+30*Elevator[e].k,4);
		printf("                        ");
		gotoxy(3+30*Elevator[e].k,4);
		printf("电梯%d已加速下降！",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"电梯1已加速下降！");
		}
		else{
			strcpy(ElevatorChar[0],"电梯0已加速下降！");
		}
		Addshixu(Downtime,NULL,diantidown,Elevator,e);
	}
}
//电梯去基层
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
	printf("无人请求电梯%d!将进入%d层",Elevator[e].k,Basefloor);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"无人请求电梯1!将进入1层");
	}
	else{
		strcpy(ElevatorChar[0],"无人请求电梯0!将进入1层");
	}
	Elevator[e].CallDianti[Basefloor]=2;
}
// 结束乘客进出，正在关门
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
		printf("电梯%d正在关门",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"电梯1正在关门");
		}
		else{
			strcpy(ElevatorChar[0],"电梯0正在关门");
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
		printf("电梯%d正在关门",Elevator[e].k);
		if(Elevator[e].k){
			strcpy(ElevatorChar[1],"电梯1正在关门");
		}
		else{
			strcpy(ElevatorChar[0],"电梯0正在关门");
		}
        Addshixu(Doortime,NULL,closedoor,Elevator,e);
    }
}
//电梯上升
void diantiup(People ap,Elevatorcanshu *&Elevator,int e)
{
	Elevator[e].Floor++;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("电梯%d正在上升",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"电梯1正在上升");
	}
	else{
		strcpy(ElevatorChar[0],"电梯0正在上升");
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
//电梯下降 
void diantidown(People ap,Elevatorcanshu *&Elevator,int e)
{
	Elevator[e].Floor--;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("电梯%d正在下降",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"电梯1正在下降");
	}
	else{
		strcpy(ElevatorChar[0],"电梯0正在下降");
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
//电梯门关上 
void closedoor(People ap,Elevatorcanshu *&Elevator,int e)
{
    if(Elevator[e].drcl==0||Time!=Elevator[e].drcltime+Doortime)
		return;
    Elevator[e].drcl=0;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("电梯%d门关了",Elevator[e].k);
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"电梯1门关了");
	}
	else{
		strcpy(ElevatorChar[0],"电梯0门关了");
	}
}
//电梯停下 
void diantistop(People ap,Elevatorcanshu *&Elevator,int e)
{
    Elevator[e].state=Idle;
    Elevator[e].d1=0;Elevator[e].d3=0;
	gotoxy(3+30*Elevator[e].k,4);
	printf("                        ");
	gotoxy(3+30*Elevator[e].k,4);
	printf("电梯%d停了，当前层是%d",Elevator[e].k,Elevator[e].Floor);
	int a=Elevator[e].Floor,i;
	if(Elevator[e].k){
		strcpy(ElevatorChar[1],"电梯1停了，当前层是");
		for(i=0;ElevatorChar[1][i]!='\0';i++){
		}
		ElevatorChar[1][i]='0'+Elevator[e].Floor;
		ElevatorChar[1][i+1]='\0';
	}
	else{
		strcpy(ElevatorChar[0],"电梯0停了，当前层是");
		for(i=0;ElevatorChar[0][i]!='\0';i++){
		}
		ElevatorChar[0][i]='0'+Elevator[e].Floor;
		ElevatorChar[0][i+1]='\0';
	}
}
