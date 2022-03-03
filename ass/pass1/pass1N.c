#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    unsigned int locationCounter, oprant, startingAddress, opTabOprant;
    FILE *inputFile, *opTabFile, *symbolTab, *IntermediateFile, *lengthFile;
    int l, len;
    char opCode[20], label[20], oprator[20], opTabOpCode[20];
    lengthFile = fopen("length.txt", "w");
    inputFile = fopen("input.txt", "r");
    symbolTab = fopen("symtab.txt", "w");
    fclose(symbolTab);
    IntermediateFile = fopen("intermediate.txt", "w");
    fscanf(inputFile, "%s %s %x", label, opCode, &oprant);
    if (strcmp(opCode, "START") == 0)
    {
        startingAddress = oprant;
        locationCounter = startingAddress;
        printf("-\t%s\t%s\t%x\n", label, opCode, oprant);
        fprintf(IntermediateFile, "\n-\t%s\t%s\t%x\n", label, opCode, oprant);
    }
    else
        locationCounter = 0;
    fscanf(inputFile, "%s %s", label, opCode);
    while (!feof(inputFile)){
        fscanf(inputFile, "%s", oprator);
        printf("\n%x\t%s\t%s\t%s\n", locationCounter, label, opCode, oprator);
        fprintf(IntermediateFile, "\n%x\t%s\t%s\t%s\n", locationCounter, label, opCode, oprator);
        if (strcmp(label, "-") != 0)
        {   
            char readSymbol[10];
            int value;
            symbolTab = fopen("symtab.txt", "r");
            while(!feof(symbolTab)){
                fscanf(symbolTab, "%s,%x", readSymbol,&value);
               // printf("%s\n",readSymbol);
                if(strcmp(label,readSymbol)==0){
                    fclose(lengthFile);
                    fclose(inputFile);
                    fclose(IntermediateFile);
                    lengthFile = fopen("length.txt", "w");
                    symbolTab = fopen("symtab.txt", "w");
                    fclose(symbolTab);
                    IntermediateFile = fopen("intermediate.txt", "w");
                    fclose(lengthFile);
                    fclose(IntermediateFile);
                    printf("Error");
                    exit(0);
                }
            };
            fclose(symbolTab);
            symbolTab = fopen("symtab.txt", "a");
            fprintf(symbolTab, "\n%x\t%s\n", locationCounter, label);  
            fclose(symbolTab);

        }
        int error=1;
        opTabFile = fopen("optab.txt", "r");
        while (!feof(opTabFile))
        {
            fscanf(opTabFile, "%s %x", opTabOpCode, &opTabOprant);
            if (strcmp(opCode, opTabOpCode) == 0)
            {
                locationCounter = locationCounter + 3;
                error=0;
                break;
            }
        }
        fclose(opTabFile);
        if (strcmp(opCode, "WORD") == 0)

        {
            locationCounter = locationCounter + 3;
        }
        else if (strcmp(opCode, "RESW") == 0)
        {
            oprant = atoi(oprator);
            locationCounter = locationCounter + (3 * oprant);
	   
        }
        else if (strcmp(opCode, "BYTE") == 0)
        {
            
            if (oprator[0] == 'X')
                locationCounter = locationCounter + 1;
            else
            {
                len = strlen(oprator) - 2;
                locationCounter = locationCounter + len;
            }
        }
        else if (strcmp(opCode, "RESB") == 0)
        {
            
            oprant = atoi(oprator);
            locationCounter = locationCounter + oprant;
	
        }else if(error==1&&strcmp(opCode, "END") != 0){
            fclose(lengthFile);
            fclose(inputFile);
            fclose(IntermediateFile);
            printf("Syntax Error\n");
            lengthFile = fopen("length.txt", "w");
            symbolTab = fopen("symtab.txt", "w");
            fclose(symbolTab);
            IntermediateFile = fopen("intermediate.txt", "w");
            fclose(lengthFile);
            fclose(IntermediateFile);
            exit(0);
        }
        fscanf(inputFile, "%s%s", label, opCode);
	
    }
    if (strcmp(opCode, "END") == 0)
    {
        printf("Program length =\t%x\n", locationCounter - startingAddress);
        fprintf(lengthFile, "%x", locationCounter - startingAddress);
    }
    fclose(lengthFile);
     //fclose(symbolTab);
    fclose(inputFile);
    fclose(IntermediateFile);
}