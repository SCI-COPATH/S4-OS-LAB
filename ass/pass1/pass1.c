#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    unsigned int lc, op1, sa, o;
    FILE *inputFile, *opTabFile, *symbolTab, *IntermediateFile, *lengthFile;
    int l, len;
    char m1[20], la[20], op[20], otp[20];
    lengthFile = fopen("length.txt", "w");
    inputFile = fopen("input.txt", "r");
    symbolTab = fopen("symtab.txt", "w");
    IntermediateFile = fopen("intermediate.txt", "w");
    fscanf(inputFile, "%s %s %x", la, m1, &op1);
    if (strcmp(m1, "START") == 0)
    {
        sa = op1;
        lc = sa;
        printf("-\t%s\t%s\t%x\n", la, m1, op1);
        fprintf(IntermediateFile, "\n-\t%s\t%s\t%x\n", la, m1, op1);
    }
    else
        lc = 0;
    fscanf(inputFile, "%s %s", la, m1);
    while (!feof(inputFile))
    {
        fscanf(inputFile, "%s", op);
        printf("\n%x\t%s\t%s\t%s\n", lc, la, m1, op);
        fprintf(IntermediateFile, "\n%x\t%s\t%s\t%s\n", lc, la, m1, op);
        if (strcmp(la, "-") != 0)
        {
            fprintf(symbolTab, "\n%x\t%s\n", lc, la);
        }
        opTabFile = fopen("optab.txt", "r");
        while (!feof(opTabFile))
        {
            fscanf(opTabFile, "%s %x", otp, &o);
            if (strcmp(m1, otp) == 0)
            {
                lc = lc + 3;
                break;
            }
        }
        fclose(opTabFile);
        if (strcmp(m1, "WORD") == 0)

        {
            lc = lc + 3;
        }
        else if (strcmp(m1, "RESW") == 0)
        {
            op1 = atoi(op);
            lc = lc + (3 * op1);
        }
        else if (strcmp(m1, "BYTE") == 0)
        {
            if (op[0] == 'X')
                lc = lc + 1;
            else
            {
                len = strlen(op) - 2;
                lc = lc + len;
            }
        }
        else if (strcmp(m1, "RESB") == 0)
        {
            op1 = atoi(op);
            lc = lc + op1;
        }
        fscanf(inputFile, "%s%s", la, m1);
    }
    if (strcmp(m1, "END") == 0)
    {
        printf("Program length =\n%x", lc - sa);
        fprintf(lengthFile, "%x", lc - sa);
    }
    fclose(lengthFile);
    fclose(inputFile);
    fclose(symbolTab);
    fclose(IntermediateFile);
}
