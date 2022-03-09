#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int strToNum(char charator[]){
	int len=strlen(charator);
	int res=0;
	for(int i=0;i<len;i++){
		res=res*10+(int)charator[i]-48;
	}
	return res;
}
void hexaToNum(char input,char * output){
	switch(input){
		case '0':strcpy(output,"0000");
			break;
		case '1':strcpy(output,"0001");
			break;
		case '2':strcpy(output,"0010");
			break;
		case '3':strcpy(output,"0011");
			break;
		case '4':strcpy(output,"0100");
			break;
		case '5':strcpy(output,"0101");
			break;
		case '6':strcpy(output,"0110");
			break;
		case '7':strcpy(output,"0111");
			break;
		case '8':strcpy(output,"1000");
			break;
		case '9':strcpy(output,"1000");
			break;
		case 'A':strcpy(output,"1010");
			break;
		case 'B':strcpy(output,"1011");
			break;
		case 'C':strcpy(output,"1100");
			break;
		case 'D':strcpy(output,"1101");
			break;
		case 'E':strcpy(output,"1110");
			break;
		case 'F':strcpy(output,"1111");
			break;
			
	}

}
void main(){
	FILE * readobj, * output,*tempFile;
	char t,recType;
	char maskbit[5],maskBitHexa[3];
	readobj=fopen("objcode.txt","r");
	int startingAddress,absaluteAddress,length,textRecodeLength,intex=0,startingAddresstxt;
	printf("Enter Starting Address : ");
	scanf("%x",&startingAddress);
	char readCode[8],codeName[32];
	output=fopen("output.txt","w");
	fscanf(readobj,"%[^^]",readCode);
	if(strcmp(readCode,"H")==0){
		fscanf(readobj,"%[^^]",readCode);
		fscanf(readobj,"%c",&t);
		fscanf(readobj,"%[^^]",codeName);
		fscanf(readobj,"%c",&t);
		//printf("%s\n",codeName);	
		fscanf(readobj,"%x",&absaluteAddress);
		fscanf(readobj,"%c",&t);
		fscanf(readobj,"%x",&length);
		fscanf(readobj,"%c",&t);
		//printf("%x\n",absaluteAddress);	
	}
	do{
		fscanf(readobj,"%[^^]",readCode);	
		fscanf(readobj,"%c",&t);
		if(strcmp(readCode,"\nT")==0){
			recType='T';
			fscanf(readobj,"%x",&startingAddresstxt);	
			fscanf(readobj,"%c",&t);
			fscanf(readobj,"%x",&textRecodeLength);	
			fscanf(readobj,"%c",&t);
			textRecodeLength=textRecodeLength/3;
			fscanf(readobj,"%[^^]",readCode);
			strcpy(maskBitHexa,readCode);	
			fscanf(readobj,"%c",&t);		
		}else if(strcmp(readCode,"\nE")==0){
			recType='E';
		}if(recType=='T'){	
			int tempAddress=startingAddresstxt;
			hexaToNum(maskBitHexa[intex],maskbit);
			int maskIntex=0,objAddress;
			char load[5];
			//printf("%s",readCode);
			for(int i=0;i<textRecodeLength;){
				
				fscanf(readobj,"%[^^]",readCode);	
				fscanf(readobj,"%c",&t);	
				tempFile=fopen("tempFile.txt","w");
				
				for(int t=0;t<6;t++){
					fprintf(tempFile,"%c",readCode[t]);
					if(t==1)
						fprintf(tempFile,"\t");
				}
				fclose(tempFile);
				tempFile=fopen("tempFile.txt","r");
				fscanf(tempFile,"%s\t%x",load,&objAddress);
				//printf("%s\t%x\n",load,objAddress);
				fclose(tempFile);
				if(maskbit[maskIntex]=='1'){
					printf("%x\t%s\n",objAddress+startingAddress,load);
					fprintf(output,"%x\t%s\n",objAddress+startingAddress,load);
				}else {
					printf("%x\t%s\n",objAddress,load);	
					fprintf(output,"%x\t%s\n",objAddress,load);objAddress
				}
				
				i++;
					maskIntex++;
			}
			
			
		}
		
	}while(recType!='E');
	fclose(readobj);
	fclose(output);
}


