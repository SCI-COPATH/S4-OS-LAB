#include<stdio.h>
struct Process{
    int ID;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
};
void calculate(struct Process process[],int numberOfProcess){
    for(int i=0;i<numberOfProcess;i++){
        if(i>0){
            process[i].waitingTime=process[i-1].burstTime+process[i-1].waitingTime;
        }else{
            process[i].waitingTime=0;
        }
        process[i].turnAroundTime=process[i].waitingTime+process[i].burstTime;
    }
}
void show(struct Process process[],int numberOfProcess){
    float avgWaitingTime=0,avgTurnAroundTime=0;
    printf("Process ID\tBurst Time\tWaiting Time\tTurn Around Time\n");
     for(int i=0;i<numberOfProcess;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\n",process[i].ID,process[i].burstTime,process[i].waitingTime,process[i].turnAroundTime);
        avgTurnAroundTime+=process[i].turnAroundTime;
        avgWaitingTime+=process[i].waitingTime;
     }
     printf("Avarage Turn Around Time : %f\n",avgTurnAroundTime/(float)numberOfProcess);
     printf("Avarage Waiting Time : %f\n",avgWaitingTime/(float)numberOfProcess);
}
void main(){
   int numberOfProcess;
   printf("Enter Number Of Process : ") ;
   scanf("%d",&numberOfProcess);
   struct Process process[numberOfProcess];
   for(int i=0;i<numberOfProcess;i++){
       process[i].ID=i+1;
       printf("Enter Burst Time of %d th Process: ",i+1);
       scanf("%d",&process[i].burstTime);
   } 
   calculate(process,numberOfProcess);
   show(process,numberOfProcess);
}