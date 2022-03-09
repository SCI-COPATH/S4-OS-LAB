#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char opcode[7],startingAddress[15],copy[7],symbol[15],lable[15],oprant[15],length[10],address[10],readOpTab[10],value[3],readAddrss[5],readSym[20];
int numOp;
int errorFlag=1;
int opError=1;
int counter=0;
void main(){
    FILE *opTab, *indermediate,*len,*objectCode,*symtab;
    opTab=fopen("optab.txt","r");
    symtab=fopen("symtab.txt","r");
    indermediate=fopen("intermediate.txt","r");
    len=fopen("length.txt","r");
    objectCode=fopen("objectCode.txt","w");
    fscanf(len,"%s",length);
    fscanf(indermediate,"%s\t%s\t%s\t%s\n",address,lable,opcode,address);
    if(strcmp(opcode,"START")==0){
        fprintf(objectCode,"H^%s^%s^%s",opcode,address,length);
        printf("H^%s^%s^%s",opcode,address,length);
        strcpy(startingAddress,address);
    }
    while(!feof(indermediate)){
        if(counter==0){
            printf("\nT^%s^1E^",address);
            fprintf(objectCode,"\nT^%s^1E^",address);
            counter++;
        }
        fscanf(indermediate,"%s\t%s\t%s\t%s\n",address,lable,opcode,oprant);
       // printf("\noprant :%s\n",opcode);
        if(strcmp(opcode,"END")==0){
            printf("\nE^%s\n",startingAddress);
            fprintf(objectCode,"\nE^%s\n",startingAddress);
        }
        while(!feof(opTab)){
            fscanf(opTab,"%s\t%s\n",readOpTab,value);
            if(strcmp(readOpTab,opcode)==0){
                opError=0;
                printf("%s",value);
                fprintf(objectCode,"%s",value);
               // fscanf(indermediate,"%s\n",oprant);
                while(!feof(symtab)){
                    fscanf(symtab,"%s\t%s\n",readAddrss,readSym);
                    if(strcmp(oprant,readSym)==0){
                        printf("%s^",readAddrss);
                        fprintf(objectCode,"%s^",readAddrss);
                        errorFlag=0;
                        counter=(counter+1)%9;
                        break;
                    }
                }
               if(errorFlag==1){
                    printf("\nEROOR OCURE\n");
                    exit(0);
                }
                
                errorFlag=1;
                fclose(symtab);
                symtab=fopen("symtab.txt","r");
                break;
            }
        }
        fclose(opTab);
        opTab=fopen("optab.txt","r");
        if(strcmp(copy,"RESW")==0||strcmp(copy,"RESB")==0){
            opError=0;
            break;
        }else if(strcmp(copy,"WORD")==0||strcmp(copy,"BYTE")==0){
            opError=0;
            break;
        }
      if(opError==1){
             printf("\nEROOR OCURE\n");
             exit(0);
        }
        opError=0;
    }
    fclose(opTab);
    fclose(symtab);
    fclose(len);
    fclose(indermediate);
    fclose(objectCode);
}