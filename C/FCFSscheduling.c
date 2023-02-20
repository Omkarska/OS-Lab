#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct process
{
    int p;
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
} process;

void init(process *pr, int p, int AT, int BT)
{
    pr->p = p;
    pr->AT = AT;
    pr->BT = BT;
    pr->CT = 0;
    pr->TAT = 0;
    pr->WT = 0;
}

void execute(process *pr[], int nop)
{
    if (nop > 0)
    {
        process *tmp;
        for (int i = 0; i < nop - 1; i++)
        {
            for (int j = 0; j < nop - i - 1; j++)
            {
                if (pr[j]->AT > pr[j + 1]->AT)
                {
                    tmp = pr[j];
                    pr[j] = pr[j + 1];
                    pr[j + 1] = pr[j];
                }
            }
        }
        pr[0]->CT += pr[0]->BT;
        for (int i = 1; i < nop; i++)
        {
            pr[i]->CT = pr[i - 1]->CT + pr[i]->BT;
        }
        for (int i = 0; i < nop; i++)
        {
            pr[i]->TAT += pr[i]->CT - pr[i]->AT;
        }
        for (int i = 0; i < nop; i++)
        {
            pr[i]->WT += pr[i]->TAT - pr[i]->BT;
        }
        for (int i = 0; i < nop; i++)
        {
            printf("p%d |", pr[i]->p);
        }
        printf("\n");
        for (int i = 0; i < nop; i++)
        {
            printf("   %d", pr[i]->CT);
        }
        printf("\n");
        printf("Process  AT  BT  CT  TAT  WT");
        printf("\n");
        for (int i = 0; i < nop; i++)
        {
            printf("%d  %d  %d  %d  %d  %d", pr[i]->p, pr[i]->AT, pr[i]->BT, pr[i]->CT, pr[i]->TAT, pr[i]->WT);
            printf("\n");
        }
        }
}

void main()
{
    process *pr[20];
    memset(pr, NULL, sizeof(process));
    int nop, a, b;
    printf("Enter number of processes\n");
    scanf("%d", &nop);
    for (int i = 0; i < nop; i++)
    {
        pr[i] = malloc(sizeof(process));
        printf("Enter arrival time and Burst time for process %d\n", i);
        scanf("%d%d", &a, &b);
        init(pr[i], i, a, b);
    }
    execute(pr, nop);
}