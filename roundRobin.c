#include<stdio.h>
struct Process{
    int ID;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int tempBurstTime;
};
void calculateAndPrint(struct Process process[],int numberOfProcess,int quntam){
    int maxBurstTime=process[0].burstTime;
    for(int i=0;i<numberOfProcess;i++){
        process[i].turnAroundTime=0;
        process[i].waitingTime=0;
    }
    for(int i=1;i<numberOfProcess;i++){
        if(maxBurstTime<process[i].burstTime)
            maxBurstTime=process[i].burstTime;
    }
    int wait=0,need=0;
    for(int i=0,cycle=1;i<=maxBurstTime;i+=quntam,cycle++){
        printf("\nCycle : %d\n",cycle);
        for(int j=0;j<numberOfProcess;j++){
            if(process[j].tempBurstTime>0){
                printf("process[%d]\t",process[j].ID);
                need = process[j].tempBurstTime>=quntam?quntam:process[j].tempBurstTime;
                process[j].turnAroundTime=wait+need;
                wait+=need;
                process[j].tempBurstTime-=need;
            }
        }  
    }
    float avgWaitingTime=0,avgTurnAroundTime=0;
    printf("Process ID\tWaiting Time\tTurn Around Time\n");
     for(int i=0;i<numberOfProcess;i++){
        process[i].waitingTime= process[i].turnAroundTime-process[i].burstTime;
        printf("%d\t\t%d\t\t%d\n",process[i].ID,process[i].waitingTime,process[i].turnAroundTime);
        avgTurnAroundTime+=process[i].turnAroundTime;
        avgWaitingTime+=process[i].waitingTime;
     }
     printf("Avarage Turn Around Time : %f\n",avgTurnAroundTime/(float)numberOfProcess);
     printf("Avarage Waiting Time : %f\n",avgWaitingTime/(float)numberOfProcess);
    
}
void main(){
   int numberOfProcess,quntam;
   printf("Enter Number Of Process : ") ;
   scanf("%d",&numberOfProcess);
   struct Process process[numberOfProcess];
   for(int i=0;i<numberOfProcess;i++){
       process[i].ID=i+1;
       printf("Enter Burst Time of %d th Process: ",i+1);
       scanf("%d",&process[i].burstTime);
       process[i].tempBurstTime=process[i].burstTime;
   } 
   printf("Enter Quntam : ");
   scanf("%d",&quntam);
   calculateAndPrint(process,numberOfProcess,quntam);
}