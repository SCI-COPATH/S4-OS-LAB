#include <stdio.h>
void sort(int array[],int limit,int dis){
	for(int i=0;i<limit;i++){
		for(int j=i+1;j<limit;j++){
			if(dis==0){
				if(array[j]>array[i]){
					int temp=array[i];
					array[i]=array[j];
					array[j]=temp;
				}
			}else{
				if(array[j]<array[i]){
					int temp=array[i];
					array[i]=array[j];
					array[j]=temp;
				}
			}
		}
	}
}
void scan(int disk[],int limit,int head,int start,int finish){
	int totalMovement=0;
	int initialHead=head;
	int eq=-1,lowerLimit=0,upperLimit=0;
	for(int i=0;i<limit;i++){
		if(disk[i]==head)
			eq=disk[i];
		else if(disk[i]<head)
			lowerLimit++;
		else if(disk[i]>head)
			upperLimit++;
	}
	int upper[upperLimit];
	int lower[lowerLimit];
	for(int i=0,j=0,k=0;i<limit;i++){
		if(disk[i]<head){
			lower[j]=disk[i];
			j++;
		}
		else if (disk[i]>head){
			upper[k]=disk[i];
			k++;
		}
	}
	sort(upper,upperLimit,1);
	sort(lower,lowerLimit,0);
	printf("Seequence : ");
	if(eq!=-1)
		disk[0]=eq;
	if(upperLimit!=0)
		for(int  i=0;i<upperLimit;i++)
			printf("[%d]->",upper[i]);
	printf("[%d*]->",finish);
	for(int  i=0;i<lowerLimit-1;i++)
		printf("[%d]->",lower[i]);
	if(lowerLimit!=0)
		printf("[%d]\n",lower[lowerLimit-1]);
	totalMovement=lowerLimit!=0?(finish-initialHead)+(finish-lower[lowerLimit-1]):finish-initialHead;
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
	scan(disk,loc,head,0,199);
}
