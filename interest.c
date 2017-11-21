#include <stdio.h>
#include <stdlib.h>

int main(int ArgCount, char** Args)
{
    char Buffer[128];

    printf("Enter the base starting amount: ");
    fgets(Buffer, sizeof(Buffer), stdin);
    float Amount = atof(Buffer);

    printf("Enter a periodic deposit amount: ");
    fgets(Buffer, sizeof(Buffer), stdin);
    float Deposit = atof(Buffer);

    int DepositAtStart = 0;
    int Period = 0;
    if (0.0f != Deposit)
    {
        printf("Enter the deposit period (cycles/deposit): ");
        fgets(Buffer, sizeof(Buffer), stdin);
        Period = atoi(Buffer);

        int Error = 1;
        char Ch;
        while (Error)
        {
            printf("Make deposit Before or After compounding? (b/a): ");
            fgets(Buffer, sizeof(Buffer), stdin);
            Ch = Buffer[0];
            if (Ch == 'b' || Ch == 'B')
            {
                DepositAtStart = 1;
                Error = 0;
            }
            else if (Ch == 'a' || Ch == 'A')
            {
                DepositAtStart = 0;
                Error = 0;
            }
            else
            {
                printf("Error: unrecognized entry. Try again.\n");
            }
        }
    }

    printf("Enter the number of cycles: ");
    fgets(Buffer, sizeof(Buffer), stdin);
    int Cycles = atoi(Buffer);

    printf("Enter the interest rate (percentage): ");
    fgets(Buffer, sizeof(Buffer), stdin);
    float Rate = (atof(Buffer) * 0.01f) + 1.0f;

    float TotalInvested = Amount;

    for (int Iteration=0; Iteration<Cycles; Iteration++)
    {
        if (0.0f != Deposit && DepositAtStart)
        {
            if (0 == (Iteration % Period))
            {
                Amount += Deposit;
                TotalInvested += Deposit;
            }
        }

        Amount = Amount*Rate;


        if (0.0f != Deposit && !DepositAtStart)
        {
            if (0 == (Iteration % Period))
            {
                Amount += Deposit;
                TotalInvested += Deposit;
            }
        }
    }

    printf("\nTotal invested: %f\nEnd balance: %f\n", TotalInvested, Amount);

    return 0;
}