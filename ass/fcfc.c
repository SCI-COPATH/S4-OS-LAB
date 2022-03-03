#include <stdio.h>
void fcfs(int disk[],int limit,int head,int start,int finish){
	int totalMovement=0,temp;		
	for(int i=0;i<limit-1;i++){
		printf("[%d]->",disk[i]);
		temp=disk[i]>head?disk[i]-head:head-disk[i];
		totalMovement=totalMovement+temp;
		head=disk[i];
	}
	printf("[%d]\n",disk[limit-1]);
	temp=disk[limit-1]>head?disk[limit-1]-head:head-disk[limit-1];
	totalMovement=totalMovement+temp;
	head=disk[limit-1];
	printf("Total number Movement  : %d\n",totalMovement);
	
}	
void main(){
	int loc,head;
	printf("Enter number of locations : ");
	scanf("%d",&loc);
	printf("Enter head position : ");
	scanf("%d",&head);
	int disk[loc];
	printf("Enter the locations \n");
	for(int i=0;i<loc;i++){
		scanf("%d",&disk[i]);
	}
	fcfs(disk,loc,head,0,199);
}
