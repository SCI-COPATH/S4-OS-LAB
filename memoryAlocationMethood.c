#include <stdio.h>
typedef struct {
    float total;
    float available;
    int ID;
}partition;
typedef struct{
    float size;
    int ID;
    int alotedID;
}proces;
void firstFit(partition partitions[],int numberOfPartition,proces process[],int numberOfProcess){
    for(int i=0;i<numberOfPartition;i++)
        partitions[i].available=partitions[i].total;
    for(int i=0;i<numberOfProcess;i++){
        for(int j=0;j<numberOfPartition;j++){
            if(process[i].size<=partitions[j].available){
                process[i].alotedID=partitions[j].ID;
                partitions[j].available=partitions[j].available-process[i].size;
                break;
            }
        }
    }
}
void bistFit(partition partitions[],int numberOfPartition,proces process[],int numberOfProcess){

}
void worstFit(partition partitions[],int numberOfPartition,proces process[],int numberOfProcess){

}
void display(partition partition[],proces process[],int numberOfProcess){
    printf("Process ID\tProcess Size\tPartition ID\tPartition Size\n");
    for(int i=0;i<numberOfProcess;i++){
        printf("%d\t\t%f",process[i].ID,process[i].size);
        if(process[i].alotedID>=0){
            printf("\t\t%d\t%f\n",process[i].alotedID,partition[process[i].alotedID-1].total);
        }else{
            printf("\tNot aloted\tNot aloted\n");
        }
    }
}
void main(){
    int numberOfPartition,numberOfProcess;
    printf("Enter Number Of Partition : ");
    scanf("%d",&numberOfPartition);
    partition partitions[numberOfPartition];
    printf("Enter The Size Of Partitions\n");
    for(int i=0;i<numberOfPartition;i++){
        printf("%d : ",i+1);
        partitions[i].ID=i+1;
        scanf("%f",&partitions[i].total);
        partitions[i].available=partitions[i].total;
    }
    printf("Enter Number Of Process : ");
    scanf("%d",&numberOfProcess);
    proces process[numberOfProcess];
    printf("Enter The Size Of Process\n");
    for(int i=0;i<numberOfProcess;i++){
        printf("%d : ",i+1);
        process[i].ID=i+1;
        process[i].alotedID=-1;
        scanf("%f",&process[i].size);
    }
    firstFit(partitions,numberOfPartition,process,numberOfProcess);
    display(partitions,process,numberOfProcess);
}