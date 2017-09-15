#include<stdio.h>
#include<stdlib.h>
#include<conio.h>




void loading();
void PIP();


int fling=0;

struct node
{
	int process_no;
	float arrival_time,time_quantum,remaining_bt,bt;
	struct node *next;
};

struct node *n1,*head=NULL,*head1=NULL;
int n;
float avgwt=0,avgtat=0;
struct node *create_list(struct node *head,int n);
struct node *delete_position(struct node *head);
void display(struct node *head,int n);

struct node *create_list(struct node *head,int n)
{
	struct node *temp;
	int i,o=2;
	n1=(struct node *)malloc(sizeof(struct node));
	n1->process_no=1;
	printf("\n\tProcess#1\n");
	printf("Enter the Arrival time: ");
	scanf("%f",&n1->arrival_time);
	printf("\nEnter the Burst time: ");
	scanf("%f",&n1->remaining_bt);
	n1->bt=n1->remaining_bt;
	n1->next=NULL;
	head=n1;
	n1->time_quantum=(float)(n*10*1)/((n-0)*n1->remaining_bt);
	for (i=0;i<n-1;i++)
	{
		temp=(struct node *)malloc(sizeof(struct node));
		temp->process_no=o++;
		printf("\n\tProcess#%d\n",i+2);
        printf("Enter the Arrival time: ");
        scanf("%f",&temp->arrival_time);
        printf("\nEnter the Burst time: ");
		scanf("%f",&temp->remaining_bt);
        temp->bt=temp->remaining_bt;
		temp->time_quantum=(float)(n*10*1)/((n-0)*temp->remaining_bt);
		temp->next=NULL;
		n1->next=temp;
		n1=temp;
	}
	printf("List created\n");
	return head;
}

struct node* selection_sort(struct node *head)
{
	struct node* start=head,*t,*min;
	int k,i=1;
	float j;
	while(i<n)
	{
	    int p=1;
		min=start;
		t=start->next;
		while (p<=n-i)
		{
			if (min->arrival_time > t->arrival_time)
			{
				min=t;
			}
			t=t->next;
			p++;
		}
			j=start->arrival_time;
			start->arrival_time=min->arrival_time;
			min->arrival_time=j;
			j=start->remaining_bt;
			start->remaining_bt=min->remaining_bt;
			min->remaining_bt=j;
			j=start->bt;
			start->bt=min->bt;
			min->bt=j;
			j=start->time_quantum;
			start->time_quantum=min->time_quantum;
			min->time_quantum=j;
			k=start->process_no;
			start->process_no=min->process_no;
			min->process_no=k;
			start=start->next;
			i++;
	}
	return head;
}

int check_completion(struct node * head)
{
    struct node *b=head;
    while (b->next!=NULL)
    {
        if (b->remaining_bt!=0)
        {
            return 1;
        }
    }
        return 0;
}

void display(struct node *head,int n)
{
	struct node *a=head;
	int i=1;
	while(i<=n)
    {
    printf("++++++++++++++++++++++++++++++++++\n");
    printf("%d\t%f\t%f\t%f\n",a->process_no,a->arrival_time,a->remaining_bt,a->time_quantum);
    a=a->next;
    i++;
    }
}


void loading(){
int i, loading = 236;
	system("COLOR 0E");
	printf("\n\n\t\t\t    WELCOME TO\n\n");
	PIP();
	printf("\n\n\n\n\n\n\n\t\t\t      ");
	for(i=1;i<=7;++i){
		printf("%c ", loading);
		Sleep(500);
		printf("%c ", loading);
		Sleep(500);
		printf("%c", loading);
		Sleep(500);
		//system("cls");
		printf("\b\b\b\b       \b\b\b\b\b\b\b");
	}
	Sleep(500);
}

void PIP(){
	char s1=48, s2=201, s3=206, s4=200, s5=187, s6=188, s7=216, s8=181, s9=198;//for ASCII characters
	printf("\n\t\t\t    %c%c%c%c%c%c%c%c%c%c", s2, s3, s3, s3, s3, s3, s3, s3, s3, s5);
	printf("\n\t\t\t    %c SABSRV %c", s7, s7);
	printf("\n\t\t\t    %c%c%c%c%c%c%c%c%c%c", s4, s3, s3, s3, s3, s3, s3, s3, s3, s6);
	//printf("\n\t\t\t\t\t    %c| A powerful converter |%c", s8, s9);
}

void New_Era()
{
  int tq,stop=0;
  float wait_time=0,turnaround_time=0,time;
  printf("Enter Total Processes: ");
  scanf("%d",&n);
  head=create_list(head,n);
  int loop=2,i=0;
  head=selection_sort(head);
  printf("\n\t>>>>>>>>>>>>>>>>>> LIST <<<<<<<<<<<<<<<<<<<<<<\n");
  display(head,n);
  printf("\n\nProcess\t|Turnaround Time\t|Waiting Time\n\n");
  time=head->arrival_time;
  struct node *test=head;
  while (1)
  {
	  while (i<n)
      {
      if(test->arrival_time <= time && test->remaining_bt > 0)
      {
          if(test->remaining_bt <= test->time_quantum && test->remaining_bt > 0)
          {
              time = time + test->remaining_bt;
              test->remaining_bt=0;
          }
          else if(test->remaining_bt>0 && test->remaining_bt >= test->time_quantum)
            {
                test->remaining_bt = test->remaining_bt - test->time_quantum;
                time = time + test->time_quantum;
            }
          if(test->remaining_bt==0)
          {
              wait_time = wait_time + time - test->arrival_time - test->bt;
              avgwt+=wait_time;
              turnaround_time = turnaround_time + time - test->arrival_time;
              avgtat+=turnaround_time;
			  printf("P[%d]\t|\t%f\t|\t%f\n",test->process_no,turnaround_time,wait_time);
              stop++;
          }
          loop++;
      }
      test->time_quantum = (float)(n*10*loop)/((n-stop)*(test->remaining_bt));
      if (test->next==NULL)
      {
          test=head;
          i=0;
          break;
      }
      test=test->next;

      i++;
      }
      if(stop==n){
      	printf("\n Average Waiting Time = %f",(avgwt/n));
        printf("\n Average Turn around Time   time = %f\n\n",(avgtat/n));
        getch();
        system("cls");
        main();
      }
  }
}

void round_robin()
{

  int count,j,n,time,remain,flag=0,time_quantum;
  int wait_time=0,turnaround_time=0,at[100],bt[100],rt[100];
  printf("\n\t*******Round Robin*******\n");
  printf("Enter Total Process:\t ");
  scanf("%d",&n);
  remain=n;
  for(count=0;count<n;count++)
  {
    printf("Enter Arrival Time of Process[%d]:",count+1);
    scanf("%d",&at[count]);
    printf("Enter Burst Time of Process[%d]:",count+1);
	scanf("%d",&bt[count]);
    rt[count]=bt[count];
  }
  printf("Enter Time Quantum:\t");
  scanf("%d",&time_quantum);
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(time=0,count=0;remain!=0;)
  {
    if(rt[count]<=time_quantum && rt[count]>0)
    {
      time+=rt[count];
      rt[count]=0;
      flag=1;
    }
    else if(rt[count]>0)
    {
      rt[count]-=time_quantum;
      time+=time_quantum;
    }
    if(rt[count]==0 && flag==1)
    {
      remain--;
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]);
      wait_time+=time-at[count]-bt[count];
      turnaround_time+=time-at[count];
      flag=0;
    }
    if(count==n-1)
      count=0;
    else if(at[count+1]<=time)
      count++;
    else
      count=0;
  }
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);
  printf("Avg Turnaround Time = %f\n",turnaround_time*1.0/n);


}
void priority_scheduling()
{
  int i,j,n,time,sum_wait=0,sum_turnaround=0,smallest;
  int at[100],bt[100],pt[100],rt[100],remain;
  printf("\n\tPriority Scheduling*****\n");
  printf("Enter no of Processes : ");
  scanf("%d",&n);
  remain=n;
  for(i=0;i<n;i++)
  {
    printf("\nEnter Arrival time of P[%d]:",i+1);
    scanf("%d",&at[i]);
    printf("\nEnter Burst time of P[%d]:",i+1);
	scanf("%d",&bt[i]);
    printf("\nEnter Priority time of P[%d]:",i+1);
    
	scanf("%d",&pt[i]);
    rt[i]=bt[i];
  }
  pt[9]=11;
  printf("\n\nProcess\t|Turnaround time|waiting time\n");
  for(time=0;remain!=0;time++)
  {
    smallest=9;
    for(i=0;i<n;i++)
    {
      if(at[i]<=time && pt[i]<pt[smallest] && rt[i]>0)
      {
    smallest=i;
      }
    }
    rt[smallest]--;
    if(rt[smallest]==0)
    {
      remain--;
      printf("P[%d]\t|\t%d\t|\t%d\n",smallest+1,time+1-at[smallest],time+1-at[smallest]-bt[smallest]);
      sum_wait+=time+1-at[smallest];
      sum_turnaround+=time+1-at[smallest]-bt[smallest];
    }
  }
  printf("\nAvg waiting time = %f\n",sum_wait*1.0/n);
  printf("Avg turnaround time = %f\n",sum_turnaround*1.0/n);
}
 
void sjf() 
{
	int arrival_time[100], burst_time[100], temp[100];
	int i, smallest, count = 0, time, limit;
	double wait_time = 0, turnaround_time = 0, end;
	float average_waiting_time, average_turnaround_time;
	printf("\n\t*****SJF*****\t");
	
	printf("\nEnter the Total Number of Processes:\t");
	scanf("%d", &limit); 
	printf("\nEnter Details of %d Processes\n", limit);
	for(i = 0; i < limit; i++)
 	{
		printf("\nEnter Arrival Time:\t");
		scanf("%d", &arrival_time[i]);
		printf("Enter Burst Time:\t");
		scanf("%d", &burst_time[i]); 
		temp[i] = burst_time[i];
	}
  	burst_time[9] = 9999;  
 	for(time = 0; count != limit; time++)
 	{
   		smallest = 9;
  		for(i = 0; i < limit; i++)
  		{
   			if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
			{
   				smallest = i;
			}
  		}
  		burst_time[smallest]--;
  		if(burst_time[smallest] == 0)
  		{
   			count++;
   			end = time + 1;
   			wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
   			turnaround_time = turnaround_time + end - arrival_time[smallest];
  		}
 	}
	average_waiting_time = wait_time / limit; 
	average_turnaround_time = turnaround_time / limit;
 	printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
    	printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
}

void fcfs()
{
  int bt[100],at[100],wait_Time_Sum=0,turn_Time_Sum=0;
  int time=0,n,i,smallest,count=0;
  printf("\n\t*****FCFS*****\n");
  printf("Enter no of processes : ");
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    printf("Enter arrival time for process P%d : ",i+1);
    scanf("%d",&at[i]);
    printf("Enter burst time for process P%d : ",i+1);
    scanf("%d",&bt[i]);
  }
    
  printf("\n\nProcess\t|Turnaround Time| Waiting Time\n\n");
  at[99]=99999;
    
  while(count!=n)  //End the loop when n process finish
  {
    smallest=99; // Checking For index of Process with smallest Arrival Time
    for(i=0;i<n;i++)
    {
      if(at[i]<at[smallest] && bt[i]>0)
      {
      smallest=i;
      }
    }
    //Index of Smallest  Arrival Time stored in `smallest`
    time+=bt[smallest];  //Incrementing Current Time
    wait_Time_Sum+=time-at[smallest]-bt[smallest];
    turn_Time_Sum+=time-at[smallest];
      
    printf("P[%d]\t|\t%d\t|\t%d\n",smallest+1,time-at[smallest],time-at[smallest]-bt[smallest]);
      
    bt[smallest]=0;  //Making burst time of current Process 0 so that it won't run again
    count++;
  }
    
  printf("\n average waiting time = %f",wait_Time_Sum*1.0/n);
  printf("\n average turnaround time = %f\n",turn_Time_Sum*1.0/n);
}



void main(){
if(fling==0){
loading();
fling=1;
}
system("cls");
PIP();
int a;
//char x='y';
while(1)//x!='n'
{

printf("\n\n\tChoose one of the Scheduing Algorithms\n1.FCFS\n2.SJF\n3.Priority Scheduling\n4.Round Robin\n5.SABSRV\n6.Exit\nEnter Your Choice: ");
scanf("%d",&a);

switch(a){
	case 1:fcfs();
		break;

	case 2:sjf();
		break;
		
	case 3:priority_scheduling();
		break;
		
	case 4:round_robin();
		break;
	case 5:New_Era();
			break;
	case 6:	printf("\n\n\t......Thank You......");
		    exit(0);
		    break;
	
		default:printf("You Lost Your Chance***....");
}
//printf("\n\nDo you wish to Continue..?(y/n)\n");
//getchar();
//scanf("%c",&x);
}
}


